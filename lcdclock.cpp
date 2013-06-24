#include <iostream>
#include <ctime>
#include <sstream>
#include "ST7565/ST7565.cpp"
#include "minecrafter_font.c"

// Numéros GPIO Broadcom
#define PIN_SID 10
#define PIN_SCLK 11
#define PIN_A0 24
#define PIN_RST 23
#define PIN_CS 8

using namespace std;

ST7565 glcd(PIN_SID, PIN_SCLK, PIN_A0, PIN_RST, PIN_CS);
void drawclock();
bool blink = true;

int main()
{
	glcd.begin(0x18);
	glcd.clear();

	while(1) {
		drawclock();
		usleep(1000000);
	}
}

void drawclock() {
	int commonY = ((64 / 2) - (Minecrafter_height / 2));
	int commonX = (128 / 2);

	time_t temps = time(0);
	struct tm *now = localtime(&temps);

	char buffer[10];
	int clock[4];
	strftime(buffer, 10, "%H%M", now);
	for(int i = 0; i<4; i++) {
		stringstream ss;
		string s;
		ss << buffer[i];
		ss >> s;
		istringstream iss(s);
		iss >> clock[i];
	}

	glcd.clear();

	glcd.drawbitmap(commonX - (Minecrafter_width/2) - (Minecrafter_width*2), commonY, Minecrafter[clock[0]], Minecrafter_width, Minecrafter_height, BLACK);
	glcd.drawbitmap(commonX - (Minecrafter_width/2) - Minecrafter_width, commonY, Minecrafter[clock[1]], Minecrafter_width, Minecrafter_height, BLACK);

	if(blink) {
		glcd.drawbitmap(commonX - (Minecrafter_width / 2), commonY, Minecrafter[10], Minecrafter_width, Minecrafter_height, BLACK);
		blink = false;
	} else {
		blink = true;
	}

	glcd.drawbitmap(commonX + (Minecrafter_width/2), commonY, Minecrafter[clock[2]], Minecrafter_width, Minecrafter_height, BLACK);
	glcd.drawbitmap(commonX + (Minecrafter_width/2) + Minecrafter_width, commonY, Minecrafter[clock[3]], Minecrafter_width, Minecrafter_height, BLACK);

	glcd.display();
}
