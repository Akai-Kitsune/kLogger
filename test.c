


#include "logger.h"

void test1()
{
	__buffer* buffer = buffer_init(512);
	FILE* file = buffer_get_file("logTest.txt");
	buffer_write(buffer, "HELLO WORLD", file);
	buffer_write(buffer, "\n1.1", file);
	buffer_write(buffer, "\n!@#$%^&*()_+", file);
	buffer_reset(buffer, file);
	fclose(file);
	buffer_free(buffer);
}

int main(void){
	test1();
	return 0;
}