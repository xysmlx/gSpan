// #pragma comment(linker, "/STACK:102400000,102400000")
#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cmath>
#include <set>
#include <list>
#include <map>
#include <iterator>
#include <cstdlib>
#include <vector>
#include <queue>
#include <ctime>
#include <stack>
#include <algorithm>
#include <functional>
using namespace std;
typedef long long ll;
#define pb push_back
#define ROUND(x) round(x)
#define FLOOR(x) floor(x)
#define CEIL(x) ceil(x)
const int inf = 0x3f3f3f3f;

struct Vertex
{
	int id;
	int label;
	Vertex(int _id = 0, int _label = 0): id(_id), label(_label) {}
	~Vertex() {}
};

struct Edge
{
	int u;
	int v;
	int label;
	int next;
	Edge(int _u = 0, int _v = 0, int _label = 0, int _next = -1): u(_u), v(_v), label(_label), next(_next) {}
	~Edge() {}
};

struct DFSCodeNode
{
	int a, b;
	int la, lb;
	int lab;
	DFSCodeNode(int _a = -1, int _b = -1, int _la = -1, int _lab = -1, int _b = -1): a(_a), b(_b), la(_la), lab(_lab), lb(_lb) {}
	~DFSCodeNode() {}

	bool operator < (const DFSCodeNode &o) const
	{
		//
		return 0;
	}
};

struct DFSCode
{
	//
};

struct Graph
{
	const static int maxv = 1010;
	const static int maxe = 5010;

	int head[maxv];
	int vn;
	int en;
	Vertex vtx[maxv]; // 0 to vn-1
	Edge edge[maxe]; // 0 to en-1

	Graph()
	{
		memset(head, -1, sizeof(head));
		vn = 0;
		en = 0;
	}
	~Graph() {}

	void init()
	{
		memset(head, -1, sizeof(head));
		en = 0;
	}

	void addv(int id, int label)
	{
		vtx[id] = Vertex(id, label);
		vn++;
	}

	void addse(int u, int v, int label)
	{
		edge[en] = Edge(u, v, label, head[u]);
		head[u] = en++;
	}
	void adde(int u, int v, int label)
	{
		addse(u, v, label);
		addse(v, u, label);
	}
};

struct InputFilter
{
	map<int, int> mpv;
	map<int, int> mpe;
	vector<Vertex> vecv;
	vector<Edge> vece;

	void init()
	{
		mpv.clear();
		mpe.clear();
		vecv.clear();
		vece.clear();
	}
};

struct Solver
{
	const static int maxGraph = 10010;
	const static int therK = 1; //

	Graph graph[maxGraph]; // 0 to cntGraph-1
	int cntGraph;

	void init()
	{
		cntGraph = 0;
		for (int i = 0; i < maxGraph; i++)
			graph[i] = Graph();
	}
	void input()
	{
		char buff[110];
		int n, m, p, q, l;
		while (gets(buff))
		{
			if (strcmp(buff, "t # -1") == 0) break;
			if (buff[0] == 't')
			{
				sscanf(buff, "t # %d", &n);
				cntGraph++;
			}
			else if (buff[0] == 'v')
			{
				sscanf(buff, "v %d %d", &m, &l);
				graph[n].addv(m, l);
			}
			else if (buff[0] == 'e')
			{
				sscanf(buff, "e %d %d %d", &p, &q, &l);
				graph[n].adde(p, q, l);
			}
			else puts("Error!");
		}
	}
	void debug()
	{
		cout << cntGraph << endl;
		cout << graph[0].vn << " " << graph[0].en << endl;
		cout << graph[1].vn << " " << graph[1].en << endl;
	}
	void solve()
	{
		//
	}
	void output()
	{
		debug();
	}
};

Solver solver;

void init()
{
	solver.init();
}
void input()
{
	solver.input();
}
void debug()
{
	//
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