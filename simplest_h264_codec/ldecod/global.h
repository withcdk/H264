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
extern struct InputParam *input;

void error(char *text, int code);
void init_cfg(struct InputParam *input, char *cfgFileName);




struct InputParam
{
	char infile[100];//H.264 inputfile
	char chOutFile[100];// Decoded YUV 4:2:0 output
	char chRefFile[100];// Optional YUV 4:2:0 reference file for SNR measurement
	int iDpbSize;// frame buffer size
	int iFileFormat;// File format of the input file, PAR_OF_ANNEXB or PAR_OF_RTP
	int iRefOffset;
	int iPocScale;
};


//define structure type
struct SnrParam
{
	float snr_y;
	float snr_u;
	float snr_v;
};

extern struct SnrParam *snr;//extern extends the scope of the global variable SNR to this file


typedef struct ImgParam
{
	int number;//frame number
} ImgParam_t;


// output file types
typedef enum
{
	PAR_OF_ANNEXB, // current TML description
	PAR_OF_RTP, // RTP packet output format
} PAR_OF_TYPE;


extern FILE *pOut;// pointer to output YUV file
extern FILE *pRef;// pointer to input original reference YUV file

#endif




