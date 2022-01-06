#include "timeseries.h"


vector<string> splitString(string line, string token) {
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

/// <summary>
/// returns data as columns vector
/// </summary>
/// <returns></returns>
vector<vector<float>> TimeSeries::getColumns() const {
	vector<vector<float>> columns = vector<vector<float>>();
	vector<float> temp;
	for (int i = 0; i < this->titles.size(); i++) {
		temp = vector<float>();
		for (vector<float> v : this->rows) {
			temp.push_back(v[i]);
		}
		columns.push_back(temp);
	}
	return columns;
}

/// <summary>
/// returns title-name by index
/// throws exceptios if index is out of bound
/// </summary>
/// <param name="i"></param>
/// <returns></returns>
string TimeSeries::nameByNum(int i) const {
	if (i < 0 || i >= this->titles.size()) {
		throw "out of bound";
	}
	return this->titles[i];
}

/// <summary>
/// returns index of a title
/// throws exception if title doesnt exist
/// </summary>
/// <param name="str"></param>
/// <returns></returns>
int TimeSeries::indxByStr(string str) const {
	int i = -1;
	for (string s : this->titles) {
		i++;
		if (s.compare(str) == 0) {
			return i;
		}
	}
	throw "non existant title";
}

/// <summary>
/// returns row_vector by index
/// throws exceptios if index is out of bound
/// </summary>
/// <param name="i"></param>
/// <returns></returns>
vector<float> TimeSeries::getRow(int i) const {
	if (i < 0 || i >= this->rows.size()) {
		throw "out of bound";
	}
	return this->rows[i];
}

/// <summary>
/// returns value of rows[i][j]
/// throws exceptios if i or j are out of bound
/// </summary>
/// <param name="i"></param>
/// <param name="j"></param>
/// <returns></returns>
float TimeSeries::getVal(int i, int j) const {
	if (i < 0 || i >= this->rows.size()) {
		throw "i out of bound";
	}
	vector<float> v = this->rows[i];
	if (j < 0 || j > v.size()) {
		throw "j out of bound";
	}
	return v[j];
}

/// <summary>
/// returns row count
/// </summary>
/// <returns></returns>
int TimeSeries::rowCount() const {
	return this->rows.size();
}