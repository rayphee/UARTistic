/*
 * render-extended.h
 *
 *  Created on: Apr 12, 2017
 *      Author: rafi
 */

#ifndef LIB_BSP_EFM8_MEMORY_LCD_INC_RENDER_EXTENDED_H_
#define LIB_BSP_EFM8_MEMORY_LCD_INC_RENDER_EXTENDED_H_

#include "../lib/bsp/efm8_memory_lcd/inc/config/render_config.h"
#include "render.h"

#if !defined(RENDER_LINE_SEG) || defined(IS_DOXYGEN)
/***************************************************************************//**
 * @brief Controls variable segment pointer target memory space for parameters
 *
 * Specifies the memory space for a user defined line buffer array.
 *
 * Default setting is @c SI_SEG_IDATA and may be overridden by defining in
 * **memory_lcd_config.h**.
 *
 ******************************************************************************/
#define RENDER_LINE_SEG                         SI_SEG_IDATA
#endif

#if !defined(RENDER_STR_SEG) || defined(IS_DOXYGEN)
/***************************************************************************//**
 * @brief Controls variable segment pointer target memory space for parameters
 *
 * Specifies the memory space for a user defined string.
 *
 * Default setting is @c SI_SEG_GENERIC and may be overridden by defining in
 * **memory_lcd_config.h**.
 *
 ******************************************************************************/
#define RENDER_STR_SEG                          SI_SEG_GENERIC
#endif

#define FONT_WIDTH_EXT          6               ///< Character width in px
#define FONT_HEIGHT_EXT         8               ///< Character height in px
#define FONT_MAP_SPACING_EXT    8               ///< Character spacing in font map

void renderAndWriteCenteredText(uint8_t posy, uint8_t underlined, SI_VARIABLE_SEGMENT_POINTER(str, char, RENDER_STR_SEG));

void renderAndWrite(uint8_t x, uint8_t y, uint8_t underlined, SI_VARIABLE_SEGMENT_POINTER(str, char, RENDER_STR_SEG));

void renderAndWriteHorizontalLine(uint8_t xstart, uint8_t xend, uint8_t y);

uint16_t timeInMilliseconds(uint16_t timeInMilli);
uint16_t timeInSeconds(uint16_t timeInMilli);
uint16_t timeInMinutes(uint16_t timeInMilli);
uint16_t timeInHours(uint16_t timeInMilli);

#endif /* LIB_BSP_EFM8_MEMORY_LCD_INC_RENDER_EXTENDED_H_ */
