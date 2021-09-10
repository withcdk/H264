#include "stdafx.h"
#include "Stream.h"
#include "NALUnit.h"

#include <iostream>

using namespace std;

//���캯��
CStreamFile::CStreamFile(TCHAR *fileName)
{
	m_fileName = fileName;
	file_info();
	_tfopen_s(&m_inputFile, m_fileName, _T("rb"));
	if (NULL == m_inputFile)
	{
		file_error(0);
	}

#if TRACE_CONFIG_LOGOUT
	g_traceFile.open("trace.txt");
	if (!g_traceFile.is_open())
	{
		file_error(1);
	}
#endif


}

//��������
CStreamFile::~CStreamFile()
{
	if (NULL != m_inputFile)
	{
		fclose(m_inputFile);//�ر���
		m_inputFile = NULL;//����ϰ�ߣ��ļ�ָ��Ҫ��NULL
	}

#if TRACE_CONFIG_LOGOUT
	if (g_traceFile.is_open())
	{
		g_traceFile.close();
	}
#endif


}




void CStreamFile::file_info()
{
	if (m_fileName)
	{
		wcout << L"file name:" << m_fileName << endl;
	}

}

void CStreamFile::file_error(int idx)
{
	switch (idx)
	{
	case 0:
		wcout << L"error: opening input file failed." << endl;
		break;
	case 1:
		wcout << L"error: opening trace file failed." << endl;
		break;
	default:
		break;
	}
}

int CStreamFile::Parse_h264_bitstream()
{
	int ret = 0;
	do
	{
		ret = find_nal_prefix();
		//����NAL UNIT
		if (m_nalVec.size())
		{
			UINT8 nalType = m_nalVec[0] & 0x1F;//��ȡ��5λ����ΪNAL ͷ��Ϣ���������̶��ֶΣ�ռ8bit�������5bitΪNAL��Ԫ����
			dump_NAL_type(nalType);
			ebsp_to_sodb();//ȥ����ֹ����У���ֽ�0x03
			CNALUnit nalUnit(&m_nalVec[1], m_nalVec.size() - 1);//��ռ1���ֽڵ�NAL headerȥ��
		}
	} while (ret);
	return 0;
}

int CStreamFile::find_nal_prefix()
{
	/*
	00 00 00 01 x x x x x x 00 00 00 01
	*/
	UINT8 prefix[3] = { 0 };
	UINT8 fileByte;
	/*
	[0][1][2] = {0 0 0}  ->  ��һ���ֽڷ���[0]��λ�� [1][2][0] = {0 0 0}   ->    ��һ���ֽڷ���[1]��λ�� [2][0][1] = {0 0 0}
	���ǰ��3���ֽھ�Ϊ0����ô�ٶ�һ���ֽڣ�getc() = 1�Ļ��������ж� ->  0 0 0 1
	[0][1][2] = {0 0 1}  ->  ��һ���ֽڷ���[0]��λ�� [1][2][0] = {0 0 1}   ->    ��һ���ֽڷ���[1]��λ�� [2][0][1] = {0 0 1}
	*/

	m_nalVec.clear();

	int pos = 0, getPrefix = 0;//�����������ļ����ĸ�λ��

							   /*��prefix[3]������г�ʼ��*/
	for (int idx = 0; idx < 3; idx++)
	{
		prefix[idx] = getc(m_inputFile);
		m_nalVec.push_back(prefix[idx]);
	}


	while (!feof(m_inputFile))
	{
		if ((prefix[pos % 3] == 0) && (prefix[(pos + 1) % 3] == 0) && (prefix[(pos + 2) % 3] == 1))
		{
			//0x 00 00 01 found, start_code_prefix_one_3bytes(0x00 00 01)
			getPrefix = 1;
			m_nalVec.pop_back();
			m_nalVec.pop_back();
			m_nalVec.pop_back();
			break;
		}
		else if ((prefix[pos % 3] == 0) && (prefix[(pos + 1) % 3] == 0) && (prefix[(pos + 2) % 3] == 0))
		{
			if (1 == getc(m_inputFile))
			{
				//0x 00 00 00 01 found, zero_byte(0x00) + start_code_prefix_one_3bytes(0x00 00 01)
				getPrefix = 2;
				m_nalVec.pop_back();
				m_nalVec.pop_back();
				m_nalVec.pop_back();
				break;
			}
		}
		else
		{// current position is not the start code
			fileByte = getc(m_inputFile);
			prefix[(pos++) % 3] = fileByte;
			m_nalVec.push_back(fileByte);
		}
	}

	return getPrefix;
}

void CStreamFile::ebsp_to_sodb()
{
	//00 00 03
	if (m_nalVec.size() < 3)
	{
		return;
	}

	for (vector<UINT8>::iterator itor = m_nalVec.begin() + 2; itor != m_nalVec.end(); )
	{
		if ((3 == *itor) && (0 == *(itor - 1)) && (0 == *(itor - 2)))
		{
			vector<UINT8>::iterator temp = m_nalVec.erase(itor);//erase()����ֵָ����ɾ��Ԫ�ص���һ��λ��
			itor = temp;
		}
		else
		{
			itor++;
		}
	}
}

void CStreamFile::dump_NAL_type(UINT8 nalType)
{
#if TRACE_CONFIG_CONSOLE
	wcout << L"NAL Unit Type: " << nalType << endl;

#endif

#if TRACE_CONFIG_LOGOUT
	g_traceFile << "NAL Unit Type: " << to_string(nalType) << endl;
#endif
}

