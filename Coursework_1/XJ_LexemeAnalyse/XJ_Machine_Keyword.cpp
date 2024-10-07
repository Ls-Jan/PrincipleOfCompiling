#pragma once
#include"./XJ_Machine_Keyword.h"

namespace XJ_Machine {
	Keyword::Keyword(XJ_StringTreeNode* root, XJ_Token::Type tokenType) {
		this->root = root;
		this->curr = root;
		this->type = tokenType;
	}
	bool Keyword::Opt_NextChar(char ch) {
		auto curr = this->curr;
		if (curr) {
			curr = curr->Get_NextNode(ch);
			this->curr = curr;
			if (curr) {
				this->valid = curr->Get_IsFinalNode();
			}
		}
		return curr != nullptr;
	}
};
