
#include"./XJQ_ScanResultPreview.h"
#include<QStandardItemModel.h>
#include<QEvent.h>
#include<QMovie.h>
#include<QMimeData.h>
#include<QSplitter.h>

static QStringList headers = {//表格标题
	"无效匹配",
	"位置+长度",
	"字串内容",
	"类型",
};

XJQ_ScanResultPreview::XJQ_ScanResultPreview(const char* tokenName[], int textChangeDelayms) :QWidget(nullptr) {
	this->te = new QTextEdit;
	this->tb = new QTableView;
	this->msk = new QLabel(this->tb);
	this->timer = new QTimer;
	this->mv = new QMovie(":/XJQ_ScanResultPreview/LoadingGIF.gif");
	this->tokenName = tokenName;
	auto spt = new QSplitter;
	spt->addWidget(this->te);
	spt->addWidget(this->tb);
	auto box = new QHBoxLayout(this);
	box->addWidget(spt);
	this->setAcceptDrops(true);
	this->resize(800, 400);

	{
		auto model = new QStandardItemModel;
		auto tb = this->tb;
		model->setHorizontalHeaderLabels(headers);
		tb->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选中模式为选中行
		tb->setSelectionMode(QAbstractItemView::SingleSelection);//设置选中单个
		tb->setEditTriggers(QAbstractItemView::NoEditTriggers);
		tb->setModel(model);
		tb->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);
		tb->horizontalHeader()->setStretchLastSection(true);
		QObject::connect(tb->selectionModel(), &QItemSelectionModel::currentChanged, this, &XJQ_ScanResultPreview::Lnk_RowChanged);
	}

	{
		auto te = this->te;
		auto palette = te->palette();
		palette.setBrush(QPalette::Highlight, Qt::red);
		te->setPalette(palette);
		te->setAcceptDrops(false);
		QObject::connect(te, &QTextEdit::textChanged, [this]() {
			this->timer->start();
			});
	}

	{
		auto timer = this->timer;
		timer->setInterval(textChangeDelayms);
		timer->setSingleShot(true);
		QObject::connect(timer, &QTimer::timeout, [this]() {
			emit this->textChanged();
			});
	}

	{
		auto msk = this->msk;
		auto palette = this->te->palette();
		palette.setBrush(QPalette::ColorRole::Window, QColor(0, 0, 0, 128));
		msk->hide();
		msk->setPalette(palette);
		msk->setMovie(this->mv);
		msk->setAlignment(Qt::AlignmentFlag::AlignCenter);
		msk->setAutoFillBackground(true);
	}
}

XJQ_ScanResultPreview::~XJQ_ScanResultPreview() {
	this->msk->resize(this->tb->size());
	delete this->mv;
}

void XJQ_ScanResultPreview::resizeEvent(QResizeEvent* event) {
	this->msk->resize(this->tb->size());
}

void XJQ_ScanResultPreview::dropEvent(QDropEvent* event) {
	auto mData = event->mimeData();
	if (mData->hasUrls()) {
		auto path = mData->urls().back().toLocalFile();
		auto file = new QFile(path);
		file->open(QIODevice::OpenMode::enum_type::ReadOnly);
		auto data = file->readAll();
		if (!data.isEmpty()) {
			this->te->setText(data);
		}
		file->close();
		delete file;
	}
}

void XJQ_ScanResultPreview::dragEnterEvent(QDragEnterEvent* event) {
	auto urls = event->mimeData()->urls();
	if (urls.length()==1) {
		event->acceptProposedAction();
	}
}


void XJQ_ScanResultPreview::Opt_Add(XJ_ScanToken* tokenLst, int count) {
	QStandardItemModel* model = dynamic_cast<QStandardItemModel*>(this->tb->model());
	char buf[1024] = "";
	auto text=this->te->toPlainText();
	for (auto i = 0; i < count; ++i) {
		auto token = tokenLst[i];
		sprintf_s(buf, "( %d , %d )", token.start, token.length);
		auto pos = new QStandardItem(buf);
		auto type = new QStandardItem(this->tokenName[token.type]);
		auto invalid = new QStandardItem(token.valid ? " " : "√");

		auto str = new QStandardItem(text.mid(token.start,token.length));
		invalid->setTextAlignment(Qt::AlignCenter);
		model->appendRow({ invalid,pos,str,type });
	}
}

void XJQ_ScanResultPreview::Opt_Clear() {
	QStandardItemModel* model = dynamic_cast<QStandardItemModel*>(this->tb->model());
	model->clear();
	model->setHorizontalHeaderLabels(headers);
}

void XJQ_ScanResultPreview::Set_Text(const char* text) {
	this->te->setText(text);
}

void XJQ_ScanResultPreview::Lnk_RowChanged(const QModelIndex& curr, const QModelIndex& prev) {
	auto str = curr.siblingAtColumn(1).data(0).toString();
	int pos[2] = { 0,0 };
	bool next = false;
	int i = 0;
	for (auto p = str.begin(); p != str.end(); ++p) {//str形如 ( S , L )，其中S和L都是正整数
		if (p->isNumber()) {
			pos[i] = pos[i] * 10 + p->digitValue();
			next = true;
		}
		else {
			if (next) {
				next = false;
				++i;
				if (i > 1)
					break;
			}
		}
	}
	auto cursor = this->te->textCursor();
	cursor.setPosition(pos[0]);
	cursor.setPosition(pos[0] + pos[1], QTextCursor::KeepAnchor);
	this->te->setTextCursor(cursor);
}

void XJQ_ScanResultPreview::Set_Busy(bool flag) {
	this->mv->setPaused(!flag);
	this->msk->setVisible(flag);
	this->msk->resize(this->tb->size());
}

std::string XJQ_ScanResultPreview::Get_Text() {
	//实测发现，这里的toStdString在Release模式下会出现程序崩溃，原因不明，多半是Qt的问题，直接用std::string(const char*)绕开
	return std::string(this->te->toPlainText().toUtf8().data());
	return this->te->toPlainText().toStdString();
}


