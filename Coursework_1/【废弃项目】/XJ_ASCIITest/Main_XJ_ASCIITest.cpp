
#include"XJ_ASCIITest.h"
#include<stdio.h>
#include<locale>
#include<vector>



int main() {
	setlocale(LC_ALL, ".utf-8");//本项目使用的是utf-8
	const char str[] = "AAA∞BBB\n";

	XJ_ASCIITest at;
	for (int i = 0; str[i]; ++i) {
		char ch = str[i];
		at.Opt_Next(ch);
		printf_s("%s %d\n", at.Get_IsASCII() ? " " : ">", ch);
	}
	printf_s("\n\n");
	return 0;
}

