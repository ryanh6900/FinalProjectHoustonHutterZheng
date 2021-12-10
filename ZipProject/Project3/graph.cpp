#include "graph.h"

//Defines
#define PI 3.14159265358979323846
#define GRADOS_RADIANES PI / 180

graph::graph()
{

}

void graph::insertEdge(city* A, city* B, unsigned int weight)
{
	//Map code
	string mapCodeA = A->cityName + " " + A->state;
	string mapCodeB = B->cityName + " " + B->state;

	Edge* _EdgeA = new Edge(B, A, weight);
	Edge* _EdgeB = new Edge(A, B, weight);

	adjList[mapCodeA].push_back(_EdgeA);
	adjList[mapCodeB].push_back(_EdgeB);
}

int graph::BellmanFord(string A, string B, vector<string>& path)
{
	//iterator
	unordered_map<string, vector<Edge*>>::iterator it;

	//Set each distance to infinity
	int V = adjList.size();
	unordered_map<string, int> dist;
	unordered_map<string, string> pathway;

	for (it = adjList.begin(); it != adjList.end(); it++)
	{
		dist[it->first] = INT_MAX;
		pathway[it->first] = "";
	}

	dist[A] = 0;

	//Compute shortest distance
	for (it = adjList.begin(); it != adjList.end(); it++)
	{
		for (int j = 0; j < it->second.size(); j++)
		{
			city* _u = it->second[j]->to;
			city* _v = it->second[j]->from;
			string u = _u->cityName + " " + _u->state;
			string v = _v->cityName + " " + _v->state;

			int weight = it->second[j]->weight;

			if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
			{
				dist[v] = dist[u] + weight;
				pathway[v] = u;
			}

			if (dist[v] != INT_MAX && dist[v] + weight < dist[u])
			{
				dist[u] = dist[v] + weight;
				pathway[u] = v;
			}
		}
	}

	pathway[A] = "NULL";
	string temp = pathway[B];

		while (temp != "NULL")
		{
			path.push_back(temp);
			//cout << temp + " ";
			temp = pathway[temp];
		}

	return dist[B];
}

int graph::dijkstra(string A, string B, vector<string>& path)
{
	//iterator
	unordered_map<string, vector<Edge*>>::iterator it;

	//priority queue
	priority_queue < pair<unsigned int, string>, vector<pair<unsigned int, string>>, greater<pair<unsigned int, string>>> pq;

	//Set each distance to infinity
	unordered_map<string, unsigned int> dist;
	for (it = adjList.begin(); it != adjList.end(); it++)
	{
		dist[it->first] = INT_MAX;
	}

	//Pathway
	unordered_map<string, string> pathway;

	//push first term
	pq.push(make_pair(0, A));
	dist[A] = 0;

	//Loop till queue is empty
	while (!pq.empty())
	{
		//Get least weight unvisited
		string minCity = pq.top().second;
		pq.pop();

		//iterate through popped node
		for (int j = 0; j < adjList[minCity].size(); j++)
		{
			city* _u = adjList[minCity][j]->to;
			city* _v = adjList[minCity][j]->from;
			string u = _u->cityName + " " + _u->state;
			string v = _v->cityName + " " + _v->state;

			int weight = adjList[minCity][j]->weight;

			if (dist[u] > dist[v] + weight)
			{
				dist[u] = dist[v] + weight;
				pq.push(make_pair(dist[u], u));
				pathway[u] = v;
			}
		}
	}

	pathway[A] = "NULL";
	string temp = pathway[B];

	while (temp != "NULL")
	{
		path.push_back(temp);
		temp = pathway[temp];
	}

	return dist[B];
}

string graph::dijkstra_util(unordered_map<string, int> dist, unordered_map<string, bool> visited)
{
	//Min
	int min = INT_MAX;
	string minIndex = "NULL";

	//iterator
	unordered_map<string, int>::iterator it;

	for (it = dist.begin(); it != dist.end(); it++)
	{
		if (dist[it->first] < min && visited[it->first] == false)
		{
			min = dist[it->first];
			minIndex = it->first;
		}
	}

	return minIndex;
}

