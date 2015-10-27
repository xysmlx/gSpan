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
}

void InputFilter::addv(int id, int label)
{
	vecv.pb(Vertex(id, label));
	if (cntv[label] == 0) listv.pb(label);
	cntv[label]++;
}

void InputFilter::adde(int u, int v, int label)
{
	vece.pb(Edge(u, v, label));
	if (cnte[label] == 0) liste.pb(label);
	cnte[label]++;
}

void InputFilter::filterV()
{
	for (int i = 0; i < listv.size(); i++)
		filterv.pb(Node(listv[i], cntv[listv[i]]));
	sort(filterv.begin(), filterv.end());
	for (int i = 0; i < filterv.size(); i++)
		mpv[filterv[i].id] = i + 2;
}

void InputFilter::filterE()
{
	for (int i = 0; i < liste.size(); i++)
		filtere.pb(Node(liste[i], cnte[liste[i]]));
	sort(filtere.begin(), filtere.end());
	for (int i = 0; i < filtere.size(); i++)
		mpe[filtere[i].id] = i + 2;
}

void InputFilter::filter()
{
	filterV();
	filterE();
}