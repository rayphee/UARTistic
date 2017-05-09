//-----------------------------------------------------------------------------
// EFM8BB3_UART0_Interrupt.c
//-----------------------------------------------------------------------------
// Copyright 2014 Silicon Laboratories, Inc.
// http://developer.silabs.com/legal/version/v11/Silicon_Labs_Software_License_Agreement.txt
//
// Program Description:
//
// This program demonstrates how to configure the EFM8BB3 to write to and
// read from the UART0 interface. The program reads a word using the UART0
// interrupt and outputs that word to the screen, with all characters in
// uppercase.
//
// Resources:
//   SYSCLK - 24.5 MHz HFOSC0 / 1
//   UART0  - 115200 baud, 8-N-1
//   Timer1 - UART0 clock source
//   P0.4   - UART0 TX
//   P0.5   - UART0 RX
//   P2.2   - Board Controller enable
//   P3.4   - Display enable
//
//-----------------------------------------------------------------------------
// How To Test: EFM8BB3 STK
//-----------------------------------------------------------------------------
// 1) Place the switch in "AEM" mode.
// 2) Connect the EFM8BB3 STK board to a PC using a mini USB cable.
// 3) Compile and download code to the EFM8BB3 STK board.
//    In Simplicity Studio IDE, select Run -> Debug from the menu bar,
//    click the Debug button in the quick menu, or press F11.
// 4) On the PC, open HyperTerminal (or any other terminal program) and connect
//    to the JLink CDC UART Port at 115200 baud rate and 8-N-1.
// 5) Run the code.
//    In Simplicity Studio IDE, select Run -> Resume from the menu bar,
//    click the Resume button in the quick menu, or press F8.
// 6) Using a terminal program on the PC, input any number of lower-case
//    characters, up to UART_BUFFERSIZE (default 64), followed by either
//    a carriage return ('\r'), a newline character ('\n'), or a tilda ('~').
//    The program will change the input characters to upper-case and output
//    them over UART.
//
// Target:         EFM8BB3
// Tool chain:     Generic
//
// Release 0.1 (ST)
//    - Initial Revision
//    - 20 MAY 2015
//

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <SI_EFM8BB3_Register_Enums.h>
#include <SI_EFM8BB3_Defs.h>
#include "retargetserial.h"
#include "render.h"
#include "../lib/bsp/efm8_memory_lcd/inc/render-extended.h"
#include "disp.h"
#include "joystick.h"
#include "InitDevice.h"

//-----------------------------------------------------------------------------
// Pin Definitions
//-----------------------------------------------------------------------------
SI_SBIT (DISP_EN, SFR_P3, 4);          // Display Enable
#define DISP_BC_DRIVEN   0             // 0 = Board Controller drives display
#define DISP_EFM8_DRIVEN 1             // 1 = EFM8 drives display

SI_SBIT (BC_EN, SFR_P2, 2);            // Board Controller Enable
#define BC_DISCONNECTED 0              // 0 = Board Controller disconnected
                                       //     to EFM8 UART pins
#define BC_CONNECTED    1              // 1 = Board Controller connected
                                       //     to EFM8 UART pins

//-----------------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------------
// Variables in Interrupts.c
unsigned char xdata textBuffer[520] = {0};
int bufOffset = 0;
int bufLen = 0;
char xdata thatDankDisplayShit[21];
int8_t scrollOffset = 0;
uint8_t allowScroll = 1;
int bl_;
int bo_;
int min(int a, int b){
	if(a<b) return a; else return b;
}
int max(int a, int b){
	if(a>b) return a; else return b;
}
//-----------------------------------------------------------------------------
// Main Routine
//-----------------------------------------------------------------------------
static uint8_t getJoystick(void)
{
  uint32_t mv;
  uint8_t dir;

  ADC0CN0_ADBUSY = 1;
  while (!ADC0CN0_ADINT);
  ADC0CN0_ADINT = 0;

  mv = ((uint32_t)ADC0) * 3300 / 1024;

  dir = JOYSTICK_convert_mv_to_direction(mv);

  return dir;
}

