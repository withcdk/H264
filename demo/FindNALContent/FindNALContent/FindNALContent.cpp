// FindNALContent.cpp : �������̨Ӧ�ó������ڵ㡣
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
	[0][1][2] = {0 0 0}  ->  ��һ���ֽڷ���[0]��λ�� [1][2][0] = {0 0 0}   ->    ��һ���ֽڷ���[1]��λ�� [2][0][1] = {0 0 0}
	���ǰ��3���ֽھ�Ϊ0����ô�ٶ�һ���ֽڣ�getc() = 1�Ļ��������ж� ->  0 0 0 1
	[0][1][2] = {0 0 1}  ->  ��һ���ֽڷ���[0]��λ�� [1][2][0] = {0 0 1}   ->    ��һ���ֽڷ���[1]��λ�� [2][0][1] = {0 0 1}
	*/

	nalBytes.clear();

	int pos = 0, getPrefix = 0;//�����������ļ����ĸ�λ��

	/*��prefix[3]������г�ʼ��*/
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
		{//��ǰ��������ʼ���λ��
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
	find_nal_prefix(&pFile_in, nalBytes);//����ʼ�룬������ʼ���޳�nalBytes����

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

