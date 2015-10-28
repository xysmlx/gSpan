#ifndef GSPAN_H
#define GSPAN_H

#include "firsthead.h"
#include "InputFilter.h"
#include "Graph.h"
#include "DFSCode.h"

class GSPAN
{
public:
	struct EdgeCMP // Cmp of map<>
	{
		bool operator ()(const Edge &o1, const Edge &o2) const
		{
			if (o1.u == o2.u&&o1.v == o2.v) return o1.label < o2.label;
			if (o1.u == o2.u) return o1.v < o2.v;
			return o1.u < o2.u;
		}
	};
	struct VertexCMP // Cmp of map<>
	{
		bool operator ()(const Vertex &o1, const Vertex &o2) const
		{
			return o1.label < o2.label;
		}
	};
	struct FreqEdgeSortNode
	{
		Edge e;
		int cnt;
		FreqEdgeSortNode(Edge _e = Edge(), int _cnt = 0) :e(_e), cnt(_cnt) {}
		bool operator < (const FreqEdgeSortNode &o) const // greater
		{
			return cnt > o.cnt;
		}
	};

public:
	GSPAN() {}
	void init();
	void input(const InputFilter &_inputFilter, double _minSup); // Build relabeled graph
	void GenSeedSet(); // Generate the seed edge set
	void NextDFSCode(const DFSCode &dfsCode); // Find the next dfscode and update the rightpath
	bool PatternInGraph(const Graph &graph, const DFSCode &dfscode); // Is this pattern in this graph?
	void SubMining(); // Sub-Mining Procedure
	void gSpan(); // Run gSpan

public:
	const static int maxGraph = 10010; // Maximum graph number of graph set

public:
	ofstream out;

	double minSup; // minimum support
	int minSupDeg; // minSup * cntGraph

	Graph graph[maxGraph]; // 0 to cntGraph-1
	int cntGraph; // Num of graphs in the graph set

	map<Edge, int, EdgeCMP> freqEdgeCnt; // Count edge's frequency
	set<Edge, EdgeCMP> freqEdgeVis; // Visit or not in a graph

	vector<Edge> freqEdge; // Freq edge set
};

#endif