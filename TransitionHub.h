#pragma once
#include "BasicStation.h"
#include <utility>

class TransitionHub : public Station
{
private:
	Array<pair<string, string>, MAX_T_STATIONS> transitionStations; //first - station name, second - line name
public:
	
	TransitionHub(const string& stNm, const string& sLnNm, const Array<pair<string, string>, MAX_T_STATIONS>& tSt) :
		Station(stNm, sLnNm), transitionStations(tSt) {}
	const string& getName() const override { return stationName; }
	const string getType() const override { return "Transition Hub"; }
	const string& getStationLineName() const override { return stationLineName; }
	Array<pair<string, string>, MAX_T_STATIONS>& getTransitionStations() { return transitionStations; }
	void setTransitionStation(const pair<string, string>& trStations) { transitionStations += trStations; }
	void stationInformation() const override;
};
 