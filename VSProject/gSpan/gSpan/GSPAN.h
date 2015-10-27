#ifndef GSPAN_H
#define GSPAN_H

#include "firsthead.h"
#include "Graph.h"

class GSPAN
{
public:
	GSPAN() {}
	void init();
	void input(const vector<string> &inputStr, double _minSup);

public:
	const static int maxGraph = 10010;

public:
	double minSup; // minimum support
	int minSupDeg; // minSup * cntGraph

	Graph graph[maxGraph]; // 0 to cntGraph-1
	int cntGraph;
};

#endif