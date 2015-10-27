#ifndef GRAPH_H
#define GRAPH_H

#include "firsthead.h"
#include "Vertex.h"
#include "Edge.h"

class Graph
{
public:
	Graph()
	{
		memset(head, -1, sizeof(head));
		vn = 0;
		en = 0;
	}
	~Graph() {}

	void init();
	void addv(int id, int label);
	void addse(int u, int v, int label);
	void adde(int u, int v, int label);

public:
	const static int maxv = 1010;
	const static int maxe = 5010;

public:
	int head[maxv];
	int vn;
	int en;
	Vertex vtx[maxv]; // 0 to vn-1
	Edge edge[maxe]; // 0 to en-1
};

#endif