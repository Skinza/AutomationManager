#ifndef __Driver_h
#define __Driver_h

#include "MainProcessor.h"
#include <string>

namespace am {
	class Driver {
		public:
			virtual std::string getDriverID() = 0;
			Driver();
			virtual ~Driver() = 0;
			void setMainProcessor(MainProcessor*);
			virtual void start() = 0;
			MainProcessor* m_itsMainProcessor;
			
	};
}

#endif
