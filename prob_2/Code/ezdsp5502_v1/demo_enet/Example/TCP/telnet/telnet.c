/*******************************************************************************
*                                                                              *
*  @file      telnet.c                                                         *
*  @brief     Test Program for the telnet protocol                             *
*                                                                              *
*  @author    D.SignT GmbH & Co. KG, Claus Hermbusche                          *
*  @date      2011-09-19
*                                                                              *
*  @details                                                                    *
*    This program installs a Telnet-server on TCP port 23 to perform ASCII up- *
*    and downloads to and from configuration file located on address 0x30000 in*
*    FLASH memory and application file in intel hex format located on address  *
*    0x00000.                                                                  *
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
#include <ctype.h>

/*******************************************************************************
  network support function
*******************************************************************************/
#include "..\..\..\netlib\dsknet.h"          /* network support               */
#include "telnet.h"                          /* telnet support                */

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
  MAX_PING_DATA is used to specify the maximum data to be pinged. For normal
  operation a value 64 to 100 should be sufficient.
*******************************************************************************/
#define MAX_PING_DATA             100

/*******************************************************************************
 defines for user menu
*******************************************************************************/
#define TMENU1     0
#define TMENU2     1


/*******************************************************************************
*                                                                              *
*    GLOBALS                                                                   *
*                                                                              *
*******************************************************************************/
/*******************************************************************************
 program name
*******************************************************************************/
char *program_name = "telnet";


/*******************************************************************************
 for 32bit alignment (needed if DMA-transfers used) define the following
 messages as char-arrays:
*******************************************************************************/
char hello_msg[] = "\x1B[2J" \
  "  -------------------------------------------------\r\n"
  " | D.SignT             DSK-KSZ8851  Set-Up Utility |\r\n"
  " |                                                 |\r\n"
  " | netlib-Rev XX.XX                                |\r\n"
  " |                                                 |\r\n"
  " | (c) D.SignT "__DATE__"           www.dsignt.de |\r\n"
  "  -------------------------------------------------\r\n";


char commands[] = "\r\n commands:\r\n"
                 " d   - download config or hex file from flash memory\r\n"
                 " u   - upload config or hex file to flash memory\r\n"
                 " enter command [h for help] > ";
char crlf[]  = "\r\n";

char out_of_memory_msg[] = "error: out of memory\r\n";
char success_msg[] = " Success\r\n";
char upload_msg[] = " upload <I>ntel-Hex or <C>onfig file [i|c] ? ";
char download_msg[] = " download <I>ntel-Hex or <C>onfig file [i|c] ? ";
char file_msg[] = "\r\n <I>ntel-Hex or <C>onfig file [i|c] ? ";
char goodbye_msg[] = " goodbye! ";
char receive_hex_msg[] = "\r\n ready to receive Intel-Hex file..  ";
char send_hex_msg[] = "\r\n sending Intel-Hex file..  \r\n";
char receive_config_msg[] = "\r\n ready to receive config file..  ";
char send_config_msg[] = "\r\n sending config file..  \r\n";

unsigned char telnet_option_msg[]= { TELNET_IAC, TELNET_WILL, 1, 0 };

/*******************************************************************************
 user buffer
*******************************************************************************/
char global_buffer[MAX_BUFFER];            /* global buffer for user input    */


/*******************************************************************************
  direntry_type: used for creating a directory:

     direntry_type dir1 = {"dirname", "filename", size, access, filetype, location };

*******************************************************************************/
direntry_type application = {"application"  , "app.hex"   , 0x30000, FTP_RW | FSYS_WRITE_BOOT_SECTOR, 'I', 0x0000 };
direntry_type config      = {"configuration", "config.txt", 0x10000, FTP_RW , 'A', 0x30000 };


/*******************************************************************************
*                                                                              *
*    FUNCTIONS                                                                 *
*                                                                              *
*******************************************************************************/

