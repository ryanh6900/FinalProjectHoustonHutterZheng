#pragma once

//Includes
#include <string>

using namespace std;

class city
{
	private:

	public:
		string cityName;
		string state;
		string longitude;
		string latitude;

		city(string cityName, string state);
		city(string cityName, string state, string longitude, string latitude);
};

