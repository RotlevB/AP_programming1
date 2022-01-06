

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include<iostream>
#include <string.h>

#include <fstream>
#include <vector>
#include "HybridAnomalyDetector.h"

using namespace std;

class DefaultIO{
public:
	virtual string read()=0;
	virtual void write(string text)=0;
	virtual void write(float f)=0;
	virtual void read(float* f)=0;
	virtual ~DefaultIO(){}

	// you may add additional methods here
};

// you may add here helper classes
class CData {
public:
	TimeSeries *train, *test;
	HybridAnomalyDetector* detector;
	vector<AnomalyReport> reports;
	CData() :test(nullptr), train(nullptr), detector(new HybridAnomalyDetector()) {};
	~CData() {
		delete this->detector;
	}
};

class Range {
public:
	int start;
	int end;
	string description;
	Range(int start, int end, string description) :start(start), end(end), description(description) {}
};

// you may edit this class
class Command{
	DefaultIO* dio;
public:
	Command(DefaultIO* dio):dio(dio){}
	virtual void execute()=0;
	virtual ~Command(){}
};



// implement here your command classes
class UploadCommand : public Command {
	DefaultIO* dio;
	CData* data;
public:
	UploadCommand(DefaultIO* dio, CData* data) :Command(dio), dio(dio), data(data) {};
	void writeFile(string filename) {
		string str = dio->read();
		ofstream file;
		file.open(filename);
		while (str.compare("done") != 0) {
			file << str << "\n";
			str = dio->read();
		}
		dio->write("Upload complete.\n");
		file.close();
		return;
	}
	virtual void execute() {
		dio->write("Please upload your local train CSV file.\n");
		writeFile("train.csv");
		dio->write("Please upload your local test CSV file.\n");
		writeFile("test.csv");
		if (data->test != nullptr) {
			delete data->test;
			delete data->train;
		}
		data->test = new TimeSeries("test.csv");
		data->train = new TimeSeries("train.csv");
		return;
	}
};

class SettingsCommand : public Command {
	DefaultIO* dio;
	CData* data;
public:
	SettingsCommand(DefaultIO* dio, CData* data) :Command(dio), dio(dio), data(data) {};
	virtual void execute() {
		dio->write("The current correlation threshold is " + to_string(data->detector->getTreshold()) + "\n");
		dio->write("Type a new threshold\n");
		string str = dio->read();
		float f = stof(str);
		if (f < 0 || f > 1) {
			dio->write("please choose a value between 0 and 1.\n");
			execute();
		}
		return;
	}
};

class DetectCommand : public Command {
	DefaultIO* dio;
	CData* data;
public:
	DetectCommand(DefaultIO* dio, CData* data) :Command(dio), dio(dio), data(data) {};
	virtual void execute() {
		data->detector->learnNormal(*data->train);
		data->reports = data->detector->detect(*data->test);
		dio->write("anomaly detection complete.\n");
		return;
	}
};

class DisplayCommand : public Command {
	DefaultIO* dio;
	CData* data;
public:
	DisplayCommand(DefaultIO* dio, CData* data) :Command(dio), dio(dio), data(data) {};
	virtual void execute() {
		for (AnomalyReport report : data->reports) {
			dio->write(to_string(report.timeStep) + "	" + report.description + "\n");
		}
		dio->write("Done.\n");
		return;
	}
};

class AnalyzeResultsCommand : public Command {
	DefaultIO* dio;
	CData* data;
public:
	AnalyzeResultsCommand(DefaultIO* dio, CData* data) :Command(dio), dio(dio), data(data) {};
	vector<Range> buildRanges() {
		vector<Range> ranges;
		Range last = Range(0, 0, "first");
		for (AnomalyReport report : data->reports) {
			if (last.description.compare("first") != 0) {
				if (report.description.compare(last.description) == 0 && report.timeStep == last.end + 1) {
					last.end += 1;
				}
				else {
					ranges.push_back(last);
					last = Range(report.timeStep, report.timeStep, report.description);
				}
			}
			else {
				last = Range(report.timeStep, report.timeStep, report.description);
			}
		}
		if (last.description.compare("first") != 0) {
			ranges.push_back(last);
		}
		return ranges;
	}
	virtual void execute() {
		vector<Range> ranges = buildRanges();
		int start, end;
		float tp = 0, fp = 0;
		bool found;
		vector<Range> reported;
		dio->write("Please upload your local anomalies file.\n");
		string str = dio->read();
		while (str.compare("done") != 0) {
			vector<string> v = splitString(str, ",");
			start = stoi(v[0]);
			end = stoi(v[1]);
			reported.push_back(Range(start, end, ""));
			str = dio->read();
		}
		dio->write("Upload complete.\n");

		float p = float(reported.size());
		float n = float(data->train->rowCount() - data->reports.size());
		for (Range r1 : ranges) {
			found = false;
			for (Range r2 : reported) {
				if (!(r1.start > r2.end || r1.end < r2.start)) {
					tp += 1;
					found = true;
					break;
				}
			}
			if (!found) {
				fp += 1;
			}
		}
		tp /= p;
		fp /= n;
		dio->write("True Positive Rate: " + to_string(tp) + "\n");
		dio->write("False Positive Rate: " + to_string(fp) + "\n");
		return;
	}
};

class MenuCommand : public Command {
	DefaultIO* dio;
	CData* data;
public:
	MenuCommand(DefaultIO* dio, CData* data) : Command(dio), dio(dio), data(data) {};
	virtual void execute() {
		dio->write("Welcome to the Anomaly Detection Server.\n");
		dio->write("Please choose an option:\n");
		dio->write("1.upload a time series csv file\n");
		dio->write("2.algorithm settings\n");
		dio->write("3.detect anomalies\n");
		dio->write("4.display results\n");
		dio->write("5.upload anomalies and analyze results\n");
		dio->write("6.exit\n");
		return;
	}
};


#endif /* COMMANDS_H_ */
