#pragma once

//Includes
#include <vector>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <queue>

//Headers
#include "city.h"

using namespace std;

struct Edge
{
	city* from;
	city* to;
	unsigned int weight;

	Edge(city* _toCity, city* _fromCity, unsigned int _weight) {
		this->to = _toCity;
		this->from = _fromCity;
		this->weight = _weight;
	}
};

//GRAPH
class graph
{
	private:

	public:
		//Adjacency list
		//string name format "city state"
		unordered_map<string, vector<Edge*>> adjList;

		//Constructor
		graph();
		void insertEdge(city* A, city* B, unsigned int weight);
		int BellmanFord(string A, string B, vector<string> &path);
		int dijkstra(string A, string B, vector<string>& path);
		string dijkstra_util(unordered_map<string, int> dist, unordered_map<string, bool> visited);
};

