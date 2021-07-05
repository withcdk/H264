#ifndef _STREAM_H_

#define _STREAM_H_

#include <vector>

class CStreamFile
{
public:
	CStreamFile(TCHAR *fileName);//¹¹Ôìº¯Êý£¬chendekai
	~CStreamFile();



private:
	FILE      *m_inputFile;
	TCHAR     *m_fileName;

	std::vector<uint8> m_nalVec;

	void file_info();
	void file_error(int idx);


};


#endif // !_STREAM_H_

