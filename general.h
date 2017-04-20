#ifndef GENERAL_H
#define GENERAL_H


#define MIN(a, b) ((a) < (b) ? (a) : (b))

#define ERROR(str) do { \
			perror(str); \
			fprintf(stderr, "line %d file %s\n", __LINE__, \
					__FILE__); \
			fprintf(stderr, "terminating\n"); \
			exit(EXIT_FAILURE); \
		} while(0)


#endif
