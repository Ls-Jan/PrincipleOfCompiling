#pragma once

//这个类用于字节判断，主要区分一个字节是否为ASCII
class XJ_ASCIITest {
private:
	int restCount = 0;
	int fixedCount = 1;
	int followCount = 0;
public:
	/*
		fixedCount指定n个连续字节视作一组，例如UTF-16总以2个字节为一字符、UTF-32以4个字节为一字符；
		followCount指定在出现大于127的字节时与将后面连跟的n个字节一同视作一组，在fixedCount=1时有效，例如GB18030需指定为1，因为多字节字符总是一大一小成组的，例如𬌗0x9931D239；

		如果文件是utf-8编码，那么两个参数依次指定为1和0；
		如果是UTF-16编码，依次指定2和0；
		如果是GB18030编码，依次指定1和1；
	*/
	void Opt_Start(int fixedCount = 1, int followCount = 0);
	void Opt_Next(char ch);//读取下一字节
	void Opt_Reset();//重置状态
	bool Get_IsASCII();//判断是否为独立的ASCII字符
};



class XJ_CharTest {

};



