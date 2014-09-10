all:
	g++ \
		-I MainProcessor \
		-I Driver \
		-I Driver/P1Driver \
		-I Driver/ZwaveDriver \
		Driver/Driver.cpp \
		Driver/ZwaveDriver/ZwaveDriver.cpp \
		Driver/P1Driver/P1Driver.cpp \
		Driver/P1Driver/P1Telegram.cpp \
		MainProcessor/MainProcessor.cpp \
		Main.cpp \
		-pthread \
		-o driverProcessor 

obj/MainProcessor.o: 
	g++ -c MainProcessor/MainProcessor.cpp -o obj/MainProcessor.o
