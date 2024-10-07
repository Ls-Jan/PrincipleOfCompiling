#pragma once
#include"./XJ_Machine_String.h"
#include<limits.h>

namespace XJ_Machine {
	String::String() {
		this->step = 0;
		this->valid = false;
	}
	bool String::Opt_NextChar(char ch) {
		if (this->step == 0) {
			if (this->wellCount >= 0) {
				if (ch == '#') {
					++this->wellCount;
					return true;
				}
			}
			else {
				if (this->type != XJ_Token::Type::val_byte && (ch == 'b' || ch == 'B')) {
					this->type = XJ_Token::Type::val_byte;
					return true;
				}
				else if (ch == 'r' || ch == 'R') {
					this->wellCount = 0;
					return true;
				}
			}
			if (ch == '\'') {
				this->charCount = 1;
				this->step = 1;
				this->quote = ch;
				this->wellCount = this->wellCount > 0 ? INT_MAX : 0;//单字符还带#？必无效
				return true;
			}
			else if (ch == '\"') {
				this->charCount = INT_MAX;//这里直接怼最大数是因为放心，真不敢相信会有2^31B=2GB大小的字符串(算是一个设计隐患，真有这种奇葩情况再升级为int64)
				this->step = 1;
				this->quote = ch;
				if (this->type == XJ_Token::Type::val_byte)
					this->type = this->wellCount >= 0 ? XJ_Token::Type::val_byteStr_Naive : XJ_Token::Type::val_byteStr;
				else
					this->type = this->wellCount >= 0 ? XJ_Token::Type::val_str_Naive : XJ_Token::Type::val_str;
				return true;
			}
			return false;
		}
		else if (this->step == 1) {
			if (this->passOne) {
				this->passOne = false;
				this->charCount -= 1;
			}
			else if (ch == '\\') {
				this->passOne = true;
			}
			else if (ch == this->quote) {
				this->step = 2;
				this->valid = this->wellCount == 0;
			}
			else {
				this->charCount -= 1;
			}
			return true;
		}
		else {
			if (ch == '#') {
				this->wellCount -= 1;
				this->valid = this->wellCount == 0;
				return true;
			}
			return false;
		}
	}
};


