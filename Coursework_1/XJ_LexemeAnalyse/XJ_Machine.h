#pragma once

namespace XJ_Machine {
	class Base;//基类
	class Anno;//注释匹配
	class Identity;//关键字、运算符等固定字串的匹配
	class Keyword;//关键词匹配
	class Number;//数值匹配
	class String;//字符串匹配
	enum class CharType {//列举大多数字符，其余的小部分字符如下划线、小数点等需要自行判断
		Space,//空白字符，包括回车，一些场合需要提前对回车进行判断
		Digit,//数字0-9
		Letter,//字母a-zA-Z
		Separator,//分隔符()[]{}
		Underline,//下划线
		Dot,//小数点
		Other,//其他字符
	};
	bool Opt_InitCharTypeTable(CharType table[128]);//初始化字符类型表，数组长度为128
	extern CharType charTypeTable[128];//显式声明extern，这样就可以避免重定义。初始化工作交由XJ_Machine.cpp文件完成，利用到C/C++的语言特性
};


