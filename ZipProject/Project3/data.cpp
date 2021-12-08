#pragma once

//Files
#include "LinkedList.h"

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

using namespace std;

//hash function
int Hash(string str) {
	int h = 1357593;
	int mult = 1257;
	for (int i = 0; i < str.length(); i++)
		h = str[i] + mult * h;
	if (h < 0)
		h = -h;
	if (h < 0)
		h = 0;
	h = h % 1000;
	return h;
}

//trims the spaces before and after string s
string trim(string s) {
	char* str = new char[s.length() + 1];
	strcpy(str, s.c_str());
	int i, len;
	len = strlen(str);
	for (i = 0; i < len; i++) {
		if (str[i] != ' ') break;
	}
	memmove(str, str + i, len - i + 1);
	len = strlen(str);
	for (i = len - 1; i >= 0; i--) {
		if (str[i] != ' ') break;
	}
	str[i + 1] = 0;
	string toReturn(str);
	return toReturn;
}

//Read File from MapProject
void readFileNamedPlaces(string fName, List**& hashtable) {
	ifstream fin(fName.c_str());
	if (fin.fail()) {
		cout << "Error opening " << fName << ".\n";
		exit(1);
	}

	int hashval;
	place* temp = NULL;
	string line, s_numcode, s_abbrev, s_name, s_dist, s_repcode,
		s_longitude, s_latitude, s_area, s_population;
	int i_numcode, i_population, i_repcode, length;
	double d_area, d_latitude, d_longitude, d_dist;
	while (!fin.eof()) {
		line = "";
		getline(fin, line);
		if (fin.fail()) break;

		s_numcode = trim(line.substr(0, 8));
		s_abbrev = trim(line.substr(8, 2));
		s_name = trim(line.substr(10, 50));
		length = line.length();
		s_dist = trim(line.substr(length - 8, 8));
		s_repcode = trim(line.substr(length - 13, 5));
		s_longitude = trim(line.substr(length - 24, 11));
		s_latitude = trim(line.substr(length - 34, 10));
		s_area = trim(line.substr(length - 48, 14));
		s_population = trim(line.substr(length - 55, 7));
		i_numcode = atoi(s_numcode.c_str());
		i_population = atoi(s_population.c_str());
		i_repcode = atoi(s_repcode.c_str());
		d_area = atof(s_area.c_str());
		d_latitude = atof(s_latitude.c_str());
		d_longitude = atof(s_longitude.c_str());
		d_dist = atof(s_dist.c_str());
		temp = new place(s_abbrev, s_name, i_population, d_area, d_latitude, d_longitude, i_repcode, d_dist);
		hashval = Hash(temp->getCityLower());
		if (hashtable[hashval]->getFirst() != NULL)
			hashtable[hashval]->addEnd(temp);
		else
			hashtable[hashval]->addFront(temp);
	}
	fin.close();
}


