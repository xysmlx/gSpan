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
	int la, lab, lb;
	DFSCodeNode(int _a = -1, int _b = -1, int _la = -1, int _lab = -1, int _lb = -1): a(_a), b(_b), la(_la), lab(_lab), lb(_lb) {}
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

class Graph
{
public:
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

class InputFilter
{
public:
	const static int maxv = 1010;
	const static int maxe = 5010;

	int therK;

	struct Node
	{
		int id;
		int cnt;
		Node(int _id = 0, int _cnt = 0): id(_id), cnt(_cnt) {}
		bool operator < (const Node &o) const
		{
			return cnt > o.cnt;
		}
	};

	int cntv[maxv], cnte[maxe];
	int mpv[maxv], mpe[maxe];
	vector<Vertex> vecv;
	vector<Edge> vece;
	vector<int> listv, liste;
	vector<Node> filterv, filtere;

	void init()
	{
		memset(cntv, 0, sizeof(cntv));
		memset(cnte, 0, sizeof(cnte));
		memset(mpv, -1, sizeof(mpv));
		memset(mpe, -1, sizeof(mpe));
		vecv.clear();
		vece.clear();
		listv.clear();
		liste.clear();
		filterv.clear();
		filtere.clear();
	}
	void addv(int id, int label)
	{
		vecv.pb(Vertex(id, label));
		if (cntv[label] == 0) listv.pb(label);
		cntv[label]++;
	}
	void adde(int u, int v, int label)
	{
		vece.pb(Edge(u, v, label));
		if (cnte[label] == 0) liste.pb(label);
		cnte[label]++;
	}
	void filterV()
	{
		for (int i = 0; i < listv.size(); i++)
			if (cntv[listv[i]] >= therK)
				filterv.pb(Node(listv[i], cntv[listv[i]]));
		sort(filterv.begin(), filterv.end());
		for (int i = 0; i < filterv.size(); i++)
			mpv[filterv[i]] = i + 2;
	}
	void filterE()
	{
		for (int i = 0; i < liste.size(); i++)
			if (cnte[liste[i]] >= therK)
				filtere.pb(Node(liste[i], cnte[liste[i]]));
		sort(filtere.begin(), filtere.end());
		for (int i = 0; i < filtere.size(); i++)
			mpe[filtere[i]] = i + 2;
	}
	void filter(int _therK)
	{
		therK = _therK;
		filterV();
		filterE();
	}
};

class Solver
{
public:
	const static int maxGraph = 10010;
	const static int therK = 1; //

	InputFilter inputfilter;
	Graph graph[maxGraph]; // 0 to cntGraph-1
	int cntGraph;

	void init()
	{
		cntGraph = 0;
		for (int i = 0; i < maxGraph; i++)
			graph[i] = Graph();
		inputfilter.init();
	}
	void execInputGraph(int n)
	{
		inputfilter.filter(therK);
		//

		inputfilter.init();
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
				execInputGraph(n);
				sscanf(buff, "t # %d", &n);
				cntGraph++;
			}
			else if (buff[0] == 'v')
			{
				sscanf(buff, "v %d %d", &m, &l);
				inputfilter.addv(m, l);
			}
			else if (buff[0] == 'e')
			{
				sscanf(buff, "e %d %d %d", &p, &q, &l);
				inputfilter.adde(p, q, l);
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