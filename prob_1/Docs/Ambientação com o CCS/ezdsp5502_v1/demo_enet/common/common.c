/*******************************************************************************
*                                                                              *
*  @file      common.c                                                         *
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
#include <string.h>


/*******************************************************************************
  Board Support Library
*******************************************************************************/
#include ".\bsl\include\ezdsp5502.h"
#include ".\bsl\include\ezdsp5502_i2c.h"
#include ".\bsl\include\ezdsp5502_i2cgpio.h"
#include ".\bsl\include\ezdsp5502_gpio.h"

/*******************************************************************************
  Chip Support Library
*******************************************************************************/
#ifndef CHIP_5502
#define CHIP_5502
#endif
#include <csl.h>                             /* chip support library          */
#include <csl_icache.h>
#include <csl_gpio5502.h>

/*******************************************************************************
  common support function
*******************************************************************************/
#include "..\netlib\dsknet.h"                /* network support               */
#include "common.h"                          /* init app, on exit function    */
#include "..\dsk\dskemif.h"                  /* EMIF setting                  */
#include "..\dsk\dskpll.h"                   /* PLL setting                   */
#include "CPrintf.h"                         /* CPrintf defines               */
#include "oled_printf.h"                     /* Oled defines                  */


/******************************************************************************/
/*                                                                            */
/*   DEFINES                                                                  */
/*                                                                            */
/******************************************************************************/

/*******************************************************************************
  EXIT macro with error code setting
*******************************************************************************/
#ifndef EXIT
#define EXIT(ec)  (exit (exit_code = (ec)))
#endif



/******************************************************************************/
/*                                                                            */
/*   GLOBALS                                                                  */
/*                                                                            */
/******************************************************************************/

/*******************************************************************************
 exit table
*******************************************************************************/
#pragma DATA_SECTION (exit_tab, ".cio");
static char *exit_tab[] =
{
    "unknown error\r\n",
    "InitializeUART() failed\r\n",
    "dsk_init() failed\r\n",
    "net_init() failed\r\n",
    "ICMP socket error\r\n",
    "socket_open() failed\r\n",
    "ftp_server_init() failed\r\n",
    "http_server_init() failed\r\n",
    "CPrintf() buffer overflow error\r\n",
    "No UART handle error\r\n",
    "Device not available on DSK!\r\nplease change outputchannel to CCS:\r\nCPrintf_select_output (CPRINTF_CCS_OUTPUT);\r\nexiting program\r\n",
    "ERROR: Invalid Handle, GPT_open failed\r\n",
};

/*******************************************************************************
 exit code
*******************************************************************************/
int exit_code = 0;

/*******************************************************************************
 link
*******************************************************************************/
uint16_t _link = 0;

/*******************************************************************************
 program name
*******************************************************************************/
extern char *program_name;

/*******************************************************************************
  ledstate
*******************************************************************************/
static unsigned int ledstate = 0;


/******************************************************************************/
/*                                                                            */
/*   FUNCTIONS                                                                */
/*                                                                            */
/******************************************************************************/

/*******************************************************************************

    @brief      link status change callback function
    @param      link mode: HDX_10, HDX_100, FDX_10, FDX_100
    @return     nothing

*******************************************************************************/
#pragma CODE_SECTION(link_status , ".commonsect");
void link_status (uint8_t mode)
{
    CPrintf ("\r\n Link status changed: ");

    switch (mode)
    {
        case 0xff:
            LED_off (3);
            _link = 0;
            CPrintf ("No Link\r\n");
            break;

        default:
            LED_on (3);
            _link = 1;
            CPrintf ("Linked at %dMbit %s duplex\r\n",
                    (mode & SPEED_100) ? 100:10,
                    (mode & FULL_DUPLEX) ? "full":"half");
            break;
    }
}

/***************************************************************************//**

    @brief      show a descriptive errorcode on exit
    @param      void
    @return     nothing

*******************************************************************************/
#pragma CODE_SECTION(PrintExitCode , ".commonsect");
void PrintExitCode ( void )
{
    OledPrintf (0, "error occurred");
    OledPrintf (1, "exit code: %d", exit_code);

    /***************************************************************************
     in case of cprintf buffer overflow a printf is not possible
     set LEDs to signal exit status
    ***************************************************************************/
    if (exit_code != BUFFEROVERFLOW_ERROR)
    {
        CPrintf (exit_tab[exit_code]);
        if ( (exit_code >= MAC_ERROR) && (exit_code <= HTTPSERVER_ERROR) )
        {
            CPrintf (" possibly insufficient heap\r\n");
        }
        CPrintf (" Program halted!");
    }
    else
    {
        LED_on (0);
        LED_on (1);
        LED_on (2);
        LED_on (3);
    }

    AppCleanup();

    return;
}

