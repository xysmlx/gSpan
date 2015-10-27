#include "InputFilter.h"

void InputFilter::init()
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
	inputStr.clear();
}

void InputFilter::addv(int id, int label)
{
	vecv.push_back(Vertex(id, label));
	if (cntv[label] == 0) listv.push_back(label);
	cntv[label]++;
}

void InputFilter::adde(int u, int v, int label)
{
	vece.push_back(Edge(u, v, label));
	if (cnte[label] == 0) liste.push_back(label);
	cnte[label]++;
}

void InputFilter::filterV()
{
	for (int i = 0; i < listv.size(); i++)
		filterv.push_back(Node(listv[i], cntv[listv[i]]));
	sort(filterv.begin(), filterv.end());
	for (int i = 0; i < filterv.size(); i++)
		mpv[filterv[i].label] = i + 2;
}

void InputFilter::filterE()
{
	for (int i = 0; i < liste.size(); i++)
		filtere.push_back(Node(liste[i], cnte[liste[i]]));
	sort(filtere.begin(), filtere.end());
	for (int i = 0; i < filtere.size(); i++)
		mpe[filtere[i].label] = i + 2;
}

void InputFilter::filter()
{
	filterV();
	filterE();
}