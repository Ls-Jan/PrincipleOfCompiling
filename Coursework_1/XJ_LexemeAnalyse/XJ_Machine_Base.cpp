#pragma once
#include"./XJ_Machine.h"
#include"./XJ_Machine_Base.h"

namespace XJ_Machine {
	bool Base::Get_IsValid() {//判断匹配结果是否有效，例如0b10354这种明显错误的数字，以及使用单引号的字符串'ABC'
		return this->valid;
	}
	XJ_Token::Type Base::Get_TokenType() {//获取token类型
		return this->type;
	}
};



