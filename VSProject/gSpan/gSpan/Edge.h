#ifndef EDGE_H
#define EDGE_H

#include "firsthead.h"

struct Edge
{
	int u;
	int v;
	int label;
	int next;
	bool del;

	Edge(int _u = 0, int _v = 0, int _label = 0, int _next = -1) : u(_u), v(_v), label(_label), next(_next), del(0) {}
	~Edge() {}
};

#endif