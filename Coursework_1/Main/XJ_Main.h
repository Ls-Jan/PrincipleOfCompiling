#pragma once


#include"../XJQ_ScanResultPreview/XJQ_ScanResultPreview.h"
#include"../XJ_LexemeAnalyse/XJ_LexemeAnalyse.h"

#include<QMainWindow.h>
#include<QApplication.h>

class XJ_Main :public QMainWindow {
private:
	XJ_LexemeAnaylse* la;
	XJQ_ScanResultPreview* pv;
public:
	XJ_Main();
	~XJ_Main();
	void Set_Text(const char* text);
	void Set_Text_ByDialog();
protected slots:
	void Lnk_TextChanged();
};

