/*******************************************************************************
*                                                                              *
*  @file      NetTest.c                                                        *
*  @brief     Network test program                                             *
*                                                                              *
*  @author    D.SignT GmbH & Co. KG, Claus Hermbusche                          *
*  @date      2011-09-19
*                                                                              *
*  @details                                                                    *
*                                                                              *
*  This program installs a UDP echo server (port 7),                           *
*  and a TCP server listening on port 1061.                                    *
*                                                                              *
*  To verify this program, first 'ping' the DSP:                               *
*  >ping 192.168.168.200                                                       *
*  If the settings and network connections are correct, the pings              *
*  will be replied.                                                            *
*                                                                              *
*  The UDP Echo server will re-send (echo) anything it receives.               *
*  To verify this, start NetCat (nc) with the following command                *
*  >nc -u 192.168.168.200 7                                                    *
*       |       |         |                                                    *
*       |       |         +-- port 7 = Echo Port                               *
*       |       +------------ the DSP's IP address                             *
*       +-------------------- use UDP transfers                                *
*                                                                              *
*  Any characters you type in the console window will be returned.             *
*  NetCat doesn't send the characters immediately, it will send                *
*  the entire string following a terminating CR. Please note that              *
*  the maximum length of the character string is limited by the                *
*  size of the buffer used for UDP echo (1024). You may also                   *
*  transmit a file by re-directing it to stdin:                                *
*  >nc -u 192.168.168.200 7 < hello.txt                                        *
*                                                                              *
*  The TCP server will respond to any incoming request on port 1061            *
*  and return a short message. To verify this, start NetCat with               *
*  the following command                                                       *
*  >nc 192.168.168.200 1061                                                    *
*            |         |                                                       *
*            |         +-- port 1061 = the port the DSP listens to             *
*            +------------ the DSP's IP address                                *
*                                                                              *
*  Type a CR, the DSP will respond with its messge                             *
*                                                                              *
*                                                                              *
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


#ifdef __cplusplus
extern "C" {
#endif /* !__cplusplus */
/*******************************************************************************
  local prototypes
*******************************************************************************/
int32_t tcp_call_back (SOCKET *so, void *data, uint32_t len, uint32_t ec);
int32_t udp_call_back (SOCKET *so, void *data, uint32_t len, uint32_t ec);

#ifdef __cplusplus
} // extern "C"
#endif

/*******************************************************************************
*                                                                              *
*    DEFINES                                                                   *
*                                                                              *
*******************************************************************************/
/* - */


/*******************************************************************************
*                                                                              *
*    GLOBALS                                                                   *
*                                                                              *
*******************************************************************************/
/*******************************************************************************
 program name
*******************************************************************************/
char *program_name = "nettest";


static char *tcp_tx = "this is the DSP response\r\n";

static char buffer[1024];                    /* buffer for UDP echos          */
static char tcp_rx[16];                      /* buffer for TCP requests       */
SOCKET *udp_echo;
SOCKET *tcp_server;


/*******************************************************************************
*                                                                              *
*    FUNCTIONS                                                                 *
*                                                                              *
*******************************************************************************/


/*******************************************************************************

    @brief  This function is called each time new data is received or on errors

    @param  so   - socket
    @param  data - pointer to received data
    @param  len  - received data length
    @param  ec   - error code
    @return >= 0 - if message processed or < 0  - if socket was closed

*******************************************************************************/
int32_t udp_call_back (SOCKET *so, void *data, uint32_t len, uint32_t ec)
{
    switch (ec)
    {
        case 0:
            /*******************************************************************
             send echo
            *******************************************************************/
            net_send (so, data, (uint16_t)len);
            break;

        default:
            /*******************************************************************
             else print error
            *******************************************************************/
            net_print_error (ec, CPrintf);
            break;
    }

    /***************************************************************************
     return true, if message processed
    ***************************************************************************/
    return (1);
}


