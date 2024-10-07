#pragma once
#include"./XJ_Machine.h"
#include"./XJ_Machine_Base.h"

namespace XJ_Machine {
	class Anno :public Base {//注释匹配
	private:
		int depth = 0;//块注释深度，为0则是行注释
		bool isSecond = false;//判断当前是否对应注释的第二个符号
		bool passOne = false;//使用反斜杠，跳过一个字符
		int emphasis = 0;//注释开头的强调符号个数，例如!和*
		int step = 0;
	public:
		Anno();
		virtual bool Opt_NextChar(char ch);
	};
};
