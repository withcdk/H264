/************************************************************************/
/*! 
 *  \file 
 *    global.h
 *  \brief
 *    global definitions for H.264 decoder.
 *  \author
 *    De-Kai Chen     <cdk5@foxmail.com>
*/
/************************************************************************/

#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <stdio.h>


#ifdef WIN32
#define snprintf _snprintf
#endif



#define ET_SIZE 300     //size of error text buffer
extern char errortext[ET_SIZE];//buffer for error message for exit with error()

void error(char *text, int code);

struct inp_par
{
	char infile[100];//H.264 inputfile

};


//定义结构体类型
struct snr_par
{
	float snr_y;
	float snr_u;
	float snr_v;
};

extern struct snr_par *snr;//extern将全局变量snr的作用域扩展到本文件


typedef struct img_par
{
	int number;//frame number
} ImageParameters;



#endif




