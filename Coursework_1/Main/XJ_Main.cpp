#include "XJ_Main.h"
#include<QMenu.h>
#include<QMenuBar.h>
#include<QFileDialog.h>

XJ_Main::XJ_Main() {
	this->la = new XJ_LexemeAnaylse;
	this->pv = new XJQ_ScanResultPreview(XJ_Token::Name.data(), XJ_Token::Name.size());
	this->pv->setParent(this);
	this->la->Set_CharMode(true);
	QObject::connect(this->pv, &XJQ_ScanResultPreview::textChanged, this, &XJ_Main::Lnk_TextChanged);
	this->setCentralWidget(this->pv);
	this->resize(1000, 600);
	auto menuBar = new QMenuBar(this);
	auto menu = new QMenu("文件");
	menuBar->addMenu(menu);
	QObject::connect(menu->addAction("添加文件"),&QAction::triggered,this,&XJ_Main::Set_Text_ByDialog);

	menu = new QMenu("说明");
	menuBar->addMenu(menu);
	menu->addAction("可以拖拽文件")->setEnabled(false);
	menu->addAction("只允许UTF8文件")->setEnabled(false);
	this->setMenuBar(menuBar);
	menuBar->show();
}

XJ_Main::~XJ_Main() {
	delete this->la;
}

void XJ_Main::Set_Text(const char* text) {
	this->pv->Set_Text(text);
}

void XJ_Main::Set_Text_ByDialog(){
	auto path = QFileDialog::getOpenFileName(this, "添加文本文件", "./", "*.txt");
	auto file = new QFile(path);
	file->open(QIODevice::OpenMode::enum_type::ReadOnly);
	auto data = file->readAll();
	if (!data.isEmpty()) {
		this->pv->Set_Text(data);
	}
	file->close();
	delete file;
}

void XJ_Main::Lnk_TextChanged() {
	this->pv->Set_Busy(true);//设置为忙状态
	auto str = this->pv->Get_Text();//从文本框传递过来的字符串是UTF8编码的，因此XJ_LexemeAnaylse只需要固定使用UTF8字符集即可。
	this->pv->Opt_Clear();
	this->la->Opt_Reset();
	this->la->Opt_Scan(str.data(), str.size());
	auto tokens = this->la->Get_Tokens();
	this->pv->Opt_Add(reinterpret_cast<XJ_ScanToken*>(tokens->data()), tokens->size());
	this->pv->Set_Busy(false);
}


