#pragma once
#include "Line.h"
#include "StationWithTransition.h"
#include "TransitionHub.h"
#include <fstream>

class Subway
{
private:
	vector<Line> Lines;
	int stationsNumber;
	int linesNumber;
public:
	Subway() : Lines(), stationsNumber(0), linesNumber(0) {}
	Line& operator [] (const unsigned int& lineIndex) {
		if (lineIndex >= Lines.size() || lineIndex < 0)
			throw exception("Error! Out of range\n");
		else return Lines[lineIndex];
	}
	Subway& operator += (const Line& newLine) 
	{
		Lines.push_back(newLine);
		linesNumber++;
		return *this;
	}
	friend ostream& operator << (ostream& out, const Subway& SUBWAY);
	const int getStationsNumber() const { return stationsNumber; }
	void incrementSetterStationsNumber() { stationsNumber++; }
	const int getLinesNumber() const { return (int)linesNumber; }
	const int findLine(const string& lineName) const;
	bool findStation(const string& stationName) const;
	const int findStation(const string& stationName, const string& lineName) const;
	//void drawSubwayGFVZ();
};;