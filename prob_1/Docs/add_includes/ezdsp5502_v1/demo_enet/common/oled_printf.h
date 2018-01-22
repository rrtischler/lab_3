/*******************************************************************************
*                                                                              *
*  @file      oled_printf.h                                                    *
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


/******************************************************************************/
/*                                                                            */
/*   DEFINES                                                                  */
/*                                                                            */
/******************************************************************************/


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
#pragma CODE_SECTION(InitOled , ".commonsect");
void InitOled ( void);

/*******************************************************************************

  @brief  check if character is printable

  @param  c = character to test
  @return 0 == character is not printable
          1 == character is printable

*******************************************************************************/
int16_t IsPrintable ( int8_t c );

/*******************************************************************************

  @brief  clear line

  @param  line - line number
  @return

*******************************************************************************/
void ClearLine ( int16_t line );

/*******************************************************************************

  @brief  select line

  @param  line - line number
  @return

*******************************************************************************/
void SelectLine ( int16_t line );

/*******************************************************************************

  @brief  Print one character on display

  @param   c = charater to pront
  @return  0 = illegal charater
           1 = success

*******************************************************************************/
int16_t printChar(int8_t c);

/*******************************************************************************

  @brief  Print string on display

  @param  line => 0 == 1. line
                  1 == 2. line
          s => string to print
  @return 1

*******************************************************************************/
int16_t printString(int16_t line, const char *s);

/***************************************************************************//**

    @brief      Custom printf function
    @param      format - format string
    @return     nothing

*******************************************************************************/
void OledPrintf(int16_t line, const char *format, ...);
