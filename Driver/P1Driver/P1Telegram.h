#ifndef P1Telegram_H
#define P1Telegram_H

#include <string>

namespace am {
	//see http://www.netbeheernederland.nl/themas/hotspot/hotspot-documenten/?dossierid=11010056&title=Slimme%20meter&onderdeel=Documenten&pageindex=1
	class P1Telegram {
		public:
			enum TariffIndicator {
				NORMAL = 2,
				LOW = 1
			};
			// constructor
			P1Telegram();
			// header info
			std::string header;
			// p1 data objects
			std::string deviceID;
			// meter reading used normal tariff in 0.001kWh
			double electricityUsedNormal;
			// meter reading used low tariff in 0.001kWh
			double electricityUsedLow;
			// meter reading delivered normal tarif in 0.001kWh
			double electricityDeliveredNormal;
			// meter reading delivered low tarif in 0.001kWh
			double electricityDeliveredLow;
			// current tariff indicator
			TariffIndicator tariff;
			// current power used
			double powerUsed;
			// current power delivered to net
			double powerDelivered;

			void debugPrint();
	};
}
#endif
