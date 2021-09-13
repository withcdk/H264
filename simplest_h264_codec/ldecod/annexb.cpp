/**  
 ******************************************************************************
 *brief: Annex B Byte stream format 
 *author: De-Kai Chen  cdk5@foxmail.com
 ******************************************************************************
 */
#include <stdlib.h>


#include "annexb.h"
#include "global.h"


FILE *bits = NULL;// the bit stream file



void open_bitstream_file(char *fn)
{
	if (NULL == (bits = fopen(fn, "rb")))
	{
		snprintf(errortext, ET_SIZE, "Cannot open Annex B ByteStream file %s", input->infile);
		error(errortext, 500);
	}
}




