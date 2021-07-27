// huffuman.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include <fstream>

#include <queue>//使用C++里STL提供的模板库——优先级队列，实现二叉树
#include <vector>
#include <string>

using namespace std;


//每一个符号定义为一个结构体，包括字符和出现频次
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
	MinHeapNode(char data, unsigned freq)//构造函数，类似于类的构造函数，其实类和结构体是差不多的
	{
		left = right = NULL;
		this->data = data;
		this->freq = freq;
	}
};

typedef struct MinHeapNode MinHeapNode;

struct compare
{
	bool operator()(MinHeapNode* l, MinHeapNode *r)//重载（）运算符
	{
		return (l->freq > r->freq);
	}
};

static void get_huffman_code(MinHeapNode *root, string code)//遍历hafuman树（从根节点开始），root为haffuman树的根节点，code为二值化码输出
{
	if (!root)
	{
		return;
	}

	if (root->data != -1)//合并而成的新节点的data值都被设置成了-1，如果不等于-1，说明已经到了haffuman树的终端节点
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

	while (inputFile.good())//检测流的状态是否正常
	{
		cout << buf;
		nodeArr[buf].character = buf;
		nodeArr[buf].frequency++;
		buf = inputFile.get();
	}
	cout << endl;
	priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare>  minHeap;//STL，优先级队列
	for (int idx = 0; idx < 256; idx++)
	{
		if (nodeArr[idx].frequency > 0)
		{
			cout << "Node " << idx << ": [" << nodeArr[idx].character << ", " << nodeArr[idx].frequency << "]" << endl;
			minHeap.push(new MinHeapNode(nodeArr[idx].character, nodeArr[idx].frequency));//装入优先级队列中，并排好序
		}
	}

	MinHeapNode *leftNode = NULL, *rightNode = NULL, *topNode = NULL;
	while (minHeap.size() != 1)//优先级队列中只剩下最后一个节点，也就是根节点时，结束循环
	{
		leftNode = minHeap.top();//优先级队列中权值最小的那个元素
		minHeap.pop();//把这个元素剔除

		rightNode = minHeap.top(); //优先级队列中下一个权值最小的那个元素
		minHeap.pop();//再把这个元素剔除

		topNode = new MinHeapNode(-1, leftNode->freq + rightNode->freq);//合并节点的data赋值为-1，没有意义，叶子节点合并成一个节点
		topNode->left = leftNode;
		topNode->right = rightNode;
		minHeap.push(topNode);//在minHeap中装入一个节点，pop出两个节点，push入一个节点，这样每次循环都会删掉一个，最终知道minHeap只剩下最后一个根节点
	}
	get_huffman_code(topNode, "");

	inputFile.close();
    return 0;
}

