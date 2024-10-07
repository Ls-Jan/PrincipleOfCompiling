#pragma once
#include"./XJ_Machine_Number.h"

namespace XJ_Machine {
	Number::Number() {
		this->type = XJ_Token::Type::val_int_10;
		this->acceptMaxDigit = '9';
		this->valid = false;
	}
	bool Number::Opt_NextChar(char ch) {
		if (this->step == 0) {
			if (this->acceptSign && (ch == '+' || ch == '-')) {
				this->acceptSign = false;
				return true;
			}
			else if (this->acceptBOX) {
				if (ch == 'b' || ch == 'B') {
					this->acceptMaxDigit = '1';
					this->type = XJ_Token::Type::val_int_2;
				}
				else if (ch == 'o' || ch == 'O') {
					this->acceptMaxDigit = '7';
					this->type = XJ_Token::Type::val_int_8;
				}
				else if (ch == 'x' || ch == 'X') {
					this->acceptLetterA_F = true;
					this->type = XJ_Token::Type::val_int_16;
				}
				else {
					this->acceptBOX = false;
				}
				if (this->acceptBOX) {
					this->acceptLetterE = false;
					this->acceptDot = false;
					this->valid = false;
					this->step = 1;
					return true;
				}
			}
			if (charTypeTable[ch] == CharType::Digit || ch == '_') {
				this->acceptSign = false;
				this->valid = true;
				if (ch == '0' && this->acceptBOX == false) {
					this->acceptBOX = true;
				}
				else {
					this->step = 1;
				}
				return true;
			}
			else if (ch == '.') {
				this->type = XJ_Token::Type::val_float;
				this->valid = false;
				this->acceptDot = false;
				this->step = 1;
				return true;
			}
			return false;
		}
		else if (this->step == 1) {
			this->valid = true;
			if (charTypeTable[ch] == CharType::Digit) {
				if (ch > this->acceptMaxDigit) {
					this->step = 2;
					this->valid = false;
				}
				return true;
			}
			else if (charTypeTable[ch] == CharType::Letter) {
				if (!this->acceptLetterA_F || !(('a' <= ch && ch <= 'f') || ('A' <= ch && ch <= 'F'))) {
					this->step = 2;
					this->valid = false;
				}
				return true;
			}
			else if (ch == '_') {//无脑接受下划线
				return true;
			}
			else if (ch == '.') {
				this->type = XJ_Token::Type::val_float;
				this->valid = false;
				if (!this->acceptDot) {
					this->step = 2;
				}
				return true;
			}
		}
		else if (this->step == 2) {//进step2的都是无效匹配，只不过仍能继续吃字符
			if (charTypeTable[ch] == CharType::Letter || charTypeTable[ch] == CharType::Digit || ch == '_' || ch == '.')
				return true;
		}
		return false;
	}
};
