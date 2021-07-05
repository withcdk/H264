#include "stdafx.h"
#include "Stream.h"

#include <iostream>

using namespace std;

//构造函数
CStreamFile::CStreamFile(TCHAR *fileName)
{
	m_fileName = fileName;
	file_info();
	_tfopen_s(&m_inputFile, m_fileName, _T("rb"));
	if (NULL == m_inputFile)
	{
		file_error(0);
	}
}

//析构函数
CStreamFile::~CStreamFile()
{
	if (NULL != m_inputFile)
	{
		fclose(m_inputFile);
		m_inputFile = NULL;
	}
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
	default:
		break;
	}
}

