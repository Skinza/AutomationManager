#include "P1Driver.h"
#include <iostream>
#include <termios.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "P1Telegram.h"
#include <sstream>

namespace am {

	// for testing only
	const char* testTelegram =
                                "/ISk5\\2MT382-1003\n"
                                "\n"
                                "0-0:96.1.1(5A424244303035313232383832363132)\n"
                                "1-0:1.8.1(03269.309*kWh)\n"
                                "1-0:1.8.2(02111.834*kWh)\n"
                                "1-0:2.8.1(00000.002*kWh)\n"
                                "1-0:2.8.2(00000.000*kWh)\n"
                                "0-0:96.14.0(0002)\n"
                                "1-0:1.7.0(0000.76*kW)\n"
                                "1-0:2.7.0(0000.00*kW)\n"
                                "0-0:17.0.0(0999.00*kW)\n"
                                "0-0:96.3.10(1)\n"
                                "0-0:96.13.1()\n"
                                "0-0:96.13.0()\n"
                                "!\n";

	void P1Driver::start() {
		std::cout << "p1 is starting" << std::endl;
		// start reading thread
		//std::thread readThread = std::thread(&P1Driver::readProc,this);
		pthread_t readThread;
		pthread_create(&readThread,NULL,P1Driver::readProcHelper,this);

	}

	void * P1Driver::readProcHelper(void *context) {
		((P1Driver *)context)->readProc();
	}

	void P1Driver::readProc() {
		this->serialFD = open("/dev/pts/1",O_RDONLY | O_NOCTTY);
		if(this->serialFD) { // open serial device is success
			termios portSettings;
			char buf[255];
			int res;

			// zero out struct
			memset(&portSettings,0,sizeof(portSettings));
			// p1 settings are: B9600 7n1
			// see https://www.mkssoftware.com/docs/man5/struct_termios.5.asp for flags
			// set baudrate
			cfsetispeed(&portSettings,B9600);
			cfsetospeed(&portSettings,B9600);
			// set control flags
			portSettings.c_cflag |= (CLOCAL | CREAD | CS7 | PARENB);
			// set input flags
			portSettings.c_iflag |= (IGNBRK | IGNCR | IGNPAR);
			// we do not set output flags, p1 is read only
			// portSettings.c_oflag
			// set local flags
			portSettings.c_lflag |= (ICANON);

			// clean line and push settings
			tcflush(this->serialFD, TCIFLUSH);
			tcsetattr(this->serialFD,TCSANOW,&portSettings);

			bool isCurrentlyReadingTelegram = false;
			std::string dataline, datalineId, datalineData;
			std::size_t datalineFound;
			am::P1Telegram* telegram;
			while(1) { //tbd, some start/stop mechanism
				res = read(this->serialFD,buf,255);
				buf[res]=0;             /* set end of string, so we can printf */
				//printf(":%s:%d\n", buf, res);
				//printf("p1 data: %s", buf, res);
				if(!isCurrentlyReadingTelegram && buf[0] == '/') { // we where waiting for this start
					//std::cout << "begin of telegram" << std::endl;
					//printf("header: %s",buf,res);
					isCurrentlyReadingTelegram = true;
					// create telegram (we should delete this somewhere)
					telegram = new am::P1Telegram;
					telegram->header.assign(buf,res-1); // -1 to remove CRLF
				} else if(isCurrentlyReadingTelegram && buf[0] == '!') { // end of telegram detected
					//std::cout << "end of telegram" << std::endl;
					isCurrentlyReadingTelegram = false;
					// we should handle the telegram
					//std::cout << "test" <<  telegram->electricityUsedNormal << std::endl;
					telegram->debugPrint();
				} else if(isCurrentlyReadingTelegram) { // in the middle of telegram and begin was detected
					//printf("data: %s", buf);
					dataline.assign(buf,res-1);
					datalineFound = dataline.find_first_of('(',0);
					if(datalineFound != std::string::npos) {
						datalineId = dataline.substr(0,datalineFound);
						datalineData = dataline.substr(datalineFound+1,(dataline.length()-datalineFound)-2);
						if(datalineId == "0-0:96.1.1") {
							telegram->deviceID = datalineData;
						} else if(datalineId == "1-0:1.8.1") {
							telegram->electricityUsedLow= this->p1rawdata2double(datalineData);		
						} else if(datalineId == "1-0:1.8.2") {
                                                        telegram->electricityUsedNormal = this->p1rawdata2double(datalineData);
						} else if(datalineId == "1-0:2.8.1") {
                                                        telegram->electricityDeliveredLow = this->p1rawdata2double(datalineData);
						} else if(datalineId == "1-0:2.8.2") {
                                                        telegram->electricityDeliveredNormal = this->p1rawdata2double(datalineData);
						} else if(datalineId == "1-0:1.7.0") {
                                                        telegram->powerUsed = this->p1rawdata2double(datalineData);
						} else if(datalineId == "1-0:2.7.0") {
                                                        telegram->powerDelivered = this->p1rawdata2double(datalineData);
						} else if(datalineId == "0-0:96.14.0") {
							if(datalineData == "0001") {
                                                        	telegram->tariff = P1Telegram::LOW;
							} else {
								telegram->tariff = P1Telegram::NORMAL;
							}
						} /*else {
							std::cout << "this data is not implemented" << std::endl;
						}*/
					}
				}
			}				
		} else {
			// tbd: error handling could not open serial device
		}
		/*while(true) {
			if(!this->deviceReported) {
				this->m_itsMainProcessor->reportNewDevice(this, "/ISk5\\2MT382-1003");
				this->deviceReported = true;
			}
			usleep(1000000);
			std::cout << "hallo, ik kom uit de p1 driver" << std::endl;
		}*/
	}

	double P1Driver::p1rawdata2double(const std::string& _strdata) {
		double retval = 0.0;
		std::size_t starFound;
		starFound = _strdata.find_first_of('*',0);

		std::istringstream i(_strdata);
  		if (!(i >> retval)) {
			// something went wrong, tbd: errorhandling
		}
		
		return retval;
	}
		
	

	P1Driver::P1Driver():
		deviceReported(false),
		serialFD(0)
	{
		std::cout << "constructor of p1driver called" << std::endl;
	}

	P1Driver::~P1Driver() {
		std::cout << "p1 driver destructed" << std::endl;
	}

	std::string P1Driver::getDriverID() { return "P1"; }


}
