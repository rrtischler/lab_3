/*******************************************************************************
*                                                                              *
* @file      cprintf.c                                                         *
* @verbatim                                                                    *
*                       ___ \    ___| _)              __ __|                   *
*                       |    | \    \  |   _     __ \   |                      *
*                       |    |  ---    | (   |  |   |   |                      *
*                      _____/_)_____/ _| \__,|  |  _|  _|                      *
*                                        |___/                                 *
*                      Digital Signalprocessing Technology                     *
* @endverbatim                                                                 *
* @brief     CPrintf definition                                                *
*                                                                              *
* @author    D.SignT GmbH & Co. KG, Claus Hermbusche                           *
* @date      2011-09-19
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
  DSP/BIOS includes
*******************************************************************************/
#ifdef USE_DSPBIOS
#include <std.h>
#include <lck.h>
#include <tsk.h>
#include <sys.h>
#endif

/*******************************************************************************
  Runtime Source
*******************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

/*******************************************************************************
  common support function
*******************************************************************************/
//~ #include "uartio.h"
#include "cprintf.h"
#include "common.h"

/*******************************************************************************
*                                                                              *
*    DEFINES                                                                   *
*                                                                              *
*******************************************************************************/
/* - */

/***************************************************************************//**

*                                                                              *
*    GLOBALS                                                                   *
*                                                                              *
*******************************************************************************/

/***************************************************************************//**

 output device selection
    CPRINTF_NO_OUTPUT          0
    CPRINTF_CCS_OUTPUT         1
    CPRINTF_UART_OUTPUT        2
    CPRINTF_USB_OUTPUT         4
    CPRINTF_NET_OUTPUT         8
*******************************************************************************/
uint16_t output_device = CPRINTF_NO_OUTPUT;

/***************************************************************************//**
 conversion buffer
*******************************************************************************/
#pragma DATA_SECTION (buffer, ".cio");
static char buffer[CPRINTF_BUFFER_SIZE];


