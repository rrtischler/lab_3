/*******************************************************************************
*                                                                              *
*  @file      oled_printf.c                                                    *
*  @verbatim                                                                   *
*                       ___ \    ___| _)              __ __|                   *
*                       |    | \    \  |   _     __ \   |                      *
*                       |    |  ---    | (   |  |   |   |                      *
*                      _____/_)_____/ _| \__,|  |  _|  _|                      *
*                                        |___/                                 *
*                      Digital Signalprocessing Technology                     *
*  @endverbatim                                                                *
*  @brief     simple OLED printf                                               *
*                                                                              *
*  @author    D.SignT GmbH & Co. KG, Claus Hermbusche                          *
*  @date      2011-09-19
*                                                                              *
*  Software License Agreement                                                  *
*  Copyright (C) 2011 D.SignT GmbH & Co. KG - http://www.dsignt.de             *
*                                                                              *
*  Redistribution and use in source and binary forms, with or without          *
*  modification, are permitted provided that the following conditions          *
*  are met:                                                                    *
*                                                                              *
*    Redistributions of source code must retain the above copyright            *
*    notice, this list of conditions and the following disclaimer.             *
*                                                                              *
*    Redistributions in binary form must reproduce the above copyright         *
*    notice, this list of conditions and the following disclaimer in the       *
*    documentation and/or other materials provided with the                    *
*    distribution.                                                             *
*                                                                              *
*    Neither the name of D.SignT GmbH & Co. KG nor the names of its            *
*    contributors may be used to endorse or promote products derived           *
*    from this software without specific prior written permission.             *
*                                                                              *
*  Disclaimer                                                                  *
*  THIS SOFTWARE IS PROVIDED BY D.SIGNT GMBH & CO. KG "AS IS" AND ANY          *
*  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE           *
*  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR          *
*  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL D.SIGNT GMBH & CO. KG BE          *
*  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR         *
*  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT           *
*  OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR          *
*  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,       *
*  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE        *
*  OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,           *
*  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                          *
*                                                                              *
*******************************************************************************/

/*******************************************************************************
*                                                                              *
*    INCLUDES                                                                  *
*                                                                              *
*******************************************************************************/
/*******************************************************************************
  Runtime Source
*******************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

/*******************************************************************************
  Board Support Library
*******************************************************************************/
#include ".\bsl\include\ezdsp5502.h"
#include "lcd.h"

/*******************************************************************************
  common support function
*******************************************************************************/
#include "..\netlib\dsknet.h"                /* network support               */
#include "common.h"                          /* init app, on exit function    */
#include "oled_printf.h"                     /* Oled defines                  */

/******************************************************************************/
/*                                                                            */
/*   DEFINES                                                                  */
/*                                                                            */
/******************************************************************************/

/*******************************************************************************
 8x8 font limits
*******************************************************************************/
#define F8X8_MIN           f8x8[5]
#define F8X8_MAX           f8x8[6]
#define F8X8_WIDTH_OFFSET  7
#define F8X8_FIRST_CHAR    97

/*******************************************************************************
 conversion buffer limit
*******************************************************************************/
#define MAX_PRINTF_BUFFER   128

/******************************************************************************/
/*                                                                            */
/*   GLOBALS                                                                  */
/*                                                                            */
/******************************************************************************/

