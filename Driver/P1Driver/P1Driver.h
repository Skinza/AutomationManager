#ifndef P1Driver_h
#define P1Driver_h

#include "Driver.h"

namespace am {
	class P1Driver: public Driver {
		public:
			void start();
			std::string getDriverID();
			P1Driver();
			~P1Driver();
		private:
			int serialFD; // file pointer to serial device
			bool deviceReported;
			static void* readProcHelper(void*);
			void readProc();
			double p1rawdata2double(const std::string&);
	};
}

#endif
