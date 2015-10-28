#include "head.h"
#include "Solver.h"

Solver solver;

void init()
{
	solver.init("in.txt", 0.5);
}
void input()
{
	solver.input();
}
void solve()
{
	solver.solve();
}
void output()
{
	solver.output();
}

int main()
{
	init();
	input();
	solve();
	output();

	//getchar();
	return 0;
}