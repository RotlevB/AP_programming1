#include "CLI.h"

CLI::CLI(DefaultIO* dio){
	this->dio = dio;
	this->data = new CData();
	this->commands = vector<Command*>();
	this->commands.push_back(new MenuCommand(this->dio, this->data));
	this->commands.push_back(new UploadCommand(this->dio, this->data));
	this->commands.push_back(new SettingsCommand(this->dio, this->data));
	this->commands.push_back(new DetectCommand(this->dio, this->data));
	this->commands.push_back(new DisplayCommand(this->dio, this->data));
	this->commands.push_back(new AnalyzeResultsCommand(this->dio, this->data));
}

void CLI::start(){
	int i = 0;
	while (i != 6) {
		commands[i]->execute();
		if (i != 0) {
			commands[0]->execute();
		}
		i = stoi(dio->read());
		if (i < 0 || i > 6) {
			i = 0;
		}
		
	}
}


CLI::~CLI() {
	delete this->data;

}

