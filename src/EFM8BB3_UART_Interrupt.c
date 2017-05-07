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
//#include "spi.h"
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
unsigned char xdata textBuffer[520];
int bufOffset = 0;
int bufLen = 0;

//-----------------------------------------------------------------------------
// Main Routine
//-----------------------------------------------------------------------------
SI_INTERRUPT (UART0_ISR, UART0_IRQn)
{
	int endOffset;
	if(P1_B4 == 0){
			P1_B4 = 1;
			P1_B5 = 1;
			P1_B6 = 1;
		}
		else{
			P1_B4 = 0;
			P1_B5 = 0;
			P1_B6 = 0;
		}
	while(SCON0_RI) {
			SCON0_RI = 0;
			endOffset = (bufOffset + bufLen)%520;
			textBuffer[endOffset] = SBUF0;
	if(bufLen < 520) bufLen++; else bufOffset++;
		}
}

void main (void)
{
   enter_DefaultMode_from_RESET();

   DISP_EN = DISP_EFM8_DRIVEN;           // EFM8 does not drive display

   BC_EN = BC_DISCONNECTED;               // Board controller connected to EFM8
                                       // UART pins
   IE_EA = 1;

   DISP_Init();

   renderAndWriteCenteredText(46, 1, "Hello");

   while(1)
   {

   }
}
