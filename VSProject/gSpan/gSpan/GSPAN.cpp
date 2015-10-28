#include "GSPAN.h"

void GSPAN::init()
{
	cntGraph = 0;
	for (int i = 0; i < maxGraph; i++)
		graph[i] = Graph();
	freqEdge.clear();
	freqEdgeCnt.clear();
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

void GSPAN::NextDFSCode(const DFSCode &dfsCode)
{
	//
}

bool GSPAN::PatternInGraph(const Graph &graph, const DFSCode &dfscode)
{
	//
	return 0;
}

void GSPAN::SubMining()
{
	//
}

void GSPAN::gSpan()
{
	GenSeedSet();
}