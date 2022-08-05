#include "StationWithTransition.h"

void StationWithTransition::stationInformation() const
{
	cout << "Station Name: " << stationName << endl;
	cout << "Station Type: Station With Transition" << endl;
	cout << "Transition Lines: ";
	if (transitionLines.empty()) cout << "Empty\n";
	else {
		for (unsigned int i = 0; i < MAX_T_LINES; i++)
			if (!transitionLines[i].empty()) cout << transitionLines[i] << " ";
		cout << endl;
	}
}