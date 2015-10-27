#ifndef INPUTFILTER_H
#define INPUTFILTER_H

#include "firsthead.h"
#include "Vertex.h"
#include "Edge.h"

class InputFilter
{
public:
	struct Node
	{
		int id;
		int cnt;
		Node(int _id = 0, int _cnt = 0) : id(_id), cnt(_cnt) {}
		bool operator < (const Node &o) const
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
};

#endif