#include "GSPAN.h"

void GSPAN::init()
{
	cntGraph = 0;
	for (int i = 0; i < maxGraph; i++)
		graph[i] = Graph();
	freqEdge.clear();
	freqEdgeCnt.clear();
	unFreqEdge.clear();
	//cntFreqPattern = 0;
	freqPattern.clear();
	out.open("out.txt", ios::out);
}

void GSPAN::input(const InputFilter &inputFilter, double _minSup)
{
	minSup = _minSup;

	int n, m, p, q, l;
	for (int _ = 0;_ < (int)inputFilter.inputStr.size() - 1;_++)
	{
		if (inputFilter.inputStr[_][0] == 't')
		{
			sscanf(inputFilter.inputStr[_].c_str(), "t # %d", &n);
			cntGraph++;
		}
		else if (inputFilter.inputStr[_][0] == 'v')
		{
			sscanf(inputFilter.inputStr[_].c_str(), "v %d %d", &m, &l);
			graph[n].addv(m, inputFilter.mpv[l]);
			//cout << m << " " << inputFilter.mpv[l] << endl;
		}
		else if (inputFilter.inputStr[_][0] == 'e')
		{
			sscanf(inputFilter.inputStr[_].c_str(), "e %d %d %d", &p, &q, &l);
			graph[n].adde(p, q, inputFilter.mpe[l]);
			//cout << p << " " << q << " " << inputFilter.mpe[l] << endl;
		}
		else puts("Error!");
	}
	minSupDeg = (int)ceil(minSup*cntGraph);
	//cout << minSup*cntGraph << " " << minSupDeg << endl;
	//minSupDeg = 3; // For test
}

void GSPAN::GenSeedSet() // OK, No bugs
{
	for (int _ = 0;_ < cntGraph;_++)
	{
		freqEdgeVis.clear();
		for (int i = 0;i < graph[_].en;i++)
		{
			Edge tmp = Edge(graph[_].vtx[graph[_].edge[i].u].label, graph[_].vtx[graph[_].edge[i].v].label, graph[_].edge[i].label, -1);
			if (tmp.u > tmp.v) swap(tmp.u, tmp.v);
			if (freqEdgeVis.find(tmp) == freqEdgeVis.end())
			{
				freqEdgeCnt[tmp]++;
				freqEdgeVis.insert(tmp);
			}
		}
	}
	cout << "freqEdgeCnt Size: " << freqEdgeCnt.size() << endl;

	vector<FreqEdgeSortNode> vec;
	for (auto ite = freqEdgeCnt.begin();ite != freqEdgeCnt.end();ite++)
	{
		if (ite->second >= minSupDeg)
			vec.push_back(FreqEdgeSortNode(ite->first, ite->second));
		else unFreqEdge.push_back(ite->first);
	}
	sort(vec.begin(), vec.end());

	for (auto ite = vec.begin();ite != vec.end();ite++)
		freqEdge.push_back(ite->e);
	cout << "freqEdge Size: " << freqEdge.size() << endl;

	// For debug
	out << "Seed Set:" << endl;
	for (auto ite = freqEdge.begin();ite != freqEdge.end();ite++)
		out << ite->u << " " << ite->v << " " << ite->label << endl;
}

void GSPAN::RebuildGraph(int id)
{
	Graph ret = Graph();
	ret.vn = graph[id].vn;
	memcpy(ret.vtx, graph[id].vtx, sizeof(ret.vtx));
	for (int i = 0;i < graph[id].en;i += 2)
		if (!graph[id].edge[i].del)
			ret.adde(graph[id].edge[i].u, graph[id].edge[i].v, graph[id].edge[i].label);
	graph[id] = ret;
}

void GSPAN::DeleteEdgeFlag(const Edge &e)
{
	for (int _ = 0;_ < cntGraph;_++)
	{
		for (int i = 0;i < graph[_].en;i++)
		{
			if (graph[_].vtx[graph[_].edge[i].u].label == e.u&&
				graph[_].vtx[graph[_].edge[i].v].label == e.v&&
				graph[_].edge[i].label == e.label)
			{
				graph[_].edge[i].del = 1;
				graph[_].edge[i ^ 1].del = 1;
			}
		}
	}
}

void GSPAN::DeleteEdge(const Edge &e)
{
	DeleteEdgeFlag(e);
	for (int i = 0;i < cntGraph;i++)
		RebuildGraph(i);
}

