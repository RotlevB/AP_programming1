

#ifndef TIMESERIES_H_
#define TIMESERIES_H_

#include <unordered_map>
#include<fstream>
using namespace std;

class TimeSeries{
private:

	vector<string> titles;
	vector<vector<float>> rows;
	
public:

	vector<vector<float>> getColums();
	string nameByNum(int i);
	vector<float> getRow(int i);
	float getVal(int i, int j);
	int rowCount();
	vector<string> splitString(string line, string token);
	TimeSeries(const char* CSVfileName){
		ifstream myfile(CSVfileName);

	}

};



#endif /* TIMESERIES_H_ */
