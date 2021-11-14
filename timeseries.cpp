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
	vector<vector<float>> columns = vector<vector<float>>(); //the return object
	for (int i = 0; i < this->rows[0].size; i++) { //num of new vectors
		vector<float> single_new_col = vector<float>(); //create new col
		for (vector<float> v : rows) {
			single_new_col.push_back(v[i]);
		}
		columns.insert(i, single_new_col);
	}
	return columns;
}
string TimeSeries::nameByNum(int i) {

}
vector<float> TimeSeries::getRow(int i) {

}
float TimeSeries::getVal(int i, int j) {

}
int TimeSeries::rowCount() {

}