/***************************************************************************//**

    @brief      initialize application
    @param      dsp_clock [Hz]
    @return     nothing

*******************************************************************************/
#pragma CODE_SECTION(AppInit , ".commonsect");
void AppInit (uint32_t dsp_clock)
{
    /***************************************************************************
     locals
    ***************************************************************************/
    char version[6];              /* for netlib version string                */
    UNREFERENCED_PARAMETER(dsp_clock);

    /***************************************************************************
     global disable interrupts
    ***************************************************************************/
    _disable_interrupts();

    /***************************************************************************
      install exit function
    ***************************************************************************/
    atexit (PrintExitCode );

    /***************************************************************************
     let cpu interrupt vector point to our own interrupt vector table at 0xFE00
     as specified in linker command file
    ***************************************************************************/
    *IVPD = *IVPH = 0xFE;

    /***************************************************************************
      initialize pll
    ***************************************************************************/
    init_pll ();

    /***************************************************************************
      initialize EMIF
    ***************************************************************************/
    init_emif ();

    /***************************************************************************
      initialize Chip and Board Support Library
    ***************************************************************************/
    //~ CSL_init();
    EZDSP5502_init ();

    /***************************************************************************
      enable instruction cache
    ***************************************************************************/
    ICACHE_setup();
    ICACHE_enable();

    /***************************************************************************
      initialize LEDs
    ***************************************************************************/
    LED_init ();

    /***************************************************************************
      Setup I2C GPIOs for Switches
    ***************************************************************************/
    EZDSP5502_I2CGPIO_configLine(  SW0, IN );
    EZDSP5502_I2CGPIO_configLine(  SW1, IN );

    /***************************************************************************
      Use GPIO4 as SPI Flash chip select
    ***************************************************************************/
    EZDSP5502_GPIO_init(GPIO_GPIO_PIN4);
    EZDSP5502_GPIO_setDirection(GPIO_GPIO_PIN4, GPIO_GPIO_PIN4_OUTPUT);

    /***************************************************************************
      initialize display
    ***************************************************************************/
    InitOled();

    /***************************************************************************
      print program name and netlib revision
    ***************************************************************************/
    OledPrintf (0, "%s", program_name);
    OledPrintf (1, "netlib rev: %s", get_netlib_ver (version));

}

/***************************************************************************//**

    @brief      disable interrupts, DMA, timer etc.
    @param      void
    @return     nothing

*******************************************************************************/
#pragma CODE_SECTION(AppCleanup , ".commonsect");
void AppCleanup (void)
{
    /***************************************************************************
      stop timer
    ***************************************************************************/
    //~ TIMER(0)->ctl = 0x301;

    /***************************************************************************
      disable interrupt
    ***************************************************************************/
    _disable_interrupts();
    *(int*)0x0003 = *(int*)0x0003 | 0x0800; // Set INTM
    *(int*)0x0000 = 0;                      // Clear IER0
    *(int*)0x0045 = 0;                      // Clear IER1
    *(int*)0x0004 = *(int*)0x0004 | 0x2000; // Set CACLR (Clear Cache)

    /***************************************************************************
      disable DMA
    ***************************************************************************/
    *(int*)0xC01 = 0;    // DMA0
    *(int*)0xC21 = 0;    // DMA1
    *(int*)0xC41 = 0;    // DMA2
    *(int*)0xC61 = 0;    // DMA3
    *(int*)0xC81 = 0;    // DMA4
    *(int*)0xCA1 = 0;    // DMA5

}


