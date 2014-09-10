#include "P1Telegram.h"
#include <iostream>
#include <stdio.h>

namespace am {
	P1Telegram::P1Telegram():
		header(""),
		deviceID(""),
		electricityUsedNormal(0.0),
		electricityUsedLow(0.0),
		electricityDeliveredNormal(0.0),
		electricityDeliveredLow(0.0),
		tariff(NORMAL),
		powerUsed(0.0),
		powerDelivered(0.0)	
	{
	}

	void P1Telegram::debugPrint() {
		std::cout << "===== Telegram =====" << std::endl;
		std::cout << "Device Specific Header: " << this->header << std::endl;
		std::cout << "DeviceID: " << this->deviceID << std::endl;
		std::cout << "Tariff: ";
		if(this->tariff == P1Telegram::NORMAL) std::cout << "NORMAL" << std::endl;
		if(this->tariff == P1Telegram::LOW) std::cout << "LOW" << std::endl;
		printf("Meter used normal: %fkWh\n",this->electricityUsedNormal);
		printf("Meter used low: %fkWh\n",this->electricityUsedLow);
		printf("Meter delivered normal: %fkWh\n",this->electricityDeliveredNormal);
		printf("Meter delivered low: %fkWh\n",this->electricityDeliveredLow);
		printf("Power used: %fkW\n",this->powerUsed);
		printf("Power delivered: %fkW\n",this->powerDelivered);
		std::cout << "====================" << std::endl;
		

	}
}
