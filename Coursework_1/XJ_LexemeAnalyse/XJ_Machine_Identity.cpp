#pragma once
#include"./XJ_Machine_Identity.h"

namespace XJ_Machine {
	Identity::Identity() {
		this->valid = true;
		this->type = XJ_Token::Type::id;
	}
	bool Identity::Opt_NextChar(char ch) {
		auto type = charTypeTable[ch];
		if ((type == CharType::Digit && (this->isFirst == false)) || type == CharType::Letter || ch == '_') {
			this->isFirst = false;
			return true;
		}
		return false;
	}

};
