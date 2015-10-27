#include "Graph.h"

void Graph::init()
{
	memset(head, -1, sizeof(head));
	en = 0;
}

void Graph::addv(int id, int label)
{
	vtx[id] = Vertex(id, label);
	vn++;
}

void Graph::addse(int u, int v, int label)
{
	edge[en] = Edge(u, v, label, head[u]);
	head[u] = en++;
}

void Graph::adde(int u, int v, int label)
{
	addse(u, v, label);
	addse(v, u, label);
}