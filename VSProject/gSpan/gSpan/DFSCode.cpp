#include "DFSCode.h"

void DFSCode::init()
{
	dfsCodeList.clear();
	rightPath.clear();
}

Graph DFSCode::Convert2Graph()
{
	bool vis[Graph::maxv];
	memset(vis, 0, sizeof(vis));
	Graph graph = Graph();
	for (int i = 0;i < (int)dfsCodeList.size();i++)
	{
		Vertex tvertexa = Vertex(dfsCodeList[i].a, dfsCodeList[i].la);
		Vertex tvertexb = Vertex(dfsCodeList[i].b, dfsCodeList[i].lb);
		Edge tedge = Edge(dfsCodeList[i].a, dfsCodeList[i].b, dfsCodeList[i].lab, -1);
		if (!vis[tvertexa.id])
		{
			graph.addv(tvertexa.id, tvertexa.label);
			vis[tvertexa.id] = 1;
		}
		if (!vis[tvertexb.id])
		{
			graph.addv(tvertexb.id, tvertexb.label);
			vis[tvertexb.id] = 1;
		}
		graph.adde(tedge.u, tedge.v, tedge.label);
	}
	return graph;
}

void DFSCode::GenAllDFSCode(const Graph &g, DFSCode &ret, DFSCode now)
{
	if (now.rightPath.size() == 0)
	{
		//
	}
}

DFSCode DFSCode::FindMinDFSCode()
{
	Graph graph = Convert2Graph();
	DFSCode ret = *this;
	DFSCode tmp = DFSCode();
	GenAllDFSCode(graph, ret, tmp);
	return ret;
}

bool DFSCode::isMinDFSCode()
{
	return FindMinDFSCode() < *this;
}