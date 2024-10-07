
#include"./XJ_StringTreeNode.h"

#include<locale>
int main() {
	setlocale(LC_ALL, ".utf8");

	XJ_StringTreeNode root;
	root.Opt_NewBranch({
		"ABCDE",
		"ABC"
		});

	std::vector<const char*>test = {
		"ABCDEF",
		"ABCDE",
		"ABCD",
		"ABC",
		"AB",
	};
	printf_s("匹配成功的字串会用箭头标识\n\n");
	for (auto str = test.begin(); str != test.end(); ++str) {
		XJ_StringTreeNode* curr = &root;
		for (auto i = 0; (*str)[i]; ++i) {
			curr = curr->Get_NextNode((*str)[i]);
			if (curr == nullptr)
				break;
		}
		if (curr && curr->Get_IsFinalNode())
			printf_s("%4s ", "->");
		else
			printf_s("%4s ", "");
		printf_s("%s\n", *str);
	}
	return 0;
}


