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
		else if (this->isBackward() && o.isBackward() && b == o.b&&lab < o.lab) return 1;
		else if (this->isForward() && o.isForward() && a > o.a) return 1;
		else if (this->isForward() && o.isForward() && a == o.a&&la < o.la) return 1;
		else if (this->isForward() && o.isForward() && a == o.a &&la == o.la&&lab < o.lab) return 1;
		else if (this->isForward() && o.isForward() && a == o.a &&la == o.la&&lab == o.lab&&lb < o.lb) return 1;
		return 0;
	}
	bool operator == (const DFSCodeNode &o) const
	{
		return a == o.a&&b == o.b&&la == o.la&&lab == o.lab&&lb == o.lb;
	}
};

struct DFSCode
{
	void init()
	{
		dfsCodeList.clear();
	}
	void Convert2Graph()
	{
		//
	}
	bool operator < (const DFSCode &o) const
	{
		int minsize = min(dfsCodeList.size(), o.dfsCodeList.size());
		for (int i = 0;i < minsize;i++)
			if (dfsCodeList[i] < o.dfsCodeList[i]) return 1;
		return dfsCodeList.size() < o.dfsCodeList.size();
	}

	vector<DFSCodeNode> dfsCodeList;
};

#endif
