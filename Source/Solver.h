#ifndef SOLVER_H
#define SOLVER_H

#include "firsthead.h"
#include "InputFilter.h"
#include "GSPAN.h"

class Solver
{
public:
	void init();
	void input();
	void debug();
	void solve();
	void output();

public:
	double minSup = 0.5; // minimum support

public:
	InputFilter inputFilter;
	GSPAN gspan;
};

#endif