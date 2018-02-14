/*******************************************************************************
*                                                                              *
*  @file      HTTPjava.c                                                       *
*  @brief     java HTTP server example                                         *
*                                                                              *
*  @author    D.SignT GmbH & Co. KG, Claus Hermbusche                          *
*  @date      2011-09-19
*                                                                              *
*  @details                                                                    *
*  This program installs a HTTP server (port 80) with fix IP 192.168.168.200.  *
*                                                                              *
*  To verify this program, first 'ping' the DSP:                               *
*  >ping 192.168.168.200                                                       *
*  If the settings and network connections are correct, the pings will be      *
*  replied.                                                                    *
*                                                                              *
*  To see the web page type in your browser:                                   *
*                                                                              *
*  >http://192.168.168.200/index.htm                                           *
*                                                                              *
*  All pages and messages are hardcoded via c-variables into the code, but can *
*  also be loaded from internal flash.                                         *
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
#include <string.h>

/*******************************************************************************
  network support function
*******************************************************************************/
#include "..\..\..\netlib\dsknet.h"          /* network support               */
#include "..\..\..\netlib\httplib.h"         /* http support                  */

/*******************************************************************************
  common support function
*******************************************************************************/
#include "..\..\..\common\CPrintf.h"         /* CPrintf defines               */
#include "..\..\..\common\common.h"          /* on exit function              */
#include "..\..\..\common\oled_printf.h"     /* Oled defines                  */

/*******************************************************************************
  network configuration
*******************************************************************************/
#include "..\..\..\common\netconfig.c"       /* network configuration         */
#include ".\webpage\webpage.c"               /* generated webpage             */


#ifdef __cplusplus
extern "C" {
#endif /* !__cplusplus */

/*******************************************************************************
  local prototypes
*******************************************************************************/


#ifdef __cplusplus
} // extern "C"
#endif

/*******************************************************************************
*                                                                              *
*    DEFINES                                                                   *
*                                                                              *
*******************************************************************************/


/*******************************************************************************
*                                                                              *
*    GLOBALS                                                                   *
*                                                                              *
*******************************************************************************/

/*******************************************************************************
 program name
*******************************************************************************/
char *program_name = "java HTTP server";

/*******************************************************************************
  direntry_type: used for creating a directory entry:

direntry_type dir1 = { dir, file, length, access, type, flash/ram address };

  The maximum dir and file length is 60 characters. Blanks are not allowed.

*******************************************************************************/
direntry_type led1 = {"led1"  , "led1.gif"  , sizeof(ledoff_gif) , FTP_RW | FTP_RAM, 'B', (uint32_t)ledoff_gif };
direntry_type led2 = {"led2"  , "led2.gif"  , sizeof(ledoff_gif) , FTP_RW | FTP_RAM, 'B', (uint32_t)ledoff_gif };
direntry_type led3 = {"led3"  , "led3.gif"  , sizeof(ledoff_gif) , FTP_RW | FTP_RAM, 'B', (uint32_t)ledoff_gif };
direntry_type led4 = {"led4"  , "led4.gif"  , sizeof(ledoff_gif) , FTP_RW | FTP_RAM, 'B', (uint32_t)ledoff_gif };


#include ".\webpage\webpage.gen"           /* generated page list             */


/*******************************************************************************
*                                                                              *
*    FUNCTIONS                                                                 *
*                                                                              *
*******************************************************************************/
/*******************************************************************************

    @brief  Update LED states

    @return nothing

*******************************************************************************/
#pragma CODE_SECTION(UpdateLedStates , ".commonsect");
void UpdateLedStates (void)
{
    /***************************************************************************
     locals
    ***************************************************************************/
    uint16_t led_mask = 1, i;
    direntry_type *fp;
    uint16_t leds = LED_state();

    for ( i=0; i<4; i++ )
    {
        fp = user[0].dir[led1.index+i];

        if ( leds & led_mask )
        {
            /*******************************************************************
             change file to ledon.gif
            *******************************************************************/
            fp-> offset = (uint32_t)ledon_gif;
            fp-> size = sizeof(ledon_gif);
            fp-> max_offset = (uint32_t)ledon_gif + fp->size;
        }
        else
        {
            /*******************************************************************
         change file to ledoff.gif
            *******************************************************************/
            fp-> offset = (uint32_t)ledoff_gif;
            fp-> size = sizeof(ledoff_gif);
            fp-> max_offset = (uint32_t)ledoff_gif + fp-> size;
        }
        led_mask <<= 1;
    }
}

