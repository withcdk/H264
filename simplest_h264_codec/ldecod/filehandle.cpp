/************************************************************************/
/*! 
 *  \file 
 *    filehandle.cpp
 *  \brief
 *    Trace file handling and standard error handling function.
 *  \author
 *    De-Kai Chen     <cdk5@foxmail.com>
*/
/************************************************************************/

#include <stdlib.h>
#include <stdio.h>

#include "global.h"


/*************************************************
Function Description: Error handling procedure. Print error message to stderr and exit
                        with supplied code.
Input para: text:Error message
            code:Exit code         
Author£ºDe-Kai Chen
*************************************************/
void error(char *text, int code)
{
	fprintf(stderr, "%s\n", text);
	exit(code);
}


