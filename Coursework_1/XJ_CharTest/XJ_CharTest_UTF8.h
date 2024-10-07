#pragma once
#include"./XJ_CharTest_Base.h"


class XJ_CharTest_UTF8 :public XJ_CharTest_Base {
public:
	virtual void Opt_NextByte(unsigned char ch);
};