/*******************************************************************************

    @brief      Transmit a user specified file from or to FLASH or RAM

    @param      server         - connected TCP server socket
    @param      dir            - pointer to file specified above
    @param      rw             - read/write flag (FTP_READ, FTP_WRITE)
    @param      flags          - flags for controlling action:
                          @sa      FSYS_SEND_ALL     - generate blocking call
                          @sa      FSYS_ERASE_SECTOR - pre-erase FLASH-sectors
                          @sa      FSYS_WRITE_BOOT_SECTOR - write boot sector

    @return   TRUE           - Success
    @return   FASLE          - Error occurred

    @sa          fsys_get_file_size() - netlib
    @sa          fsys_init_flash()    - netlib
    @sa          fsys_send_all()      - netlib
    @sa          net_send_string()    - netlib

*******************************************************************************/
int transmit_file ( SOCKET *server,
                    direntry_type *dir,
                    unsigned int rw,
                    unsigned int flags  )
{
    /***************************************************************************
     locals
    ***************************************************************************/
    int ret;
    char *buffer;

    /***************************************************************************
     malloc some space for transmission
     note: the used data buffer for file transmission must be dynamic; it is
     freed automatically after file transmission
    ***************************************************************************/
    buffer = (char *) malloc (1500 * sizeof (char));

    if ( buffer == NULL )   // out of memory
    {
        net_send_string (server, out_of_memory_msg);
        ret = FALSE;
    }
    else
    {
        /***********************************************************************
         initialize sending
        ***********************************************************************/
        dir -> data_con = server;                     // actual server connection
        dir -> buffer   = buffer;                     // data buffer
        dir -> pos      = 0;                          // offset
        dir -> rw       = rw;                         // transmit direction
        dir -> size     = fsys_get_file_size (dir);   // get actual filesize

        if ( rw == FTP_WRITE )
        {
            /*******************************************************************
             initialize FLASH sectors
             used for automatic sector erase
            *******************************************************************/
            fsys_init_flash ();
        }

        /***********************************************************************
         transmit data
           flags:
           FSYS_SEND_ALL          - process blocking call
           FSYS_ERASE_SECTOR      - erase FLASH-sector before data transmission
           FSYS_WRITE_BOOT_SECTOR - write boot sector
        ***********************************************************************/
        fsys_send_all (dir, 0, flags);
        /***********************************************************************
         buffer is freed automatically in fsys_send_all()!!!
        ***********************************************************************/


        /***********************************************************************
         check success
        ***********************************************************************/
        if ( dir -> error < 0 )
        {
            switch (dir -> error)
            {
                case FSYS_BIOS_PROTECT_ERROR :
                    net_send_string (server, "BIOS protect error\r\n");
                    break;
                case FSYS_CHECKSUM_ERROR :
                    net_send_string (server, "intel hex checksum error\r\n");
                    break;
                case FSYS_INTEL_HEX_ERROR :
                    net_send_string (server, "intel hex error\r\n");
                    break;
                case FSYS_SECTOR_ERASE_ERROR :
                    net_send_string (server, "sector erase error\r\n");
                    break;
                case FSYS_FLASH_PROGRAM_ERROR :
                    net_send_string (server, "FLASH program error\r\n");
                    break;
                case FSYS_BUFFER_UNDERRUN_ERROR :
                    net_send_string (server, "buffer underrun error\r\n");
                    break;
                case FSYS_OUT_OF_MEMORY_ERROR :
                    net_send_string (server, "out of memory error\r\n");
                    break;
                case FSYS_OUT_OF_RANGE_ERROR :
                    net_send_string (server, "out of range error\r\n");
                    break;
                default:
                    net_send_string (server, "Unknown error!\r\n");
            }
        }
        else
        {
            net_send_string (server, success_msg);
        }

        ret = TRUE;
    }
    return (ret);
}

