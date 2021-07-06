// FindNALContent.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

typedef unsigned char uint8;
using namespace std;

static int find_nal_prefix(FILE **pFileIn, vector<uint8> &nalBytes) 
{
	FILE *pFile = *pFileIn;
	/*
	00 00 00 01 x x x x x x 00 00 00 01
	*/
	uint8 prefix[3] = { 0 };
	uint8 fileByte;
	/*
	[0][1][2] = {0 0 0}  ->  下一个字节放在[0]的位置 [1][2][0] = {0 0 0}   ->    下一个字节放在[1]的位置 [2][0][1] = {0 0 0}
	如果前面3个字节均为0，那么再读一个字节，getc() = 1的话，可以判断 ->  0 0 0 1
	[0][1][2] = {0 0 1}  ->  下一个字节放在[0]的位置 [1][2][0] = {0 0 1}   ->    下一个字节放在[1]的位置 [2][0][1] = {0 0 1}
	*/

	nalBytes.clear();

	int pos = 0, getPrefix = 0;//读到二进制文件的哪个位置

	/*对prefix[3]数组进行初始化*/
	for (int idx = 0; idx < 3; idx++)
	{
		prefix[idx] = getc(pFile);
		nalBytes.push_back(prefix[idx]);
	}


	while (!feof(pFile))
	{
		if ((prefix[pos % 3] == 0) && (prefix[(pos + 1) % 3] == 0) && (prefix[(pos + 2) % 3] == 1))
		{
			//0x 00 00 01 found
			getPrefix = 1;
			nalBytes.pop_back();
			nalBytes.pop_back();
			nalBytes.pop_back();
			break;
		}
		else if ((prefix[pos % 3] == 0) && (prefix[(pos + 1) % 3] == 0) && (prefix[(pos + 2) % 3] == 0))
		{
			if (1 == getc(pFile))
			{
				//0x 00 00 00 01 found
				getPrefix = 2;
				nalBytes.pop_back();
				nalBytes.pop_back();
				nalBytes.pop_back();
				break;
			}
		}
		else
		{//当前并不是起始码的位置
			fileByte = getc(pFile);
			prefix[(pos++) % 3] = fileByte;
			nalBytes.push_back(fileByte);
		}
	}

	return getPrefix;
}


int _tmain(int argc, _TCHAR* argv[])
{
	FILE *pFile_in = NULL;
	_tfopen_s(&pFile_in, argv[1], _T("rb"));
	if (!pFile_in)
	{
		printf("Error: Opening input file failed.\n");
	}

	vector<uint8> nalBytes;
	find_nal_prefix(&pFile_in, nalBytes);//找起始码，并把起始码剔除nalBytes容器

	find_nal_prefix(&pFile_in, nalBytes);
	for (int idx = 0; idx < nalBytes.size(); idx++)
	{
		printf("%x ", nalBytes.at(idx));
	}
	printf("\n");

	find_nal_prefix(&pFile_in, nalBytes);
	for (int idx = 0; idx < nalBytes.size(); idx++)
	{
		printf("%x ", nalBytes.at(idx));
	}
	printf("\n");

	find_nal_prefix(&pFile_in, nalBytes);
	for (int idx = 0; idx < nalBytes.size(); idx++)
	{
		printf("%x ", nalBytes.at(idx));
	}
	printf("\n");

	fclose(pFile_in);
    return 0; 
}

