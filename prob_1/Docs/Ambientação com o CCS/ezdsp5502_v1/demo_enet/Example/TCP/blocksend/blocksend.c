/*******************************************************************************
*                                                                              *
*  @file      Blocksend.c                                                      *
*  @brief     Sending a continuous data stream over TCP                        *
*                                                                              *
*  @author    D.SignT GmbH & Co. KG, Claus Hermbusche                          *
*  @date      2011-09-19
*                                                                              *
*  To verify this program, first 'ping' the DSP:                               *
*                                                                              *
*  >ping 192.168.168.200                                                       *
*                                                                              *
*  If the settings and network connections are correct, the pings will be      *
*  replied.                                                                    *
*                                                                              *
*  Establish a TCP connection on port 5031:                                    *
*                                                                              *
*  >nc 192.168.168.200 5031 > test.dat                                         *
*                                                                              *
*  A continuous data stream will be written into test.dat until the connection *
*  is closed.                                                                  *
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
 define maximum TCP packet size
*******************************************************************************/
#define PACKET_SIZE     1460

/*******************************************************************************
 define data buffer size
*******************************************************************************/
#define TCP_TX_PACKETS   10
#define BUFFER_SIZE (PACKET_SIZE * TCP_TX_PACKETS)


/*******************************************************************************
*                                                                              *
*    GLOBALS                                                                   *
*                                                                              *
*******************************************************************************/

/*******************************************************************************
 program name
*******************************************************************************/
char *program_name = "blocksend";


/*******************************************************************************
 data buffer
*******************************************************************************/
#pragma DATA_SECTION(data_buffer,".databuffer");
static unsigned char data_buffer[BUFFER_SIZE];


SOCKET *tcp_server;


/*******************************************************************************
*                                                                              *
*    FUNCTIONS                                                                 *
*                                                                              *
*******************************************************************************/

/*******************************************************************************

    @brief      send a block of data
    @param      socket - established TCP socket
    @param      data   - pointer to the beginning of data
    @param      size   - size of data
    @return     1 if successful or 0 on error

*******************************************************************************/
int32_t net_send_block (SOCKET *socket, void *data, unsigned int size)
{
    /***************************************************************************
     locals
    ***************************************************************************/
    unsigned char *bptr;
    uint32_t length = size;
    uint32_t send_length;
    int32_t ret;

    /***************************************************************************
     base pointer to data
    ***************************************************************************/
    bptr= (unsigned char *)data;

    while ( length > 0 )
    {
        /***********************************************************************
         if data length is greater than maximum packet size, limit send length
         to maximum packet size
        ***********************************************************************/
        send_length = ((length > PACKET_SIZE) ? PACKET_SIZE : length);

        net_isq ();

        /***********************************************************************
         try to send packet
        ***********************************************************************/
        ret= net_send (socket, bptr, send_length);

        /***********************************************************************
         check success
        ***********************************************************************/
        switch ( ret )
        {
            case 0:
                /***************************************************************
                 the data could not be transmitted immediately
                 check error code
                ***************************************************************/
                //~ if ( socket-> error_code == SO_NO_LINK)
                //~ {
                    //~ /***********************************************************
                     //~ link is down, return immediately
                    //~ ***********************************************************/
                    //~ shutdown (tcp_server, 0);
                    //~ return (0);
                //~ }

                while ( socket-> error_code )
                {
                    net_isq ();

                    /***********************************************************
                     check connection status
                    ***********************************************************/
                    if ( tcp_get_state (socket) != TCP_ESTABLISHED )
                    {
                        /*******************************************************
                         connection was closed, return immediately
                        *******************************************************/
                        return (0);
                    }
                    if (socket-> error_code == SO_MMU_ERROR)
                    {
                        CPrintf("MMU error\r\n");
                    }
                }
                //~ break;   // fall through

            case 1:
                /***************************************************************
                 advance base pointer, decrement length
                ***************************************************************/
                bptr+= PACKET_SIZE;
                length -= send_length;
                break;

            default :
                /***************************************************************
                 all other cases are errors
                ***************************************************************/
                return(0);
        }
    }

    /***************************************************************************
      activate the following wait for completion, when data may change after
      return
    ***************************************************************************/
    //~ while (!tcp_tx_complete(socket))         net_isq ();

    return(1);
}

/*******************************************************************************

    @brief      Initialize MAC, sockets and protocols
    @param      -
    @return     0 - success or >0 - error occurred

*******************************************************************************/
#pragma CODE_SECTION(InitializeNetwork,".commonsect");
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
      ICMP socket allows to 'ping' the DSP
    ***************************************************************************/
    if ( install_icmp_socket (100) == NULL )
    {
        EXIT(ICMP_ERROR);                       /* possibly insufficient heap */
    }

    CPrintf (".");

    /***************************************************************************
      create TCP data server socket on port 5031
    ***************************************************************************/
    tcp_server = socket_open (ANY_ADDRESS,
                              ANY_PORT,
                              5031,
                              DATATYPE_CHAR,
                              TCP_INIT_FUNC);
    if ( tcp_server == NULL )
    {
        EXIT(SOCKETOPEN_ERROR);                 /* possibly insufficient heap */
    }


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
    volatile int ret;
    static char buffer[100];      /* buffer for incoming TCP data             */
    uint32_t ip;

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
    CPrintf (" To verify this program, first 'ping' the DSP:\r\n");
    CPrintf (">ping %s\r\n", dsp_ip_addr);
    CPrintf ("\r\n");
    CPrintf (" If the settings and network connections are correct,\r\n the pings will be replied.\r\n");
    CPrintf ("\r\n");
    CPrintf ("Establish a TCP connection on port 5031:\r\n");
    CPrintf (">nc %s 5031 > test.dat\r\n", dsp_ip_addr);
    CPrintf ("A continuous data stream will be written into test.dat until the connection is\r\n closed.\r\n");

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

        /***********************************************************************
         wait for incoming connection
        ***********************************************************************/
        while ( !accept (tcp_server) )
        {
            net_recv (tcp_server, buffer, sizeof(buffer));
            net_isq ();
        }

        /***********************************************************************
         if we fall here, a TCP connection has been established successfully
         clear the error_code SO_CONNECTION_ESTABLISHED
        ***********************************************************************/
        tcp_server-> error_code = 0;
        for(;;)
        {
            net_isq ();

            /*******************************************************************
             send a block of data
            *******************************************************************/
            ret = net_send_block (tcp_server, data_buffer, BUFFER_SIZE);

            /*******************************************************************
             check connection
            *******************************************************************/
            if ( tcp_get_state (tcp_server) != TCP_ESTABLISHED )
            {
                CPrintf (" connection on data socket lost!\r\n\r\n");
                break;
            }
        }
    }
}

