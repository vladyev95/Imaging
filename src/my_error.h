#ifndef MY_ERROR_H
#define MY_ERROR_H

#include <stdlib.h>
#include <error.h>
#include <errno.h>


#define ERROR(s, e) error_at_line(EXIT_FAILURE, e, __FILE__, __LINE__, s)



#endif
