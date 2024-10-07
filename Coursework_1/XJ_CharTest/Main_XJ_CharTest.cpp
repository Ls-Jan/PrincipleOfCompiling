
#include"./XJ_CharTest_UTF8.h"
#include<stdio.h>
#include<locale>
#include<vector>



int main() {
	setlocale(LC_ALL, ".utf-8");//本项目使用的是utf-8
	const char str[] = "AAA∞BBB\n";

	XJ_CharTest_UTF8 charTest;
	for (int i = 0; str[i]; ++i) {
		char ch = str[i];
		charTest.Opt_NextByte(ch);
		if (charTest.Get_IsCharBeginByte())
			printf_s("\n");
		printf_s("%d ", ch);
	}
	printf_s("\n\n");
	return 0;
}

