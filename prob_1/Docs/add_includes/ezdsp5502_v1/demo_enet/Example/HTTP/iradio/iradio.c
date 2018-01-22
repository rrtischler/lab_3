/*******************************************************************************
*                                                                              *
*  @file      iradio.c                                                         *
*  @brief     receiving internet radio stream                                  *
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
#include <string.h>
#include <ctype.h>

/*******************************************************************************
  Board Support Library
*******************************************************************************/
//~ #include ".\bsl\include\ezdsp5502.h"
//~ #include ".\bsl\include\ezdsp5502_i2c.h"
#include "..\..\..\common\bsl\include\ezdsp5502_i2cgpio.h"

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
int32_t tcp_callback (SOCKET *so, void *data, uint32_t len, uint32_t ec);
int8_t *string_dup ( int8_t *buffer);
int32_t http_get_line (int8_t *dest, int8_t *src);

#ifdef __cplusplus
} // extern "C"
#endif


/*******************************************************************************
*                                                                              *
*    DEFINES                                                                   *
*                                                                              *
*******************************************************************************/
/*******************************************************************************
 data buffer size
*******************************************************************************/
#define MAX_DATA    1460

/*******************************************************************************
 station_type is used to describe a station.
*******************************************************************************/
typedef struct station
{
    int8_t *name;
    uint16_t port;
    int8_t *address;
    int8_t *request;
    int8_t *real_name;
} station_type;

/*******************************************************************************
 this string is offered in HTTP get request
*******************************************************************************/
#define __PLAYER__        "User-Agent: C5509Player/1.0.0.1\r\n"

/*******************************************************************************
 some station require a special player
*******************************************************************************/
#define __NSPLAYER__      "User-Agent: NSPlayer/11.0.5721.5251\r\n"

/*******************************************************************************
 6 station description available in this demo
*******************************************************************************/
#define MAX_STATION  6

/*******************************************************************************
*                                                                              *
*    GLOBALS                                                                   *
*                                                                              *
*******************************************************************************/

/*******************************************************************************
 program name
*******************************************************************************/
char *program_name = "IRadio";

/*******************************************************************************
 GEL file iradiocontrol.gel is used to set action.
 Possible values:
   1 - connect
   2 - disconnect
   3 - next station
   4 - previous station
*******************************************************************************/
unsigned long action = 0;


/*******************************************************************************
 global socket
*******************************************************************************/
SOCKET *tcp_socket = INVALID_SOCKET;  /* socket descriptor                    */

/*******************************************************************************
 data buffer pointer, space is allocated from heap
*******************************************************************************/
char *data;                           /* data buffer for iradio stream        */

/*******************************************************************************
 buffer for incoming stream information
*******************************************************************************/
char info[200];

/*******************************************************************************
 pointer to stream information
*******************************************************************************/
char *pinfo;

/*******************************************************************************
 new info is set, when a new stream title was received
*******************************************************************************/
int new_info = 0;


