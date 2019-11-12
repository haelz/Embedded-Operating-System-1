
#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "WS2812.h"
#include "xparameters.h"
#include "xil_io.h"
#include "sleep.h"
#include "math.h"
#include <stdint.h>
//#include "typedef.h"
//#include "xgpio.h"

#define WS2812ADR XPAR_WS2812_0_S00_AXI_BASEADDR

u16 result;

struct uint24_t { unsigned long v:24; };
typedef struct uint24_t __attribute__((packed)) uint24_t;

int GameArray[64];
int color = 0x0f0000;
int arraypos=0;

void drawPixel(int X, int Y);
void drawGame();

int main()
{
    init_platform();
    int readreg, Status;
    int itel;
    printf("Starting Pong.\n\r");

    //WS2812_mWriteReg(WS2812ADR,WS2812_S00_AXI_SLV_REG0_OFFSET, 0xFFFFFF);
    //WS2812_mWriteReg(WS2812ADR,WS2812_S00_AXI_SLV_REG64_OFFSET, 0xFF);
    //WS2812_mWriteReg(WS2812ADR,WS2812_S00_AXI_SLV_REG64_OFFSET, 0x00);
    //XGpio_DiscreteWrite(&Gpio, GPIO_CHANNEL, 0x00);
   // WS2812_mWriteReg(WS2812ADR, 0, 1500000);

	for(;;){
    //WS2812_mWriteReg(WS2812ADR,WS2812_S00_AXI_SLV_REG0_OFFSET, 0xFFFFFF);
		//readreg= WS2812_mReadReg(WS2812ADR,WS2812_S00_AXI_SLV_REG0_OFFSET);
		//printf("Readreg0: %d\n\r", readreg);
		//itel++;
		//XGpio_DiscreteWrite(&Gpio, GPIO_CHANNEL, 0x01);
		//XGpio_DiscreteWrite(&Gpio, GPIO_CHANNEL, 0x00);
		//WS2812_mWriteReg(WS2812ADR,WS2812_S00_AXI_SLV_REG0_OFFSET, 0xffffff);
		/*
		WS2812_mWriteReg(WS2812ADR,WS2812_S00_AXI_SLV_REG0_OFFSET, color);
		WS2812_mWriteReg(WS2812ADR,WS2812_S00_AXI_SLV_REG7_OFFSET, color);
		WS2812_mWriteReg(WS2812ADR,WS2812_S00_AXI_SLV_REG8_OFFSET, color);
		WS2812_mWriteReg(WS2812ADR,WS2812_S00_AXI_SLV_REG12_OFFSET, color);
		WS2812_mWriteReg(WS2812ADR,WS2812_S00_AXI_SLV_REG16_OFFSET, color);
		sleep(2);
		WS2812_mWriteReg(WS2812ADR,WS2812_S00_AXI_SLV_REG0_OFFSET, 0x000000);
		WS2812_mWriteReg(WS2812ADR,WS2812_S00_AXI_SLV_REG7_OFFSET, 0x000000);
		WS2812_mWriteReg(WS2812ADR,WS2812_S00_AXI_SLV_REG8_OFFSET, 0x000000);
		*/

		/*
		WS2812_mWriteReg(WS2812ADR,WS2812_S00_AXI_SLV_REG15_OFFSET, color);
		WS2812_mWriteReg(WS2812ADR,WS2812_S00_AXI_SLV_REG16_OFFSET, color);
		WS2812_mWriteReg(WS2812ADR,WS2812_S00_AXI_SLV_REG23_OFFSET, color);
		sleep(2);
		WS2812_mWriteReg(WS2812ADR,WS2812_S00_AXI_SLV_REG24_OFFSET, 0xFFFFFF);
		WS2812_mWriteReg(WS2812ADR,WS2812_S00_AXI_SLV_REG2_OFFSET, 0xFFFFFF);
		WS2812_mWriteReg(WS2812ADR,WS2812_S00_AXI_SLV_REG63_OFFSET, 0xFFFFFF);
		sleep(2);
		WS2812_mWriteReg(WS2812ADR,WS2812_S00_AXI_SLV_REG0_OFFSET, 0x000000);
		WS2812_mWriteReg(WS2812ADR,WS2812_S00_AXI_SLV_REG2_OFFSET, 0x000000);
		WS2812_mWriteReg(WS2812ADR,WS2812_S00_AXI_SLV_REG63_OFFSET, 0x000000);
		sleep(2);
		readreg = WS2812_mReadReg(WS2812ADR,WS2812_S00_AXI_SLV_REG0_OFFSET);
		printf("Readreg0: %d\n\r", readreg);

		 */
		drawPixel(1,1);
		drawPixel(1,8);
		drawPixel(8,1);
		drawPixel(8,8);
		drawGame();
		printf("loop");
		//sleep(2);
	}

    cleanup_platform();
    return 0;
}

void drawPixel(int X, int Y){
	arraypos=0;

	arraypos = (1-X)*(-9);
	printf("Arraypos: %d", arraypos);
	sleep(2);
	GameArray[(Y-X)+arraypos] = color;

}
void drawGame(){
	int rgbByte=0;
	for (int i=0; i<=252; i=i+4)
	{
		WS2812_mWriteReg(WS2812ADR,i,GameArray[rgbByte]);
		//printf("%d \n\r", i);
		//sleep(3);
		if (rgbByte < 63){
		rgbByte++;
		}
		else break;
		//printf("Stuck in loop");
	}
}
