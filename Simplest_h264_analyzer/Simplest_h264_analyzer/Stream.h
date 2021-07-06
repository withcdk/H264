#ifndef _STREAM_H_

#define _STREAM_H_

#include <vector>

class CStreamFile
{
public:
	CStreamFile(TCHAR *fileName);//���캯����chendekai
	~CStreamFile();

	//Open API
	int Parse_h264_bitstream();


private:
	FILE      *m_inputFile;
	TCHAR     *m_fileName;

	std::vector<uint8> m_nalVec;//��ͷ�ļ�����ò�Ҫʹ��using namespace std;

	void file_info();
	void file_error(int idx);

	int find_nal_prefix();

	void ebsp_to_sodb();//sodb -> rbsp -> ebsp
};


#endif // !_STREAM_H_

