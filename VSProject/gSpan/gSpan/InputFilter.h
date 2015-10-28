#ifndef INPUTFILTER_H
#define INPUTFILTER_H

#include "head.h"
#include "Graph.h"

class InputFilter
{
public:
	struct Node
	{
		int label;
		int cnt;
		Node(int _label = 0, int _cnt = 0) : label(_label), cnt(_cnt) {}
		bool operator < (const Node &o) const // greater
		{
			return cnt > o.cnt;
		}
	};

public:
	void init();
	void addv(int id, int label);
	void adde(int u, int v, int label);
	void filterV();
	void filterE();
	void filter();

public:
	const static int maxv = 1010;
	const static int maxe = 5010;

public:
	int cntv[maxv], cnte[maxe];
	int mpv[maxv], mpe[maxe];
	vector<Vertex> vecv;
	vector<Edge> vece;
	vector<int> listv, liste;
	vector<Node> filterv, filtere;
	vector<string> inputStr;
};

#endif