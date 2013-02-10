SRC = lcdtest.cpp
OUT = lcdtest 
OPT = -I/usr/local/include -L/usr/local/lib -lwiringPi
all:
	g++ $(OPT) -o $(OUT) $(SRC)

clean:
	rm -rf ./lcdtest
