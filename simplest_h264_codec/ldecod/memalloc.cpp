/************************************************************************/
/*! 
 *  \file 
 *    memalloc.cpp
 *  \brief
 *    Memory allocation and free helper funtions.
 *  \author
 *    De-Kai Chen     <cdk5@foxmail.com>
*/
/************************************************************************/


#include "memalloc.h"


char errortext[ET_SIZE];//buffer for error message for exit with error()

void no_mem_exit(char *where)
{
	snprintf(errortext, ET_SIZE, "Could not allocate memory: %s", where);
	error(errortext, 100);
}





