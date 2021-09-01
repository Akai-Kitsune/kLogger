//----------------------------------------------------------------------------------------------------
/*
Copyright (C) 31.08.2021 Aleksei Likhachev
 
This program is distributed in the hope that it will be useful, 
but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the KI General Public License version for more details.
*/
//----------------------------------------------------------------------------------------------------

#ifndef __LOGGER_H__
#define __LOGGER_H__

//CONFIGUARE
#define __LOGGER_INCLUDE_DEFAULT_LIBRARIES
#define __LOGGER_CPP
//----------------------------------------------------------------------------------------

#ifdef  __LOGGER_INCLUDE_DEFAULT_LIBRARIES
	#include<stdlib.h>
	#include<stdio.h>
	#include<stdint.h>
	#include <string.h>
#endif //__LOGGER_INCLUDE_DEFAULT_LIBRARIES

typedef enum __logger_buf_error {
	_LOGGET_ERROR_OPEN_FILE = -5,
    _LOGGER_ATTEMPT_TO_INIT_ZERO_BYTES = -4,
    _LOGGER_ATTEMPT_TO_ALLOCATE_ZERO_BYTES = -3,
    _LOGGER_ATTEMPT_TO_ACCESS_A_NONEXISTENT_ENTITY = -2,
    _LOGGER_OUT_OF_MEMORY = -1,
}__logger_buf_error;

typedef struct __buffer
{
	char* _mem;
	uint32_t _size_buf;
	uint32_t _size_use_buf;
}__buffer;

static int8_t logger_error_id = 0;

__buffer* buffer_init(uint32_t bits);
FILE* buffer_get_file(const char* str);
void buffer_reset(__buffer* buffer, FILE* file);
void buffer_write(__buffer* buffer, const char* str, FILE* file);
void buffer_set(__buffer* buffer, uint32_t offset);
void buffer_free(__buffer* buffer);

#endif //__LOGGER_H__