/*******************************************************************************
 8x8 font table
    created with FontEditor written by H. Reddmann
    HaReddmann at t-online dot de
*******************************************************************************/
#pragma DATA_SECTION (f8x8, ".cio");
int8_t f8x8[] =
{
    0x01, 0x76, 0x08, 0x08, 0x01, 0x20, 0x7A,
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00,
    0x04, 0x02, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x01, 0x00, 0x00, 0x00, 0x00, 0x04,
    0x00, 0x06, 0x06, 0x06, 0x06, 0x05, 0x05, 0x06, 0x06, 0x01, 0x04, 0x05, 0x04, 0x07, 0x06, 0x06,
    0x06, 0x06, 0x06, 0x05, 0x05, 0x05, 0x05, 0x07, 0x05, 0x05, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x04, 0x04, 0x04, 0x04, 0x04, 0x02, 0x04, 0x04, 0x01, 0x01, 0x04, 0x01, 0x07, 0x04, 0x05,
    0x04, 0x04, 0x02, 0x04, 0x02, 0x04, 0x04, 0x05, 0x03, 0x03, 0x03,
    0x00, 0xC0, 0x40, 0x3E, 0x41, 0x41, 0x3E, 0x02, 0x7F, 0x62, 0x51, 0x49, 0x46, 0x22, 0x41, 0x49,
    0x36, 0x18, 0x16, 0x7F, 0x10, 0x2F, 0x45, 0x45, 0x39, 0x3E, 0x49, 0x49, 0x32, 0x01, 0x71, 0x0D,
    0x03, 0x36, 0x49, 0x49, 0x36, 0x26, 0x49, 0x49, 0x3E, 0x48, 0x02, 0x51, 0x09, 0x06, 0x60, 0x1C,
    0x13, 0x13, 0x1C, 0x60, 0x7F, 0x49, 0x49, 0x49, 0x49, 0x36, 0x3E, 0x41, 0x41, 0x41, 0x41, 0x22,
    0x7F, 0x41, 0x41, 0x41, 0x41, 0x3E, 0x7F, 0x49, 0x49, 0x49, 0x41, 0x7F, 0x09, 0x09, 0x09, 0x01,
    0x3E, 0x41, 0x41, 0x49, 0x29, 0x7A, 0x7F, 0x08, 0x08, 0x08, 0x08, 0x7F, 0x7F, 0x30, 0x40, 0x40,
    0x3F, 0x7F, 0x08, 0x14, 0x22, 0x41, 0x7F, 0x40, 0x40, 0x40, 0x7F, 0x03, 0x0C, 0x30, 0x0C, 0x03,
    0x7F, 0x7F, 0x03, 0x0C, 0x30, 0x40, 0x7F, 0x3E, 0x41, 0x41, 0x41, 0x41, 0x3E, 0x7F, 0x09, 0x09,
    0x09, 0x09, 0x06, 0x3E, 0x41, 0x41, 0x51, 0x61, 0xBE, 0x7F, 0x09, 0x09, 0x09, 0x09, 0x76, 0x26,
    0x49, 0x49, 0x49, 0x32, 0x01, 0x01, 0x7F, 0x01, 0x01, 0x3F, 0x40, 0x40, 0x40, 0x3F, 0x03, 0x1C,
    0x60, 0x1C, 0x03, 0x03, 0x1C, 0x60, 0x18, 0x60, 0x1C, 0x03, 0x63, 0x14, 0x08, 0x14, 0x63, 0x03,
    0x04, 0x78, 0x04, 0x03, 0x61, 0x51, 0x49, 0x45, 0x43, 0x20, 0x54, 0x54, 0x78, 0x7F, 0x44, 0x44,
    0x38, 0x38, 0x44, 0x44, 0x28, 0x38, 0x44, 0x44, 0x7F, 0x38, 0x54, 0x54, 0x18, 0x7E, 0x09, 0x98,
    0xA4, 0xA4, 0x7C, 0x7F, 0x08, 0x04, 0x78, 0x7D, 0xFD, 0x7F, 0x18, 0x24, 0x40, 0x7F, 0x7C, 0x04,
    0x04, 0x7C, 0x04, 0x04, 0x78, 0x7C, 0x04, 0x04, 0x78, 0x38, 0x44, 0x44, 0x44, 0x38, 0xFC, 0x24,
    0x24, 0x18, 0x18, 0x24, 0x24, 0xFC, 0x7C, 0x04, 0x48, 0x54, 0x54, 0x24, 0x3E, 0x44, 0x3C, 0x40,
    0x40, 0x7C, 0x1C, 0x60, 0x60, 0x1C, 0x1C, 0x60, 0x18, 0x60, 0x1C, 0x6C, 0x10, 0x6C, 0x9C, 0xA0,
    0x7C, 0x64, 0x54, 0x4C
};

/*******************************************************************************
 conversion buffer
*******************************************************************************/
#pragma DATA_SECTION (buffer, ".cio");
static char buffer[MAX_PRINTF_BUFFER];

/******************************************************************************/
/*                                                                            */
/*   FUNCTIONS                                                                */
/*                                                                            */
/******************************************************************************/

/*******************************************************************************

  @brief  initialize display

  @param
  @return

*******************************************************************************/
#pragma CODE_SECTION(InitOled , ".cprintfsect");
void InitOled ( void)
{
    /***************************************************************************
      locals
    ***************************************************************************/
    /* - */

    osd9616_init( );   // Initialize  Display
    osd9616_send(0x00,0x2e);  // Deactivate Scrolling

    ClearLine ( 0 );
    ClearLine ( 1 );
}

/*******************************************************************************

  @brief  check if character is printable

  @param  c = character to test
  @return 0 == character is not printable
          1 == character is printable

*******************************************************************************/
#pragma CODE_SECTION(IsPrintable , ".cprintfsect");
int16_t IsPrintable ( int8_t c )
{
    /***************************************************************************
      locals
    ***************************************************************************/
    /* - */

    /***************************************************************************
      is character available?
    ***************************************************************************/
    if ( (c<F8X8_MIN) || (c>F8X8_MAX))
    {
        return (0);
    }
    return (1);
}

