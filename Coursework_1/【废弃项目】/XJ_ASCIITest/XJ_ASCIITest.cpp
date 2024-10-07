

#include"XJ_ASCIITest.h"

void XJ_ASCIITest::Opt_Start(int fixedCount, int followCount) {
	this->fixedCount = fixedCount < 1 ? 1 : fixedCount;
	this->followCount = followCount;
	this->restCount = 0;
}

bool XJ_ASCIITest::Get_IsASCII() {
	return this->restCount == 0;
}

void XJ_ASCIITest::Opt_Next(char ch) {
	--this->restCount;
	if (this->restCount <= 0) {
		this->restCount = this->fixedCount - 1;
		if (this->fixedCount == 1) {
			if (ch < 0) {
				this->restCount = this->followCount + 1;
			}
		}
	}
}

void XJ_ASCIITest::Opt_Reset(){
	this->restCount = 0;
}

