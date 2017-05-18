#define _CRT_SECURE_NO_WARNINGS 1

#include"HuffmanTree.h"
 
typedef size_t LongType;
struct CharInfo               //這里可以形象的叫這结构体为字母包
{
	char _ch;
	LongType _Count;
	string  _HUffmanCode;
	//這里不写构造，因为赫夫曼编码刚开始的时候不适合生成  调用默认的构造函数

	bool operator !=(const CharInfo& ch)
	{  
		return this->_Count != ch._Count;
	}

	bool operator < (const CharInfo& ch)
	{
		return this->_Count < ch._Count;
	}

	CharInfo operator+(const CharInfo& ch)
	{
		CharInfo tmpInfo;
		tmpInfo._Count = this->_Count + ch._Count;
		return tmpInfo;
	}
	
};
class FileCompass
{
public:
	typedef HuffmanTreeNode<CharInfo> CharNode;
private:
	CharInfo Info[256];
public:
	FileCompass() //构造这256个字母的结构体   初始化
	{
		for (size_t i = 0; i < 256; i++)
		{
			Info[i]._ch = i;
			Info[i]._Count = 0;
		}
	}
	void Compass(const char* filename)//   压缩文件
	{
		assert(filename);
		FILE* fout = fopen(filename, "r");        //這里的 "r"是什么意思？
		assert(fout);

		//统计字符出现的次数
		char ch = fgetc(fout);                 //fgec的用法
		while (ch!=EOF)                      //EOF：文件结束标志？？
		{
			Info[ch]._Count++;
			ch = fgetc(fout);
		}


		                                                   //搭建出现字母的赫夫曼树，将文件中出现的字母进行建堆，没有出现就不需要建堆了 所以需要用的invalid
		CharInfo _invalidInfoNode;
		_invalidInfoNode._Count = 0;                          //出现次数为0的字母包
		HuffmanTree<CharInfo> _h(Info, 256,_invalidInfoNode);

		GetHuffmanCode(_h.GetRoot());

	
	}
	//获取赫夫曼编码（递归，从底下往上跑）[*]
	void GetHuffmanCode(CharNode* root)
	{
		string _code;
		if (root == NULL)                               //返回条件
			return;
		if (root->_left == NULL&&root->_right == NULL)
		{
			CharNode* cur = root;
			CharNode* parent = cur->_parent;
			while (parent != NULL)
			{
			    if (cur == parent->_left)
				{
					_code.push_back('0');
				}
				if (cur == parent->_right)
				{
					_code.push_back('1');
				}
				cur = parent;
				parent = cur->_parent;
			}
			Info[root->_data._ch]._HUffmanCode = _code;    //找到结点之后直接生成编码放进去
			return;
		}
		GetHuffmanCode(root->_left);
		GetHuffmanCode(root->_right);
	
	}


	//解压
	void UnCompass(const char* filename)
	{
	
	}

};


void testCompass()
{
	FileCompass fcps;
	fcps.Compass("TestInput.txt");

}
int main()
{
	testCompass();
	return 0;
}
