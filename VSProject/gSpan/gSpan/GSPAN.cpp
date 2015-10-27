#include "GSPAN.h"

void GSPAN::init()
{
	cntGraph = 0;
	for (int i = 0; i < maxGraph; i++)
		graph[i] = Graph();
}

void GSPAN::input(const vector<string> &inputStr, double _minSup)
{
	minSup = _minSup;

	//

	minSupDeg = minSup*cntGraph;
}