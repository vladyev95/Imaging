#ifndef ERROR_H
#define ERROR_H

#include <stdlib.h>
#include <stdio.h>

#define ERROR(str) do { \
			perror(str); \
			fprintf(stderr, "line %d file %s\n", __LINE__, \
					__FILE__); \
			fpritnf(stderr, "terminating\n"); \
			exit(EXIT_FAILURE); \
		} while(0)


#endif
