/*
 * render-extended.c
 *
 *  Created on: Apr 12, 2017
 *      Author: rafi
 */

#include "bsp.h"
#include "disp.h"
#include "../lib/bsp/efm8_memory_lcd/inc/render-extended.h"
#include <string.h>

static SI_SEGMENT_VARIABLE(line[16], uint8_t, RENDER_LINE_SEG);

void renderAndWriteCenteredText(uint8_t y, uint8_t underlined, SI_VARIABLE_SEGMENT_POINTER(str, char, RENDER_STR_SEG))
{
	uint8_t x = (128-RENDER_GetStrSize(str))/2;
	renderAndWrite(x, y, underlined, str);
	RENDER_ClrLine(line);
}

void renderAndWriteHorizontalLine(uint8_t xstart, uint8_t xend, uint8_t y){
	RENDER_LineSegmentLine(line, xstart, xend);
	DISP_WriteLine(y, line);
	RENDER_ClrLine(line);
}

void renderAndWrite(uint8_t x, uint8_t y, uint8_t underlined, SI_VARIABLE_SEGMENT_POINTER(str, char, RENDER_STR_SEG)){
	uint8_t internal_y;
	for (internal_y = 0; internal_y < FONT_HEIGHT; internal_y++)
		{
			RENDER_StrLine(line, x, internal_y, str);
			DISP_WriteLine(y+internal_y, line);
		}
	if (underlined != 0){
		renderAndWriteHorizontalLine(x, x+RENDER_GetStrSize(str), y+8);
	}
	RENDER_ClrLine(line);
}

uint16_t timeInMilliseconds(uint16_t timeInMilli){
	uint16_t timeInMilliseconds = timeInMilli;
	timeInMilliseconds = timeInMilliseconds % 10;
	return timeInMilliseconds;
}

uint16_t timeInSeconds(uint16_t timeInMilli){
	uint16_t timeInSeconds;
	timeInSeconds = (timeInMilli / 10) % 60;
	return timeInSeconds;
}

uint16_t timeInMinutes(uint16_t timeInMilli){
	uint16_t timeInMinutes;
	timeInMinutes = (timeInMilli / 600) % 60;
	return timeInMinutes;
}

uint16_t timeInHours(uint16_t timeInMilli){
	uint16_t timeInHours;
	timeInHours = (timeInMilli / 36000) % 24;
	return timeInHours;
}
