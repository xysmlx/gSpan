#ifndef DFSCODENODE_H
#define DFSCODENODE_H

#include "firsthead.h"

struct DFSCodeNode
{
	int a, b;
	int la, lab, lb;
	DFSCodeNode(int _a = -1, int _b = -1, int _la = -1, int _lab = -1, int _lb = -1) : a(_a), b(_b), la(_la), lab(_lab), lb(_lb) {}
	~DFSCodeNode() {}
	bool isForward() const
	{
		return a < b;
	}
	bool isBackward() const
	{
		return a > b;
	}

	bool operator < (const DFSCodeNode &o) const
	{
		if (this->isBackward() && o.isForward()) return 1;
		else if (this->isBackward() && o.isBackward() && b < o.b) return 1;
		return 0;
	}
	bool operator == (const DFSCodeNode &o) const
	{
		return 0;
	}
};

#endif
