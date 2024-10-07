#pragma once
#include"./XJ_Machine.h"
#include"./XJ_Machine_Base.h"

namespace XJ_Machine {
	class Identity :public Base {//标识符匹配
	private:
		bool isFirst = true;
	public:
		Identity();
		virtual bool Opt_NextChar(char ch);
	};

};
