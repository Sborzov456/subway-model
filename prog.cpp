#include "Subway.h"
int dialogForOption(const char** msgs, int rc)
{
	int choice;
	while (1)
	{
		for (int i = 0; i < rc; i++) std::cout << msgs[i] << std::endl;
		std::cout << "Enter your choice --> ";
		std::cin >> choice;
		if (choice >= 0 && choice < rc) break;
		if (!std::cin.good()) {
			throw exception("Error! Incorrect input\n");
		}
		throw exception("Error! This option does not exist \n");
	}
	return choice;
}
int dialogForStation(const Subway& SUBWAY, string& lineName, string& stationName, int& lineIndex)
{
	if (SUBWAY.getLinesNumber() == 0) {
		cout << "Error! Subway is empty\n";
		return -1;
	}
	while (lineIndex == -1) {
		cout << "Line for station --> ";
		cin >> lineName;
		lineIndex = SUBWAY.findLine(lineName);
		if (lineIndex == -1) cout << "Line not found!\n";
	}
	bool existStationError = 1;
	while (existStationError == 1)
	{
		cout << "Station name --> ";
		cin >> stationName;
		existStationError = SUBWAY.findStation(stationName);
		if (existStationError == 1) cout << "Station already exist!\n";
	}
	return 0;
}
int main() 
{
	cout << " ------------------------------------------------\n";
	cout << "                   SUBWAY	V.1.2                 \n";
	cout << "        HELLO, WELCOME TO THE UNDERGROUND!       \n";
	cout << " ------------------------------------------------\n\n";
	Subway SUBWAY;
	const char* msgs[] = {
	"[0]: Quit",
	"[1]: Add line",
	"[2]: Add station",
	"[3]: Convert type of station",
	"[4]: Edit station",
	"[5]: Print subway",
	"[6]: READY TEST",
	"[7]: DRAW IN GRAPHVIZ" 
	};
	int option = -1;
	while (option != 0) {
		try {
			option = dialogForOption(msgs, 8);
		}
		catch (const exception& exc) {
			cerr << exc.what();
		}
		switch (option) {
		case 1: {
			string lineName = string();
			int lineExist = 0;
			while (lineExist >= 0)
			{
				cout << "Line Name --> ";
				cin >> lineName;
				lineExist = SUBWAY.findLine(lineName);
				if (lineExist >= 0) cout << "Line already exist!\n";
			}
			Line newLine(lineName);
			SUBWAY += newLine;
			break;
		}
		case 2: {
			if (SUBWAY.getLinesNumber() == 0) {
				cout << "Subway is empty!\n";
				break;
			}
			const char* msgs[] = {
			"[0]: Quit",
			"[1]: Station",
			"[2]: Station With Transition",
			"[3]: Transfer Hub"
			};
			int option = -1;
			while (option != 0) {
				try {
					option = dialogForOption(msgs, 4);
				}
				catch (const exception& exc) {
					cerr << exc.what();
				}
				if (option == 1) {
					string lineName = string();
					string stationName = string();
					int lineIndex = -1;
					if (dialogForStation(SUBWAY, lineName, stationName, lineIndex) == -1) break;
					Station* newStation = new Station(stationName, lineName);
					try {
						SUBWAY[lineIndex] += newStation;
					}
					catch (const exception& exc) {
						cerr << exc.what();
					}
					SUBWAY.incrementSetterStationsNumber();
				}
				else if (option == 2) {
					if (SUBWAY.getLinesNumber() <= 1) {
						cout << "There are too few lines for transition!\n";
						break;
					}
					string lineName = string();
					string stationName = string();
					int lineIndex = -1;
					if(dialogForStation(SUBWAY, lineName, stationName, lineIndex) == -1) break;
					Array<string, MAX_T_LINES> transitionLines;
					int EXIT = -1;
					while(transitionLines.size() < MAX_T_LINES)
					{
						if (transitionLines.size() >= SUBWAY.getLinesNumber() - 1) {
							cout << "No more transfer lines!\n";
							break;
						}
						string transitionLine;
						cout << "Line[" << transitionLines.size() << "] --> ";
						cin >> transitionLine;
						int transitionLineIndex = SUBWAY.findLine(transitionLine);
						if (transitionLineIndex == -1){
							cout << "Line not found!\n";
							continue;
						}
						else if (transitionLineIndex == lineIndex) {
							cout << "No transition to line which station is located!\n";
							continue;
						}
						if (transitionLines.find(transitionLine)) {
							cout << "This line already added!\n";
							continue;
						}
						if (SUBWAY.findStation(stationName, transitionLine) == -1) {
							Station* sameNameStationOnTL = new StationWithTransition(stationName, transitionLine, lineName);
							SUBWAY[transitionLineIndex] += sameNameStationOnTL;
							SUBWAY.incrementSetterStationsNumber();
						}
						transitionLines += transitionLine;
						cout << "[0]: EXIT\n[1]: CONTINUE\nEnter --> ";
						cin >> EXIT;
						if (EXIT == 0) break;
					}
					Station* newStation = new StationWithTransition(stationName, lineName, transitionLines);
					try {
						SUBWAY[lineIndex] += newStation;
					}
					catch (const exception& exc) {
						cerr << exc.what();
					}
					SUBWAY.incrementSetterStationsNumber();
				}
				else if (option == 3) {
					if (SUBWAY.getStationsNumber() < 1 || SUBWAY.getLinesNumber() <= 1) {
						cout << "There are too few stations or lines for transition!\n";
						break;
					}
					string lineName = string();
					string stationName = string();
					int lineIndex = -1;
					if(dialogForStation(SUBWAY, lineName, stationName, lineIndex) == -1) break;
					Array<pair<string, string>, MAX_T_STATIONS> transitionStations;
					int EXIT = -1;
					while (transitionStations.size() < MAX_T_STATIONS) {
						if (transitionStations.size() >= SUBWAY.getStationsNumber()) {
							cout << "No more transfer stations!\n";
							break;
						}
						cout << "Station [" << transitionStations.size() << "]\n";
						pair<string, string> transitionStation;
						
						while(true) {
							cout << "Line name --> ";
							cin >> transitionStation.second;
							if (SUBWAY.findLine(transitionStation.second) == -1) {
								cout << "Line not found!\n";
								continue;
							}
							if (transitionStation.second == lineName) {
								cout << "No transition to line which station is located!\n";
								continue;
							}
							else break;
						}
						while (true) {
							cout << "Station name --> ";
							cin >> transitionStation.first;
							if (SUBWAY.findStation(transitionStation.first, transitionStation.second) == -1) {
								cout << "Station not found!\n";
								continue;
							}
							else break;
						}
						if (transitionStations.find(transitionStation)) {
							cout << "This station already added!\n";
							continue;
						}
						transitionStations += transitionStation;
						cout << "[0]: EXIT\n[1]: CONTINUE\nEnter --> ";
						cin >> EXIT;
						if (EXIT == 0) break;
					}
					Station* newStation = new TransitionHub(stationName, lineName, transitionStations);
					try {
						SUBWAY[lineIndex] += newStation;
					}
					catch (const exception& exc) {
						cerr << exc.what();
					}
					SUBWAY.incrementSetterStationsNumber();
				}
			}
			break;
		}
		case 3: {
			if (SUBWAY.getStationsNumber() == 0) {
				cout << "Subway is empty!\n";
				break;
			}
			cout << "You can only change the type of Basic Station ^_^\n";
			const char* msgs[] = {
				"[0]: Quit",
				"[1]: Convert to Station With Transition",
				"[2]: Convert to Transfer Hub"
			};
			int option = -1;
			while (option != 0) {
				cout << "[0]: EXIT\n[1]: START CONVERT\n";
				int choice;
				cout << "Enter your choice --> ";
				cin >> choice;
				if (choice == 0) break;
				string stationName = string();
				string lineName = string();
				int stationIndex = -1;
				int lineIndex = -1;
				while (true) {
					cout << "Line name --> ";
					cin >> lineName;
					lineIndex = SUBWAY.findLine(lineName);
					if (lineIndex == -1) {
						cout << "Line not found!\n";
						continue;
					}
					while (stationIndex == -1) {
						cout << "Station name --> ";
						cin >> stationName;
						stationIndex = SUBWAY.findStation(stationName, lineName);
						if (stationIndex == -1) cout << "Station not found!\n";
					}
					if (SUBWAY[lineIndex][stationIndex]->getType() != "Station Without Transition") {
						cout << "This station is not Station Without Transition!\n";
						continue;
					}
					else break;
				}
				try {
					option = dialogForOption(msgs, 3);
				}
				catch (const exception& exc) {
					cerr << exc.what();
				}
				if (option == 1) {
					Array<string, MAX_T_LINES> transitionLines;
					int EXIT = -1;
					while (transitionLines.size() < MAX_T_LINES)
					{
						if (transitionLines.size() >= SUBWAY.getLinesNumber() - 1) {
							cout << "No more transfer lines!\n";
							break;
						}
						string transitionLine;
						cout << "Line[" << transitionLines.size() << "] --> ";
						cin >> transitionLine;
						int transitionLineIndex = SUBWAY.findLine(transitionLine);
						if (transitionLineIndex == -1) {
							cout << "Line not found!\n";
							continue;
						}
						else if (transitionLineIndex == lineIndex) {
							cout << "No transition to line which station is located!\n";
							continue;
						}
						if (transitionLines.find(transitionLine)) {
							cout << "This line already added!\n";
							continue;
						}
						if (SUBWAY.findStation(stationName, transitionLine) == -1) {
							Station* sameNameStationOnTL = new StationWithTransition(stationName, transitionLine, lineName);
							SUBWAY[transitionLineIndex] += sameNameStationOnTL;
							SUBWAY.incrementSetterStationsNumber();
						}
						transitionLines += transitionLine;
						cout << "[0]: EXIT\n[1]: CONTINUE\nEnter --> ";
						cin >> EXIT;
						if (EXIT == 0) break;
					}
					SUBWAY[lineIndex][stationIndex] = SUBWAY[lineIndex][stationIndex]->convertToStationWithTransition(transitionLines);
				}
				else if (option == 2) {
					Array<pair<string, string>, MAX_T_STATIONS> transitionStations;
					int EXIT = -1;
					while (transitionStations.size() < MAX_T_STATIONS) {
						if (transitionStations.size() >= SUBWAY.getStationsNumber() - 1) {
							cout << "No more transfer stations!\n";
							break;
						}
						cout << "Station [" << transitionStations.size() << "]\n";
						pair<string, string> transitionStation;

						while (true) {
							cout << "Line name --> ";
							cin >> transitionStation.second;
							if (SUBWAY.findLine(transitionStation.second) == -1) {
								cout << "Line not found!\n";
								continue;
							}
							if (transitionStation.second == lineName) {
								cout << "No transition to line which station is located!\n";
								continue;
							}
							else break;
						}
						while (true) {
							cout << "Station name --> ";
							cin >> transitionStation.first;
							if (SUBWAY.findStation(transitionStation.first, transitionStation.second) == -1) {
								cout << "Station not found!\n";
								continue;
							}
							else break;
						}
						if (transitionStations.find(transitionStation)) {
							cout << "This station already added!\n";
							continue;
						}
						transitionStations += transitionStation;
						cout << "[0]: EXIT\n[1]: CONTINUE\nEnter --> ";
						cin >> EXIT;
						if (EXIT == 0) break;
					}
					SUBWAY[lineIndex][stationIndex] = SUBWAY[lineIndex][stationIndex]->convertToTransitionHub(transitionStations);
				}
			}
			break;
		}
		case 4: {
			if (SUBWAY.getStationsNumber() == 0) {
				cout << "Subway is empty!\n";
				break;
			}
			string stationName = string();
			string lineName = string();
			int stationIndex = -1;
			int lineIndex = -1;
			while (true) {
				cout << "Line name --> ";
				cin >> lineName;
				lineIndex = SUBWAY.findLine(lineName);
				if (lineIndex == -1) {
					cout << "Line not found!\n";
					continue;
				}
				while (stationIndex == -1) {
					cout << "Station name --> ";
					cin >> stationName;
					stationIndex = SUBWAY.findStation(stationName, lineName);
					if (stationIndex == -1) cout << "Station not found!\n";
				}
				break;
			}
			if (SUBWAY[lineIndex][stationIndex]->getType() == "Station Without Transition") {
				cout << "No options for Station Without Transition!\n";
			}
			else if (SUBWAY[lineIndex][stationIndex]->getType() == "Station With Transition") {
				const char* msgs[] = { "[0]: Quit", "[1]: Add transition line" };
				int option = -1;
				while (option != 0) {
					try {
						option = dialogForOption(msgs, 2);
					}
					catch(const exception& exc) {
						cerr << exc.what();
					}
					if (option == 1) {
						Array<string, MAX_T_LINES> buf(dynamic_cast<StationWithTransition*>(SUBWAY[lineIndex][stationIndex])->getTransitionLines());
						if (buf.full()) {
							cout << "No more transition lines!\n";
							break;
						}
						if (SUBWAY.getLinesNumber() - 1 <= buf.size()) {
							cout << "There are too few lines for transition!\n";
							break;
						}
						string transitionLine = string();
						int transitionLineIndex = -1;
						while (true) {
							cout << "Enter line --> ";
							cin >> transitionLine;
							transitionLineIndex = SUBWAY.findLine(transitionLine);
							if (transitionLineIndex == -1) {
								cout << "Line not found!\n";
								continue;
							}
							if (buf.find(transitionLine)) {
								cout << "This line already added!\n";
								continue;
							}
							break;
						}
						if (SUBWAY.findStation(stationName, transitionLine) == -1) {
							Station* sameNameStationOnTL = new StationWithTransition(stationName, transitionLine, lineName);
							SUBWAY[transitionLineIndex] += sameNameStationOnTL;
							SUBWAY.incrementSetterStationsNumber();
						}
						dynamic_cast<StationWithTransition*>(SUBWAY[lineIndex][stationIndex])->setTransitionLines(transitionLine);
					}
				}
			}
			else if (SUBWAY[lineIndex][stationIndex]->getType() == "Transition Hub") {
				const char* msgs[] = { "[0]: Quit", "[1]: Add transition station" };
				int option = -1;
				while (option != 0) {
					try {
						option = dialogForOption(msgs, 2);
					}
					catch (const exception& exc) {
						cerr << exc.what();
					}
					if (option == 1) {
						Array<pair<string, string>, MAX_T_STATIONS> buf(dynamic_cast<TransitionHub*>(SUBWAY[lineIndex][stationIndex])->getTransitionStations());
						if (buf.full()) {
							cout << "No more transition stations!\n";
							break;
						}
						if (SUBWAY.getStationsNumber() - 1 <= buf.size()) {
							cout << "There are too few lines or stations for transition!\n";
							break;
						}
						pair<string, string> transitionStation;
						while (true) {
							cout << "Enter line --> ";
							cin >> transitionStation.second;
							if (SUBWAY.findLine(transitionStation.second)) {
								cout << "Line not found!\n";
								continue;
							}
							while (true) {
								cout << "Enter station --> ";
								cin >> transitionStation.first;
								if (SUBWAY.findStation(transitionStation.first, transitionStation.second) == -1) {
									cout << "Station not found!\n";
									continue;
								}
								if (buf.find(transitionStation)) {
									cout << "This station already added!\n";
									continue;
								}
								break;
							}
							break;
						}
						dynamic_cast<TransitionHub*>(SUBWAY[lineIndex][stationIndex])->setTransitionStation(transitionStation);
					}
				}
			}
			break;
		}
		case 5: {
			try {
				cout << SUBWAY;
			}
			catch (const exception& exc) {
				cerr << exc.what();
			}
			break;
		}
		case 6: {
			cout << "\nTEST:\n";
			cout << "1) Create RED line\n2) Create BLUE line\n";
			cout << "3) Create SWoutT A(RED)\n4) Create SwoutT B(BLUE)\n";
			cout << "5) Convert A to Transfer Hub with transfer to B\n6) Convert B to Transfer Hub with transfer to A\n\n";

			Subway TEST_SUBWAY;
			Line RED("RED");
			Station* A = new Station("A", "RED");
			RED += A;
			TEST_SUBWAY += RED;

			Line BLUE("BLUE");
			Station* B = new Station("B", "BLUE");
			BLUE += B;
			TEST_SUBWAY += BLUE;

			cout << "SUBWAY 1\n";
			cout << TEST_SUBWAY;

			pair<string, string> p_A("B", "BLUE");
			Array<pair<string, string>, MAX_T_STATIONS> trSt_A; 
			trSt_A += p_A;
			TEST_SUBWAY[0][0] = TEST_SUBWAY[0][0]->convertToTransitionHub(trSt_A);

			cout << "SUBWAY 2\n";
			cout << TEST_SUBWAY;

			pair<string, string> p_B("A", "RED");
			Array<pair<string, string>, MAX_T_STATIONS> trSt_B;
			trSt_B += p_B;
			TEST_SUBWAY[1][0] = TEST_SUBWAY[1][0]->convertToTransitionHub(trSt_B);

			cout << "SUBWAY 3\n";
			cout << TEST_SUBWAY;
			break;
		}
		case 7: {
			string lineForDraw = string();
			int lineForDrawIndex = -1;
			while (lineForDrawIndex == -1) {
				cout << "Enter line you want to draw --> ";
				cin >> lineForDraw;
				lineForDrawIndex = SUBWAY.findLine(lineForDraw);
				if (lineForDrawIndex == -1)
					cout << "Line not found!\n";
			}
			string lineColor;
			cout << "Enter line color --> ";
			cin >> lineColor;
			SUBWAY[lineForDrawIndex].drawLineGFVZ(lineColor);
		}
		}
	}
	return 0;
}