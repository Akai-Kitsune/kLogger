//----------------------------------------------------------------------------------------------------
/*
Copyright (C) 31.08.2021 Aleksei Likhachev
 
This program is distributed in the hope that it will be useful, 
but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the KI General Public License version for more details.
*/
//----------------------------------------------------------------------------------------------------

#include "logger.h"

__buffer* buffer_init(uint32_t bits)
{
	static __buffer* buffer;
	buffer = (__buffer*)malloc(sizeof(__buffer));
	if(buffer == NULL){
		logger_error_id = _LOGGER_OUT_OF_MEMORY;
		return NULL;
	}
	else{
		buffer->_mem = (char*)malloc(bits);
		if(buffer->_mem == NULL){
			logger_error_id = _LOGGER_OUT_OF_MEMORY;
			return NULL;
		}
		else{
			buffer->_size_use_buf = 0;
			buffer->_size_buf = bits;
			return buffer;
		}
	}
}

FILE* buffer_get_file(const char* str)
{
	FILE* file = fopen(str, "w");
	if(file == NULL){
		file = fopen(str, "a");
		if(file == NULL){
			logger_error_id = _LOGGET_ERROR_OPEN_FILE;	
			return NULL;
		}
		else{
			return file;
		}
	}
	else{
		return file;
	}
}

void buffer_reset(__buffer* buffer, FILE* file)
{
	if(buffer == NULL || file == NULL){
		logger_error_id = _LOGGER_ATTEMPT_TO_ACCESS_A_NONEXISTENT_ENTITY;
	}
	else{
		fprintf(file, "%s", buffer->_mem);
		//buffer->_size_use_buf = 0;
		buffer_set(buffer, 0);
	}
}

void buffer_write(__buffer* buffer, const char* str, FILE* file)
{
	if(buffer == NULL){
		logger_error_id = _LOGGER_ATTEMPT_TO_ACCESS_A_NONEXISTENT_ENTITY;
	}
	else {
		if(strlen(str) + buffer->_size_use_buf <= buffer->_size_buf){
			memcpy(buffer->_mem + buffer->_size_use_buf, str, strlen(str) + 1);
			buffer->_size_use_buf += strlen(str);
		}
		else{
		uint32_t left = buffer->_size_buf - buffer->_size_use_buf;
        memcpy(buffer->_mem + buffer->_size_use_buf, str, left);
        buffer->_size_use_buf += left;
        buffer_reset(buffer, file);
        uint32_t right = strlen(str) - left;
        memcpy(buffer->_mem + buffer->_size_use_buf, str + left, right);
        buffer->_size_use_buf += right;
		}
	
		if (buffer->_size_use_buf >= buffer->_size_buf*0.950) {
        	buffer_reset(buffer, file);
  		}
  	}  
}

void buffer_set(__buffer* buffer, uint32_t offset)
{
	if(	buffer == NULL){
		logger_error_id = _LOGGER_ATTEMPT_TO_ACCESS_A_NONEXISTENT_ENTITY;
	}
	else{
		buffer->_size_use_buf = offset;
	}
}

void buffer_free(__buffer* buffer)
{
	if(buffer == NULL){
		logger_error_id = _LOGGER_ATTEMPT_TO_ACCESS_A_NONEXISTENT_ENTITY;
	}
	else{
		if(buffer->_mem == NULL){
			free(buffer);
		}
		else{
			free(buffer->_mem);
			free(buffer);
		}
	}
}