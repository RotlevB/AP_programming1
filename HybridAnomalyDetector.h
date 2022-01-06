

#ifndef HYBRIDANOMALYDETECTOR_H_
#define HYBRIDANOMALYDETECTOR_H_

#include "SimpleAnomalyDetector.h"
#include "minCircle.h"

class HybridAnomalyDetector:public SimpleAnomalyDetector {
	vector<correlatedFeatures> cf;
	float threshold;
public:
	HybridAnomalyDetector();
	virtual ~HybridAnomalyDetector();
	virtual string checkLine(const TimeSeries& ts, int i) const;
	virtual void learnNormal(const TimeSeries& ts);
	virtual vector<AnomalyReport> detect(const TimeSeries& ts);
	vector<correlatedFeatures> getNormalModel();
	virtual void setThreshold(float threshold);
	virtual float getTreshold();
};

#endif /* HYBRIDANOMALYDETECTOR_H_ */
