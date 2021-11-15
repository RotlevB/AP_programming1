
#include "SimpleAnomalyDetector.h"

SimpleAnomalyDetector::SimpleAnomalyDetector() {
	this->cf = vector<correlatedFeatures>();
	this->threshold = 0.9;
}

SimpleAnomalyDetector::~SimpleAnomalyDetector() {
	// TODO Auto-generated destructor stub
}

/// <summary>
/// checks if line i in Timeseries is irregular
/// if it is, return the anomaly descryption
/// else returns ""
/// </summary>
/// <param name="ts"></param>
/// <param name="i"></param>
/// <returns></returns>
string SimpleAnomalyDetector::checkLine(const TimeSeries& ts, int i) const {
	vector<float> v = ts.getRow(i);
	int x, y;
	for (correlatedFeatures cor : this->cf) {
		try {
			x = ts.indxByStr(cor.feature1);
			y = ts.indxByStr(cor.feature2);
			if (dev(Point(v[x], v[y]), cor.lin_reg) > cor.threshold) {
				return cor.feature1 + "-" + cor.feature2;
			}
		} catch (const char* msg) {
			return "";
		}
	}
	return "";
}

void SimpleAnomalyDetector::learnNormal(const TimeSeries& ts){
	vector<vector<float>> columns = ts.getColumns();
	float p;
	Point temp(0, 0);
	float max;
	float d, maxDev;
	int index;
	correlatedFeatures cor;
	for (int i = 0; i < columns.size(); i++) {
		max = 0;
		index = -1;
		for (int j = i + 1; j < columns.size(); j++) {
			p = pearson(&columns[i][0], &columns[j][0], columns[i].size());
			if (p > this->threshold && p > max) {
				max = p;
				index = j;
			}
		}
		if (index != -1) {
			cor = correlatedFeatures();
			maxDev = 0;
			cor.feature1 = ts.nameByNum(i);
			cor.feature2 = ts.nameByNum(index);
			cor.corrlation = max;
			vector<Point*> points = vector<Point*>();
			for (int j = 0; j < columns[i].size(); j++) {
				points.push_back(new Point(columns[i][j], columns[index][j]));
			}
			cor.lin_reg = linear_reg(&points[0], columns[i].size());
			for (Point* p : points) {
				d = dev(*p, cor.lin_reg);
				if (d > maxDev) {
					maxDev = d;
				}
				delete[] p;
			}
			cor.threshold = maxDev * 1.1;
			this->cf.push_back(cor);
		}
	}
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries& ts){
	vector<AnomalyReport> ar = vector<AnomalyReport>();
	string str;
	for (int i = 0; i < ts.rowCount(); i++) {
		str = this->checkLine(ts, i);
		if (str.compare("") != 0) {
			ar.push_back(AnomalyReport(str, long(i+1)));
			cout << str << endl;
		}
	}
	return ar;
}