/*******************************************************************************
*                                                                              *
*    FUNCTIONS                                                                 *
*                                                                              *
*******************************************************************************/
/***************************************************************************//**

  @brief    Select the CPrintf output device

  @param    device - output device
  @return   nothing
  @sa       CPRINTF_NO_OUTPUT, CPRINTF_CCS_OUTPUT, CPRINTF_UART_OUTPUT

*******************************************************************************/
#pragma CODE_SECTION(CPrintf_select_output , ".cprintfsect");
void CPrintf_select_output (uint16_t device)
{
    /***************************************************************************
     locals
    ***************************************************************************/
    static uint16_t Initialized = 0;

    if ( device == 0 )
    {
        /***********************************************************************
         output disabled
        ***********************************************************************/
        output_device = device;
        return;
    }

    if ( (device & CPRINTF_OUTPUT_MASK) == 0 )
    {
        /***********************************************************************
         device not available
        ***********************************************************************/
        EXIT(CPRINTF_DEVICE_ERROR);
    }

    output_device = device & CPRINTF_OUTPUT_MASK;

#ifdef  CPRINTF_CCS_AVAILABLE
    if (output_device & CPRINTF_CCS_OUTPUT)
    {
        if (!(Initialized & CPRINTF_CCS_OUTPUT))
        {
            /*******************************************************************
              CCS output needs no initialization
            *******************************************************************/
            Initialized |= CPRINTF_CCS_OUTPUT;
        }
    }
#endif

#ifdef  CPRINTF_UART_AVAILABLE
    if (output_device & CPRINTF_UART_OUTPUT)
    {
        if (!(Initialized & CPRINTF_UART_OUTPUT))
        {
            /*******************************************************************
              initialize UART
            *******************************************************************/
            if (UartInitialize())
            {
                //~ printf ("couldn't get a UART handle!\r\nexiting program\r\n");
                EXIT(INITUART_ERROR);
            }
            else
            {
                printf (" UART successfully initialized!\r\n\n please connect a free serial PC port to connector P8\r\n on your EVM and start a terminal program configured to\r\n     >>115200 baud, 8 bits, 1 stop bit, no parity<<\r\n to see CPrintf outputs\r\n");
            }
            Initialized |= CPRINTF_UART_OUTPUT;
        }
    }
#endif

#ifdef  CPRINTF_USB_AVAILABLE
    //~ if (output_device & CPRINTF_USB_AVAILABLE)
    //~ {
        //~ if (!(Initialized & CPRINTF_USB_OUTPUT))
        //~ {
            //~ /*******************************************************************
              //~ initialize USB connection
            //~ *******************************************************************/
            //~ if ( InitializeUSB())
            //~ {
                //~ EXIT(CPRINTF_DEVICE_ERROR);
            //~ }
            //~ else
            //~ {
                //~ printf (" USB successfully initialized!\r\n\n please connect a USB terminal to see CPrintf outputs\r\n");
            //~ }
            //~ Initialized |= CPRINTF_USB_OUTPUT;
        //~ }
    //~ }
#endif

#ifdef  CPRINTF_NET_AVAILABLE
    if (output_device & CPRINTF_NET_OUTPUT)
    {
        if (!(Initialized & CPRINTF_NET_OUTPUT))
        {
            /*******************************************************************
              check if stack is initialized
            *******************************************************************/
            if (!is_net_init())
            {
                EXIT(NETINIT_ERROR);           /* Stack not initialized*/
            }

            /*******************************************************************
              initialize Net connection
            *******************************************************************/
            if ( InitializeNetLog())
            {
                EXIT(CPRINTF_DEVICE_ERROR);
            }
            else
            {
                printf (" NET Log successfully initialized!\r\n\n please connect a UDP terminal to see CPrintf outputs\r\n");
            }
            Initialized |= CPRINTF_NET_OUTPUT;
        }
    }
#endif
}

/***************************************************************************//**

    @brief      Custom printf function
    @param      format - format string
    @return     nothing

*******************************************************************************/
#pragma CODE_SECTION(CPrintf , ".cprintfsect");
void CPrintf(const char *format, ...)
{
    /***************************************************************************
     locals
    ***************************************************************************/
    va_list argptr;
    int cnt;

    if ( output_device == 0 )
    {
        /***********************************************************************
         output disabled
        ***********************************************************************/
        return;
    }

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
     limited to CPRINTF_BUFFER_SIZE. Check for buffer overflow and exit if
      necessary.
    ***************************************************************************/
    if (cnt > CPRINTF_BUFFER_SIZE)
    {
        EXIT(BUFFEROVERFLOW_ERROR);
    }

    /***************************************************************************
     write string
    ***************************************************************************/
#ifdef  CPRINTF_CCS_AVAILABLE
    if (output_device & CPRINTF_CCS_OUTPUT)
    {
        /***********************************************************************
         output to CCS
        ***********************************************************************/
        if (!(buffer[0] == '\x1b'))  // CCS does not allow escape sequence outputs
        {
            printf (buffer);
            fflush (stdout);
        }
        else
        {
            printf ("\n\n\n");    // else insert some new lines
        }
    }
#endif

#ifdef  CPRINTF_UART_AVAILABLE
    if (output_device & CPRINTF_UART_OUTPUT)
    {
        /***********************************************************************
         output to UART
        ***********************************************************************/
        UartWriteStr (buffer);
    }
#endif

#ifdef  CPRINTF_NET_AVAILABLE
    if (output_device & CPRINTF_NET_OUTPUT)
    {
        /***********************************************************************
         output to network connection
        ***********************************************************************/
        if (_link )
        {
            NetWriteStr (buffer);
        }
    }
#endif

    /***************************************************************************
     end variable argument list
    ***************************************************************************/
    va_end(argptr);

}
