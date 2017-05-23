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
		FILE* fout = fopen(filename, "r");        //這里的 "r"是什么意思？   以读的方式
		assert(fout);

		//统计字符出现的次数
		char ch = fgetc(fout);                 //fgetc的用法
		while (ch!=EOF)                      //EOF：文件结束标志
		{
			Info[ch]._Count++;
			ch = fgetc(fout);
		}


		                                                   //搭建出现字母的赫夫曼树，将文件中出现的字母进行建堆，没有出现就不需要建堆了 所以需要用的invalid
		CharInfo _invalidInfoNode;
		_invalidInfoNode._Count = 0;                          //出现次数为0的字母包
		HuffmanTree<CharInfo> _h(Info, 256,_invalidInfoNode);

		string code;
		GetHuffmanCodeII(_h.GetRoot(),code);



		//创建压缩文件进行压缩
		//1.
		string compassfile = filename;                   //這里存在疑问
		compassfile = compassfile + ".huffman";
		FILE* fIn = fopen(compassfile.c_str(), "w");      //注意這里的c_str().....    还有這里就会创建一个新的文件
		assert(fIn);

		//2.
		char value = 0;
		int count = 0;              //要注意這里的count的刚开始的值和最后结束的值
		fseek(fout, 0, SEEK_SET);     //fseek函数的返回值为整形，不是一个文件指针  fout指针指向文件首字母
		char ch1 = fgetc(fout);        //fgetc操作函数
		while (ch1!=EOF)
		{
			string& code = Info[ch1]._HUffmanCode;     
			for (size_t i = 0; i < code.size(); i++)
			{
				value <<= 1;                      //注意移位并不会改变变量本身的值
				if (code[i] == '1')                //string支持了[]的重载
				{
					value |= 1;
				}
				else
				{
					value |= 0;
				}
				count++;

				if (count == 8)                   //满8位就写到压缩文件里面去  然后重新给8位0
				{
					fputc(value, fIn);            //fputc的使用
					value = 0;
					count = 0;
				}
			}
			ch1 = fgetc(fout);
		}

		fclose(fIn);
		fseek(fout, 0, SEEK_SET);
		fclose(fout);

	  
	}
	//获取每一个字符的赫夫曼编码（递归，从底下往上跑）[*]
	//void GetHuffmanCode(CharNode* root)
	//{
	//	string _code;
	//	if (root == NULL)                               //返回条件
	//		return;
	//	if (root->_left == NULL&&root->_right == NULL)
	//	{
	//		CharNode* cur = root;
	//		CharNode* parent = cur->_parent;
	//		while (parent != NULL)
	//		{
	//		    if (cur == parent->_left)
	//			{

	//				_code.push_back('0');
	//			}
	//			if (cur == parent->_right)
	//			{
	//				_code.push_back('1');
	//			}
	//			cur = parent;
	//			parent = cur->_parent;
	//		}
	//		Info[root->_data._ch]._HUffmanCode = _code;    //找到结点之后直接生成编码放进去
	//		reverse(_code.begin(), _code.end());
	//		return;
	//	}
	//	GetHuffmanCode(root->_left);
	//	GetHuffmanCode(root->_right);
	//}
	
	//第二种方法：  
	void GetHuffmanCodeII(CharNode* root, string code)   //从高处往下递归递归下去，遇到叶子结点就把编码放到字母包的赫夫曼编码里面去。
	{
		if (root == NULL)
			return;
		if (root->_left == NULL&&root->_right == NULL)
		{
			Info[root->_data._ch]._HUffmanCode = code;     //注意這里不需要反转
			return;
		}
		GetHuffmanCodeII(root->_left, code + '0');     //注意：string是支持+的
		GetHuffmanCodeII(root->_right, code + '1');
	}

	//解压
	void UnCompass(const char* filename)
	{
	   	assert(filename);
		string uncompassfile = filename;
		size_t pos = uncompassfile.rfind('.');
	    
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
