#include "Line.h"

ostream& operator << (ostream& out, const Line& outputLine)
{
	out << outputLine.lineName << " LINE\n";
	if (outputLine.Stations.empty()) cout << "No stations yet";
	for (unsigned int i = 0; i < outputLine.Stations.size(); i++) {
		outputLine.Stations[i]->stationInformation();
	}
	out << "\n";
	return out;
}
void Line::drawLineGFVZ(const string& lineColor)
{
	ofstream fout;
	fout.open("C:\\Users\\boroz\\Desktop\\graphviz\\subway.txt");
	fout << "graph G {\n";
	for (unsigned int i = 0; i < Stations.size(); ++i) {
		fout << Stations[i]->getName() << "[color = " << lineColor << "]\n";
	}
	for (unsigned int i = 0; i < Stations.size(); ++i) {
		fout << Stations[i]->getName();
		if (i != Stations.size() - 1) fout << "--";
	}
	fout << "[color = " << lineColor << "];\n";
	fout << "}";
	fout.close();
	system("C:\\Users\\boroz\\Graphviz\\bin\\dot.exe -Tpng -Gsize=9,15\! -Gdpi=100 -o C:\\Users\\boroz\\Desktop\\graphviz\\subway.png C:\\Users\\boroz\\Desktop\\graphviz\\subway.txt");
	system("C:\\Users\\boroz\\Desktop\\graphviz\\subway.png");
}