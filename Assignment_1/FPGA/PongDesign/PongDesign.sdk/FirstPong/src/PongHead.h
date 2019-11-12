#ifndef _PongHead_H_
#define _PongHead_H_

#include "stdlib.h"
#include "stdio.h"
#include "time.h"
#include "math.h"
#include <stdint.h>
#include "WS2812.h"
#include "Hcsr04_Sensor.h"

#define true 1
#define false 0

#define bigX 1
#define bigY 1
#define NumberX bigX*bigY
#define tickspeed 10

#define WS2812ADR XPAR_WS2812_0_S00_AXI_BASEADDR

int color = 0xff0000 ;
int BalkLinks = 3;
int BalkRechts = 3;
int BallX = 4;//1;
int BallY = 5; //4;
int BallMovex=1;
int BallMovey=0;
int Speed = tickspeed;
int LokatieBalkL=1; 
int LokatieBalkR=8;

uint24 PixelArray;

/** The rgb_color struct represents the color for an 8-bit GRB LED.
    Examples:
      Black:      (rgb_color){ 0, 0, 0 }
      Pure red:   (rgb_color){ 255, 0, 0 }
      Pure green: (rgb_color){ 0, 255, 0 }
      Pure blue:  (rgb_color){ 0, 0, 255 }
      White:      (rgb_color){ 255, 255, 255} */
typedef struct rgb_color
{
  unsigned char red, green, blue;
} rgb_color;


void StartGame();
void ticker();
void hitdetect();
void drawgame();
void drawPixel(int X, int Y);
void drawline(int x1, int y1, int x2, int y2);

#endif