/*******************************************************************************

    @brief      process a user menu

    @param      tcp_server - established connection
    @param      c - command to process
    @return     always TRUE
    @sa         net_send_string()    - netlib
    @sa         tolower()            - rts
    @sa         net_isq()            - netlib
    @sa         transmit_file()      - this file

*******************************************************************************/
int user_menu ( SOCKET *tcp_server, unsigned char *c )
{
    /***************************************************************************
     locals
    ***************************************************************************/
    int ret = TRUE;
    static unsigned int rw = 0;               /* read/write flag              */
    static unsigned int menu_level = TMENU1;  /* menu level                   */

    switch ( menu_level )
    {
        case TMENU1:
            /*******************************************************************
             parse command
            *******************************************************************/
            switch ( tolower(*c) )
            {
                /***************************************************************
                 upload command
                ***************************************************************/
                case 'u':
                    /***********************************************************
                     set direction
                    ***********************************************************/
                    rw = FTP_WRITE;

                    /***********************************************************
                     switch to next menu
                    ***********************************************************/
                    menu_level = TMENU2;

                    /***********************************************************
                     print message
                    ***********************************************************/
                    net_send_string (tcp_server, upload_msg);
                    break;

                /***************************************************************
                 download command
                ***************************************************************/
                case 'd':
                    /***********************************************************
                     set direction
                    ***********************************************************/
                    rw = FTP_READ;

                    /***********************************************************
                     print message
                    ***********************************************************/
                    net_send_string (tcp_server, download_msg);

                    /***********************************************************
                     switch to next menu
                    ***********************************************************/
                    menu_level = TMENU2;
                    break;

                /***************************************************************
                 unknown command
                ***************************************************************/
                default :
                    rw = 0;
                    net_send_string (tcp_server, commands);
                    break;
            } // switch
            break;

        case TMENU2:
            /*******************************************************************
             parse command
            *******************************************************************/
            switch ( tolower(*c) )
            {
                /***************************************************************
                 intel-hex file
                ***************************************************************/
                case 'i' :
                    if ( rw & FTP_WRITE )
                    {
                        net_send_string (tcp_server, receive_hex_msg);
                    }
                    else
                    {
                        net_send_string (tcp_server, send_hex_msg);
                    }
                    /***********************************************************
                     start transmission
                    ***********************************************************/
                    transmit_file ( tcp_server, &application, rw, FSYS_SEND_ALL | FSYS_WRITE_BOOT_SECTOR);

                    /***********************************************************
                     print available commands
                    ***********************************************************/
                    net_send_string (tcp_server, commands);

                    /***********************************************************
                     back to root menu
                    ***********************************************************/
                    menu_level = TMENU1;
                    break;

                /***************************************************************
                 config file
                ***************************************************************/
                case 'c' :
                    if ( rw & FTP_WRITE )
                    {
                        net_send_string (tcp_server, receive_config_msg);
                    }
                    else
                    {
                        net_send_string (tcp_server, send_config_msg);
                    }
                    /***********************************************************
                     start transmission
                    ***********************************************************/
                    transmit_file ( tcp_server, &config, rw, FSYS_SEND_ALL);

                    /***********************************************************
                     print available commands
                    ***********************************************************/
                    net_send_string (tcp_server, commands);

                    /***********************************************************
                     back to root menu
                    ***********************************************************/
                    menu_level = TMENU1;
                    break;

                /***************************************************************
                 Escape
                ***************************************************************/
                case 0x1b :

                    /***********************************************************
                     print available commands
                    ***********************************************************/
                    net_send_string (tcp_server, commands);

                    /***********************************************************
                     back to root menu
                    ***********************************************************/
                    menu_level = TMENU1;
                    break;

                /***************************************************************
                 wrong command print message
                ***************************************************************/
                default  :
                    net_send_string (tcp_server,  file_msg);
                    break;
            }
            break;

        default :
            break;
    } // switch

    return (ret);
}

