#include"./XJ_LexemeAnalyse.h"
#include"../XJ_CharTest/XJ_CharTest_UTF8.h"
#include"../XJ_CharTest/XJ_CharTest_UTF16BE.h"
#include"../XJ_CharTest/XJ_CharTest_GB18030.h"

XJ_LexemeAnaylse::XJ_LexemeAnaylse() {
	this->Set_Charset(true);//分析UTF-8
	this->strNode_op = new XJ_StringTreeNode;
	this->strNode_key = new XJ_StringTreeNode;
	this->strNode_delimiter = new XJ_StringTreeNode;
	this->charTest = new XJ_CharTest_UTF8;
	this->strNode_op->Opt_NewBranch(XJ_Token::FixedToken::Operators.data(), XJ_Token::FixedToken::Operators.size());
	this->strNode_key->Opt_NewBranch(XJ_Token::FixedToken::Keywords.data(), XJ_Token::FixedToken::Keywords.size());
	this->strNode_delimiter->Opt_NewBranch(XJ_Token::FixedToken::Delimiter.data(), XJ_Token::FixedToken::Delimiter.size());
	this->Opt_Reset();
}

XJ_LexemeAnaylse::~XJ_LexemeAnaylse() {
	for (auto p = this->group.begin(); p != this->group.end(); ++p)
		delete* p;
	delete this->strNode_op;
	delete this->strNode_key;
	delete this->strNode_delimiter;
	delete this->charTest;
}

std::vector<XJ_Token::Token>* XJ_LexemeAnaylse::Get_Tokens() {
	return &this->tokens;
}

void XJ_LexemeAnaylse::Set_Charset(bool isUTF8, bool isUTF16BE, bool isGB18030 ) {
	XJ_CharTest_Base* charTest = nullptr;
	if (isUTF8)
		charTest = new XJ_CharTest_UTF8;
	else if (isUTF16BE)
		charTest = new XJ_CharTest_UTF16BE;
	else if (isGB18030)
		charTest = new XJ_CharTest_GB18030;
	if (charTest) {
		delete this->charTest;
		this->charTest = charTest;
	}
}

void XJ_LexemeAnaylse::Opt_Reset() {
	for (auto p = this->group.begin(); p != this->group.end(); ++p)
		delete* p;
	this->group.clear();
	this->tokens.clear();
	this->pos = this->useCharPos ? 0 : -1;
	this->invalidChar = false;
	this->charTest->Opt_Reset();
}

void XJ_LexemeAnaylse::Opt_Scan(const char str[], int count,bool isFinalStr) {//能够断片式接受字串
	bool empty = this->group.empty();
	bool asciiTest_DonMove = false;
	for (auto i = 0; i < count; ++i) {
		char ch = str[i];
		if (asciiTest_DonMove)
			asciiTest_DonMove = false;
		else {
			if(this->useCharPos==false ||this->charTest->Get_IsCharBeginByte())
				this->pos += 1;
			this->charTest->Opt_NextByte(ch);
		}
		if (this->charTest->Get_IsASCII() == false)//无效的字符，避免后续造成麻烦，索性在这将ch改成一个无效的字符
			ch = 1;//不敢赋0
		if (empty) {
			if (this->charTest->Get_IsASCII() && XJ_Machine::charTypeTable[ch] == XJ_Machine::CharType::Space) {
				this->invalidChar = false;
				continue;
			}
			if (this->invalidChar == false) {
				this->tokens.push_back(XJ_Token::Token{ this->pos,0,static_cast<int>(XJ_Token::Type::invalid),false });
			}
			empty = false;
			this->accept = false;
			this->group.push_back(new XJ_Machine::Keyword(this->strNode_key, XJ_Token::Type::key));
			this->group.push_back(new XJ_Machine::Keyword(this->strNode_op, XJ_Token::Type::op));
			this->group.push_back(new XJ_Machine::Keyword(this->strNode_delimiter, XJ_Token::Type::delimiter));
			this->group.push_back(new XJ_Machine::Number);
			this->group.push_back(new XJ_Machine::Anno);
			this->group.push_back(new XJ_Machine::Identity);
			this->group.push_back(new XJ_Machine::String);
		}
		XJ_Token::Token* token = &this->tokens.back();
		std::vector<XJ_Machine::Base*>success;
		std::vector<XJ_Machine::Base*>fail;
		for (auto p = this->group.begin(); p != this->group.end(); ++p) {
			XJ_Machine::Base* stat = *p;
			auto flag = stat->Opt_NextChar(ch);
			if (flag)
				success.push_back(stat);
			else
				fail.push_back(stat);
		}
		if (success.size() == 0) {//全军覆没，在其中挑选最可能的结果
			if (this->accept) {
				bool flag = false;
				for (auto p = fail.begin(); p != fail.end(); ++p) {
					auto stat = *p;
					if (stat->Get_IsValid()) {
						flag = true;
						token->type = static_cast<int>(stat->Get_TokenType());
						token->valid = true;
						break;
					}
				}
				if (flag == false) {//没有一个符合的，说明此时这个token是非法的，需要对这个特殊的token单独分析。
					//这里就懒得分析了，直接挂valid=false
					auto stat = fail.front();
					token->valid = stat->Get_IsValid();
				}
				--i;
				asciiTest_DonMove = true;
			}
			else {
				this->invalidChar = true;
			}
			empty = true;
		}
		else {
			auto stat = success.front();
			token->type = static_cast<int>(stat->Get_TokenType());
			this->accept = true;
			if (this->invalidChar) {
				this->invalidChar = false;
			}
		}
		if (!asciiTest_DonMove) {
			token->length = pos - token->start+1;
		}
		for (auto p = fail.begin(); p != fail.end(); ++p) {
			delete* p;
		}
		this->group = success;
	}
	if (isFinalStr) {
		if (this->group.size()) {
			XJ_Machine::Base* stat = nullptr;
			for (auto p = this->group.begin(); p != this->group.end(); ++p) {
				if ((*p)->Get_IsValid()) {
					stat = *p;
					break;
				}
			}
			if (stat == nullptr)
				stat = this->group.front();
			auto token = &this->tokens.back();
			token->type = static_cast<int>(stat->Get_TokenType());
			token->valid = stat->Get_IsValid();
		}
	}
}


void XJ_LexemeAnaylse::Set_CharMode(bool flag){
	this->useCharPos = flag;
	this->pos = flag?0:-1;
}



