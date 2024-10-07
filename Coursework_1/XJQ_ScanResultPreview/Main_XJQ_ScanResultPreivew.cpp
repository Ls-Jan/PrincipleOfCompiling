

#include"./XJQ_ScanResultPreview.h"
#include<QtWidgets/QApplication.h>
#include<stdio.h>

const char* TokenName[] = {
	"标识符",
	"关键词",
	"字面量-整数",
	"字面量-浮点数",
	"字面量-字符串",
	"运算符",
	"分隔符",
	"注释",
};

int main(int argc, char* argv[]) {
	QApplication app(argc, argv);

	XJQ_ScanResultPreview pv(TokenName);
	XJ_ScanToken lst[] = {
		XJ_ScanToken{0,5,1,true},
		XJ_ScanToken{6,8,2,true},
		XJ_ScanToken{13,4,3,false},
	};

	pv.Set_Text("AAAAAAA\nBBBBBBBB\nCCCCCCCC");
	pv.Opt_Add(lst, 3);
	//pv.Set_Busy(true);
	pv.show();

	return app.exec();
}