/*******************************************************************************

  @brief  clear line

  @param  line - line number
  @return

*******************************************************************************/
#pragma CODE_SECTION(ClearLine , ".cprintfsect");
void ClearLine ( int16_t line )
{
    /***************************************************************************
      locals
    ***************************************************************************/
    int16_t i;

    /***************************************************************************
      select line
    ***************************************************************************/
    SelectLine ( line );

    /***************************************************************************
      clear line
    ***************************************************************************/
    for(i=0;i<128;i++)
    {
        osd9616_send(0x40,0x00);
    }
}

/*******************************************************************************

  @brief  select line

  @param  line - line number
  @return

*******************************************************************************/
#pragma CODE_SECTION(SelectLine , ".cprintfsect");
void SelectLine ( int16_t line )
{
    /***************************************************************************
      locals
    ***************************************************************************/
    /* - */

    /***************************************************************************
      select line
    ***************************************************************************/
    osd9616_send(0x00,0x00);   // Set low column address
    osd9616_send(0x00,0x10);   // Set high column address
    osd9616_send(0x00,0xb0+line); // Set page
}


/*******************************************************************************

  @brief  Print one character on display

  @param   c = charater to pront
  @return  0 = illegal charater
           1 = success

*******************************************************************************/
#pragma CODE_SECTION(printChar , ".cprintfsect");
int16_t printChar(int8_t c)
{
    /***************************************************************************
      locals
    ***************************************************************************/
    int16_t i, char_width_offset, char_offset ;

    /***************************************************************************
      is character available?
    ***************************************************************************/
    if ( !IsPrintable (c))
    {
        return (0);
    }

    /***************************************************************************
      get offset from font table
    ***************************************************************************/
    char_width_offset = c - F8X8_MIN + F8X8_WIDTH_OFFSET;

    /***************************************************************************
      calculate offset to printable character
    ***************************************************************************/
    char_offset = F8X8_FIRST_CHAR;
    for (i = F8X8_WIDTH_OFFSET; i<char_width_offset; i++)
    {
        char_offset += f8x8[i];
    }

    /***************************************************************************
      add space to next character
    ***************************************************************************/
    osd9616_send(0x40, 0x00);

    /***************************************************************************
      print character
    ***************************************************************************/
    for (i = f8x8[char_width_offset]; i>0; i--)
    {
        osd9616_send(0x40, f8x8[char_offset+i]);
    }

    /***************************************************************************
      return success
    ***************************************************************************/
    return (1);
}

/*******************************************************************************

  @brief  Print string on display

  @param  line => 0 == 1. line
                  1 == 2. line
          s => string to print
  @return 1

*******************************************************************************/
#pragma CODE_SECTION(printString , ".cprintfsect");
int16_t printString(int16_t line, const char *s)
{
    /***************************************************************************
      locals
    ***************************************************************************/
    int16_t len=0, i;
    int8_t *p = (int8_t *)s, cols = 0, spaces = 0;

    ClearLine ( line );
    SelectLine ( line );

    /***************************************************************************
     count columns of string including 1 space per character
     determine string length
    ***************************************************************************/
    p = (int8_t *)s;
    while (*p)
    {
        if ( IsPrintable (*p))
        {
            cols += f8x8[*p-0x19];
        }
        else
        {
            cols += f8x8['.'-0x19];
        }
        cols++;
        p++;
        len++;
    }

    /***************************************************************************
     fill remaining columns with spaces
    ***************************************************************************/
    if (cols<96)
    {
        spaces = 96-cols;
        for (i=0; i<spaces; i++)
        {
            osd9616_send(0x40, 0x00);
        }
    }

    /***************************************************************************
     print character
    ***************************************************************************/
    p = (int8_t *)(s+len);
    for (i=len; i>0; i--)
    {
        p--;
        if ( IsPrintable (*p))
        {
            printChar(*p);
        }
        else
        {
            printChar('.');
        }
    }

    /***************************************************************************
     return success
    ***************************************************************************/
    return (1);
}

/***************************************************************************//**

    @brief      Custom printf function
    @param      format - format string
    @return     nothing

*******************************************************************************/
#pragma CODE_SECTION(OledPrintf, ".cprintfsect");
void OledPrintf(int16_t line, const char *format, ...)
{
    /***************************************************************************
     locals
    ***************************************************************************/
    va_list argptr;
    int cnt;

    /***************************************************************************
     initializes variable argument list
    ***************************************************************************/
    va_start (argptr, format);

    /***************************************************************************
     print to buffer
    ***************************************************************************/
    cnt = vsprintf (buffer, format, argptr);

    /***************************************************************************
     vsprintf returns the amount of printed characters. The user buffer size is
     limited to MAX_PRINTF_BUFFER. Check for buffer overflow and exit if
      necessary.
    ***************************************************************************/
    if (cnt > MAX_PRINTF_BUFFER)
    {
        EXIT(BUFFEROVERFLOW_ERROR);
    }

    printString(line, buffer);

    /***************************************************************************
     end variable argument list
    ***************************************************************************/
    va_end(argptr);
}
