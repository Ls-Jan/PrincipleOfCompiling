#pragma once
#include"XJ_Machine.h"
#include"./XJ_Machine_Anno.h"

namespace XJ_Machine {
	Anno::Anno() {
		this->valid = false;
		this->type = XJ_Token::Type::anno_Normal;
	}
	bool Anno::Opt_NextChar(char ch) {
		if (this->step == 0) {
			if (this->isSecond) {
				if (ch == '*') {
					this->step = 1;
					this->depth = 1;
					return true;
				}
				else if (ch == '/') {
					this->valid = true;
					this->step = 1;
					return true;
				}
			}
			else {
				if (ch == '/') {
					this->isSecond = true;
					return true;
				}
			}
			return false;
		}
		else if (this->step == 1) {
			if (ch == '!' && (this->type == XJ_Token::Type::anno_Inner || this->type == XJ_Token::Type::anno_Normal)) {
				this->type = XJ_Token::Type::anno_Normal;
				return true;
			}
			else if ((this->depth > 0 && ch == '*') || (this->depth == 0 && ch == '/')) {
				if (this->type == XJ_Token::Type::anno_Normal) {
					this->type = XJ_Token::Type::anno_Outer;
					return true;
				}
				else {
					this->type = XJ_Token::Type::anno_Normal;
				}
			}
			this->step = 2;
			return true;
		}
		else if (this->step == 2) {
			if (this->passOne) {
				this->passOne = false;
				this->isSecond = false;
			}
			if (ch == '\\') {
				this->passOne = true;
			}
			if (this->depth > 0) {
				if (this->isSecond) {
					this->isSecond = false;
					if (ch == '/') {
						this->depth -= 1;
						if (this->depth == 0) {
							this->step = 3;
							this->valid = true;
						}
					}
				}
				else 	if (ch == '*')
					this->isSecond = true;
			}
			else {
				if (ch == '\n') {
					this->step = 3;
					return false;//不想要末尾的换行符
				}
			}
			return true;
		}
		return false;
	}
};
