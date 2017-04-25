#ifndef MY_ERROR_H
#define MY_ERROR_H

#include <stdlib.h>
#include <error.h>
#include <errno.h>


#define SYSCALL_ERROR(s) error_at_line(EXIT_FAILURE, errno, __FILE__, \
				__LINE__, s)

#define ERROR(s) error_at_line(EXIT_FAILURE, 0, __FILE__, __LINE__, \
				s)


#endif
