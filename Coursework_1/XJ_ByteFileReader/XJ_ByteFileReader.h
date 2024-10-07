#pragma once
#include<stdio.h>

//这个类用于字节读取
//没做回退功能，这不好做，而且也觉得没必要
//越想越觉得这玩意儿做出来就是废的
class XJ_ByteFileReader {
private:
	char* buffer[2] = { nullptr,nullptr };//双缓冲区策略
	char* currBuffer = nullptr;
	unsigned int bufCount = 0;
	unsigned int bufSize = 0;//缓冲区大小
	unsigned int bufLength = 0;//缓冲区有效数据个数-1，减1是为了对下标，不然每次越界判断都要进行额外的减法
	unsigned int bufPst = 0;
	FILE* file = nullptr;
public:
	XJ_ByteFileReader(unsigned int bufSize = 4096);
	~XJ_ByteFileReader();
	bool Opt_LoadFile(const char* fileName);//该函数调用后要再调用一次Opt_Next才会读取首个字符。
	char Get_Byte();//读取当前字节，如果返回值是0则说明已达末尾
	unsigned int Get_Pos();//获取当前位置
	bool Opt_Next();//下一个字节，成功则返回True
};


