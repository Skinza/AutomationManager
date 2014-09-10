#include "MainProcessor.h"
#include "Driver.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <unistd.h>

namespace am {
	MainProcessor::MainProcessor():
		m_processorRunning(false)
	{
		std::cout << "MainProcessor Constructor" << std::endl;
	}

	MainProcessor::~MainProcessor() {
		std::cout << "MainProcessor Destructor" << std::endl;
		for(std::map<std::string,Driver*>::iterator iter = this->m_drivers.begin(); iter != this->m_drivers.end(); ++iter) {
			// tbd: stop the driver gracefull
			// tbd: check thread safety
			this->m_drivers.erase(iter);
			delete iter->second;
		}
	}

	void MainProcessor::reportNewDevice(Driver* reportingDriver, std::string deviceID) {
		bool deviceFound = false;

		if(this->m_driverDevices.count(reportingDriver->getDriverID())) {
			if(this->m_driverDevices.at(reportingDriver->getDriverID()).count(deviceID)) {
				deviceFound = true;
			}
		} 

		if(!deviceFound) {
			std::cout << "New device reported (" << reportingDriver->getDriverID()  << " - " << deviceID  << ")" << std::endl;
                        this->m_driverDevices[reportingDriver->getDriverID()][deviceID] = "pointer to internal device";
		} else {
			std::cout << "device (" << reportingDriver->getDriverID()  << " - " << deviceID  << ") is allready known" << std::endl;
		}
	} 
	void MainProcessor::addDriver(Driver* _newDriver) {
		// set the mainprocessor so the driver knows how to report changes
		_newDriver->setMainProcessor(this);
		// add the driver to the global driver map 
		// tbd: is this thread safe? for now only mainthread alters map
		this->m_drivers[_newDriver->getDriverID()] = _newDriver;
		// start the driver
		_newDriver->start();
	}

	void MainProcessor::startProcessing() {
		this->m_processorRunning = true;
		while(this->m_processorRunning) {
			std::cout << "processor dummy sleeping for 5 seconds" << std::endl;
			usleep(5000000);
		}
	}

	void MainProcessor::stopProcessing() {
		//tbd: thread safety
		this->m_processorRunning = false;
	}
}