/*******************************************************************************
 station definition
*******************************************************************************/
station_type stations[] =
{
    {
        (int8_t *)"L1VE",
        80,
        (int8_t *)"gffstream.ic.llnwd.net",
        (int8_t *)"GET http://gffstream.ic.llnwd.net/stream/gffstream_stream_wdr_einslive_a HTTP/1.1\r\n"
        "Host: gffstream.ic.llnwd.net\r\n"
        "Accept: */*\r\n"
        __PLAYER__
        "Icy-MetaData:1\r\n"
        "Proxy-Connection: Keep-Alive\r\n\r\n"
    },
    {
        (int8_t *)"WDR2",
        80,
        (int8_t *)"gffstream.ic.llnwd.net",
        (int8_t *)"GET http://gffstream.ic.llnwd.net/stream/gffstream_w17a HTTP/1.1\r\n"
        "Host: gffstream.ic.llnwd.net\r\n"
        "Accept: */*\r\n"
        __PLAYER__
        "Icy-MetaData:1\r\n"
        "Proxy-Connection: Keep-Alive\r\n\r\n"
    },
    {
        (int8_t *)"radio Swiss Pop",
        80,
        (int8_t *)"zlz-stream12.streamserver.ch",
        (int8_t *)"GET http://zlz-stream12.streamserver.ch/2/rsp/mp3_128 HTTP/1.1\r\n"
        "Host: zlz-stream12.streamserver.ch\r\n"
        "Accept: */*\r\n"
        __PLAYER__
        "Icy-MetaData:1\r\n"
        "Proxy-Connection: Keep-Alive\r\n\r\n"
    },
    {
        (int8_t *)"radio Swiss Jazz",
        80,
        (int8_t *)"zlz-stream12.streamserver.ch",
        (int8_t *)"GET http://zlz-stream12.streamserver.ch/2/rsj/mp3_128 HTTP/1.1\r\n"
        "Host: zlz-stream12.streamserver.ch\r\n"
        "Accept: */*\r\n"
        __PLAYER__
        "Icy-MetaData:1\r\n"
        "Proxy-Connection: Keep-Alive\r\n\r\n"
    },
    {
        (int8_t *)"radio Swiss Classic",
        80,
        (int8_t *)"zlz-stream12.streamserver.ch",
        (int8_t *)"GET http://zlz-stream12.streamserver.ch/2/rsc/mp3_128 HTTP/1.1\r\n"
        "Host: zlz-stream12.streamserver.ch\r\n"
        "Accept: */*\r\n"
        __PLAYER__
        "Icy-MetaData:1\r\n"
        "Proxy-Connection: Keep-Alive\r\n\r\n"
    },
    {
        (int8_t *)"Radio 21",
        80,
        (int8_t *)"ice.streaming.spacenet.de",
        (int8_t *)"GET http://ice.streaming.spacenet.de/radio21 HTTP/1.1\r\n"
        "Host: ice.streaming.spacenet.de\r\n"
        "Accept: */*\r\n"
        __PLAYER__
        "Icy-MetaData:1\r\n"
        "Proxy-Connection: Keep-Alive\r\n\r\n"
    }
};


/*******************************************************************************
 station connection state machine states
*******************************************************************************/
static enum
{
    s_IDLE = 0,
    s_CONNECTING,
    s_REQUESTING,
    s_ESTABLISHED
} IRADIO_STATE = s_IDLE;


/*******************************************************************************
*                                                                              *
*    FUNCTIONS                                                                 *
*                                                                              *
*******************************************************************************/

/*******************************************************************************

    Function uint32_t close_station (station_type *current_station)

    close current connection, free all associated data

    Returns  0 - success
            >0 - error occurred

*******************************************************************************/
uint32_t close_station (station_type *current_station)
{
    /**************************************************************************
     locals
    **************************************************************************/
    uint32_t ret = 0;

    if (tcp_socket)
    {
        if ( tcp_get_state (tcp_socket) == TCP_ESTABLISHED )
        {
            /*******************************************************************
             shutdown connection, if established
            *******************************************************************/
            CPrintf (" Disconnecting... ");
            shutdown (tcp_socket, 10000);
            CPrintf ("success\r\n");
        }

        /***********************************************************************
         close socket
        ***********************************************************************/
        CPrintf (" Closing... ");
        socket_close (tcp_socket);
        tcp_socket = INVALID_SOCKET;
        CPrintf ("success\r\n");
    }

    /**************************************************************************
     reset state machine
    **************************************************************************/
    IRADIO_STATE = s_IDLE;

    /**************************************************************************
     free data
    **************************************************************************/
    if (current_station->real_name)
    {
        free (current_station->real_name);
        current_station->real_name = NULL;
    }

    return (ret);
}

