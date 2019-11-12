/*
    Copyright (C) 2017 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
    Copyright (C) 2012 - 2018 Xilinx, Inc. All Rights Reserved.

    Permission is hereby granted, free of charge, to any person obtaining a copy of
    this software and associated documentation files (the "Software"), to deal in
    the Software without restriction, including without limitation the rights to
    use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
    the Software, and to permit persons to whom the Software is furnished to do so,
    subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software. If you wish to use our Amazon
    FreeRTOS name, please do so in a fair use way that does not cause confusion.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
    FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
    COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
    IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
    CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

    http://www.FreeRTOS.org
    http://aws.amazon.com/freertos


    1 tab == 4 spaces!
*/

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
/* Xilinx includes. */
#include "xil_printf.h"
#include "xparameters.h"
/*user includes */
#include "gpio.h"
#include "gpioPS.h"
#include "PongHead.h"

#define TIMER_ID	1
#define DELAY_10_SECONDS	10000UL
#define DELAY_1_SECOND		1000UL
#define TIMER_CHECK_THRESHOLD	9
/*-----------------------------------------------------------*/

/* The Tx and Rx tasks as described at the top of this file. */
static void prvTxTask( void *pvParameters );
static void prvRxTask( void *pvParameters );
static void vTimerCallback( TimerHandle_t pxTimer );
/*-----------------------------------------------------------*/

/* The queue used by the Tx and Rx tasks, as described at the top of this
file. */
static TaskHandle_t xTxTask;
static TaskHandle_t xRxTask;
static QueueHandle_t xQueue = NULL;
static TimerHandle_t xTimer = NULL;
char HWstring[15] = "Hello World";
long RxtaskCntr = 0;


#define GPIO_7SEGMENT_DEVICE_ID XPAR_GPIO_0_DEVICE_ID
#define Switches_Channel 1

u32 Data;

XGpio Gpio;
XGpioPs GpioPS;
u32 Input_Pin; /* Switch button */
void startGPIOPS();

int main( void )
{
	startGPIOHardware();

	xil_printf( "Starting NeoPixel 8x8 Matrix: Pong Game by Gilles, Dennis and Jonas.\r\n" );

	xTaskCreate( 	getPlayer1Input, 					/* The function that implements the task. */
					( const char * ) "Player1Input", 		/* Text name for the task, provided to assist debugging only. */
					configMINIMAL_STACK_SIZE, 	/* The stack allocated to the task. */
					NULL, 						/* The task parameter is not used, so set to NULL. */
					tskIDLE_PRIORITY,			/* The task runs at the idle priority. */
					&xTxTask );

	xTaskCreate( 	getPlayer2Input, 					/* The function that implements the task. */
					( const char * ) "Player2Input", 		/* Text name for the task, provided to assist debugging only. */
					configMINIMAL_STACK_SIZE, 	/* The stack allocated to the task. */
					NULL, 						/* The task parameter is not used, so set to NULL. */
					tskIDLE_PRIORITY,			/* The task runs at the idle priority. */
					&xTxTask );

	xTaskCreate( GamePongTask,
				 ( const char * ) "GamePongLogic",
				 configMINIMAL_STACK_SIZE,
				 NULL,
				 tskIDLE_PRIORITY + 1,
				 &xRxTask );

	xQueuePlayer1 = xQueueCreate( 	2,						/* There is only one space in the queue. */
							sizeof( HWstring ) );	/* Each space in the queue is large enough to hold a uint32_t. */
	xQueuePlayer2 = xQueueCreate( 	2,						/* There is only one space in the queue. */
							sizeof( HWstring ) );	/* Each space in the queue is large enough to hold a uint32_t. */

	/* Check the queue was created. */
	configASSERT( xQueue );

	const TickType_t x10seconds = pdMS_TO_TICKS( DELAY_10_SECONDS );

	xTimerTickRate = xTimerCreate( (const char *) "Timer",
							x10seconds,
							pdFALSE,
							(void *) TIMER_ID,
							vTimerCallback);

	/* Check the timer was created. */
	configASSERT( xTimer );

	xTimerStart( xTimer, 0 );

	/* Start the tasks and timer running. */
	vTaskStartScheduler();

	for( ;; );
}


/*-----------------------------------------------------------*/
static void getPlayer1Input( void *pvParameters )
{
const TickType_t x1second = pdMS_TO_TICKS( DELAY_1_SECOND );
	for( ;; )
	{

		if (XGpioPs_ReadPin(&GpioPS, Input_Pin))
			{
			player1balk--;
			}
		if (XGpioPs_ReadPin(&GpioPS, Input_Pin))
			{
			player1balk++;
			}

			xQueueSend( xQueuePlayer1,			/* The queue being written to. */
					&playerpositiony, /* The address of the data being sent. */
					0UL );			/* The block time. */
	}
}

/*-----------------------------------------------------------*/
static void getPlayer2Input( void *pvParameters )
{

	for( ;; )
	{
		switch (readvalue){
		case 0 ... 35 :
		}
		/* Block to wait for data arriving on the queue. */
		xQueueSend( 	xQueuePlayer2,				/* The queue being read. */
						&Recdstring,	/* Data is read into this address. */
						portMAX_DELAY );	/* Wait without a timeout for data. */

		/* Print the received data. */
		xil_printf( "Rx task received string from Tx task: %s\r\n", Recdstring );
		RxtaskCntr++;
	}
}

/*-----------------------------------------------------------*/
static void GamePongTask( void *pvParameters )
{
//char Recdstring[15] = "";

	for( ;; )
	{
		/* Block to wait for data arriving on the queue. */
		xQueueReceive( 	xQueue,				/* The queue being read. */
						Recdstring,	/* Data is read into this address. */
						portMAX_DELAY );	/* Wait without a timeout for data. */

		/* Print the received data. */
		xil_printf( "Rx task received string from Tx task: %s\r\n", Recdstring );
		RxtaskCntr++;
	}
}

void startGPIOHardware()
{
	volatile int Delay;

	int status;

	//Init PS
	XGpioPs_Config *GPIOPSConfigPtr;
	GPIOPSConfigPtr = XGpioPs_LookupConfig(XPAR_PS7_GPIO_0_DEVICE_ID);
	status = XGpioPs_CfgInitialize(&GpioPS, GPIOPSConfigPtr,GPIOPSConfigPtr->BaseAddr);

	if (status != XST_SUCCESS) {
		printf("status error \n\r");
		return XST_FAILURE;
	}
    printf("Starting GPIO PS\n\r");
    Input_Pin = 0;
	XGpioPs_SetDirectionPin(&GpioPS,Input_Pin,0);

	//Init PL
	XGpio_Config *GPIOConfigPtr;
	status = XGpio_Initialize(&Gpio, GPIO_7SEGMENT_DEVICE_ID);
	if (status != XST_SUCCESS) {
		xil_printf("Gpio Initialization Failed\r\n");
		return XST_FAILURE;
	}

	XGpio_SetDataDirection(&Gpio, Switches_Channel, 0x11);

    return;
}


