#pragma once
#include <iostream>
#include <string>
#include "TemplateArray.h" //custom array
#include <vector>
#include <stdexcept>
#include <utility>
#define MAX_T_LINES 3
#define MAX_T_STATIONS 3

using namespace std;
class Station
{
protected:
	string stationName;//name of station
	string stationLineName;//name of the line on which the station is located
public:
	Station(const string& stNm, const string& sLnNm) : stationName(stNm), stationLineName(sLnNm) {}
	virtual const string& getName() const { return stationName; }
	virtual const string getType() const { return "Station Without Transition"; }
	virtual const string& getStationLineName() const { return stationLineName; }
	Station* convertToStationWithTransition(const Array<string, MAX_T_LINES>& trLines);
	Station* convertToTransitionHub(const Array<pair<string, string>, MAX_T_STATIONS>& trStations);
	virtual void stationInformation() const;
	
};;