/*******************************************************************************

    @brief  This function is called each time new data is received or on errors
            or connection status changes

    @param  so   - socket
    @param  data - pointer to received data
    @param  len  - received data length
    @param  ec   - error code
    @return >= 0 - if message processed or < 0  - if socket was closed

*******************************************************************************/
int32_t tcp_call_back (SOCKET *so, void *data, uint32_t len, uint32_t ec)
{
    UNREFERENCED_PARAMETER(data);
    UNREFERENCED_PARAMETER(len);
    switch (ec)
    {
        case 0:
            /*******************************************************************
             send TCP message
            *******************************************************************/
            net_send (so, tcp_tx, strlen(tcp_tx));
            break;

        case SO_CONNECTION_ESTABLISHED:
            /*******************************************************************
             connection established
            *******************************************************************/
            net_print_error (ec, CPrintf);
            break;

        case SO_CONNECTION_CLOSED:
            /*******************************************************************
             connection closed
            *******************************************************************/
            net_print_error (ec, CPrintf);
            break;
        default:
            /*******************************************************************
             else print error
            *******************************************************************/
            net_print_error (ec, CPrintf);

            /*******************************************************************
             shutdown connection
            *******************************************************************/
            shutdown (so, 100);
            break;
    }

    /***************************************************************************
     return true, if message processed
    ***************************************************************************/
    return (1);
}

/*******************************************************************************

    @brief      Initialize MAC, sockets and protocols
    @param      -
    @return     0 - success or >0 - error occurred

*******************************************************************************/
int InitializeNetwork (void)
{
    /***************************************************************************
      locals
    ***************************************************************************/
    uint16_t ret;

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
    dns_setting = DNS_ENABLE;
    if ( !net_init (dsp_ip_addr, dhcp_setting, dns_server_ip, dns_setting))
    {
        EXIT(NETINIT_ERROR);           /* out of memory, try to increase heap */
    }

    CPrintf (".");

    /***************************************************************************
      configure gateway
    ***************************************************************************/
    net_set_gateway (dns_server_ip,
                     "255.255.255.0");

    /***************************************************************************
      ICMP socket allows to 'ping' the DSP
    ***************************************************************************/
    if ( install_icmp_socket (1024) == NULL )
    {
        EXIT(ICMP_ERROR);                       /* possibly insufficient heap */
    }

    CPrintf (".");

    /***************************************************************************
      create UDP echo socket
    ***************************************************************************/
    udp_echo = socket_open (ANY_ADDRESS,
                            ANY_PORT,
                            ECHO_PORT,
                            DATATYPE_CHAR,
                            UDP_INIT_FUNC);

    if ( udp_echo == NULL )
    {
        EXIT(SOCKETOPEN_ERROR);                 /* possibly insufficient heap */
    }

    CPrintf (".");

    /***************************************************************************
      define callback function for received UDP packets
    ***************************************************************************/
    socket_define_callback (udp_echo, udp_call_back, buffer, sizeof(buffer));

    CPrintf (".");

    /***************************************************************************
      create TCP data server socket on port 1061
    ***************************************************************************/
    tcp_server = socket_open (ANY_ADDRESS,
                              ANY_PORT,
                              1061,
                              DATATYPE_CHAR,
                              TCP_INIT_FUNC);
    if ( tcp_server == NULL )
    {
        EXIT(SOCKETOPEN_ERROR);                 /* possibly insufficient heap */
    }

    CPrintf (".");

    /***************************************************************************
      define callback function for received TCP packets
    ***************************************************************************/
    socket_define_callback (tcp_server, tcp_call_back, tcp_rx, sizeof(tcp_rx));

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
    char version[6];              /* for netlib version string                */
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
    CPrintf (" To verify this program, first 'ping' the DSP:\r\n");
    CPrintf (">ping %s\r\n", dsp_ip_addr);
    CPrintf ("\r\n");
    CPrintf (" UDP test:\r\n");
    CPrintf (">nc -u %s 7\r\n", dsp_ip_addr);
    CPrintf ("\r\n");
    CPrintf (" TCP test\r\n");
    CPrintf (">nc %s 1061\r\n", dsp_ip_addr);
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
      main program loop: process network
    ***************************************************************************/
    for ( ;; )
    {
        net_isq();
    }
}