void GSPAN::DeleteUnFreqEdge()
{
	for (int i = 0;i < (int)unFreqEdge.size();i++)
		DeleteEdgeFlag(unFreqEdge[i]);
	for (int i = 0;i < cntGraph;i++)
		RebuildGraph(i);
}

bool GSPAN::JudgePatternInGraph(Graph &graph, const DFSCode &dfscode, int ith, int now) // OK, No bugs
{
	//cout << "now: " << now << " " << graph.vtx[now].label << " " << graph.vtx[now].seq << endl;
	if (ith == (int)dfscode.dfsCodeList.size()) return 1;
	if (now == -1) // From initial vertex
	{
		for (int i = 0;i < graph.vn;i++)
		{
			if (graph.vtx[i].label == dfscode.dfsCodeList[ith].la)
			{
				graph.vtx[i].seq = dfscode.dfsCodeList[ith].a;
				if (JudgePatternInGraph(graph, dfscode, ith, i)) return 1;
				graph.vtx[i].seq = -1;
			}
		}
		return 0;
	}

	if (dfscode.dfsCodeList[ith].isBackward()) // Backward
	{
		for (int i = graph.head[now];~i;i = graph.edge[i].next)
		{
			Edge e = graph.edge[i];
			if (e.label == dfscode.dfsCodeList[ith].lab&&
				graph.vtx[e.v].label == dfscode.dfsCodeList[ith].lb&&
				graph.vtx[e.v].seq == dfscode.dfsCodeList[ith].b)
			{
				if (JudgePatternInGraph(graph, dfscode, ith + 1, now)) return 1;
			}
		}
		return 0;
	}
	else // Forward
	{
		for (int u = 0;u < graph.vn;u++)
		{
			if (graph.vtx[u].seq == dfscode.dfsCodeList[ith].a)
			{
				for (int i = graph.head[u];~i;i = graph.edge[i].next)
				{
					Edge e = graph.edge[i];
					if (e.label == dfscode.dfsCodeList[ith].lab&&
						graph.vtx[e.v].label == dfscode.dfsCodeList[ith].lb&&
						graph.vtx[e.v].seq == -1)
					{
						graph.vtx[e.v].seq = dfscode.dfsCodeList[ith].b;
						if (JudgePatternInGraph(graph, dfscode, ith + 1, e.v)) return 1;
						graph.vtx[e.v].seq = -1;
					}
				}
			}
		}
	}

	return 0;
}

// Has bugs, but higher performence. TO SOLVE
//bool GSPAN::JudgePatternInGraph(Graph &graph, const DFSCode &dfscode, int ith, int now)
//{
//	cout << "now: " << now << " " << graph.vtx[now].label << " " << graph.vtx[now].seq << endl;
//	if (ith == (int)dfscode.dfsCodeList.size()) return 1;
//	if (now == -1) // From initial vertex
//	{
//		for (int i = 0;i < graph.vn;i++)
//		{
//			if (graph.vtx[i].label == dfscode.dfsCodeList[ith].la)
//			{
//				graph.vtx[i].seq = dfscode.dfsCodeList[ith].a;
//				if (JudgePatternInGraph(graph, dfscode, ith, i)) return 1;
//				graph.vtx[i].seq = -1;
//			}
//		}
//		return 0;
//	}
//
//	if (dfscode.dfsCodeList[ith].isBackward()) // Backward
//	{
//		for (int i = graph.head[now];~i;i = graph.edge[i].next)
//		{
//			Edge e = graph.edge[i];
//			if (e.label == dfscode.dfsCodeList[ith].lab&&
//				graph.vtx[e.v].label == dfscode.dfsCodeList[ith].lb&&
//				graph.vtx[e.v].seq == dfscode.dfsCodeList[ith].b)
//			{
//				if (JudgePatternInGraph(graph, dfscode, ith + 1, now)) return 1;
//			}
//		}
//		return 0;
//	}
//	else // Forward
//	{
//		for (int i = graph.head[now];~i;i = graph.edge[i].next)
//		{
//			Edge e = graph.edge[i];
//			if (e.label == dfscode.dfsCodeList[ith].lab&&
//				graph.vtx[e.v].label == dfscode.dfsCodeList[ith].lb&&
//				graph.vtx[e.v].seq == -1)
//			{
//				graph.vtx[e.v].seq = dfscode.dfsCodeList[ith].b;
//				if (JudgePatternInGraph(graph, dfscode, ith + 1, e.v)) return 1;
//				graph.vtx[e.v].seq = -1;
//			}
//		}
//	}
//
//	return 0;
//}

