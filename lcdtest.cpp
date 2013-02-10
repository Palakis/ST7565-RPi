#include <iostream>
#include "ST7565/ST7565.cpp"

// Numéros GPIO Broadcom
#define PIN_SID 10
#define PIN_SCLK 11
#define PIN_A0 24
#define PIN_RST 23
#define PIN_CS 8

using namespace std;

int main() {
	ST7565 glcd(PIN_SID, PIN_SCLK, PIN_A0, PIN_RST, PIN_CS);
	glcd.begin(0x18);
	glcd.display();
	cout << "Hello, World !" << endl;
	return 0;
}
