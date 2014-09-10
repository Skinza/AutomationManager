#include <iostream>
#include "MainProcessor.h"
#include "Driver.h"
#include "P1Driver.h"
#include "ZwaveDriver.h"
#include <signal.h>


am::MainProcessor* mp;

void handle_sigint(int signal) {
	std::cout << "Caught signal " << std::endl;
	mp->stopProcessing();
}

int main() {
	int retval = 0;

	signal(SIGINT,handle_sigint);
	
	mp = new am::MainProcessor();

	mp->addDriver(new am::P1Driver());
	//mp->addDriver(new am::ZwaveDriver());
	

	std::cout << "mainprocessor start met verwerken (gebruikt mainthread ook)" << std::endl;
	mp->startProcessing();
	
	std::cout << "housekeeping - removing objects" << std::endl;
	delete mp;
	
	return retval;
}

