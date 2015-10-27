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
	bool del;
	Vertex(int _id = 0, int _label = 0): id(_id), label(_label), del(0) {}
	~Vertex() {}
};

struct Edge
{
	int u;
	int v;
	int label;
	int next;
	bool del;
	Edge(int _u = 0, int _v = 0, int _label = 0, int _next = -1): u(_u), v(_v), label(_label), next(_next), del(0) {}
	~Edge() {}
};

struct DFSCodeNode
{
	int a, b;
	int la, lab, lb;
	DFSCodeNode(int _a = -1, int _b = -1, int _la = -1, int _lab = -1, int _lb = -1): a(_a), b(_b), la(_la), lab(_lab), lb(_lb) {}
	~DFSCodeNode() {}
	bool isForward() const
	{
		return a < b;
	}
	bool isBackward() const
	{
		return a > b;
	}

	bool operator < (const DFSCodeNode &o) const
	{
		if (this->isBackward() && o.isForward()) return 1;
		else if (this->isBackward() && o.isBackward() && b < o.b) return 1;
		return 0;
	}
	bool operator == (const DFSCodeNode &o) const
	{
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

public:
	const static int maxv = 1010;
	const static int maxe = 5010;

public:
	int head[maxv];
	int vn;
	int en;
	Vertex vtx[maxv]; // 0 to vn-1
	Edge edge[maxe]; // 0 to en-1
};

class InputFilter
{
public:
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

public:
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
			filterv.pb(Node(listv[i], cntv[listv[i]]));
		sort(filterv.begin(), filterv.end());
		for (int i = 0; i < filterv.size(); i++)
			mpv[filterv[i].label] = i + 2;
	}
	void filterE()
	{
		for (int i = 0; i < liste.size(); i++)
			filtere.pb(Node(liste[i], cnte[liste[i]]));
		sort(filtere.begin(), filtere.end());
		for (int i = 0; i < filtere.size(); i++)
			mpe[filtere[i].label] = i + 2;
	}
	void filter()
	{
		filterV();
		filterE();
	}

public:
	const static int maxv = 1010;
	const static int maxe = 5010;

public:
	int cntv[maxv], cnte[maxe];
	int mpv[maxv], mpe[maxe];
	vector<Vertex> vecv;
	vector<Edge> vece;
	vector<int> listv, liste;
	vector<Node> filterv, filtere;
};

class GSPAN
{
public:
	GSPAN() {}
	void init()
	{
		cntGraph = 0;
		for (int i = 0; i < maxGraph; i++)
			graph[i] = Graph();
	}
	void input(const vector<string> &inputStr, int _therK)
	{
		therK = _therK;
	}

public:
	const static int maxGraph = 10010;

public:
	double minSup; // minimum support
	int minSupDeg; // minSup*cntGraph

	Graph graph[maxGraph]; // 0 to cntGraph-1
	int cntGraph;
};

class Solver
{
public:
	void init()
	{
		inputFilter.init();
		inputStr.clear();
		gspan.init();
	}
	void input()
	{
		char buff[110];
		int n, m, p, q, l;
		while (gets(buff))
		{
			inputStr.pb(buff);
			if (strcmp(buff, "t # -1") == 0) break;
			if (buff[0] == 't')
			{
				// sscanf(buff, "t # %d", &n);
				// cntGraph++;
			}
			else if (buff[0] == 'v')
			{
				sscanf(buff, "v %d %d", &m, &l);
				inputFilter.addv(m, l);
			}
			else if (buff[0] == 'e')
			{
				sscanf(buff, "e %d %d %d", &p, &q, &l);
				inputFilter.adde(p, q, l);
			}
			else puts("Error!");
		}
		gspan.input(inputStr, minSup);
	}
	void debug()
	{
		//
	}
	void solve()
	{
		//
	}
	void output()
	{
		debug();
	}

public:
	const static double minSup = 0.5; // minimum support

public:
	InputFilter inputFilter;
	vector<string> inputStr;
	GSPAN gspan;
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