bool GSPAN::isPatternInGraph(Graph graph, const DFSCode &dfscode)
{
	return JudgePatternInGraph(graph, dfscode, 0, -1);
}

void GSPAN::SolveFreqPattern(const DFSCode &dfscode)
{
	freqPattern.push_back(dfscode);
	/*out << "Pattern #" << cntFreqPattern++ << ": " << endl;
	for (int i = 0;i < (int)dfscode.dfsCodeList.size();i++)
	{
		DFSCodeNode t = dfscode.dfsCodeList[i];
		out << t.a << " " << t.b << " " << t.la << " " << t.lab << " " << t.lb << endl;
	}*/
}

bool GSPAN::isFreqPattern(const DFSCode &dfscode) // OK, No bugs
{
	//puts("++isFreqPattern?++");
	int cnt = 0;
	for (int i = 0;i < cntGraph;i++)
		if (isPatternInGraph(graph[i], dfscode)) cnt++;
	DFSCode t = dfscode;
	//t.output();
	/*cout << "pattern cnt: " << cnt << endl;
	puts("--isFreqPattern?--");*/
	if (cnt >= minSupDeg)
	{
		SolveFreqPattern(dfscode);
		return 1;
	}
	return 0;
}

void GSPAN::BuildPattern(DFSCode &dfscode, int loc, int backloc, int maxseq)
{
	//dfscode.output();
	if (backloc == -1) // Generate forward edge
	{
		//puts("backloc == -1");
		for (int i = 0;i < (int)freqEdge.size();i++)
		{
			// Extend a new dfscodenode
			pair<int, int> v = dfscode.rightPath[loc];
			Edge e = freqEdge[i];
			if (e.u != v.second&&e.v != v.second) continue;
			if (e.u != v.second) swap(e.u, e.v);
			dfscode.dfsCodeList.push_back(DFSCodeNode(v.first, maxseq + 1, e.u, e.label, e.v));
			dfscode.rightPath.push_back(make_pair(maxseq + 1, e.v));

			// Test the new dfscode
			//cout << "Test the new dfscode" << endl;
			//dfscode.output();
			if (!dfscode.isMinDFSCode() || !isFreqPattern(dfscode)) // No
			{
				/*puts("++No, cut.++");
				dfscode.output();
				puts("--No, cut.--");*/

				dfscode.dfsCodeList.pop_back();
				dfscode.rightPath.pop_back();

				// Backtrack in rightpath
				if (dfscode.rightPath.size() == 1) return; // Cannot bactrack in rightpath
				vector<pair<int, int> > t1;
				t1.push_back(dfscode.rightPath[(int)dfscode.rightPath.size() - 1]);
				dfscode.rightPath.pop_back();
				for (int i = (int)dfscode.rightPath.size() - 1;i >= 0;i--) // Find a vertex to extend in rightpath
				{
					int cnt = 0;
					for (int j = 0;j < (int)dfscode.dfsCodeList.size();j++)
					{
						DFSCodeNode t = dfscode.dfsCodeList[j];
						if (t.a < t.b&&t.a == dfscode.rightPath[i].first)
							cnt++;
					}
					if (cnt < 2) break;
					t1.push_back(dfscode.rightPath[i]);
					dfscode.rightPath.pop_back();
				}
				if (dfscode.rightPath.size()>0) // Can extend
				{
					BuildPattern(dfscode, (int)dfscode.rightPath.size() - 1, -1, maxseq);
				}
				// Recover
				for (int i = (int)t1.size() - 1;i >= 0;i--)
					dfscode.rightPath.push_back(t1[i]);
			}
			else // Yes
			{
				/*puts("++Yes, continue.++");
				dfscode.output();
				puts("--Yes, continue.--");*/
				if (dfscode.rightPath.size() < 3) // No backward edge to add, continue to add forward edge
				{
					BuildPattern(dfscode, (int)dfscode.rightPath.size() - 1, -1, maxseq + 1);
				}
				else // Continue to add backward edge
				{
					int t = (int)dfscode.rightPath.size();
					BuildPattern(dfscode, t - 1, 0, maxseq);
				}
				// Recover
				dfscode.dfsCodeList.pop_back();
				dfscode.rightPath.pop_back();
			}
		}
	}
	else // Generate backware edge
	{
		//puts("backloc >= 0");
		for (int _ = 0;_ < (int)freqEdge.size();_++)
		{
			pair<int, int> u = dfscode.rightPath[loc];
			pair<int, int> v = dfscode.rightPath[backloc];
			Edge e = freqEdge[_];
			if (e.u == v.second&&e.v == u.second) swap(e.u, e.v);
			if (e.u == u.second&&e.v == v.second)
			{
				dfscode.dfsCodeList.push_back(DFSCodeNode(u.first, v.first, e.u, e.label, e.v));
				// Test the new dfscode
				if (!dfscode.isMinDFSCode() || !isFreqPattern(dfscode)) // No
				{
					dfscode.dfsCodeList.pop_back();
					if (loc - backloc > 2)
						BuildPattern(dfscode, loc, backloc + 1, maxseq);
					else
						BuildPattern(dfscode, loc, -1, maxseq);
				}
				else // Yes
				{
					if (loc - backloc > 2)
						BuildPattern(dfscode, loc, backloc + 1, maxseq);
					else
						BuildPattern(dfscode, loc, -1, maxseq);
					dfscode.dfsCodeList.pop_back();
				}
			}
		}
	}
}

