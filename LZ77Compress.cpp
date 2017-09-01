#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
///////////////////基于LZ77压缩算法的文件压缩/////////////////
#include<iostream>
#include<stdio.h>
#include<string>
#include<stdlib.h>
#include<assert.h>
#include<vector>
using namespace std;

const size_t N = 2 * 32 * 1024;     //设置缓存为64k
enum{ SlipBlock = 32 * 1024 };      //滑块设置大小为32k
typedef long long LongType;

class  ZipCompress
{
private:
	vector<unsigned char> _windows;
	size_t _frist;                   //滑动窗口在整个文件中
	size_t _last;                    //滑动窗口在整个文件中的最后的结束标志
public:
	ZipCompress()
	{
		_windows.reserve(N);        //64k大的一个数组
		_frist = 0;                
		_last = 0;                 
	}
	string Compress(const string& filename)
	{
		return _ZipFileCompress(filename);
	}
	string UnCompress(const string& filename)
	{
		return _ZipFileUnCompress(filename);
	}
protected:
	//文件压缩
	string _ZipFileCompress(const string& filename)
	{
		assert(filename.c_str());
		string CompressFileName = filename;
		CompressFileName += ".zip";
		FILE* fInput = fopen(filename.c_str(), "rb+");  //只读方式打开文件读取字符
		assert(fInput);
		FILE* fOut = fopen(CompressFileName.c_str(), "wb+"); //二进制写的方式打开压缩文件
		assert(fOut);
        FILE* pWindows = fopen(filename.c_str(), "rb+");  //指向滑动窗口的文件指针
		assert(pWindows);

		int ch = 0;
		ch = fgetc(fInput);   //从文件中读取一个字符
		LongType count = 0;
        //判断是否需要压缩  重复的字符出现超过3次就需要压缩。
		unsigned char buf = 0;
		int flag = 7;             //标记buf处理了几位，没动什么意思
		
		while (ch != EOF)       //没有读到文件结尾
		{
			int length = 0;
			long distance = 0;
			long OFFSET = ftell(fInput);//当前读取到的字符距离文件开始的距离

			if (OFFSET <= SlipBlock)
			{
				fseek(pWindows, 0, SEEK_SET);    //读取的字符偏移文件么有超过32k，那么窗口指针一直指向文件的首位置
				distance = OFFSET - 1;          //为什么是-1？
			}
			if (distance > 1)
			{
				fseek(fInput, OFFSET - 1, SEEK_SET);          //finput往回跳一个字节
				length = FindRepetition(pWindows, fInput, distance);
				fseek(fInput, OFFSET, SEEK_SET);             //回到原来的位置
			}
		}
		if (length>0)             //有重复的,用1表示有重复的
		{
			fseek(fInput, length - 1, SEEK_CUR);

			buf |= (1 << flag);        //先把flag这一位标记 设置成1
			flag--;
			if (flag < 0)    //buf这8位以经处理完毕，进行写入
			{
				fputc(buf, fOut);
				flag = 7;
				buf = 0;
			}

			//接下来把distance和length写入
			int pos = 15;
			while (pos >= 0)                    //处理两个字节的distance
			{
				if (distance&(1 << pos))        //如果length的第pos位为1
					buf |= (1 << flag);         //向buf中写1
				else
					buf &= (~(1 << flag));       //向buf中写0
				flag--;
				if (flag < 0)                    //buf这8位以经处理完毕，进行写入
				{
					fputc(buf, fOut);
					flag = 7;
					buf = 0;
				}
				pos--;
			}

			pos = 7;                             //接下来写入length
			while (pos >= 0)
			{
				if (length&(1 << pos))           //如果length的第pos位为1
					buf |= (1 << flag);           //向buf中写1
				else
					buf &= (~(1 << flag));       //向buf中写0
				flag--;
				if (flag < 0)                    //buf这8位以经处理完毕，进行写入
				{
					fputc(buf, fOut);
					flag = 7;
					buf = 0;
				}
				pos--;
			}
			count += 3;              //处理一个distance和一个length，count加三个字节
		}
		else                             //这个字符是普通字符
		{
			buf &= (~(1 << flag));       //把flag这一位设置成0
			flag--;
			if (flag < 0)                //buf这8位已经处理完毕，进行写入
			{
				fputc(buf, fOut);
				flag = 7;
				buf = 0;
			}

			//接下来处理ch这个字符
			int pos = 7;
			while (pos >= 0)
			{
				if (ch&(1 << pos))                //如果ch的第pos位为1
					buf |= (1 << flag);           //向buf中写1
				else
					buf &= (~(1 << flag));        //向buf中写0
				flag--;
				if (flag < 0)                     //buf这8位以经处理完毕，进行写入
				{
					fputc(buf, fOut);
					flag = 7;
					buf = 0;
				}
				pos--;
			}
			count++;              //处理一个字符，count++一次
		}
		ch = fgetc(fInput);
	}

