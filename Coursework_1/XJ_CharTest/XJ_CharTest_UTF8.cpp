#include "XJ_CharTest_UTF8.h"

void XJ_CharTest_UTF8::Opt_NextByte(unsigned char ch) {
	if (ch < 128) {//对应0开头
		this->length = 0;
		this->rest = 1;
	}
	else {
		if (this->rest < 1) {
			if (ch < 192) {//对应10开头
				this->rest = 0;//无效情况
			}
			else {//对应11开头
				this->length = -1;
				for (unsigned char msk = 0x80; msk > 0x10; msk >>= 1) {
					if ((msk & ch) == 0)
						break;
					++this->length;
				}
				this->rest = this->length + 1;
			}
		}
	}
	--this->rest;
}
