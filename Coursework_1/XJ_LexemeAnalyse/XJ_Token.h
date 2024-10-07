#pragma once
#include<vector>//原本打算使用C式数组的，一直被整蛊(具体原因懒得展开说明，有点繁杂)，怕了怕了

namespace XJ_Token {
	struct Token {
		int start;//起始位置
		int length;//字串长度
		int type;//类型
		bool valid;//是否有效
	};

	enum class Type {
		invalid=0,
		id,
		key,
		op,
		delimiter,
		val_int_2,
		val_int_8,
		val_int_10,
		val_int_16,
		val_float,
		val_char,
		val_str,
		val_str_Naive,
		val_byte,
		val_byteStr,
		val_byteStr_Naive,
		anno_Normal,
		anno_Inner,
		anno_Outer,
	};
	//枚举Type对应的名称
	extern std::vector<const char*> Name;
	namespace FixedToken {
		//关键字：http://rust.e.lntu.edu.cn/reference/keywords.html
		extern std::vector<const char*> Keywords;
		//运算符(表达式)：http://rust.e.lntu.edu.cn/reference/tokens.html#标点符号
		extern std::vector<const char*> Operators;
		//定界符：http://rust.e.lntu.edu.cn/reference/tokens.html#定界符
		extern std::vector<const char*> Delimiter;
	};
};





