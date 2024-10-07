#include "XJ_CharTest_Base.h"

//读取下个字节

void XJ_CharTest_Base::Opt_Reset() {//重置，虽然没啥用
	this->length = 0;
	this->rest = -1;
}

bool XJ_CharTest_Base::Get_IsASCII() {//判断是否为ASCII
	return this->length == 0;
}

bool XJ_CharTest_Base::Get_IsCharBeginByte() {//判断是否为字符开头字节
	return this->rest == this->length;
}

bool XJ_CharTest_Base::Get_IsCharEndByte() {//判断是否为字符结尾字节
	return this->rest == 0;
}
