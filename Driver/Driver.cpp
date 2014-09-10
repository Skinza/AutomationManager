#include "Driver.h"
#include <iostream>

namespace am {
	/*Driver::Driver(MainProcessor* _pMainProcessor) {
		this->m_itsMainProcessor = _pMainProcessor;
		std::cout << "Driver constructor called" << std::endl;
	}*/

	Driver::Driver() {
		// constructor does nothing
	}
	Driver::~Driver() {
		std::cout << "Driver wrapper destructor called" << std::endl;
	}

	void Driver::setMainProcessor(MainProcessor* _mainProcessor) {
		if(this->m_itsMainProcessor == NULL) { 
			this->m_itsMainProcessor = _mainProcessor;
			std::cout << "mainprocessor to report updates is set" << std::endl;
		} else {
			std::cout << "error binding to mainprocessor, mainprocessor allready set" << std::endl;
		}
	}
}