	if (flag != 7)       //如果最后的bit位不够一个整数，则就在后面补0
	{
		fputc(buf, fOut);
	}
	fwrite(&count, 1, 8, fOut);
	fclose(fInput);
	fclose(fOut);
	fclose(pWindows);                             //关闭窗口指针所指向的文件
	return FirstCompressFileName;
	}
	//文件解压
	string  _ZipFileUnCompress(const string& filename)
	{

	}
protected:
	int FindRepetition(FILE*& pWindows, FILE*& fInput, long& distance)     //函数主要是将滑动窗口中填充数据，滑动窗口大小是64k，主要为了让下面的函数求匹配子串的最大长度和距离
	{
		long OFFSET1 = ftell(pWindows);   //当前的窗口距离文件首位置的距离
		long OFFSET2 = ftell(fInput);     //当前需要比较的字符串
		int ch = 0;

		if ((size_t)OFFSET2 > _last)      //_last是滑动窗口最后的字符距离文件开头的距离，读取的字符位置已经超出了滑动窗口，实际上就是一种正常的情况
		{
			_windows.clear();
			for (size_t i = 0; i < N; i++)    //滑动窗口里面放字符，从pwindow开始放入数据
			{
				ch = fgetc(pWindows);
				if (ch == EOF)
					break;
				_windows.push_back(ch);    
			}
			_frist = OFFSET1;       //就是pWindows指向的位置
			_last = _windows.size() + OFFSET1;     //窗口最后的字符在整个文件中的位置
		}
		int length = GetRepetitionlength(fInput, distance, OFFSET1);
		return length;
	}
	//获取最大子串长度以及距离distance
	int GetRepetitionlength(FILE* fInput, long& distance, long& pWindowsPos)   
	{
		long OFFSET = ftell(fInput);     //读取的字符距离文件开头多远
		vector<unsigned char> v;
		if (Getch(fInput, v) == false)   //先将第一个字符放到v中
			return 0;
		//////////压缩核心////////////////
		size_t size = OFFSET - pWindowsPos;
		size_t index = pWindowsPos - _frist;
		int length = 0;                //字符串匹配的长度
		for (; index < size; ++index)
		{
			//先找到第一个匹配的字符
			if (_windows[index] == v[0])        
			{
				size_t flag = index;
				size_t i = 0;
				while ((flag < size) && (length < 255))   //length分配1个字节
				{
					if (i == v.size() - 1)               //這快不太懂
					{
						if (Getch(fInput, v) == false)      //不再匹配，长度统计停止，跳出循环
							break;
					}
					if (_windows[flag] == v[i])            //统计长度
					{
						length++;
						flag++;
						i++;
					}
					else
						break;
				}
				if (length >= 3)
				{
					distance = OFFSET - (index + _frist);     //将原来的距离改为匹配的子串的距离然后带出来，這样就能将两个参数带出来了
					return length;
				}
				length = 0;                                   //在下一次循环之前将长度置0;
			}
		}
		return 0;
	}

	//辅助添加比较数组
	bool Getch(FILE* fInput, vector<unsigned char>& v)   //从文件中获取一个字符到临时数组中
	{
		int ch = 0;
		ch = fgetc(fInput);
		v.push_back(ch);
		if (ch == EOF)
			return false;
		else
			return true;
	}
};
void TestLZ77Compress()
{
	ZipCompress CompressDoxc;
	CompressDoxc.Compress("鞠鑫.pdf");
}
int main()
{
	TestLZ77Compress();
	return 0;
}