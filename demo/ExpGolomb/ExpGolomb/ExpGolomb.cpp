// ExpGolomb.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <assert.h>

typedef unsigned char UINT8;




/*************************************************
Function title: get_bit_at_position
Function Description: ��ȡ����λ���ϵ�ֵ
Calls: // �����������õĺ����嵥
Called By: // ���ñ������ĺ����嵥
Input para: bytePosition���ڼ����ֽ�
            bitPosition����bytePosition�ֽڵĵڼ���bit
Output para: // �����������˵��
Return value: // ��������ֵ��˵��
Others details: // ����˵��
*************************************************/
static int get_bit_at_position(UINT8 *buf, UINT8 &bytePosition, UINT8 &bitPosition)
{
	UINT8 mask = 0, val = 0;

	mask = 1 << (7 - bitPosition);//ģ�壬��bitPosition=0ʱ����ȡ������λ��ֵ��
	                                   //��bitPosition=7ʱ����ȡ�ұ����λ��ֵ
	val = ((buf[bytePosition] & mask) != 0);//�жϸ�bitλ����0����1
		
	if (++bitPosition > 7)//++bitPosition��������һ��bit
	{
		bytePosition++;//��һ���ֽ�
		bitPosition = 0;
	}

	return val;
}

static int get_uev_code_num(UINT8 *buf, UINT8 &bytePosition, UINT8 &bitPosition)
{
	assert(bitPosition < 8);
	UINT8 val = 0, prefixZeroCount = 0;
	int prefix = 0, surfix = 0;


	//prefixZeroCount������ǰ׺0�ĸ���
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