/*******************************************************************************

    Function uint32_t open_station (station_type *new_station)

    open a new radio station

    Returns  0 - success
            >0 - error occurred

*******************************************************************************/
uint32_t open_station (station_type *new_station)
{
    /**************************************************************************
     locals
    **************************************************************************/
    static u_int16_t local_port = 5000;
    uint32_t ret = 0;

    /**************************************************************************
     get a new port
    **************************************************************************/
    if (++local_port > 6000) local_port = 5000;

    CPrintf (" Connecting to %s... ", new_station->name);

    /**************************************************************************
     if socket is already in use, shutdown socket and close station
    **************************************************************************/
    if (tcp_socket != INVALID_SOCKET)
    {
        close_station (new_station);
    }

    /**************************************************************************
     open new socket
    **************************************************************************/
    tcp_socket = socket_open ((char *)new_station->address,
                              new_station->port,
                              local_port,
                              DATATYPE_CHAR,
                              TCP_INIT_FUNC);
    if ( tcp_socket == NULL )
    {
        EXIT(SOCKETOPEN_ERROR);
    } // if

    /***************************************************************************
      activate the following line to let the gateway act as proxy server
    ***************************************************************************/
    set_socket_option (tcp_socket, SO_USE_PROXY);

    /***************************************************************************
      define callback function for received TCP packets
    ***************************************************************************/
    socket_define_callback (tcp_socket, tcp_callback, data, MAX_DATA);

    /**************************************************************************
     associate the current station information with socket for later use
    **************************************************************************/
    tcp_socket->user_pointer = (void *)new_station;

    /**************************************************************************
     connect to server
    **************************************************************************/
    IRADIO_STATE = s_CONNECTING;

    if ( connect (tcp_socket, data, 20, 600000) != TRUE )
    {
        CPrintf ("could not connect to server\r\n");
        close_station (new_station);
        ret = 1;
    }
    else
    {
        CPrintf ("connected\r\n Requesting station details...");
        IRADIO_STATE = s_REQUESTING;
        net_send (tcp_socket, new_station->request,strlen((const char *)new_station->request));
    }


    return (ret);
}

/*******************************************************************************

    Function int32_t parse_header (int8_t *header, station_type *current_station)

    parse HTTP header

    Returns  0 - success
            >0 - error occurred

*******************************************************************************/
int32_t parse_header (int8_t *header, station_type *current_station)
{
    /**************************************************************************
     locals
    **************************************************************************/
    int32_t ret = 0;
    int8_t  *cbp;  // control buffer pointer
    int8_t  *line; // buffer to hold one line
    int8_t  *lbp;  // line buffer pointer
    int32_t  length = 0;

    cbp = header;

    /**************************************************************************
     allocate a temporary memory for one line
    **************************************************************************/
    lbp = line = (int8_t *) net_allocate_aligned_buffer (MAX_DATA * sizeof(int8_t));

    if ( line == NULL )
    {
        /***********************************************************************
         out of memory
        ***********************************************************************/
        return (ret);
    }

    /***************************************************************************
     parse head
    ***************************************************************************/
    for ( ;; )
    {
        /***********************************************************************
         get a new line from header
        ***********************************************************************/
        length = http_get_line (line , cbp);

        if ( length == 0 )
        {
            if (!strncmp ((const char *)cbp, "\r\n", 2))
            {
                cbp += 2;    // header end
                break;
            }
            break;
        }
        if ( *(cbp + length) == 0)
        {
            // no header
            break;
        }

        cbp += length;
        cbp += 2; // \r\n      // line end

        /***********************************************************************
         Translate command string to lower case
        ***********************************************************************/
        for ( lbp = line; (*lbp != '\0') && (*lbp != ' '); lbp++ )
        {
            *lbp = tolower (*lbp);
        }

        if (!strncmp ((const char *)line, "icy-br:", 7))
        {
            /*******************************************************************
             bitrate
            *******************************************************************/
            CPrintf (" Bitrate: %skbit\r\n", line+7);
        }
        if (!strncmp ((const char *)line, "icy-name:", 9))
        {
            /*******************************************************************
             station name
            *******************************************************************/
            current_station->real_name = string_dup (line+9);
            CPrintf (" Station: %s\r\n", current_station->real_name);

        }
        if (!strncmp ((const char*)line, "icy-metaint:", 12))
        {
            /*******************************************************************
             interval
            *******************************************************************/
        }
    }

    free (line);

    return (ret);
}

