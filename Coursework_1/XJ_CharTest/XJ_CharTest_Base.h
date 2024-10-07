#pragma once
/*
	逐字节读入，并判断字节是不是新字符的开头。
	需要继承使用，以应对不同字符集的字符判断。
*/
class XJ_CharTest_Base {
protected:
	int length = 0;//字符对应的字节长度-1，也就是该值是实际值少1的结果。不直接记录字节长度是为了优化Get_IsCharBeginByte的判断
	int rest = -1;//字符剩余个数
public:
	virtual  void Opt_NextByte(unsigned char ch) = 0;//读取下个字节
	void Opt_Reset();
	virtual bool Get_IsASCII();//如果该字节是ASCII值那么将返回真
	bool Get_IsCharBeginByte();
	bool Get_IsCharEndByte();
};
