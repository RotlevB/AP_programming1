
#include "HybridAnomalyDetector.h"

HybridAnomalyDetector::HybridAnomalyDetector() : SimpleAnomalyDetector(), cf(vector<correlatedFeatures>()), threshold(0.9) {
	// TODO Auto-generated constructor stub
}

HybridAnomalyDetector::~HybridAnomalyDetector() {
	// TODO Auto-generated destructor stub
}

string HybridAnomalyDetector::checkLine(const TimeSeries& ts, int i) const {
	vector<float> v = ts.getRow(i);
	int x, y;
	Point p(0,0);
	for (correlatedFeatures cor : this->cf) {
		try {
			x = ts.indxByStr(cor.feature1);
			y = ts.indxByStr(cor.feature2);
			p = (Point(v[x], v[y]));
			if (!isInCircle(cor.circle, &p)) {
				return cor.feature1 + "-" + cor.feature2;
			}
		} catch (const char* msg) {
			return "";
		}
	}
	return "";
}

void HybridAnomalyDetector::learnNormal(const TimeSeries& ts) {
	SimpleAnomalyDetector::learnNormal(ts);
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
			if (p > 0.5 && p < this->threshold && p > max) {
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
			vector<Point*> r;
			for (int j = 0; j < columns[i].size(); j++) {
				points.push_back(new Point(columns[i][j], columns[index][j]));
			}
			cor.circle = findMinCircle(points, r);
			cor.circle.radius *= 1.1;
			cor.threshold = cor.circle.radius;
			this->cf.push_back(cor);
		}
	}
}

vector<AnomalyReport> HybridAnomalyDetector::detect(const TimeSeries& ts) {
	vector<AnomalyReport> ar = vector<AnomalyReport>();
	string str1, str2;
	for (int i = 0; i < ts.rowCount(); i++) {
		str1 = this->checkLine(ts, i);
		str2 = SimpleAnomalyDetector::checkLine(ts, i);
		if (str1.compare("") != 0) {
			ar.push_back(AnomalyReport(str1, long(i + 1)));
		}
		if(str2.compare("") != 0) {
			ar.push_back(AnomalyReport(str2, long(i + 1)));
		}
	}
	return ar;
}

vector<correlatedFeatures> HybridAnomalyDetector::getNormalModel() {
	vector<correlatedFeatures> nm = SimpleAnomalyDetector::getNormalModel();
	nm.insert(nm.end(), cf.begin(), cf.end());
	return nm;
}