#include "city.h"

city::city(string cityName, string state)
{
	this->cityName = cityName;
	this->state = state;
	this->longitude = "NULL";
	this->latitude = "NULL";
}

city::city(string cityName, string state, string longitude, string latitude)
{
	this->cityName = cityName;
	this->state = state;
	this->longitude = longitude;
	this->latitude = latitude;
}
