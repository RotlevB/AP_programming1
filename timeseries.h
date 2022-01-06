

#ifndef TIMESERIES_H_
#define TIMESERIES_H_

#include <fstream>
#include<vector>
#include<iostream>
#include <string>
using namespace std;

vector<string> splitString(string line, string token);

class TimeSeries{
private:

	vector<string> titles;
	vector<vector<float>> rows;
	
public:

	vector<vector<float>> getColumns() const;
	string nameByNum(int i) const;
	int indxByStr(string str) const;
	vector<float> getRow(int i) const;
	float getVal(int i, int j) const;
	int rowCount() const;

	TimeSeries(const char* CSVfileName){
		ifstream myfile(CSVfileName);
		string line;
		this->rows = vector<vector<float>>();
		getline(myfile, line);
		int i = 0;
		this->titles = splitString(line, ",");
		while (getline(myfile, line)) {
			rows.push_back(vector<float>());
			for (string str : splitString(line, ",")) {
				rows[i].push_back(stof(str));
			}
			i++;
		}
	}

};



#endif /* TIMESERIES_H_ */
