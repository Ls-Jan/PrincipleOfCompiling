#pragma once
#include"./XJ_Machine.h"
#include"./XJ_Token.h"

namespace XJ_Machine {
	class Base {
	protected:
		bool valid = true;
		XJ_Token::Type type = XJ_Token::Type::invalid;
	public:
		virtual bool Opt_NextChar(char ch) = 0;//如果不接收该字符则返回false
		bool Get_IsValid();//判断匹配结果是否有效，例如0b10354这种明显错误的数字，以及使用单引号的字符串'ABC'
		XJ_Token::Type Get_TokenType();//获取token类型
	};
};



