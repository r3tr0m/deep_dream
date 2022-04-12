#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <time.h>

char* build_dream(){

	uint64_t epoch_time 	= time(NULL);
	uint16_t memory_space 	= 500;

	char *dream = (char*)malloc(memory_space);

	if(dream == NULL){
		return NULL;
	}

	char memory_1[memory_space];
	char memory_2[memory_space];
	char memory_3[memory_space];
	char memory_4[memory_space];

	char t_byte;

	for(uint16_t byte=0; byte < memory_space; byte++){

		t_byte = (memory_1[byte] * byte) ^ (memory_2[byte] * byte) ^ (memory_3[byte] * byte) ^ (memory_4[byte] * byte);

		switch(t_byte){

			case 0:
				t_byte = (byte-1 ^ byte-2 ^ byte-3 ^ byte-4);
				break;
			default:
				break;
		}

		dream[byte] = t_byte;
	}

	return dream;

}

int64_t random_number(char *table,size_t size_type){

	char* local_dream = build_dream();

	uint64_t epoch_time 	= time(NULL);
	uint64_t r_number	= ( (uint64_t) local_dream + (uint64_t) epoch_time ) % 500;

	for(uint16_t byte=0; byte < 500; byte++)
	{

		r_number += (r_number | table[byte]) | (uint64_t) &local_dream[byte];

	}

	switch(size_type){

		case 1:
			r_number = r_number % CHAR_MAX;
			break;
		case 2:
			r_number = r_number % SHRT_MAX;
			break;
		case 4:
			r_number = r_number % UINT32_MAX;
			break;
		case 8:
			r_number = r_number % UINT64_MAX;
			break;
		default:
			break;
	}

	return r_number;
}

