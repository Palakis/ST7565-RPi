#include <iostream>
#include "ST7565/ST7565.cpp"

// Numéros GPIO Broadcom
#define PIN_SID 10
#define PIN_SCLK 11
#define PIN_A0 24
#define PIN_RST 23
#define PIN_CS 8

using namespace std;

ST7565 glcd(PIN_SID, PIN_SCLK, PIN_A0, PIN_RST, PIN_CS);
unsigned char logo16_glcd_bmp[] = { 0x30, 0xf0, 0xf0, 0xf0, 0xf0, 0x30, 0xf8, 0xbe, 0x9f, 0xff, 0xf8, 0xc0, 0xc0, 0xc0, 0x80, 0x00, 0x20, 0x3c, 0x3f, 0x3f, 0x1f, 0x19, 0x1f, 0x7b, 0xfb, 0xfe, 0xfe, 0x07, 0x07, 0x07, 0x03, 0x00, };

void testdrawline();
void testdrawrect();
void testfillrect();
void testdrawcircle();
void testdrawchar();
void testdrawbitmap(const uint8_t *bitmap, uint8_t w, uint8_t h);
void testdrawlineanim();

int main()
{
	glcd.begin(0x18);

	glcd.display();
	usleep(2000000);
	glcd.clear();

	glcd.setpixel(10, 10, BLACK);
  	glcd.display();
  	usleep(2000000);
	glcd.clear();

	testdrawline();
	glcd.display();
	usleep(2000000);
	glcd.clear();

	testdrawrect();
	glcd.display();
	usleep(2000000);
	glcd.clear();

	testfillrect();
	glcd.display();
	usleep(2000000);
	glcd.clear();

	testdrawcircle();
	glcd.display();
	usleep(2000000);
	glcd.clear();

	glcd.fillcircle(32, 32, 10, BLACK);
	glcd.display();
	usleep(2000000);
	glcd.clear();

	testdrawchar();
	glcd.display();
	usleep(2000000);
	glcd.clear();

	glcd.drawstring(0, 0, "Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation");
	glcd.display();
	usleep(2000000);
	glcd.clear();

	testdrawlineanim();
	glcd.clear();
	glcd.display();
	usleep(500000);
	testdrawbitmap(logo16_glcd_bmp, 16, 16);
	return 0;
}

void testdrawlineanim()
{
	int width = 50;
	int height = 10;
	
	int x = (128 - width) / 2;
	int y = (64 - height) / 2;

	int step = 0;
	int maxi = width - 2;
	while(step < maxi) {
		glcd.clear();
		//glcd.drawline(step, 0, step, 64, BLACK);
		glcd.drawrect(x, y, width, height, BLACK);
		glcd.fillrect(x+1, y, step, height, BLACK);
		glcd.display();

		step++;
		usleep(100000);
	}
}

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

void testdrawbitmap(const uint8_t *bitmap, uint8_t w, uint8_t h)
{
	uint8_t icons[NUMFLAKES][3];
	srandom(666);

	for(int f = 0; f < NUMFLAKES; f++)
	{
		icons[f][XPOS] = random() % 128;
		icons[f][YPOS] = 0;
		icons[f][DELTAY] = random() % 5 + 1;
	}

	while(1) {
		for(int f = 0; f < NUMFLAKES; f++) {
			glcd.drawbitmap(icons[f][XPOS], icons[f][YPOS], logo16_glcd_bmp, w, h, BLACK);
		}
		glcd.display();
		usleep(100000);

		for(int f = 0; f < NUMFLAKES; f++) {
			glcd.drawbitmap(icons[f][XPOS], icons[f][YPOS], logo16_glcd_bmp, w, h, 0);
			icons[f][YPOS] += icons[f][DELTAY];

			if(icons[f][YPOS] > 64) {
				icons[f][XPOS] = random() % 128;
				icons[f][YPOS] = 0;
				icons[f][DELTAY] = random() % 5 + 1;
			}
		}
	}
}

void testdrawline()
{
	for(int i = 0; i<128; i+=4) {
		glcd.drawline(0, 0, i, 63, BLACK);
	}
	for(int i = 0; i<64; i+=4) {
		glcd.drawline(0, 0, 127, i, BLACK);
	}

	glcd.display();
	usleep(1000000);

	for(int i = 0; i<128; i+=4) {
		glcd.drawline(i, 63, 0, 0, WHITE);
	}
	for(int i = 0; i<64; i+=4) {
		glcd.drawline(127, i, 0, 0, WHITE);
	}
}

void testdrawrect()
{
	for(int i = 0; i<64; i+=2) {
		glcd.drawrect(i, i, 128-i, 64-i, BLACK);
	}
}

void testfillrect()
{
	for(int i = 0; i<64; i++) {
		glcd.fillrect(i, i, 128-i, 64-i, i%2);
	}
}

void testdrawcircle()
{
	for(int i = 0; i<64; i+=2) {
		glcd.drawcircle(63, 31, i, BLACK);
	}
}

void testdrawchar()
{
	for(int i = 0; i<168; i++) {
		glcd.drawchar((i % 21) * 6, i/21, i);
	}
}