/***************************************************************************//**

  @brief        print error code

  @param        error_code - error code to print
  @param        pLog - printf function
  @return       nothing

*******************************************************************************/
#pragma CODE_SECTION(net_print_error , ".commonsect");
void net_print_error ( int32_t error_code, tpMessageLogFxn pLog )
{
    switch ( error_code )
    {
        case SO_TRANSMIT_ERROR :
            pLog ("transmit error\r\n");
            break;
        case SO_NO_ARP_ADDRESS :
            pLog ("no ARP address\r\n");
            break;
        case SO_TIMED_OUT :
            pLog ("connection timed out\r\n");
            break;
        case SO_IN_USE :
            pLog ("socket in use\r\n");
            break;
        case SO_NOT_ESTABLISHED :
            pLog ("socket not established\r\n");
            break;
        case SO_CONNECTION_RESET    :
            pLog ("TCP connection reset\r\n");
            break;
        case SO_WRONG_CHECKSUM :
            pLog ("wrong checksum\r\n");
            break;
        case SO_BUFFER_TOO_SMALL :
            pLog ("buffer too small\r\n");
            break;
        case SO_NO_INPUT_BUFFER :
            pLog ("no input buffer\r\n");
            break;
        case SO_NOT_OPEN :
            pLog ("socket not open\r\n");
            break;
        case SO_CONNECTION_CLOSED :
            pLog ("TCP connection closed\r\n");
            break;
        case SO_WINDOW_ERR :
            pLog ("TCP window error\r\n");
            break;
        case SO_CONNECTION_ESTABLISHED :
            pLog ("TCP connection established\r\n");
            break;
        case SO_MMU_ERROR :
            pLog ("Memory management unit error\r\n");
            break;
        case SO_SEND_PENDING :
            pLog ("TCP send pending\r\n");
            break;
        case SO_NO_LINK :
            pLog ("no link\r\n");
            break;
        case SO_DNS_ERR :
            pLog ("DNS lookup in progress\r\n");
            break;

        case FSYS_BIOS_PROTECT_ERROR :
            pLog ("BIOS protect error\r\n");
            break;
        case FSYS_CHECKSUM_ERROR :
            pLog ("intel hex checksum error\r\n");
            break;
        case FSYS_INTEL_HEX_ERROR :
            pLog ("intel hex error\r\n");
            break;
        case FSYS_SECTOR_ERASE_ERROR :
            pLog ("sector erase error\r\n");
            break;
        case FSYS_FLASH_PROGRAM_ERROR :
            pLog ("FLASH program error\r\n");
            break;
        case FSYS_BUFFER_UNDERRUN_ERROR :
            pLog ("buffer underrun error\r\n");
            break;
        case FSYS_OUT_OF_MEMORY_ERROR :
            pLog ("out of memory error\r\n");
            break;
        case FSYS_OUT_OF_RANGE_ERROR :
            pLog ("out of range error\r\n");
            break;
        default:
            pLog ("Unknown error!\r\n");
            break;
    }
}

/******************************************************************************/
/*                                                                            */
/*   LED support functions                                                    */
/*                                                                            */
/******************************************************************************/

/*******************************************************************************

    Function   LED_init

    Turn all LEDs off

    Parameter
    Returns
    Calls

*******************************************************************************/
#pragma CODE_SECTION(LED_init , ".commonsect");
void LED_init()
{
    ledstate = 0;

    /* Initialize LEDs */
   /* Setup I2C GPIO directions by line*/
    EZDSP5502_I2CGPIO_configLine(  LED0, OUT );
    EZDSP5502_I2CGPIO_configLine(  LED1, OUT );
    EZDSP5502_I2CGPIO_configLine(  LED2, OUT );
    EZDSP5502_I2CGPIO_configLine(  LED3, OUT );

    /* Turn off all LEDs by line*/
    EZDSP5502_I2CGPIO_writeLine(   LED0, HIGH );
    EZDSP5502_I2CGPIO_writeLine(   LED1, HIGH );
    EZDSP5502_I2CGPIO_writeLine(   LED2, HIGH );
    EZDSP5502_I2CGPIO_writeLine(   LED3, HIGH );

}

/*******************************************************************************

    Function  LED_off

    Parameter
    Returns
    Calls

*******************************************************************************/
#pragma CODE_SECTION(LED_off , ".commonsect");
void LED_off(unsigned int ledNum)
{
    /***************************************************************************
     locals
    ***************************************************************************/
    /* - */

    /***************************************************************************
     Check bounds for ledNum
    ***************************************************************************/
    if (ledNum >= 4)
        return;

    /***************************************************************************
     Clear the LED bit
    ***************************************************************************/
    ledstate &= ~(1 << ledNum);
    EZDSP5502_I2CGPIO_writeLine(   (~ledNum)&0x7, HIGH );
}

/*******************************************************************************

    Function  LED_on

    Parameter
    Returns
    Calls

*******************************************************************************/
#pragma CODE_SECTION(LED_on , ".commonsect");
void LED_on(unsigned int ledNum)
{
    /***************************************************************************
     locals
    ***************************************************************************/
    /* - */

    /***************************************************************************
     Check bounds for ledNum
    ***************************************************************************/
    if (ledNum >= 4)
        return;

    /***************************************************************************
     Set the LED bit
    ***************************************************************************/
    ledstate |= (1 << ledNum);
    EZDSP5502_I2CGPIO_writeLine(   (~ledNum)&0x7, LOW );
}

/*******************************************************************************

    Function  LED_toggle

    Parameter
    Returns
    Calls

*******************************************************************************/
#pragma CODE_SECTION(LED_toggle , ".commonsect");
void LED_toggle(unsigned int ledNum)
{
    /***************************************************************************
     locals
    ***************************************************************************/
    unsigned int led_mask = 1 << (ledNum);

    /***************************************************************************
     Check bounds for ledNum
    ***************************************************************************/
    if (ledNum >= 4)
        return;

    if ( ledstate & led_mask )
    {
        LED_off(ledNum);
    }
    else
    {
        LED_on(ledNum);
    }
}

/*******************************************************************************

    Function  LED_state

    Parameter
    Returns
    Calls

*******************************************************************************/
#pragma CODE_SECTION(LED_state , ".commonsect");
uint16_t LED_state(void)
{
    return (ledstate);
}

