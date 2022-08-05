#pragma once
#include "BasicStation.h"

class StationWithTransition : public Station
{
private:
	Array<string, MAX_T_LINES> transitionLines;
public:
	StationWithTransition(const string& stNm, const string& sLnNm) : Station(stNm, sLnNm), transitionLines() {}
	StationWithTransition(const string& stNm, const string& sLnNm, const Array<string, MAX_T_LINES>& tLn) : 
		Station(stNm, sLnNm), transitionLines(tLn) {
	}
	StationWithTransition(const string& stNm, const string& sLnNm, const string& oneTLn) : 
		Station(stNm, sLnNm) {
		transitionLines += oneTLn;
	}
	const string& getName() const override { return stationName; }
	const string getType() const override { return "Station With Transition"; }
	const string& getStationLineName() const override { return stationLineName; }
	Array<string, MAX_T_LINES>& getTransitionLines() { return transitionLines; }
	void setTransitionLines(const string& trLine) { transitionLines += trLine; }
	void stationInformation() const override;
};;