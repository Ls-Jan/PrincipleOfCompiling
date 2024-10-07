
#include"XJ_ByteFileReader.h"
#include"../XJ_CharTest/XJ_CharTest_UTF8.h"
#include"../XJ_CharTest/XJ_CharTest_UTF16BE.h"
#include"../XJ_CharTest/XJ_CharTest_GB18030.h"
#include<stdio.h>
#include<locale>
#include<vector>

int main() {
	setlocale(LC_ALL, ".utf-8");//本项目使用的是utf-8，如果不进行环境设置的话甚至连文件都打不开

	std::vector<std::pair<const char*,  XJ_CharTest_Base*>> paths = {
		{"./测试-UTF8.txt",new XJ_CharTest_UTF8},
		{"./测试-UTF-16BE.txt",new XJ_CharTest_UTF16BE},
		{"./测试-GB18030.txt",new XJ_CharTest_GB18030},
	};

	XJ_CharTest_Base* charTest;
	XJ_ByteFileReader bg(2);
	for (auto p = paths.begin(); p != paths.end(); ++p) {
		printf_s("%s\n", p->first);
		bg.Opt_LoadFile(p->first);
		charTest = p->second;
		bool nextLine = false;
		for (char ch=0; bg.Opt_Next();) {
			ch = bg.Get_Byte();
			charTest->Opt_NextByte(ch);
			if (charTest->Get_IsCharBeginByte())
				printf_s("\n");
			printf_s("%d ", ch);
		}
		printf_s("\n\n");
	}
	return 0;
}

