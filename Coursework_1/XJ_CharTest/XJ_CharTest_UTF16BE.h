#pragma once
#include"./XJ_CharTest_Base.h"

/*
	才发现用的是大序，
	小序则必须获取第二字节才能判断是否为四字节字符，而且也无法在获取第一字节时立马判断是否为ASCII，略整蛊，
	故不搞LE，
	只不过Windows内部貌似用的是UTF-16LE
*/
class XJ_CharTest_UTF16BE :public XJ_CharTest_Base {
private:
	bool flag = false;
public:
	virtual bool Get_IsASCII();
	virtual void Opt_NextByte(unsigned char ch);
};