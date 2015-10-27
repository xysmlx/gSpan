#include "Solver.h"

void Solver::init()
{
	inputFilter.init();
	gspan.init();
}
void Solver::input()
{
	char buff[110];
	int m, p, q, l;
	while (gets_s(buff))
	{
		inputFilter.inputStr.push_back(buff);
		if (strcmp(buff, "t # -1") == 0) break;
		if (buff[0] == 't')
		{
			// sscanf(buff, "t # %d", &n);
			// cntGraph++;
		}
		else if (buff[0] == 'v')
		{
			sscanf_s(buff, "v %d %d", &m, &l);
			inputFilter.addv(m, l);
		}
		else if (buff[0] == 'e')
		{
			sscanf_s(buff, "e %d %d %d", &p, &q, &l);
			inputFilter.adde(p, q, l);
		}
		else puts("Error!");
	}
	gspan.input(inputFilter, minSup);
}
void Solver::debug()
{
	//
}
void Solver::solve()
{
	//
}
void Solver::output()
{
	debug();
}