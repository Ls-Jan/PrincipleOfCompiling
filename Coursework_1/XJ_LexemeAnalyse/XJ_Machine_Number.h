#pragma once
#include"./XJ_Machine.h"
#include"./XJ_Machine_Base.h"

namespace XJ_Machine {
	class Number :public Base {//数字匹配
	private:
		bool acceptLetterE = true;
		bool acceptSign = true;
		char acceptMaxDigit = 0;
		bool acceptLetterA_F = false;//十六进制
		bool acceptBOX = false;//非十进制整数的前缀，即0b、0o、0x
		bool acceptDot = true;
		int step = 0;
	public:
		Number();
		virtual bool Opt_NextChar(char ch);
	};
};
