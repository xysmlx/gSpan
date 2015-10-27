#include "firsthead.h"
#include "Solver.h"

Solver solver;

void init()
{
	solver.init();
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
#ifdef xysmlx
	freopen("in.txt", "r", stdin);
#endif

	init();
	input();
	solve();
	output();
	return 0;
}