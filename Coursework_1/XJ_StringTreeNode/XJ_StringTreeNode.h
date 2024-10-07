#pragma once

#include<vector>
#include<map>

//该结构用于字符串的快速匹配。
//不使用set<string>是因为预感使用该方式会明显拖慢效率(进行不必要的构造析构、使用哈希计算等
class XJ_StringTreeNode {
private:
	std::map<char, XJ_StringTreeNode*> nexts;
	bool isFinal = false;
public:
	~XJ_StringTreeNode();
	void Opt_NewBranch(const char* str);//增枝。该行为理应限制到根节点上。
	void Opt_NewBranch(const char* str[], int count);
	void Opt_NewBranch(std::vector<const char*> lst);
	XJ_StringTreeNode* Get_NextNode(char ch);//获取该字符对应的下一节点
	bool Get_IsFinalNode();//判断是否为终结符节点
};



