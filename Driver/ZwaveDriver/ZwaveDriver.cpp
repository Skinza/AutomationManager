#include "ZwaveDriver.h"
#include <iostream>
#include <unistd.h>

namespace am {
	void ZwaveDriver::start() {
		pthread_t readThread, writeThread;
		pthread_create(&readThread,NULL,ZwaveDriver::readProcHelper,this);
		pthread_create(&writeThread,NULL,ZwaveDriver::writeProcHelper,this);
	}

	void * ZwaveDriver::readProcHelper(void* context) {
		((ZwaveDriver *)context)->readProc();
	}

	void * ZwaveDriver::writeProcHelper(void* context) {
		((ZwaveDriver *)context)->writeProc();
	}

	void ZwaveDriver::readProc() {
		while(1) {
			std::cout << "hello from zwave reader" << std::endl;
			usleep(1000000);
		}
	}

	void ZwaveDriver::writeProc() {
		while(1) {
			std::cout << "hello from zwave writer" << std::endl;
			usleep(1000000);
		}
	}

	ZwaveDriver::ZwaveDriver() {}
	ZwaveDriver::~ZwaveDriver() {
		std::cout << "zwave driver destructed" << std::endl;
	}
	std::string ZwaveDriver::getDriverID() { return "ZWAVE"; }
	
}
