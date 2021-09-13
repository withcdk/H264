/************************************************************************/
/*!
 *  \main page(two spaces in front)
 *    This is the simplest H.264/AVC decoder reference software. For detailed
 *    documentation see the comments in each file.(four spaces in front)
 * 
 *  \author
 *    De-Kai Chen
 *
 *  \version
 *    JM 8.6
 */
/*!
 *  \file 
 *    ldecod.cpp
 *  \brief
 *    H.264/AVC reference decoder project main()
 *  \author
 *    De-Kai Chen      <cdk5@foxmail.com>
*/

/************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "memalloc.h"
#include "global.h"
#include "annexb.h"



struct InputParam *input;//input parameters from input configuration file
struct SnrParam *snr;//statistics.     here we define a pointer variable to a structure variable
struct ImgParam *img;//image parameters

FILE *pOut;// pointer to output YUV file
FILE *pRef;// pointer to input original reference YUV file

/*************************************************
Description: main function for decoder
Input para:           
Author£ºDe-Kai Chen   <cdk5@foxmail.com>
*************************************************/
int main(int argc, char **argv)
{
	if ((input = (struct InputParam *)calloc(1, sizeof(struct InputParam))) == NULL) no_mem_exit("main: input");
	if ((snr = (struct SnrParam *)calloc(1, sizeof(struct SnrParam))) == NULL) no_mem_exit("main: snr");
	if ((img = (struct ImgParam *)calloc(1, sizeof(struct ImgParam))) == NULL) no_mem_exit("main: img");

	if (argc != 2)
	{
		snprintf(errortext, ET_SIZE, "Usage: %s <config.dat> \n\t<config.dat> defines decoder parameters", argv[0]);
		error(errortext, 300);
	}

	init_cfg(input, argv[1]);

	switch (input->iFileFormat)
	{
	case 0:
		open_bitstream_file(input->infile);
		break;
	default:
		printf("Unsupported file format %d, exit\n", input->iFileFormat);
	}





	/*
	while (decode_one_frame())
	{
	}
	
	*/


	printf("test_cdk OK!\n");
	return 0;
}





/*************************************************
Description: read input from configuration file
Input para: 
Return value:
Author£ºDe-Kai Chen    <cdk5@foxmail.com>
*************************************************/
void init_cfg(struct InputParam *input, char *cfgFileName)
{
	FILE *fd;
	int nalMode;

	if ((fd = fopen(cfgFileName, "r")) == NULL)
	{
		snprintf(errortext, ET_SIZE, "Error: Configuration file %s not found\n", cfgFileName);
		error(errortext, 300);
	}

	fscanf(fd, "%s", input->infile);// H.264 compressed input bitstream
	fscanf(fd, "%*[^\n]");

	fscanf(fd, "%s", input->chOutFile);// YUV 4:2:0 input format
	fscanf(fd, "%*[^\n]");

	fscanf(fd, "%s", input->chRefFile);// reference file
	fscanf(fd, "%*[^\n]");

	fscanf(fd, "%d", &input->iDpbSize);// may be overwritten in case of RTP NAL
	fscanf(fd, "%*[^\n]");
	if (input->iDpbSize < 1)
	{
		snprintf(errortext, ET_SIZE, "Decoded Picture Buffer is %d. It has to be at least 1", input->iDpbSize);
		error(errortext, 1);
	}

	fscanf(fd, "%d", &nalMode);// NAL mode
	fscanf(fd, "%*[^\n]");

	switch (nalMode)
	{
	case 0:
		input->iFileFormat = PAR_OF_ANNEXB;
		break;
	case 1:
		input->iFileFormat = PAR_OF_RTP;
		break;
	default:
		snprintf(errortext, ET_SIZE, "NAL mode %i is not supported", nalMode);
		error(errortext, 400);
	}

	fscanf(fd, "%d", &input->iRefOffset);// offset used for SNR computation
	fscanf(fd, "%*[^\n]");

	fscanf(fd, "%d", &input->iPocScale);// offset used for SNR computation
	fscanf(fd, "%*[^\n]");

	if (input->iPocScale < 1 || input->iPocScale > 2)
	{
		snprintf(errortext, ET_SIZE, "Poc Scale is %d. It has to be 1 or 2", input->iPocScale);
		error(errortext, 1);
	}

	fclose(fd);

	if ((pOut = fopen(input->chOutFile, "wb")) == NULL)
	{
		snprintf(errortext, ET_SIZE, "Error open file %s", input->chOutFile);
		error(errortext, 500);
	}

	fprintf(stdout, "--------------------------------------------------------------------------\n");
	fprintf(stdout, " Decoder config file                    : %s \n", cfgFileName);
	fprintf(stdout, "--------------------------------------------------------------------------\n");
	fprintf(stdout, " Input H.264 bitstream                  : %s \n", input->infile);
	fprintf(stdout, " Output decoded YUV 4:2:0               : %s \n", input->chOutFile);
	if ((pRef = fopen(input->chRefFile, "rb")) == NULL)
	{
		fprintf(stdout, " Input reference file                   : %s does not exist \n", input->chRefFile);
		fprintf(stdout, "                                          SNR values are not available\n");
	}
	else
		fprintf(stdout, " Input reference file                   : %s \n", input->chRefFile);

	fprintf(stdout, "--------------------------------------------------------------------------\n");
	fprintf(stdout, "POC must = frame# or field# for SNRs to be correct\n");
	fprintf(stdout, "Frame    POC   QP  SnrY    SnrU    SnrV   Time(ms)\n");

}

