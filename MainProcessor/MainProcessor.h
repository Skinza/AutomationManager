#ifndef __MainProcessor_H
#define __MainProcessor_H

#include <string>
#include <map>

// starts the main processor and waits for messages to be dropped in the queue
namespace am {
	class Driver; // forward declaration because of circular dependency 
	class MainProcessor {
		public:
			MainProcessor();
			~MainProcessor();
			void addDriver(Driver* _newDriver);
			void startProcessing();
			void stopProcessing();
			
			void reportNewDevice(Driver* reportingDriver, std::string deviceID);
		private:
			std::map<std::string,Driver*> m_drivers;
			std::map<std::string, std::map<std::string,std::string> > m_driverDevices;
			bool m_processorRunning;
	}; // eo class MainProcessor
} // eo namespace am
#endif
