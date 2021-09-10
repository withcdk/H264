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



struct inp_par *input;//input parameters from input configuration file
struct snr_par *snr;//statistics.     这里是定义一个指向结构体变量的指针变量
struct img_par *img;//image parameters

/*************************************************
Description: main function for decoder
Input para: // 输入参数说明，包括每个参数的作
          //用、取值说明及参数间关系
Author：De-Kai Chen
*************************************************/
int main(int argc, char **argv)
{
	if ((input = (struct inp_par *)calloc(1, sizeof(struct inp_par))) == NULL) no_mem_exit("main: input");
	if ((snr = (struct snr_par *)calloc(1, sizeof(struct snr_par))) == NULL) no_mem_exit("main: snr");
	if ((img = (struct img_par *)calloc(1, sizeof(struct img_par))) == NULL) no_mem_exit("main: img");




	//open_bitstream_file();



	/*
	while (decode_one_frame())
	{
	}
	
	*/


	printf("test_cdk OK!\n");
	return 0;
}




