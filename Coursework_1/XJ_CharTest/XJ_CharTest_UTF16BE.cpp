#include "XJ_CharTest_UTF16BE.h"

bool XJ_CharTest_UTF16BE::Get_IsASCII() {
	return this->flag;
}

void XJ_CharTest_UTF16BE::Opt_NextByte(unsigned char ch) {
	if (this->rest < 1) {
		if (0xDB < ch && ch < 0xE0) {//无效值
			this->rest = 0;
		}
		else {
			if (ch == 0xDB) {//高代理码点的首字节
				this->length = 3;
			}
			else {//基本面字符的首字节
				this->length = 1;
			}
			this->rest = this->length + 1;
		}
		this->flag = ch == 0;
	}
	--this->rest;
}
