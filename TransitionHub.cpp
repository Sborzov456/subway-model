#include "TransitionHub.h"

void TransitionHub::stationInformation() const 
{
	cout << "Station Name: " << stationName << endl;
	cout << "Station Type: Transition Hub\n";
	cout << "Transition Lines: ";
	if (transitionStations.empty()) cout << "Empty\n";
	else {
		for (unsigned int i = 0; i < transitionStations.size(); i++)
			cout << transitionStations[i].first << "(" << transitionStations[i].second << ") ";
		cout << endl;
	}
}