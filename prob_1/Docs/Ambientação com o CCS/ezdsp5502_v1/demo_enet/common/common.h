/***************************************************************************//**
*                                                                              *
*  @file      common.h                                                         *
*  @verbatim                                                                   *
*                       ___ \    ___| _)              __ __|                   *
*                       |    | \    \  |   _     __ \   |                      *
*                       |    |  ---    | (   |  |   |   |                      *
*                      _____/_)_____/ _| \__,|  |  _|  _|                      *
*                                        |___/                                 *
*                      Digital Signalprocessing Technology                     *
*  @endverbatim                                                                *
*  @brief     common definition and prototypes                                 *
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
#ifndef _COMMON_H
#define _COMMON_H
#include <stdlib.h>
#include <stdint.h>
#include "..\netlib\dsknet.h"               /* network support                */


/******************************************************************************/
/*                                                                            */
/*   DEFINES                                                                  */
/*                                                                            */
/******************************************************************************/


/*******************************************************************************
  EXIT macro with error code setting
*******************************************************************************/
#define EXIT(ec)  (exit (exit_code = (ec)))

/*******************************************************************************
  descriptive error codes
   note: must match the error_tab order defined in common.c
*******************************************************************************/
#define UNKNOWN_ERROR         0
#define INITUART_ERROR        1
#define MAC_ERROR             2
#define NETINIT_ERROR         3
#define ICMP_ERROR            4
#define SOCKETOPEN_ERROR      5
#define FTPSERVER_ERROR       6
#define HTTPSERVER_ERROR      7
#define BUFFEROVERFLOW_ERROR  8
#define NO_UART_HANDLE_ERROR  9
#define CPRINTF_DEVICE_ERROR  10
#define TIMER_HANDLE_ERROR    11

/*******************************************************************************
  to prevent unused parameter warning
*******************************************************************************/
#ifndef UNREFERENCED_PARAMETER
#define UNREFERENCED_PARAMETER(P)    ((P)=(P))
#endif

/*******************************************************************************
  the following defines are used to enable user defined interrupts
*******************************************************************************/
#define IER0   (( volatile unsigned int *)0x000000) /* interrupt enable reg  */
#define IER1   (( volatile unsigned int *)0x000045) /* interrupt enable reg  */
#define IVPD   (( volatile unsigned int *)0x000049) /* interrupt vector reg  */
#define IVPH   (( volatile unsigned int *)0x00004A) /* interrupt vector reg  */

/***************************************************************************//**
 macros for build date and time
*******************************************************************************/
#define BUILD_YEAR ((((__DATE__ [7] - '0') * 10 + (__DATE__ [8] - '0')) * 10 \
                    + (__DATE__ [9] - '0')) * 10 + (__DATE__ [10] - '0'))


#define BUILD_DAY ((__DATE__ [4] == ' ' ? 0 : __DATE__ [4] - '0') * 10 + (__DATE__ [5] - '0'))

#define BUILD_MONTH   (  __DATE__ [2] == 'n' ? (__DATE__ [1] == 'a' ? 1 : 6)   \
                       : __DATE__ [2] == 'b' ? 2                               \
                       : __DATE__ [2] == 'r' ? (__DATE__ [0] == 'M' ? 3 : 4)   \
                       : __DATE__ [2] == 'y' ? 5                               \
                       : __DATE__ [2] == 'l' ? 7                               \
                       : __DATE__ [2] == 'g' ? 8                               \
                       : __DATE__ [2] == 'p' ? 9                               \
                       : __DATE__ [2] == 't' ? 10                              \
                       : __DATE__ [2] == 'v' ? 11 : 12 )

#define BUILD_HOUR    ( (__TIME__ [0] - '0')*10 + (__TIME__ [1] - '0') )
#define BUILD_MINUTE  ( (__TIME__ [3] - '0')*10 + (__TIME__ [4] - '0') )
#define BUILD_SECOND  ( (__TIME__ [6] - '0')*10 + (__TIME__ [7] - '0') )


/******************************************************************************/
/*                                                                            */
/*   GLOBALS                                                                  */
/*                                                                            */
/******************************************************************************/
/*******************************************************************************
 exit code
*******************************************************************************/
extern int exit_code;

/***************************************************************************//**
 external access to link status
*******************************************************************************/
extern uint16_t _link;


/******************************************************************************/
/*                                                                            */
/*   PROTOTYPES                                                               */
/*                                                                            */
/******************************************************************************/
#ifdef __cplusplus
  extern "C" {
#endif


/***************************************************************************//**

    @brief      show a descriptive errorcode on exit
    @param      void
    @return     nothing

*******************************************************************************/
void PrintExitCode ( void );

/***************************************************************************//**

    @brief      initialize application
    @param      dsp_clock [Hz]
    @return     nothing

*******************************************************************************/
void AppInit (uint32_t dsp_clock);

/***************************************************************************//**

    @brief      disable interrupts, DMA, timer etc.
    @param      void
    @return     nothing

*******************************************************************************/
void AppCleanup (void);

/***************************************************************************//**

  @brief        print error code

  @param        error_code - error code to print
  @param        pLog - printf function
  @return       nothing

*******************************************************************************/
void net_print_error ( int32_t error_code, tpMessageLogFxn pLog );

/*******************************************************************************

    Function   LED_init

    Turn all LEDs off

    Parameter
    Returns
    Calls

*******************************************************************************/
void LED_init();

/*******************************************************************************

    Function  LED_off

    Parameter
    Returns
    Calls

*******************************************************************************/
void LED_off(unsigned int ledNum);

/*******************************************************************************

    Function  LED_on

    Parameter
    Returns
    Calls

*******************************************************************************/
void LED_on(unsigned int ledNum);

/*******************************************************************************

    Function  LED_toggle

    Parameter
    Returns
    Calls

*******************************************************************************/
void LED_toggle(unsigned int ledNum);

/*******************************************************************************

    Function  LED_state

    Parameter
    Returns
    Calls

*******************************************************************************/
uint16_t LED_state(void);

#ifdef __cplusplus
}
#endif

#endif // _COMMON_H
