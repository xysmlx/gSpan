#include "GSPAN.h"

void GSPAN::init()
{
	cntGraph = 0;
	for (int i = 0; i < maxGraph; i++)
		graph[i] = Graph();
	freqEdge.clear();
	freqEdgeCnt.clear();
}

void GSPAN::input(const InputFilter &inputFilter, double _minSup)
{
	minSup = _minSup;

	int n, m, p, q, l;
	for (int _ = 0;_ < inputFilter.inputStr.size();_++)
	{
		if (inputFilter.inputStr[_][0] == 't')
		{
			sscanf_s(inputFilter.inputStr[_].c_str(), "t # %d", &n);
			cntGraph++;
		}
		else if (inputFilter.inputStr[_][0] == 'v')
		{
			sscanf_s(inputFilter.inputStr[_].c_str(), "v %d %d", &m, &l);
			graph[n].addv(m, inputFilter.mpv[l]);
		}
		else if (inputFilter.inputStr[_][0] == 'e')
		{
			sscanf_s(inputFilter.inputStr[_].c_str(), "e %d %d %d", &p, &q, &l);
			graph[n].adde(p, q, inputFilter.mpe[l]);
		}
		else puts("Error!");
	}

	minSupDeg = minSup*cntGraph;
}

void GSPAN::GenSeedSet()
{
	for (int _ = 0;_ < cntGraph;_++)
	{
		freqEdgeVis.clear();
		for (int i = 0;i < graph[_].en;i += 2)
		{
			Edge tmp = Edge(graph[_].edge[i].u, graph[_].edge[i].v, graph[_].edge[i].label, -1);
			if (freqEdgeVis.find(tmp) == freqEdgeVis.end())
			{
				freqEdgeCnt[tmp]++;
				freqEdgeVis.insert(tmp);
			}
		}
	}

	vector<FreqEdgeSortNode> vec;
	for (auto ite = freqEdgeCnt.begin();ite != freqEdgeCnt.end();ite++)
	{
		if (ite->second > minSupDeg)
			vec.push_back(FreqEdgeSortNode(ite->first, ite->second));
	}
	sort(vec.begin(), vec.end());

	for (auto ite = vec.begin();ite != vec.end();ite++)
		freqEdge.push_back(ite->e);
}

void GSPAN::SubMining()
{
	//
}

void GSPAN::gSpan()
{
	GenSeedSet();
}