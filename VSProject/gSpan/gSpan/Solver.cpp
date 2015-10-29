#include "Solver.h"

void Solver::init(string _inputPath, double _minSup)
{
	inputFilter.init();
	gspan.init();
	inputPath = _inputPath;
	minSup = _minSup;
}
void Solver::input()
{
	string buff;
	int m, p, q, l;
	ifstream in(inputPath);
	while (getline(in, buff))
	{
		inputFilter.inputStr.push_back(buff);
		if (buff == "t # -1") break;
		if (buff[0] == 't')
		{
			// sscanf(buff, "t # %d", &n);
			// cntGraph++;
		}
		else if (buff[0] == 'v')
		{
			sscanf(buff.c_str(), "v %d %d", &m, &l);
			inputFilter.addv(m, l);
		}
		else if (buff[0] == 'e')
		{
			sscanf(buff.c_str(), "e %d %d %d", &p, &q, &l);
			inputFilter.adde(p, q, l);
		}
		else puts("Error!");
	}
	stTime = clock();
	inputFilter.filter();
	gspan.input(inputFilter, minSup);
}
void Solver::debug()
{
	cout << gspan.freqEdge.size() << endl;
}
void Solver::solve()
{
	gspan.gSpan();
}
void Solver::output()
{
	//debug();
	edTime = clock();
	cout << "Running Time: " << (double)(edTime - stTime) / (CLOCKS_PER_SEC / 1000.0) << "ms" << endl;
}