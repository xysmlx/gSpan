#include "DFSCode.h"

void DFSCode::init()
{
	dfsCodeList.clear();
	rightPath.clear();
}

void DFSCode::output()
{
	cout << "DFSCode::output: " << endl;
	for (int i = 0;i < (int)dfsCodeList.size();i++)
	{
		DFSCodeNode t = dfsCodeList[i];
		cout << t.a << " " << t.b << " " << t.la << " " << t.lab << " " << t.lb << endl;
	}
	cout << endl;
}

Graph DFSCode::Convert2Graph()
{
	bool vis[Graph::maxv];
	memset(vis, 0, sizeof(vis));
	Graph graph = Graph();
	for (int i = 0;i < (int)dfsCodeList.size();i++)
	{
		Vertex tvertexa = Vertex(dfsCodeList[i].a, dfsCodeList[i].la);
		Vertex tvertexb = Vertex(dfsCodeList[i].b, dfsCodeList[i].lb);
		Edge tedge = Edge(dfsCodeList[i].a, dfsCodeList[i].b, dfsCodeList[i].lab, -1);
		if (!vis[tvertexa.id])
		{
			graph.addv(tvertexa.id, tvertexa.label);
			vis[tvertexa.id] = 1;
		}
		if (!vis[tvertexb.id])
		{
			graph.addv(tvertexb.id, tvertexb.label);
			vis[tvertexb.id] = 1;
		}
		graph.adde(tedge.u, tedge.v, tedge.label);
	}
	return graph;
}

bool DFSCode::GenMinDFSCode(Graph &g, DFSCode &ret, int now)
{
	//puts("GenMinDFSCode");
	//ret.output();
	if (ret.dfsCodeList.size() > 0 && *this < ret) return 1;
	if ((int)ret.dfsCodeList.size() == (g.en / 2)) return 1;
	// Find min forward edge
	int nxt = -1;
	DFSCodeNode sel;
	DFSCodeNode tmp;
	for (int i = g.head[now];~i;i = g.edge[i].next)
	{
		Edge e = g.edge[i];
		if (g.vtx[e.v].seq == -1)
		{
			if (sel.a == -1)
			{
				sel = DFSCodeNode(g.vtx[now].seq, g.vtx[now].seq + 1, g.vtx[now].label, e.label, g.vtx[e.v].label);
				nxt = e.v;
			}
			tmp = DFSCodeNode(g.vtx[now].seq, g.vtx[now].seq + 1, g.vtx[now].label, e.label, g.vtx[e.v].label);
			if (tmp < sel)
			{
				sel = tmp;
				nxt = e.v;
			}
		}
	}
	//cout << "nxt: " << nxt << endl;
	if (nxt == -1) return 0;
	assert(nxt != -1); // Bugs here
	ret.dfsCodeList.push_back(sel);

	// Insert backward edge
	g.vtx[nxt].seq = g.vtx[now].seq + 1;
	vector<DFSCodeNode> back;
	for (int i = g.head[nxt];~i;i = g.edge[i].next)
	{
		Edge e = g.edge[i];
		if (g.vtx[e.v].seq != -1 && e.v != now)
			back.push_back(DFSCodeNode(g.vtx[e.u].seq, g.vtx[e.v].seq, g.vtx[e.u].label, e.label, g.vtx[e.v].label));
	}
	sort(back.begin(), back.end());
	for (int i = 0;i < (int)back.size();i++)
		ret.dfsCodeList.push_back(back[i]);

	// Continue
	ret.rightPath.push_back(make_pair(g.vtx[nxt].seq, g.vtx[nxt].label));
	bool tflag = GenMinDFSCode(g, ret, nxt);
	if (tflag) return 1;

	// Backtrack
	ret.rightPath.pop_back();
	return 0;
}

DFSCode DFSCode::FindMinDFSCode()
{
	//puts("FindMinDFSCode:");
	//this->output();
	Graph g = Convert2Graph();
	DFSCode ret = *this;
	DFSCode tmp;
	int minLabel = 0;
	for (int i = 0;i < g.vn;i++)
		minLabel = min(minLabel, g.vtx[i].label);
	vector<int> st;
	for (int i = 0;i < g.vn;i++)
		if (g.vtx[i].label == g.vtx[i].label)
			st.push_back(i);
	//cout << "st.size(): " << st.size() << endl;
	for (int i = 0;i < (int)st.size(); i++)
	{
		//cout << "st[i]: " << i << endl;
		for (int j = 0;j < g.vn;j++)
			g.vtx[j].seq = -1;
		tmp = DFSCode();
		tmp.rightPath.push_back(make_pair(0, g.vtx[i].label));
		g.vtx[i].seq = 0;
		GenMinDFSCode(g, tmp, st[i]);
		/*cout << "Compare begin:" << endl;
		ret.output();
		tmp.output();
		cout << "Compare end:" << endl;*/
		if (tmp.dfsCodeList.size() >= ret.dfsCodeList.size())
		{
			ret = min(ret, tmp);
			//system("pause");
		}
	}
	return ret;
}

bool DFSCode::isMinDFSCode()
{
	/*this->output();
	if (FindMinDFSCode() == *this)
	{
		cout << "+++Mincode+++" << endl;
		this->output();
		cout << "---Mincode---" << endl;
	}*/
	return FindMinDFSCode() == *this;
}