//-----------------------------------------------------------------------------
// getWaitJoystick
//-----------------------------------------------------------------------------
//
// Get joystick input. If joystick was moved, wait for release. Return joystick
// direction. Valid return values:
//  JOYSTICK_NONE   JOYSTICK_N   JOYSTICK_S
//  JOYSTICK_C      JOYSTICK_E   JOYSTICK_W
//
static uint8_t getWaitJoystick(void)
{
	uint32_t mv;

	 ADC0CN0_ADBUSY = 1;
	    while (!ADC0CN0_ADINT);
	    ADC0CN0_ADINT = 0;

	    mv = ((uint32_t)ADC0) * 3300 / 1024 / 4;
	    mv = mv+1;
	    return JOYSTICK_convert_mv_to_direction(mv);
}
//static uint8_t getWaitJoystick(void)
//{
//  uint8_t dir, dirSave;
//
//  dir = getJoystick();
//  dirSave = dir;
//
//  // wait for release then transition
//  while (dir != JOYSTICK_NONE)
//  {
//    dir = getJoystick();
//  }
//
//  return dirSave;
//}

static void processInput(uint8_t dir)
{
  // process input
  if (dir == JOYSTICK_N && allowScroll)
  {
    scrollOffset++;
    P1_B6 = 0;
  }
  else if (dir == JOYSTICK_S && allowScroll)
  {
    P1_B6 = 0;
    scrollOffset--;
  }
  else{
	  P1_B6 = 1;
	  P1_B5 = 1;

  }
  allowScroll = (dir == 0);
  scrollOffset = max(0,min(scrollOffset,(bufLen-1)/20-15));
}

SI_INTERRUPT (UART0_ISR, UART0_IRQn)
{
	int endOffset;
	if(P1_B4 == 0){
			P1_B4 = 1;
		}
		else{
			P1_B4 = 0;
		}
	while(SCON0_RI) {
			SCON0_RI = 0;
			endOffset = (bufOffset + bufLen)%520;
			textBuffer[endOffset] = SBUF0;
	if(bufLen < 519) bufLen++; else {
		bufOffset+=bo_;
		bufLen=bl_;
	}
		}
}

void main (void)
{
	uint8_t i;
	uint8_t j;
	uint8_t firstLine;
	bool hexModeStatus = false;
	bool lP0B2;

	bl_ = 500;
	bo_ = 20;
	enter_DefaultMode_from_RESET();


	DISP_EN = DISP_EFM8_DRIVEN;           	// EFM8 drives display

	TMR2CN0 = 2;

	BC_EN = BC_DISCONNECTED;               	// Board controller connected to EFM8
                                       	   // UART pins
	IE_EA = 1;

	DISP_Init();

	while(1)
	{
		processInput(getWaitJoystick());

		if (!P0_B2 && hexModeStatus) {
			hexModeStatus = false;
			lP0B2 = true;
		}
		else if(!P0_B2 && !hexModeStatus){
			hexModeStatus = true;
			lP0B2 = true;
		}
		else{
			lP0B2 = false;
		}
		if (!hexModeStatus){
			/*
			for (j=0; j<(bufLen/20);j++){
				for (i=0;i<21;i++){
					thatDankDisplayShit[i]=textBuffer[(21*j)+(i+scrollOffset)];
				}
				renderAndWrite(0,8*j,0, thatDankDisplayShit);
			}
			*/
			firstLine = max(0,(bufLen-1)/20-15)-scrollOffset;
			for(j=firstLine; j < min(firstLine+16,(bufLen-1)/20+1); j++){
				for(i = 0 ; i < 20; i++){
					// our offset in the buffer should be 20*j + i
					if(20*j + i >= bufLen) thatDankDisplayShit[i] = 0;
					else thatDankDisplayShit[i] = textBuffer[(20*j + i + bufOffset)%520];

				}
				renderAndWrite(0, 8*(j-firstLine),0,thatDankDisplayShit);
			}
		}
		else if (hexModeStatus) {
			DISP_ClearAll();
			renderAndWriteCenteredText(46, 1, "GOD MODE");
		}
	}
}
