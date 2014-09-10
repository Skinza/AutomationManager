#ifndef ZwaveDriver_h
#define ZwaveDriver_h

#include "Driver.h"

namespace am {
	class ZwaveDriver: public Driver {
		public:
			ZwaveDriver();
			~ZwaveDriver();
			void start();
			std::string getDriverID();
		private:
			static void* readProcHelper(void*);
			static void* writeProcHelper(void*);
                        void readProc();
			void writeProc();
	};
}

#endif
