#pragma once
#include"./XJ_Machine.h"
#include"./XJ_Machine_Base.h"
#include"../XJ_StringTreeNode/XJ_StringTreeNode.h"

namespace XJ_Machine {
	class Keyword :public Base {//固定匹配，用于关键字以及运算符的匹配
	private:
		XJ_StringTreeNode* root;
		XJ_StringTreeNode* curr;
	public:
		Keyword(XJ_StringTreeNode* root, XJ_Token::Type tokenType);
		virtual bool Opt_NextChar(char ch);
	};
};
