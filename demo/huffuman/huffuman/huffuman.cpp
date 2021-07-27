// huffuman.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <iostream>
#include <fstream>

#include <queue>//ʹ��C++��STL�ṩ��ģ��⡪�����ȼ����У�ʵ�ֶ�����
#include <vector>
#include <string>

using namespace std;


//ÿһ�����Ŷ���Ϊһ���ṹ�壬�����ַ��ͳ���Ƶ��
typedef struct
{
	unsigned char character;
	unsigned int frequency;
}CharNode;

static bool open_input_file(ifstream &input, const char *inputFileName)
{
	input.open(inputFileName);
	if (!input.is_open())
	{
		return false;
	}
	return true;
}

struct MinHeapNode
{
	char data;
	unsigned int freq;
	MinHeapNode *left, *right;
	MinHeapNode(char data, unsigned freq)//���캯������������Ĺ��캯������ʵ��ͽṹ���ǲ���
	{
		left = right = NULL;
		this->data = data;
		this->freq = freq;
	}
};

typedef struct MinHeapNode MinHeapNode;

struct compare
{
	bool operator()(MinHeapNode* l, MinHeapNode *r)//���أ��������
	{
		return (l->freq > r->freq);
	}
};

static void get_huffman_code(MinHeapNode *root, string code)//����hafuman�����Ӹ��ڵ㿪ʼ����rootΪhaffuman���ĸ��ڵ㣬codeΪ��ֵ�������
{
	if (!root)
	{
		return;
	}

	if (root->data != -1)//�ϲ����ɵ��½ڵ��dataֵ�������ó���-1�����������-1��˵���Ѿ�����haffuman�����ն˽ڵ�
	{
		cout << root->data << " : " << code << endl;;
	}

	get_huffman_code(root->left, code + "0");
	get_huffman_code(root->right, code + "1");
}


int main()
{

	ifstream inputFile;
	if (!open_input_file(inputFile, "input.txt"))
	{
		cout << "Error: opening input file failed!" << endl;
		return -1;
	}
	char buf = inputFile.get();
	CharNode nodeArr[256] = { {0,0} };

	while (inputFile.good())//�������״̬�Ƿ�����
	{
		cout << buf;
		nodeArr[buf].character = buf;
		nodeArr[buf].frequency++;
		buf = inputFile.get();
	}
	cout << endl;
	priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare>  minHeap;//STL�����ȼ�����
	for (int idx = 0; idx < 256; idx++)
	{
		if (nodeArr[idx].frequency > 0)
		{
			cout << "Node " << idx << ": [" << nodeArr[idx].character << ", " << nodeArr[idx].frequency << "]" << endl;
			minHeap.push(new MinHeapNode(nodeArr[idx].character, nodeArr[idx].frequency));//װ�����ȼ������У����ź���
		}
	}

	MinHeapNode *leftNode = NULL, *rightNode = NULL, *topNode = NULL;
	while (minHeap.size() != 1)//���ȼ�������ֻʣ�����һ���ڵ㣬Ҳ���Ǹ��ڵ�ʱ������ѭ��
	{
		leftNode = minHeap.top();//���ȼ�������Ȩֵ��С���Ǹ�Ԫ��
		minHeap.pop();//�����Ԫ���޳�

		rightNode = minHeap.top(); //���ȼ���������һ��Ȩֵ��С���Ǹ�Ԫ��
		minHeap.pop();//�ٰ����Ԫ���޳�

		topNode = new MinHeapNode(-1, leftNode->freq + rightNode->freq);//�ϲ��ڵ��data��ֵΪ-1��û�����壬Ҷ�ӽڵ�ϲ���һ���ڵ�
		topNode->left = leftNode;
		topNode->right = rightNode;
		minHeap.push(topNode);//��minHeap��װ��һ���ڵ㣬pop�������ڵ㣬push��һ���ڵ㣬����ÿ��ѭ������ɾ��һ��������֪��minHeapֻʣ�����һ�����ڵ�
	}
	get_huffman_code(topNode, "");

	inputFile.close();
    return 0;
}

