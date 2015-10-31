#ifndef SOLVER_H
#define SOLVER_H

#include "head.h"
#include "InputFilter.h"
#include "GSPAN.h"

class Solver
{
public:
	void init(string _inputPath = "in.txt", double _minSup = 0.5);
	void input();
	void debug();
	void solve();
	void output();

public:
	double minSup; // minimum support

public:
	InputFilter inputFilter;
	GSPAN gspan;

	int stTime, edTime;
	string inputPath;
};

#endif