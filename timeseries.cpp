#include "timeseries.h"


vector<string> TimeSeries::splitString(string line, string token) {
	vector<string> split;
	int position = line.find(token);
	while (position != string::npos) {
		split.push_back(line.substr(0, position));
		line.erase(0, position + token.length());
		position = line.find(token);
	}
	split.push_back(line);
	return split;
}

vector<vector<float>> TimeSeries::getColums() {

}
string TimeSeries::nameByNum(int i) {
	if (i < 0 || i >= this->titles.size()) {
		return "";
	}
	return this->titles[i];
}
vector<float> TimeSeries::getRow(int i) {
	if (i < 0 || i >= this->rows.size()) {
		return vector<float>();
	}
}
float TimeSeries::getVal(int i, int j) {

}
int TimeSeries::rowCount() {

}