/*******************************************************************************

    @brief      send a Telnet option

    @param      tcp_server - current connection
    @param      option - option to send
    @param      c - option value
    @return     nothiung
    @sa         net_send_ready()  -   netlib

*******************************************************************************/
void send_telnet_option ( SOCKET *tcp_server, unsigned char option, unsigned char c )
{
    /***************************************************************************
     locals
    ***************************************************************************/

    telnet_option_msg[1] = option;
    telnet_option_msg[2] = c;
    net_send_ready (tcp_server, telnet_option_msg, 4, 100000);

}


/*******************************************************************************

    @brief      Parse user commands

    @param      telnet - connected TCP server socket
    @return     nothing
    @sa         net_recv()           - netlib
    @sa         user_menu()          - this file
    @sa         send_telnet_option() - this file

*******************************************************************************/
void telnet_check_message ( telnet_server_type *telnet )
{
    /***************************************************************************
     locals
    ***************************************************************************/
    int len;                           /* receive length                      */
    unsigned char c, *cp;

    /***************************************************************************
     new message received ?
    ***************************************************************************/
    if ( (len = net_recv (telnet-> server, telnet-> buffer, MAX_BUFFER)) > 0 )
    {
        /***********************************************************************
         parse buffer
        ***********************************************************************/
        cp = (unsigned char *)telnet-> buffer;
        while ( len )
        {
            /*******************************************************************
             get one character
            *******************************************************************/
            c = *cp++;
            len--;

            /*******************************************************************
             parse telnet protocol
            *******************************************************************/
            switch ( telnet-> state )
            {
                case TSTATE_NORMAL:
                    if (c == TELNET_IAC)
                    {
                        telnet-> state = TSTATE_IAC;
                    }
                    else
                    {
                        /*******************************************************
                         process user command
                        *******************************************************/
                        user_menu ( telnet-> server, &c );
                    }
                    break;

                case TSTATE_IAC:
                    if (c == TELNET_IAC)
                    {
                        /*******************************************************
                         not valid, back to normal state
                        *******************************************************/
                        telnet-> state = TSTATE_NORMAL;
                    }
                    else
                    {
                        /*******************************************************
                         telnet option
                        *******************************************************/
                        switch (c)
                        {
                            case TELNET_WILL:
                                telnet-> state = TSTATE_WILL;
                                break;

                            case TELNET_WONT:
                                telnet-> state = TSTATE_WONT;
                                break;

                            case TELNET_DO:
                                telnet-> state = TSTATE_DO;
                                break;

                            case TELNET_DONT:
                                telnet-> state = TSTATE_DONT;
                                break;

                            default:
                                telnet-> state = TSTATE_NORMAL;
                                break;
                        }
                    }
                    break;

                case TSTATE_WILL:
                    /***********************************************************
                     Reply with a DONT
                    ***********************************************************/
                    send_telnet_option (telnet-> server, TELNET_DONT, c);
                    telnet-> state = TSTATE_NORMAL;
                    break;

                case TSTATE_WONT:
                    /***********************************************************
                     Reply with a DONT
                    ***********************************************************/
                    send_telnet_option (telnet-> server, TELNET_DONT, c);
                    telnet-> state = TSTATE_NORMAL;
                    break;

                case TSTATE_DO:
                    /***********************************************************
                     Reply with a WONT
                    ***********************************************************/
                    send_telnet_option (telnet-> server, TELNET_WONT, c);
                    telnet-> state = TSTATE_NORMAL;
                    break;

                case TSTATE_DONT:
                    /***********************************************************
                     Reply with a WONT
                    ***********************************************************/
                    send_telnet_option (telnet-> server, TELNET_WONT, c);
                    telnet-> state = TSTATE_NORMAL;
                    break;

                default :
                    telnet-> state = TSTATE_NORMAL;
                    break;
            } // switch
        } // while
    }
}

