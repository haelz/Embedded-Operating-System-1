
#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "WS2812.h"
#include "xparameters.h"
#include "xil_io.h"
#include "sleep.h"
#include "math.h"
#include "time.h"
#include <stdint.h>
//#include "typedef.h"
//#include "xgpio.h"

#define WS2812ADR XPAR_WS2812_0_S00_AXI_BASEADDR
#define COLOUR_INTENSITY 10

u16 result;

struct uint24_t { unsigned long v:24; };
typedef struct uint24_t __attribute__((packed)) uint24_t;

struct pixelColour
{
	uint8_t green, red, blue;
};

//--globals--
int GameArray[64];
struct pixelColour colourArray[8][8];

int BalkHit, LokatieBalkL, LokatieBalkR, BallX, BallY, BalkLinks, BalkRechts, BallMovex, BallMovey;

void drawPixel(int X, int Y);
void drawLine(int x1, int y1, int x2, int y2);
void initPongLevel();
void drawGame();
void hitdetect();
void clearArray();
void updateGame();

int main()
{
	srand((unsigned) time(0));
    LokatieBalkL = 0;
    LokatieBalkR = 7;
    BalkRechts= 3;
    BalkLinks = 3;
    BallX=rand(4)+2;
	BallY=rand(7);
	BallMovex = 1;

    init_platform();
    printf("Starting Pong.\n\r");
	for(;;)
	{
		//colourArray[0][0].blue = 100;
		updateGame();

	}

    cleanup_platform();
    return 0;
}

void updateGame()
{
	initPongLevel();
	//sleep(1);
    drawGame();
    hitdetect();
    clearArray();
	BallX = BallX + BallMovex;
    BallY = BallY + BallMovey;
}

//draws one pixel in screenbuf
void drawPixel(int X, int Y)
{

	colourArray[Y][X].red = COLOUR_INTENSITY;
}

void initPongLevel(){

	//color=GROEN
	drawLine(LokatieBalkL, BalkLinks, LokatieBalkL, BalkLinks+2);
	//color=BLUE
	drawLine(LokatieBalkR, BalkRechts, LokatieBalkR, BalkRechts+2);
	//Color=RED
	drawPixel(BallX,BallY);
}

//draws to screen buffer
void drawGame()
{
	for(int y = 0; y <= 8; ++y)
	{
		for(int x = 0; x <= 8; ++x)
		{
			int data = (colourArray[y][x].green << 16) + (colourArray[y][x].red << 8) + colourArray[y][x].blue;
			WS2812_mWriteReg(WS2812ADR,((x*4)+(y*32)), data);
		}
	}
}

void clearArray()
{
	for(int y = 0; y <= 8; ++y)
	{
		for(int x = 0; x <= 8; ++x)
		{
			colourArray[y][x].blue = 0;
			colourArray[y][x].green = 0;
			colourArray[y][x].red = 0;
		}
	}
}

void drawLine (int x1, int y1, int x2, int y2) {      //draw a line from x1,y1 to x2,y2
int dx, dy, sx, sy, err, e2;

dx = abs (x2-x1);
dy = abs (y2-y1);
if (x1<x2) sx = 1;
   else sx = -1;
if (y1<y2) sy = 1;
   else sy = -1;
err = dx-dy;
do {
   drawPixel (x1, y1);
   if ((x1 == x2) && (y1 == y2))
      break;
   e2 = 2*err;
   if (e2 > -dy) {
      err = err - dy;
		 x1 = x1+sx;
   }
   if (e2 < dx) {
      err = err + dx;
		 y1 = y1 + sy;
   }
} while (1);
	return;
}

void hitdetect()
{
  if(	BallMovex == 1 && BallX == ((LokatieBalkR-1))  )
	{
		if (BallY == BalkRechts)
		{
		BallMovex = BallMovex * -1;
		BallMovey = -1;
            BalkHit++;
		}
		else if (BallY == BalkRechts+1)
		{
		BallMovex = BallMovex * -1;
		BallMovey = 0;
            BalkHit++;
		}

		else if (BallY == BalkRechts+2)
		{
		BallMovex = BallMovex * -1;
		BallMovey = 1;
             BalkHit++;
		}


	}
	else if ( BallMovex == -1 && BallX == (LokatieBalkL+1))
	{
		if (BallY == BalkLinks)
		{
		BallMovex = BallMovex * -1;
		BallMovey = -1;
             BalkHit++;
		}
		else if (BallY == BalkLinks+1)
		{
		BallMovex = BallMovex * -1;
		BallMovey = 0;
             BalkHit++;
		}
		else if (BallY == BalkLinks+2)
		{
		BallMovex = BallMovex * -1;
		BallMovey = 1;
             BalkHit++;}
	}

    if (BallY == 7 || BallY == 0)
    {
        BallMovey = BallMovey * -1;
    }

}
