#include "GSPAN.h"

void GSPAN::init()
{
	cntGraph = 0;
	for (int i = 0; i < maxGraph; i++)
		graph[i] = Graph();
	freqEdge.clear();
	freqEdgeCnt.clear();
	unFreqEdge.clear();
	out = ofstream("out.txt");
}

void GSPAN::input(const InputFilter &inputFilter, double _minSup)
{
	minSup = _minSup;

	int n, m, p, q, l;
	for (int _ = 0;_ < (int)inputFilter.inputStr.size();_++)
	{
		if (inputFilter.inputStr[_][0] == 't')
		{
			sscanf(inputFilter.inputStr[_].c_str(), "t # %d", &n);
			cntGraph++;
		}
		else if (inputFilter.inputStr[_][0] == 'v')
		{
			sscanf(inputFilter.inputStr[_].c_str(), "v %d %d", &m, &l);
			graph[n].addv(m, inputFilter.mpv[l]);
			//cout << m << " " << inputFilter.mpv[l] << endl;
		}
		else if (inputFilter.inputStr[_][0] == 'e')
		{
			sscanf(inputFilter.inputStr[_].c_str(), "e %d %d %d", &p, &q, &l);
			graph[n].adde(p, q, inputFilter.mpe[l]);
			//cout << p << " " << q << " " << inputFilter.mpe[l] << endl;
		}
		else puts("Error!");
	}
	minSupDeg = (int)ceil(minSup*cntGraph);
	minSupDeg = 3; // For test
}

void GSPAN::GenSeedSet()
{
	for (int _ = 0;_ < cntGraph;_++)
	{
		freqEdgeVis.clear();
		for (int i = 0;i < graph[_].en;i++)
		{
			Edge tmp = Edge(graph[_].vtx[graph[_].edge[i].u].label, graph[_].vtx[graph[_].edge[i].v].label, graph[_].edge[i].label, -1);
			if (tmp.u > tmp.v) swap(tmp.u, tmp.v);
			if (freqEdgeVis.find(tmp) == freqEdgeVis.end())
			{
				freqEdgeCnt[tmp]++;
				freqEdgeVis.insert(tmp);
			}
		}
	}
	cout << "freqEdgeCnt Size: " << freqEdgeCnt.size() << endl;

	vector<FreqEdgeSortNode> vec;
	for (auto ite = freqEdgeCnt.begin();ite != freqEdgeCnt.end();ite++)
	{
		if (ite->second >= minSupDeg)
			vec.push_back(FreqEdgeSortNode(ite->first, ite->second));
		else unFreqEdge.push_back(ite->first);
	}
	sort(vec.begin(), vec.end());

	for (auto ite = vec.begin();ite != vec.end();ite++)
		freqEdge.push_back(ite->e);
	cout << "freqEdge Size: " << freqEdge.size() << endl;

	// For debug
	out << "Seed Set:" << endl;
	for (auto ite = freqEdge.begin();ite != freqEdge.end();ite++)
		out << ite->u << " " << ite->v << " " << ite->label << endl;
}

void GSPAN::RebuildGraph(int id)
{
	Graph ret = Graph();
	ret.vn = graph[id].vn;
	memcpy(ret.vtx, graph[id].vtx, sizeof(ret.vtx));
	for (int i = 0;i < graph[id].en;i += 2)
		if (!graph[id].edge[i].del)
			ret.adde(graph[id].edge[i].u, graph[id].edge[i].v, graph[id].edge[i].label);
	graph[id] = ret;
}

void GSPAN::DeleteEdgeFlag(const Edge &e)
{
	for (int _ = 0;_ < cntGraph;_++)
	{
		for (int i = 0;i < graph[_].en;i++)
		{
			if (graph[_].vtx[graph[_].edge[i].u].label == e.u&&
				graph[_].vtx[graph[_].edge[i].v].label == e.v&&
				graph[_].edge[i].label == e.label)
			{
				graph[_].edge[i].del = 1;
				graph[_].edge[i ^ 1].del = 1;
			}
		}
	}
}

void GSPAN::DeleteEdge(const Edge &e)
{
	DeleteEdgeFlag(e);
	for (int i = 0;i < cntGraph;i++)
		RebuildGraph(i);
}

void GSPAN::DeleteUnFreqEdge()
{
	for (int i = 0;i < (int)unFreqEdge.size();i++)
		DeleteEdgeFlag(unFreqEdge[i]);
	for (int i = 0;i < cntGraph;i++)
		RebuildGraph(i);
}

void GSPAN::NextDFSCode(const DFSCode &dfsCode)
{
	//
}

bool GSPAN::JudgePatternInGraph(Graph &graph, const DFSCode &dfscode, int ith, int now)
{
	if (ith == (int)dfscode.dfsCodeList.size()) return 1;
	if (now == -1)
	{
		for (int i = 0;i < graph.vn;i++)
		{
			if (graph.vtx[i].label == dfscode.dfsCodeList[ith].la)
			{
				graph.vtx[i].seq = dfscode.dfsCodeList[ith].a;
				if (JudgePatternInGraph(graph, dfscode, ith, i)) return 1;
				graph.vtx[i].seq = -1;
			}
		}
	}
	for (int i = graph.head[now];~i;i++)
	{
		Edge e = graph.edge[i];
		if (e.label == dfscode.dfsCodeList[ith].lab&&
			graph.vtx[e.v].label == dfscode.dfsCodeList[ith].lb)
		{
			if (dfscode.dfsCodeList[ith].b < dfscode.dfsCodeList[ith].a&&
				graph.vtx[e.v].seq != dfscode.dfsCodeList[ith].b)
				continue;
			int t = graph.vtx[e.v].seq;
			graph.vtx[e.v].seq = dfscode.dfsCodeList[ith].b;
			if (JudgePatternInGraph(graph, dfscode, ith + 1, e.v)) return 1;
			graph.vtx[e.v].seq = t;
		}
	}
	return 0;
}

bool GSPAN::isPatternInGraph(Graph graph, const DFSCode &dfscode)
{
	return JudgePatternInGraph(graph, dfscode, 0, -1);
}

bool GSPAN::isFreqPattern(const DFSCode &dfscode)
{
	int cnt = 0;
	for (int i = 0;i < cntGraph;i++)
		if (isPatternInGraph(graph[i], dfscode)) cnt++;
	return cnt >= minSupDeg;
}

void GSPAN::SubMining(const Edge &base)
{
	//
}

void GSPAN::gSpan()
{
	GenSeedSet();
	DeleteUnFreqEdge();
	for (int i = 0;i < (int)freqEdge.size();i++)
	{
		SubMining(freqEdge[i]);
		DeleteEdge(freqEdge[i]);
	}
}