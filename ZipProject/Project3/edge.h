#pragma once

//EDGE
class edge
{
public:
	edge(double val);
	~edge();

	double weight;
};

edge::edge(double val)
{
	weight = val;
}

edge::~edge()
{
}