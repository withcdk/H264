// ExpGolomb.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <assert.h>

typedef unsigned char UINT8;




/*************************************************
Function title: get_bit_at_position
Function Description: 获取比特位置上的值
Calls: // 被本函数调用的函数清单
Called By: // 调用本函数的函数清单
Input para: bytePosition：第几个字节
            bitPosition：第bytePosition字节的第几个bit
Output para: // 对输出参数的说明
Return value: // 函数返回值的说明
Others details: // 其它说明
*************************************************/
static int get_bit_at_position(UINT8 *buf, UINT8 &bytePosition, UINT8 &bitPosition)
{
	UINT8 mask = 0, val = 0;

	mask = 1 << (7 - bitPosition);//模板，当bitPosition=0时，求取左边最高位的值，
	                                   //当bitPosition=7时，求取右边最低位的值
	val = ((buf[bytePosition] & mask) != 0);//判断该bit位上是0还是1
		
	if (++bitPosition > 7)//++bitPosition，跳到下一个bit
	{
		bytePosition++;//下一个字节
		bitPosition = 0;
	}

	return val;
}

static int get_uev_code_num(UINT8 *buf, UINT8 &bytePosition, UINT8 &bitPosition)
{
	assert(bitPosition < 8);
	UINT8 val = 0, prefixZeroCount = 0;
	int prefix = 0, surfix = 0;


	//prefixZeroCount，计算前缀0的个数
	while (true)
	{
		val = get_bit_at_position(buf, bytePosition, bitPosition);
		if (val == 0)
		{
			prefixZeroCount++;
		}
		else
		{
			break;
		}
	}
	prefix = (1 << prefixZeroCount) - 1;
	for (size_t i = 0; i < prefixZeroCount; i++)
	{
		val = get_bit_at_position(buf, bytePosition, bitPosition);
		surfix += val * (1 << (prefixZeroCount - i - 1));
	}

	prefix += surfix;

	return prefix;
}

int main()
{
	UINT8 strArray[6] = { 0xA6, 0x42, 0x98, 0xE2, 0x04, 0x8A };
	UINT8 bytePosition = 0, bitPosition = 0;
	UINT8 dataLengthInBits = sizeof(strArray) * 8;

	int codeNum = 0;
	while ((bytePosition * 8 + bitPosition) < dataLengthInBits)
	{
		codeNum = get_uev_code_num(strArray, bytePosition, bitPosition);
		printf("ExpGolomb codeNum = %d\n", codeNum);
	}
    return 0;
}

