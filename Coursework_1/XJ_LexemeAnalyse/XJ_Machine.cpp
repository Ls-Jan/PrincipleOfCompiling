
#include"XJ_Machine.h"

namespace XJ_Machine {
	CharType charTypeTable[128];
	bool Opt_InitCharTypeTable(CharType table[128]){////初始化字符类型表，数组长度为128
		for (auto i = 0; i < 128; ++i)
			table[i] = CharType::Other;
		for (auto i = 'a'; i <= 'z'; ++i)
			table[i] = CharType::Letter;
		for (auto i = 'A'; i <= 'Z'; ++i)
			table[i] = CharType::Letter;
		for (auto i = '0'; i <= '9'; ++i)
			table[i] = CharType::Digit;
		table['\t'] = CharType::Space;
		table['\n'] = CharType::Space;
		table[' '] = CharType::Space;
		table['_'] = CharType::Underline;
		table['.'] = CharType::Dot;
		table['('] = CharType::Separator;
		table['['] = CharType::Separator;
		table['{'] = CharType::Separator;
		table[')'] = CharType::Separator;
		table[']'] = CharType::Separator;
		table['}'] = CharType::Separator;
		return true;
	}
	static bool initCharTypeTable = Opt_InitCharTypeTable(charTypeTable);
};



