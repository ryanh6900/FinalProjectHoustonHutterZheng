#pragma once

//Files
#include "LinkedList.h"
#include "graph.h"
#include "MapProject.h"

//Includes
#include <string>
#include <string>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <sstream>
#include <stdlib.h>
#include <ctime>
#include <math.h>
#include <cmath>

//Defines
#define PI 3.14159265358979323846
#define GRADOS_RADIANES PI / 180

using namespace std;

void populateGraph(graph& _graph) {
	ifstream fin("edges.csv");
	if (fin.fail()) {
		cout << "Error opening " << "edges.csv" << ".\n";
		exit(1);
	}

	vector<string> temp;
	string line;

	while (!fin.eof()) {
		line = "";
		temp.clear();

		getline(fin, line);
		if (fin.fail()) break;

		istringstream s(line);
		string term;

		while (getline(s, term, ','))
		{
			temp.push_back(term);
		}

		city* _cityA = new city(temp[0], temp[1]);
		city* _cityB = new city(temp[2], temp[3]);
		_graph.insertEdge(_cityA, _cityB, (unsigned)stoi(temp[4]));
	}

	fin.close();
}

bool isCapital(string city) {

	return true;
}

void generateData() {
	vector<city*> cityData;
	readFileNamedPlaces("named-places.txt", cityData);

	ofstream _data;
	_data.open("graphData.csv");
	//_data.open("edges.csv");

	for (int i = 0; i < cityData.size(); i++)
	{
		//Temp variables if city has no close neighbors
		unsigned int close_edge_count = 0;
		unsigned int medium_edge_count = 0;
		unsigned int large_edge_count = 0;
		unsigned int huge_edge_count = 0;
		unsigned int massive_edge_count = 0;

		//List
		for (int j = 0; j < cityData.size(); j++)
		{

			//Calculate distance
				//local variables for debugging
			city* cityA = cityData[i];
			city* cityB = cityData[j];

			double lat1 = stod(cityA->latitude) * GRADOS_RADIANES;
			double lon1 = stod(cityA->longitude) * GRADOS_RADIANES;
			double lat2 = stod(cityB->latitude) * GRADOS_RADIANES;
			double lon2 = stod(cityB->longitude) * GRADOS_RADIANES;

			//Haversine formula
			double u = sin((lat2 - lat1) / 2);
			double v = sin((lon2 - lon1) / 2);
			unsigned int dist = abs((2.0 * 6371.0 * asin(sqrt(u * u + cos(lat1) * cos(lat2) * v * v))));

			//Update new edgelist
			if (dist > 0 && dist <= 30 && close_edge_count < 5)
			{
				_data << cityA->cityName << "," << cityA->state << ",";
				_data << cityB->cityName << "," << cityB->state << ",";
				_data << dist << endl;
				close_edge_count++;
			}

			if (dist > 0 && dist <= 30 && medium_edge_count < 5)
			{
				_data << cityA->cityName << "," << cityA->state << ",";
				_data << cityB->cityName << "," << cityB->state << ",";
				_data << dist << endl;
				close_edge_count++;
			}

			if (dist > 100 && dist <= 200 && medium_edge_count < 10)
			{
				_data << cityA->cityName << "," << cityA->state << ",";
				_data << cityB->cityName << "," << cityB->state << ",";
				_data << dist << endl;
				medium_edge_count++;
			}

			if (dist > 200 && dist <= 720 && huge_edge_count < 50)
			{
				_data << cityA->cityName << "," << cityA->state << ",";
				_data << cityB->cityName << "," << cityB->state << ",";
				_data << dist << endl;
				huge_edge_count++;
			}

		}

	}

	_data.close();
}