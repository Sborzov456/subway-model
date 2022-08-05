#pragma once
#include "basicStation.h"
#include<fstream>

class Line
{
private:
	vector<Station*> Stations; 
	string lineName;
public:
	Line(const string& LNm) : lineName(LNm), Stations() {}
	Station*& operator [] (const unsigned int& stationIndex) {
		if (stationIndex >= Stations.size() || stationIndex < 0) 
			throw exception("Error! Out of range\n");
		else return Stations[stationIndex];
	}
	Station* operator [] (const unsigned int& stationIndex) const {
		if (stationIndex >= Stations.size() || stationIndex < 0)
			throw exception("Error! Out of range\n");
		else return Stations[stationIndex];
	}
	Line& operator += (Station* newStation)
	{
		Stations.push_back(newStation);
		return *this;
	}
	friend ostream& operator << (ostream& out, const Line& outputLine);
	const string& getName() const { return lineName; }
	const int getSize() const { return (int)Stations.size(); }
	vector<Station*>& getStations() { return Stations; }
	void drawLineGFVZ(const string& lineColor);
};