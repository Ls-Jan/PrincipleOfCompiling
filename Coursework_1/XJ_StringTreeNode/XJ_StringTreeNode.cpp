#include "XJ_StringTreeNode.h"

void XJ_StringTreeNode::Opt_NewBranch(std::vector<const char*> lst) {
	for (auto str = lst.begin(); str != lst.end(); ++str) {
		this->Opt_NewBranch(*str);
	}
}

void XJ_StringTreeNode::Opt_NewBranch(const char* str){
	XJ_StringTreeNode* curr = this;
	char ch = 0;
	for (auto i = 0; ; ++i) {
		ch = str[i];
		if (ch == 0)
			break;
		auto& nexts = curr->nexts;
		auto iter = nexts.find(ch);
		if (iter == nexts.end()) {
			curr = new XJ_StringTreeNode;
			nexts[ch] = curr;
		}
		else {
			curr = iter->second;
		}
	}
	curr->isFinal = true;
}

void XJ_StringTreeNode::Opt_NewBranch(const char* str[], int count){
	for (auto i = 0; i < count; ++i) {
		this->Opt_NewBranch(str[i]);
	}
}

XJ_StringTreeNode::~XJ_StringTreeNode() {
	for (auto p = this->nexts.begin(); p != this->nexts.end(); ++p) {//递归删除
		delete p->second;
	}
}

XJ_StringTreeNode* XJ_StringTreeNode::Get_NextNode(char ch) {
	auto iter = this->nexts.find(ch);
	if (iter == this->nexts.end())
		return nullptr;
	return iter->second;
}

bool XJ_StringTreeNode::Get_IsFinalNode() {
	return this->isFinal;
}