/*******************************************************************************

    @brief  Toggle LED

    @param  led_nr  - number of led to toggle (0 -3)
    @return nothing

*******************************************************************************/
#pragma CODE_SECTION(toggle_led , ".commonsect");
void toggle_led (unsigned int led_nr)
{
    /***************************************************************************
     locals
    ***************************************************************************/
    uint16_t led_mask = 1 << led_nr;
    uint16_t leds = LED_state();
    direntry_type *fp = user[0].dir[led1.index+led_nr];

    if ( leds & led_mask )
    {
        /***********************************************************************
         switch LED off
        ***********************************************************************/
        LED_off (led_nr);

        /***********************************************************************
         change file to ledoff.gif
        ***********************************************************************/
        fsys_init_file (fp, (uint32_t)ledoff_gif, sizeof(ledoff_gif));
    }
    else
    {
        /***********************************************************************
         switch LED on
        ***********************************************************************/
        LED_on (led_nr);

        /***********************************************************************
         change file to ledon.gif
        ***********************************************************************/
        fsys_init_file (fp, (uint32_t)ledon_gif, sizeof(ledon_gif));
    }
}

/*******************************************************************************

    @brief  user defined callback function; called each time a web page is requested
    or data is received.

    @param  http_server - current http server connection

    @return    _HTTP_CLOSE_CONNECTION   -  close connection
    @return    _HTTP_KEEP_ALIVE         -  keep alive

    @sa        http_send_user_page()    - http.lib

*******************************************************************************/
int32_t http_interpreter (httpserv_type *http_server)
{
    /***************************************************************************
     locals
    ***************************************************************************/
    int32_t  ret = _HTTP_CLOSE_CONNECTION;

    /***************************************************************************
     Execute specific method
    ***************************************************************************/
    switch (http_server -> method)
    {
        case _HTTP_GET:
            /*******************************************************************
             uri is the requested directory index
            *******************************************************************/
            if ( http_server -> uri == -1 )
            {
                /***************************************************************
                 uri not found: send user defined not-found-message
                ***************************************************************/
                http_send_uri (http_server, &e404);
            }
            else
            {
                if ( ( http_server -> uri == led1.index)
                  || ( http_server -> uri == led2.index)
                  || ( http_server -> uri == led3.index)
                  || ( http_server -> uri == led4.index) )
                {
                    /***********************************************************
                     update ledstatus
                    ***********************************************************/
                    UpdateLedStates();

                /***************************************************************
                 A java script in index.htm sends a command in the form:
                 GET led1.gif?Time=time_string&Led=led_nr_string HTTP 1.1 ....
                 The http_server argument list holds all form parameters
                 including the requested formular:
                     http_server -> argc = 5;
                     http_server -> argv[0] = "led1.gif";
                     http_server -> argv[1] = "Time";
                     http_server -> argv[2] = "time_string";
                     http_server -> argv[3] = "Led";
                     http_server -> argv[4] = "led_nr_string";
                ***************************************************************/
                    if ( !strncmp (http_server -> argv[3], "Led", 3) )
                    {
                        /***************************************************
                         toggle LED
                        ***************************************************/
                        toggle_led (atoi(http_server -> argv[4])-1);
                    }
                } // if

                /***************************************************************
                 send the requested page
                ***************************************************************/
                if ( http_send_user_page (http_server,
                                          user,
                                          http_server -> uri ) <= 0)
                {
                    /***********************************************************
                     uri not found: send user defined not-found-message
                    ***********************************************************/
                    http_send_uri (http_server, &e404);
                }
            }
            break;

        case _HTTP_UNKNOWN :                 /* unknown method                */
            /*******************************************************************
             method not implemented or syntax error
            *******************************************************************/
            http_send_uri (http_server, &e501);
            break;
    }

    /***************************************************************************
     back to http server
    ***************************************************************************/
    return (ret);
}

