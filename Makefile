OPT = -I/usr/local/include -L/usr/local/lib -lwiringPi
all: lcdtest lcdclock

lcdtest: clean
	g++ $(OPT) -o lcdtest lcdtest.cpp

lcdclock: clean
	g++ $(OPT) -o lcdclock lcdclock.cpp

clean:
	rm -rf ./lcdtest
	rm -rf ./lcdclock
