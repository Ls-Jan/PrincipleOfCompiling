#pragma once
#include"./XJ_Machine.h"
#include"./XJ_Machine_Base.h"

namespace XJ_Machine {
	class String :public Base{//字串匹配
	private:
		int step = 0;//阶段，分为3段，引号左侧为0，内部1，右侧2
		bool passOne = false;//使用反斜杠，跳过一个字符
		int wellCount = 0;//r后接任意个#
		int charCount = 0;//字符型只能接受一个字符，依次判断是否非法
		char quote = 0;//引号，记录是单引号还是双引号
	public:
		String();
		virtual bool Opt_NextChar(char ch);
	};
};