/*******************************************************************************

    @brief      Initialize MAC, sockets and protocols
    @param      -
    @return     0 - success or >0 - error occurred

*******************************************************************************/
#pragma CODE_SECTION(InitializeNetwork, ".commonsect");
int InitializeNetwork (void)
{
    /***************************************************************************
      locals
    ***************************************************************************/
    uint16_t ret;
    int32_t http_serv;

    /***************************************************************************
     initialize KSZ8851
      possible values
      mode: FDX_100, FDX_10, HDX_100, HDX_10, AUTO_NEG
    ***************************************************************************/
    ret = dsk_init ( network_mode, dsp_clock, link_status);

    if ( ret == 0 )
    {
        EXIT(MAC_ERROR);                            /* initialize EMAC error */
    }

    CPrintf (".");

    /***************************************************************************
     init sockets
            1. parameter:       own IP address or own HOST_NAME
            2. parameter        NULL       - own IP address is valid
                                DHCP_ENABLE - IP comes from a DHCP Server
                                                own HOST_NAME is valid
            3. parameter        DNS Server IP or NULL
            4. parameter        DNS_ENABLE or NULL
    ***************************************************************************/
    if ( !net_init (dsp_ip_addr, dhcp_setting, dns_server_ip, dns_setting))
    {
        EXIT(NETINIT_ERROR);           /* out of memory, try to increase heap */
    }

    CPrintf (".");

    /***************************************************************************
      ICMP socket allows to 'ping' the DSP
      ping data is limited to 100 byte
    ***************************************************************************/
    if ( install_icmp_socket (100) == NULL )
    {
        EXIT(ICMP_ERROR);                       /* possibly insufficient heap */
    }

    CPrintf (".");

    /***************************************************************************
      initialize http server; parameter is the specified user list
    ***************************************************************************/
    http_serv = http_server_init ( user,  /* specified user list              */
                                   NULL,  /* mmc not supported                */
                                   0);    /* max parallel connections         */
                                          /* 0 == no limit (heap limit only)  */

    if ( http_serv == 0 )
    {
        EXIT(HTTPSERVER_ERROR);                 /* possibly insufficient heap */
    }

    CPrintf (".");

    /***************************************************************************
     Set the index page, if the first defined page is not the default page.
     Read the number of the index page from generated file webpage.gen:
     {"webserver", "*" ,&clock,&dicon,&e400,&e404,&e501,&favicon,&index,&ledoff,&ledon,0},
                          ^      ^     ^     ^     ^     ^        ^
                          0      1     2     3     4     5        6
     If the index page is not named 'index', choose the index of the desired
     page
    ***************************************************************************/
    http_set_index_page ( 6);

    /***************************************************************************
     add some dynamic pages
    ***************************************************************************/
    http_add_page (&led1);
    http_add_page (&led2);
    http_add_page (&led3);
    http_add_page (&led4);

    /***************************************************************************
     define user callback function
    ***************************************************************************/
    http_define_callback ( http_interpreter);

    CPrintf (".");

    /***************************************************************************
      success
    ***************************************************************************/
    return (0);
}

/*******************************************************************************

    @brief      Main application
    @param      not used
    @return     never

*******************************************************************************/
void main ( void )
{
    /***************************************************************************
      locals
    ***************************************************************************/
    char version[6];                /* for netlib version string              */
    uint32_t ip;
    char buffer[20];                /* small buffer for ip-address conversion */

    /***************************************************************************
      initialize application
    ***************************************************************************/
    AppInit (dsp_clock);

    /***************************************************************************
      select output device for CPrintf
      possible settings:
        CPRINTF_UART_OUTPUT                       -> output to UART
        CPRINTF_CCS_OUTPUT                        -> output to CCS
        CPRINTF_UART_OUTPUT | CPRINTF_CCS_OUTPUT  -> output to UART and CCS
    ***************************************************************************/
  //  CPrintf_select_output (CPRINTF_UART_OUTPUT);  /* UART not available     */
    CPrintf_select_output (CPRINTF_CCS_OUTPUT);   /* CCS outputs              */

    CPrintf (CLRSCR);
    CPrintf ("  -------------------------------------------------\r\n");
    CPrintf (" | D.SignT          %25s demo |\r\n", program_name);
    CPrintf (" |                                                 |\r\n");
    CPrintf (" | (c) %d D.SignT                  www.dsignt.de |\r\n",BUILD_YEAR);
    CPrintf (" |                                                 |\r\n");
    CPrintf (" | netlib revision: %s                          |\r\n", get_netlib_ver (version));
    CPrintf ("  -------------------------------------------------\r\n");
    CPrintf ("\r\n");

    /***************************************************************************
     initialize network
    ***************************************************************************/
    CPrintf (" initialize network... ");
    InitializeNetwork ();
    CPrintf (" success\r\n\n");

    CPrintf (" assigned network configuration:\r\n");
    net_print_stat (0, CPrintf);

    ip = get_ip_address (0);
    OledPrintf (1, "IP: %s", inet_ntoa (ip, buffer));

    /***************************************************************************
     loop forever
    ***************************************************************************/
    for (;;)
    {
        /***********************************************************************
          call net_isq() and http_server()
        ***********************************************************************/
        net_isq ();
        http_server ();
    }
}




