#pragma once
#include<vector>
#include"./Global.h"
#include"../XJ_CharTest/XJ_CharTest_Base.h"

class XJ_LexemeAnaylse {
private:
	std::vector<XJ_Machine::Base*>group;
	std::vector<XJ_Token::Token>tokens;
	XJ_StringTreeNode* strNode_op = nullptr;
	XJ_StringTreeNode* strNode_key = nullptr;
	XJ_StringTreeNode* strNode_delimiter = nullptr;
	XJ_CharTest_Base* charTest=nullptr;
	int pos = -1;
	bool useCharPos= false;//使用字符模式
	bool invalidChar = false;//出现了无法识别的字符
	bool accept = false;//当group能成功接收一个字符时该值为真
public:
	XJ_LexemeAnaylse();
	~XJ_LexemeAnaylse();
	std::vector<XJ_Token::Token>* Get_Tokens();
	void Set_Charset(bool isUTF8 = true, bool isUTF16BE=false, bool isGB18030 = false);
	void Opt_Reset();
	void Opt_Scan(const char str[], int count, bool isFinalStr = true);//能够连续扫描，如果片段是最后一份那可以指定isFinalStr为true，以确保最后的token能够顺利获取
	void Set_CharMode(bool flag=false);//设置字符模式，该模式为真则XJ_Token::Token中的位置以字符为基准，否则以字节为基准(默认)
};