/*******************************************************************************

    @brief      handle Telnet Server

    @param      telnet_server_type *telnet
    @return     nothing
    @sa         tcp_get_state()        - netlib
    @sa         net_send_string()      - netlib
    @sa         telnet_check_message() - this file

*******************************************************************************/
void telnet_server ( telnet_server_type *telnet )
{
    /***************************************************************************
     locals
    ***************************************************************************/
    char netlib_rev_id[6];

    /***************************************************************************
     check for connection established
    ***************************************************************************/
    if ( tcp_get_state (telnet-> server) == TCP_STATE_ESTABLISHED )
    {
        /***********************************************************************
         is it a new connection ?
        ***********************************************************************/
        if ( telnet-> so_state == SOCKET_DISCONNECTED )
        {
            /*******************************************************************
             clear the SO_CONNECTION_ESTABLISHED error
            *******************************************************************/
            telnet-> server-> error_code = 0;

            get_netlib_ver (netlib_rev_id);

            /*******************************************************************
             print info
            *******************************************************************/
            hello_msg[179] = netlib_rev_id[0];  // major version
            hello_msg[180] = netlib_rev_id[1];  // major version
            hello_msg[182] = netlib_rev_id[3];  // minor version
            hello_msg[183] = netlib_rev_id[4];  // minor version
            net_send_string (telnet-> server, hello_msg);
            net_send_string (telnet-> server, commands);
            telnet-> so_state = SOCKET_CONNECTED;
        }

        /***********************************************************************
         check for new message
        ***********************************************************************/
        telnet_check_message (telnet);
    }
    else
    {
        /***********************************************************************
         if server is listening
        ***********************************************************************/
        if ( tcp_get_state (telnet-> server) == TCP_STATE_LISTEN )
        {
            /*******************************************************************
             but status connected
            *******************************************************************/
            if ( telnet-> so_state == SOCKET_CONNECTED)
            {
                /***************************************************************
                 clear status
                ***************************************************************/
                telnet-> so_state = SOCKET_DISCONNECTED;
            }
        }
    }
}

/*******************************************************************************

    @brief      Initialize EMAC, sockets and protocols
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
      ICMP socket allows to 'ping' the DSP
    ***************************************************************************/
    if ( install_icmp_socket (100) == NULL )
    {
        EXIT(ICMP_ERROR);                       /* possibly insufficient heap */
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
void main (void)
{
    /***************************************************************************
      locals
    ***************************************************************************/
    char version[6];
    telnet_server_type telnet;
    uint32_t ip;
    char buffer[20];  // small buffer for ip-address conversion

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


    /***************************************************************************
     initialize telnet server
    ***************************************************************************/
    telnet.buffer = global_buffer;
    telnet.so_state = SOCKET_DISCONNECTED;
    telnet.state = TSTATE_NORMAL;

    /***************************************************************************
      create TCP data server socket on telnet port
    ***************************************************************************/
    telnet.server = socket_open (ANY_ADDRESS,
                                 ANY_PORT,
                                 TELNET_PORT,
                                 DATATYPE_CHAR,
                                 TCP_INIT_FUNC);
    if ( telnet.server == NULL )
    {
        EXIT(SOCKETOPEN_ERROR);
    }


    /***************************************************************************
     set receive-buffer size
    ***************************************************************************/
    set_recv_buffer (telnet.server, telnet.buffer, MAX_BUFFER);

    /***************************************************************************
     init files
    ***************************************************************************/
    fsys_init_file ( &config, 0, 0);
    fsys_init_file ( &application, 0, 0);

    CPrintf (" assigned network configuration:\r\n");
    net_print_stat (0, CPrintf);

    ip = get_ip_address (0);
    OledPrintf (1, "IP: %s", inet_ntoa (ip, buffer));

    /***************************************************************************
      main program loop: process network
    ***************************************************************************/
    for ( ;; )
    {
        net_isq ();

        telnet_server (&telnet);
    }
}

