#pragma once

#include"./XJ_ScanToken.h"

#include<QWidget.h>
#include<QTextEdit.h>
#include<QTableView.h>
#include<QBoxLayout.h>
#include<QHeaderView.h>
#include<QLabel.h>
#include<QTimer.h>

class XJQ_ScanResultPreview :public QWidget {
	Q_OBJECT
signals:
	void textChanged();
private:
	QTextEdit* te;
	QTableView* tb;
	QLabel* msk;
	QMovie* mv;
	QTimer* timer;
	const char** tokenName;
public:
	XJQ_ScanResultPreview(const char* tokenName[],int textChangeDelayms=1000);
	~XJQ_ScanResultPreview();
	void Set_Text(const char* text);
	void Opt_Add(XJ_ScanToken* tokenLst, int count);
	void Opt_Clear();
	void Set_Busy(bool flag);
	std::string Get_Text();
protected slots:
	void Lnk_RowChanged(const QModelIndex& curr, const QModelIndex& prev);
protected:
	void resizeEvent(QResizeEvent* event);
	void dropEvent(QDropEvent* event);
	void dragEnterEvent(QDragEnterEvent* event);
};