void GSPAN::SubMining(const Edge &base)
{
	tmpDFSCode.init();
	tmpDFSCode.dfsCodeList.push_back(DFSCodeNode(0, 1, base.u, base.label, base.v));
	SolveFreqPattern(tmpDFSCode);
	//tmpDFSCode.output();
	tmpDFSCode.rightPath.push_back(make_pair(0, base.u));
	tmpDFSCode.rightPath.push_back(make_pair(1, base.v));
	BuildPattern(tmpDFSCode, 1, -1, 1);
}

void GSPAN::debug()
{
	/*puts("For debug ---"); // Done
	DFSCode df;
	df.dfsCodeList.push_back(DFSCodeNode(0, 1, 2, 3, 3));
	df.dfsCodeList.push_back(DFSCodeNode(1, 2, 3, 2, 4));
	df.dfsCodeList.push_back(DFSCodeNode(2, 0, 4, 4, 2));
	df.dfsCodeList.push_back(DFSCodeNode(1, 3, 3, 2, 4));
	cout << JudgePatternInGraph(graph[0], df, 0, -1) << endl;
	cout << JudgePatternInGraph(graph[1], df, 0, -1) << endl;
	cout << JudgePatternInGraph(graph[2], df, 0, -1) << endl;
	cout << JudgePatternInGraph(graph[3], df, 0, -1) << endl;
	cout << JudgePatternInGraph(graph[4], df, 0, -1) << endl;
	puts("For debug ---");*/

	puts("+++ For debug +++");
	DFSCode df;
	df.dfsCodeList.push_back(DFSCodeNode(0, 1, 2, 3, 3));
	df.dfsCodeList.push_back(DFSCodeNode(1, 2, 3, 2, 4));
	df.dfsCodeList.push_back(DFSCodeNode(2, 0, 4, 4, 2));
	df.rightPath.push_back(make_pair(0, 2));
	df.rightPath.push_back(make_pair(1, 3));
	df.rightPath.push_back(make_pair(2, 4));
	BuildPattern(df, 2, -1, 2);
	puts("--- For debug ---");
}

void GSPAN::gSpan()
{
	GenSeedSet();
	DeleteUnFreqEdge();

	//debug();

	for (int i = 0;i < (int)freqEdge.size();i++)
	{
		cout << "freqEdge: " << i << endl;
		SubMining(freqEdge[i]);
		DeleteEdge(freqEdge[i]);
	}

}

void GSPAN::output()
{
	auto tmp = freqPattern;
	freqPattern.clear();
	for (int i = 0;i < (int)tmp.size();i++)
	{
		bool flag = 1;
		for (int j = 0;j < (int)freqPattern.size();j++)
		{
			if (tmp[i] == freqPattern[j])
			{
				flag = 0;
				break;
			}
		}
		if (flag) freqPattern.push_back(tmp[i]);
	}

	for (int _ = 0;_ < (int)freqPattern.size();_++)
	{
		DFSCode dfscode = freqPattern[_];
		out << "Pattern #" << _ + 1 << ":" << endl;
		for (int i = 0;i < (int)dfscode.dfsCodeList.size();i++)
		{
			DFSCodeNode t = dfscode.dfsCodeList[i];
			out << t.a << " " << t.b << " " << t.la << " " << t.lab << " " << t.lb << endl;
		}
	}
	out << "Number of Frequent Pattern: " << freqPattern.size() << endl;
}