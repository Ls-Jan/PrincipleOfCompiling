#pragma once

#include"./XJ_CharTest_Base.h"

/*
	调用Opt_Reset前需要喂一个0字符，即调用一次Opt_NextByte(0)
*/
class XJ_CharTest_GB18030 :public XJ_CharTest_Base {
private:
	int flag = -1;//当该值为0时该判断第二字节的值，以此判断是不是四字节字符
public:
	virtual void Opt_NextByte(unsigned char ch);
};




