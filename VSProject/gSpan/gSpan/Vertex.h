#ifndef VERTEX_H
#define VERTEX_H

#include "firsthead.h"

struct Vertex
{
	int id;
	int label;
	bool del;

	Vertex(int _id = 0, int _label = 0) : id(_id), label(_label), del(0) {}
	~Vertex() {}
};

#endif