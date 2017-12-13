/*******************************************************************************
*                                                                              *
*  @file      multicast.c                                                      *
*  @brief     UDP multicast test program                                       *
*                                                                              *
*  @author    D.SignT GmbH & Co. KG, Claus Hermbusche                          *
*  @date      2011-09-19
*                                                                              *
*    Simple DSP program for receiving multicast UDP - packets. The received    *
*    data is used to switch the LED's on and off. The DSP IP address is con-   *
*    figured to 192.168.168.200. The multicast group is 239.255.1.1 port 5555. *
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

#ifdef __cplusplus
} // extern "C"
#endif

/*******************************************************************************
*                                                                              *
*    DEFINES                                                                   *
*                                                                              *
*******************************************************************************/

/*******************************************************************************
 Multicast configuration
*******************************************************************************/
#define MCAST_IP_ADDR   "239.255.1.1"     /* organisations local multicast */
#define MCAST_IP_ADDR2  "239.255.1.2"     /* organisations local multicast */
#define MCAST_PORT      5555
#define MCAST_PORT2     5556
#define DSP_PORT        5031

/*******************************************************************************
  command list
*******************************************************************************/
#define CMD_LED_INIT      1
#define CMD_LED_ON        2
#define CMD_LED_OFF       3


/*******************************************************************************
*                                                                              *
*    GLOBALS                                                                   *
*                                                                              *
*******************************************************************************/

/*******************************************************************************
 program name
*******************************************************************************/
char *program_name = "multicast";


SOCKET *udp_socket;     /* socket descriptor                                  */
char *udp_data;         /* data buffer for socket                             */


/*******************************************************************************
*                                                                              *
*    FUNCTIONS                                                                 *
*                                                                              *
*******************************************************************************/

/*******************************************************************************

    @brief  This function is called each time new data is received

    @param  so   - socket
    @param  data - pointer to received data
    @param  len  - received data length
    @param  ec   - error code
    @return >= 0 - if message processed or < 0  - if socket was closed

*******************************************************************************/
int32_t udp_call_back (SOCKET *so, void *data, uint32_t len, uint32_t ec)
{
    /***************************************************************************
      locals
    ***************************************************************************/
    char *udp_data = (char *)data;
    char buffer[20];  /* small buffer for ip-address conversion */

	UNREFERENCED_PARAMETER(len);

    switch (ec)
    {
        case 0:
            /*******************************************************************
             a new command received:
             1. byte: command
             2. byte: led number
            *******************************************************************/
            switch ( udp_data[0] )
            {
                case CMD_LED_INIT:
                    LED_init();
                    break;

                case CMD_LED_ON:
                    LED_on(udp_data[1]);
                    break;

                case CMD_LED_OFF:
                    LED_off(udp_data[1]);
                    break;

                default :
                    /* no more commands defined*/
                    break;
            } // switch

            if (IS_MULTICAST(so-> mc_group_addr))
            {
                /***************************************************************
                 when this is a multicast UDP packet, so-> dest_addr, so-> src_addr
                 and so-> src_port, so-> dest_port are invalid! Use a new offset
                 to access valid connection data:
                ***************************************************************/
                CPrintf (" New multicast data received\r\n");
                CPrintf (" Destination Address:     %s\r\n", inet_ntoa ( so-> mc_dest_addr, buffer));
                CPrintf (" Multicast Group Address: %s\r\n", inet_ntoa ( so-> mc_group_addr, buffer));
                CPrintf (" Destination Port:        %d\r\n", so-> mc_dest_port);
                CPrintf (" Source Multicast Port:   %d\r\n", so-> mc_src_port);
            }
            else
            {
                CPrintf (" New data received\r\n"
                         " Destination Address: %s\r\n"
                         " Source Address:      %s\r\n"
                         " Destination Port:    %d\r\n"
                         " Source Port:         %d\r\n\n",
                         inet_ntoa ( so-> dest_addr, buffer),
                         inet_ntoa ( so-> src_addr, buffer),
                         so-> dest_port,
                         so-> src_port);
            }
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
    if ( !net_init (dsp_ip_addr, dhcp_setting, dns_server_ip, dns_setting))
    {
        EXIT(NETINIT_ERROR);           /* out of memory, try to increase heap */
    }

    CPrintf (".");

    /***************************************************************************
      install icmp socket (for ping)
    ***************************************************************************/
    if ( install_icmp_socket (100) == NULL )
    {
        EXIT(ICMP_ERROR);                       /* possibly insufficient heap */
    }

    CPrintf (".");

    /***************************************************************************
     open socket
    ***************************************************************************/
    udp_socket = socket_open (ANY_ADDRESS,        /* all addresses            */
                              ANY_PORT,           /* destination port         */
                              DSP_PORT,           /* source port              */
                              DATATYPE_CHAR,      /* data type char           */
                              UDP_INIT_FUNC);     /* udp protocol             */
    if ( udp_socket == NULL )
    {
        EXIT(SOCKETOPEN_ERROR);                 /* possibly insufficient heap */
    } // if

    /***************************************************************************
     malloc space for data
    ***************************************************************************/
    udp_data = (char *) malloc (1000 * sizeof(char));
    if ( udp_data == NULL )
    {
        exit(UNKNOWN_ERROR);
    }

    /***************************************************************************
      define callback function for received UDP packets
    ***************************************************************************/
    socket_define_callback (udp_socket, udp_call_back, udp_data, 1000);

    /***************************************************************************
     join a multicast group
    ***************************************************************************/
    multicast_join_group (udp_socket, MCAST_IP_ADDR, MCAST_PORT);

    /***************************************************************************
     join another multicast group
    ***************************************************************************/
    multicast_join_group (udp_socket, MCAST_IP_ADDR, MCAST_PORT2);
    multicast_join_group (udp_socket, MCAST_IP_ADDR2, MCAST_PORT2);

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
void main (void)
{
    /***************************************************************************
     locals
    ***************************************************************************/
    char version[6];
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
    for(;;)
    {
        /***********************************************************************
         process net_isq()
        ***********************************************************************/
        net_isq ();
    }
}
