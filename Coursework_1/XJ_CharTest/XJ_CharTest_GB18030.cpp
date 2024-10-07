#include "XJ_CharTest_GB18030.h"
#include<stdio.h>
void XJ_CharTest_GB18030::Opt_NextByte(unsigned char ch) {
	if (this->flag == 0) {
		if (0x2F < ch && ch < 0x3A) {//四字节字符的第二字节
			this->length = 4;
			this->rest = 3;
		}
	}
	else {
		if (this->rest < 1) {
			this->flag = 0;
			if (ch < 0x80) {
				this->length = 0;
			}
			else {
				this->flag = 1;
				this->length = 1;
			}
			this->rest = this->length + 1;
		}
	}
	--this->flag;
	--this->rest;
}