/*******************************************************************************

    Function tcp_callback()

    This function is called when new data is received

    Parameter   so   - socket
                data - pointer to received data
                len  - received data length
                ec   - error code
    Returns     >= 0 - if message processed
                < 0  - if socket was closed

*******************************************************************************/
int32_t tcp_callback (SOCKET *so, void *data, uint32_t len, uint32_t ec)
{
    /**************************************************************************
     locals
    **************************************************************************/
    static int more_data = 0;
    int32_t ret = 1;
    station_type *current_station = (station_type *)so->user_pointer;
    int32_t i;
    char *buffer = (char*)data;

    /**************************************************************************
     terminate buffer
    **************************************************************************/
    buffer[len+1] = 0;

    switch (ec)
    {
        case 0:
            /*******************************************************************
             new data
            *******************************************************************/
            switch (IRADIO_STATE)
            {
                default:
                    /***********************************************************
                     wrong state; nothing to do here
                    ***********************************************************/
                    break;

                case s_REQUESTING:
                    /***********************************************************
                     check for ICY 200 message
                    ***********************************************************/
                    if ( (!strncmp (data, "ICY 200", 7)) ||
                         (!strncmp (data, "HTTP/1.1 200", 12)) )
                    {
                        /*******************************************************
                         success, connection established
                        *******************************************************/
                        IRADIO_STATE = s_ESTABLISHED;
                        CPrintf ("success\r\n");

                        /*******************************************************
                         parse header
                        *******************************************************/
                        parse_header ((int8_t *)data, current_station);

                    }
                    else
                    {
                        /*******************************************************
                         error; shutdown and close connection
                        *******************************************************/
                        close_station (current_station);
                        ret = -1;   /* socket was closed, return -1           */
                    }
                    break;

                case s_ESTABLISHED:
                    /***********************************************************
                     parse buffer for additional information
                    ***********************************************************/
                    if (more_data)
                    {
                        /*******************************************************
                         if more_data is set, the StreamTitle data is splitted
                        *******************************************************/
                        more_data = 0;

                        /*******************************************************
                         run over the entire buffer until end-marker is reached
                        *******************************************************/
                        i = 0;
                        while (i<len)
                        {
                            if (buffer[i] == 0) break;
                            if ( (buffer[i] == 0x27) && (buffer[i+1] == 0x3b) ) break;
                            if (buffer[i] == 0x27)
                            {
                                i++;      // skip 0x27
                            }
                            if (buffer[i] == 0x3d)
                            {
                                i++;      // skip 0x3d
                            }

                            /***************************************************
                             copy to global buffer
                            ***************************************************/
                            *pinfo++ = buffer[i++];
                        }

                        /*******************************************************
                         if we fall here and the end-marker or a terminating
                         zero was not found, set more data flag
                        *******************************************************/
                        if (i>=len)
                        {
                            more_data = 1;
                        }
                        else
                        {
                            /***************************************************
                             a new stream title was received, terminate string
                            ***************************************************/
                            new_info = 1;
                            *pinfo = 0;
                        }
                    }
                    else
                    {
                        /*******************************************************
                         run over the entire buffer until end-marker is reached
                        *******************************************************/
                        for ( i=0;i<len ;i++  )
                        {
                            /***************************************************
                             test for key word StreamTitle
                            ***************************************************/
                           if (buffer[i] == 'S')
                           {
                               if ( (!strncmp (&buffer[i], "StreamTitle=", 12)) )
                               {
                                   i+=13;  // skip key word

                                   while (i<len)
                                   {
                                       /****************************************
                                        read stream title until end-marker or
                                        zero
                                       ****************************************/
                                       if (buffer[i] == 0) break;
                                       if ( (buffer[i] == 0x27) && (buffer[i+1] == 0x3b) ) break;

                                       if (buffer[i] == 0x27)
                                       {
                                           i++;  // skip 0x27
                                       }
                                       if (buffer[i] == 0x3d)
                                       {
                                           i++;  // skip 0x3d
                                       }
                                       *pinfo++ = buffer[i++];
                                   }
                                   /********************************************
                                    if we fall here and the end-marker or a terminating
                                    zero was not found, set more data flag
                                   ********************************************/
                                   if (i>=len)
                                   {
                                       more_data = 1;
                                   }
                                   else
                                   {
                                       new_info = 1;
                                       *pinfo = 0;
                                   }

                                   break;
                               }
                           }
                        }
                    }

                    /***********************************************************
                     copy received data to decode buffer... to do
                    ***********************************************************/
                    break;
            }
            break;

        default:
            /*******************************************************************
             else print error
            *******************************************************************/
            net_print_error (ec, CPrintf);
            if (ec == SO_WRONG_CHECKSUM) so -> error_code = 0;
            break;
    }

    /***************************************************************************
     return true, if message processed
    ***************************************************************************/
    return (ret);
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
    if ( !net_init (dsp_ip_addr, dhcp_setting, dns_server_ip, DNS_ENABLE))
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

    net_set_gateway (dns_server_ip,
                     "255.255.255.0");

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
    station_type *current_station = &stations[0];
    int nr = 0;
    uint32_t ip;
    char buffer[20];                /* small buffer for ip-address conversion */

    /***************************************************************************
      initialize application
    ***************************************************************************/
    AppInit (dsp_clock);

    /**************************************************************************
     malloc space for incoming data
    **************************************************************************/
    data = (char *) malloc ((MAX_DATA+1) * sizeof(char));

    if ( data == NULL )
    {
        EXIT(UNKNOWN_ERROR);
    }


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
      reset station info
    ***************************************************************************/
    *info = 0;
    pinfo = info;

    /***************************************************************************
      main program loop: process network
    ***************************************************************************/
    for ( ;; )
    {
        net_isq();

        if ( EZDSP5502_I2CGPIO_readLine(SW0) == 0) action = 3;

        if ( EZDSP5502_I2CGPIO_readLine(SW1) == 0) action = 2;

        /***********************************************************************
         global variable action is controlled by file iradiocontrol.gel
        ***********************************************************************/
        switch (action)
        {
            case 1:
                /***************************************************************
                 connect to radio station
                ***************************************************************/
                action = 0;
                if (open_station (current_station))
                {
                    CPrintf ("error opening radio station\r\n");
                }

                break;

            case 2:
                /***************************************************************
                 disconnect
                ***************************************************************/
                action = 0;
                close_station (current_station);
                break;

            case 3:
                /***************************************************************
                 change radio station
                ***************************************************************/
                action = 0;
                close_station (current_station);
                if (++nr >= MAX_STATION)
                {
                    nr = 0;
                }

                current_station = &stations[nr];
                if (open_station (current_station))
                {
                    CPrintf ("error opening radio station\r\n");
                }

                break;

            case 4:
                /***************************************************************
                 change radio station
                ***************************************************************/
                action = 0;
                close_station (current_station);
                if (--nr < 0)
                {
                    nr = MAX_STATION - 1;
                }

                current_station = &stations[nr];
                if (open_station (current_station))
                {
                    CPrintf ("error opening radio station\r\n");
                }

                break;

            default:
                break;
        }

        /***********************************************************************
         display new stream title
        ***********************************************************************/
        if (new_info)
        {
            new_info = 0;
            pinfo = info;
            CPrintf("%s\r\n", info);
        }
    }
}

