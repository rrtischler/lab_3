/*******************************************************************************
*                                                                              *
*  @brief    Sample Application Program for obtaining the time from internet   *
*                                                                              *
*  @author   D.SignT GmbH & Co. KG, Claus Hermbusche                           *
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
  Chip Support Library
*******************************************************************************/
#ifndef CHIP_5502
#define CHIP_5502
#endif
//~ #include <csl.h>                             /* chip support library          */
#include <csl_gpt.h>
#include <csl_irq.h>

/*******************************************************************************
  network support function
*******************************************************************************/
#include "..\..\..\netlib\dsknet.h"          /* network support               */

/*******************************************************************************
  common support function
*******************************************************************************/
#include "..\..\..\common\CPrintf.h"         /* CPrintf defines               */
#include "..\..\..\common\common.h"          /* init app, on exit function    */
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
void install_interrupt (int vecno, void(*handler)());
void GPT_start(GPT_Handle hGpt);

/*******************************************************************************
  missing prototypes from time.h
*******************************************************************************/
_CODE_ACCESS char      *asctime(const struct tm *_timeptr);
_CODE_ACCESS struct tm *localtime(const time_t *_timer);
_CODE_ACCESS time_t     mktime(struct tm *_tptr);

#ifdef __cplusplus
} // extern "C"
#endif

/*******************************************************************************
*                                                                              *
*    DEFINES                                                                   *
*                                                                              *
*******************************************************************************/
#define NTP_WAIT_TIME   6
#define NTP_UPDATE_TIME (NTP_WAIT_TIME+100)      // 100 seconds
//~ #define NTP_UPDATE_TIME (NTP_WAIT_TIME+10)      // 10 seconds

/*******************************************************************************
  MAX_PING_DATA is used to specify the maximum data to be pinged. For normal
  operation a value 64 to 100 should be sufficient.
*******************************************************************************/
#define MAX_PING_DATA             100

/*******************************************************************************
  NTP server
*******************************************************************************/
#define HOST_NAME        "europe.pool.ntp.org"
#define NTP_PORT         123

/*******************************************************************************
 NTP header as defined in RFC 2030
*******************************************************************************/
typedef struct ntp_header
{
    uint32_t prec_poll_stra_livn;
    //~ uint8_t livnmode;
    //~ uint8_t stratum;
    //~ uint8_t poll;
    //~ uint8_t precision;
    uint32_t root_delay;
    uint32_t root_dispersion;
    uint32_t reference_id;
    uint32_t reference_ts[2];
    uint32_t originate_ts[2];
    uint32_t receive_ts[2];
    uint32_t transmit_ts[2];
    uint32_t key_id;
    uint32_t message_digest[4];
} NTP_HEADER_TYPE;


/*******************************************************************************
*                                                                              *
*    GLOBALS                                                                   *
*                                                                              *
*******************************************************************************/

/*******************************************************************************
 program name
*******************************************************************************/
char *program_name = "SNTP";


unsigned int wait_for_answer = 100;


/*******************************************************************************
  globals used in interrupt processing
*******************************************************************************/
time_t seconds = 0;

/*******************************************************************************
  used to trigger main loop from interrupt
*******************************************************************************/
volatile int trigger = 0;


SOCKET *sntp_socket = INVALID_SOCKET;           /* SNTP socket                */
static uint32_t buffer[20];                     /* buffer for NTP packets     */

Uint16 gpt12Evt_Id;
GPT_Handle myhGpt;

/*******************************************************************************
 Config structure setup for GPTx in 64bit mode
*******************************************************************************/
GPT_Config myGptCfg =
{
   0,
   GPT_GPTGPINT_RMK(
      GPT_GPTGPINT_TIN1INV_DEFAULT,
      GPT_GPTGPINT_TIN1INT_DEFAULT
   ),
   GPT_GPTGPEN_RMK(
      GPT_GPTGPEN_TOUT1EN_DEFAULT,
      GPT_GPTGPEN_TIN1EN_DEFAULT
   ),
   GPT_GPTGPDIR_RMK(
      GPT_GPTGPDIR_TOUT1DIR_DEFAULT,
      GPT_GPTGPDIR_TIN1DIR_DEFAULT
   ),
   GPT_GPTGPDAT_RMK(
      GPT_GPTGPDAT_TOUT1DAT_DEFAULT,
      GPT_GPTGPDAT_TIN1DAT_DEFAULT
   ),
   0xA300,  0x11E1,   // == 300000000 => 1s
   0x0000,   //PRD3
   0x0000,   //PRD4
   GPT_GPTCTL1_RMK(
      GPT_GPTCTL1_TIEN_DEFAULT,
      GPT_GPTCTL1_CLKSRC_DEFAULT,
      GPT_GPTCTL1_ENAMODE_CONTINUOUS,
      GPT_GPTCTL1_PWID_DEFAULT,
      GPT_GPTCTL1_CP_DEFAULT,
      GPT_GPTCTL1_INVIN_DEFAULT,
      GPT_GPTCTL1_INVOUT_DEFAULT
   ),
   GPT_GPTCTL2_RMK(
      GPT_GPTCTL2_TIEN_DEFAULT,
      GPT_GPTCTL2_CLKSRC_DEFAULT,
      GPT_GPTCTL2_ENAMODE_CONTINUOUS,
      GPT_GPTCTL2_PWID_DEFAULT,
      GPT_GPTCTL2_CP_DEFAULT,
      GPT_GPTCTL2_INVIN_DEFAULT,
      GPT_GPTCTL2_INVOUT_DEFAULT
   ),
   GPT_GPTGCTL1_RMK(
      GPT_GPTGCTL1_TDDR34_DEFAULT,
      GPT_GPTGCTL1_PSC34_DEFAULT,
      GPT_GPTGCTL1_TIMMODE_64BIT_GPTIM,
      GPT_GPTGCTL1_TIM34RS_IN_RESET,
      GPT_GPTGCTL1_TIM12RS_IN_RESET
   )
};

/*******************************************************************************
*                                                                              *
*    FUNCTIONS                                                                 *
*                                                                              *
*******************************************************************************/


/*******************************************************************************

    @brief      timer interrupt function

    @param      void
    @return     nothing

    @note       uses global variable seconds

*******************************************************************************/
interrupt void Timer0Isr(void)
{
    seconds++;
    localtime (&seconds);
    trigger = 1;
    IRQ_clear(gpt12Evt_Id);
}

/*******************************************************************************

    @brief   callback function for socket events

    This function is called when new NTP data is received

    @param   so   - socket
    @param   data - pointer to received data
    @param   len  - received data length
    @param   ec   - error code
    @return
             -   >= 0  if message processed
             -    < 0  if socket was closed

*******************************************************************************/
int32_t sntp_call_back (SOCKET *so, void *data, uint32_t len, uint32_t ec)
{
    /***************************************************************************
      locals
    ***************************************************************************/
    int32_t ret = 1;
    uint32_t sec;
    NTP_HEADER_TYPE *ntp_header = (NTP_HEADER_TYPE*)data;
    UNREFERENCED_PARAMETER(so);
    UNREFERENCED_PARAMETER(len);

    switch (ec)
    {
        case 0:
            /*******************************************************************
             valid data received, get time stamp
            *******************************************************************/
            CPrintf (" NTP reply received\r\n");

            /*******************************************************************
             setting the time must be atomic
            *******************************************************************/
            *IER0 &= ~(1<<4);
            sec = ntp_header-> transmit_ts[0];
            seconds = ((sec & 0x000000ff) << 24)
                    | ((sec & 0x0000ff00) << 8)
                    | ((sec & 0x00ff0000) >> 8)
                    | ((sec & 0xff000000) >> 24);

            *IER0 |= 1<<4;

            /*******************************************************************
             force next request
            *******************************************************************/
            wait_for_answer = NTP_WAIT_TIME+1;

            /*******************************************************************
             close socket
            *******************************************************************/
            socket_close (sntp_socket);
            sntp_socket = INVALID_SOCKET;
            ret = -1;               /* socket was closed, return -1           */
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

    net_set_gateway ("192.168.168.1",
                     "255.255.255.0");

    CPrintf (".");

    /***************************************************************************
      ICMP socket allows to 'ping' the DSP
      ping data is limited to 100 byte
    ***************************************************************************/
    if ( install_icmp_socket (MAX_PING_DATA) == NULL )
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

    @brief    Process NTP client
    @param    hostname
    @return   nothing

*******************************************************************************/
#pragma CODE_SECTION(ntp_client , ".commonsect");
void ntp_client (char *hostname)
{
    /***************************************************************************
      locals
    ***************************************************************************/
    static uint16_t local_port = 5000;
    NTP_HEADER_TYPE *ntp_header;


    ++wait_for_answer;

    if (wait_for_answer < NTP_WAIT_TIME) return;

    if (wait_for_answer == NTP_WAIT_TIME)
    {
        /***********************************************************************
          request timed out
        ***********************************************************************/
        CPrintf (" NTP request timed out\r\n");
        socket_close (sntp_socket);
        sntp_socket = INVALID_SOCKET;
    }

    if (wait_for_answer >= NTP_UPDATE_TIME)
    {
        /***********************************************************************
          start new request
        ***********************************************************************/

        if (++local_port > 6000)
        {
            local_port = 5000;
        }

        sntp_socket = socket_open (hostname,
                                   NTP_PORT,      /* destination port         */
                                   local_port,    /* source port              */
                                   DATATYPE_INT, /* data type char           */
                                   UDP_INIT_FUNC);/* udp protocol             */
        if ( sntp_socket == NULL )
        {
            EXIT(SOCKETOPEN_ERROR);             /* possibly insufficient heap */
        } // if

        /***********************************************************************
          activate the following line to let the gateway act as proxy server
        ***********************************************************************/
        set_socket_option (sntp_socket, SO_USE_PROXY);

        /***********************************************************************
          define callback function for received UDP packets
        ***********************************************************************/
        socket_define_callback (sntp_socket, sntp_call_back, buffer, sizeof(buffer));

        /***********************************************************************
          build header
        ***********************************************************************/
        ntp_header = (NTP_HEADER_TYPE*)buffer;
        memset(ntp_header, 0, sizeof(NTP_HEADER_TYPE));
        //~ ntp_header-> livnmode = 0xE3;
        ntp_header-> prec_poll_stra_livn = 0xE3;

        /***********************************************************************
          send request
        ***********************************************************************/
        net_send (sntp_socket, buffer, 17);

        /***********************************************************************
          reset timer to detect timeouts
        ***********************************************************************/
        wait_for_answer = 0;
    }
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
    struct tm *local_time;          /* structure to hold time and date        */
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
     initialize local time (use BUILD_ macros from common.h)
    ***************************************************************************/
    local_time = localtime (NULL);
    local_time->tm_year = BUILD_YEAR-1900;
    local_time->tm_mon = BUILD_MONTH-1;
    local_time->tm_mday = BUILD_DAY;
    local_time->tm_hour = BUILD_HOUR;
    local_time->tm_min = BUILD_MINUTE;
    local_time->tm_sec = BUILD_SECOND;
    seconds = mktime (local_time);
    local_time = localtime (&seconds);

    CPrintf (" Current UTC time: %s\r", asctime (local_time));

    /***************************************************************************
     Open GPT0 and verify if it is valid
    ***************************************************************************/
    myhGpt = GPT_open(GPT_DEV0, GPT_OPEN_RESET);
    if (myhGpt == (GPT_Handle)INV)
    {
        EXIT (TIMER_HANDLE_ERROR);
    }

    /***************************************************************************
     Get GPTx EventId
    ***************************************************************************/
    gpt12Evt_Id = GPT_getEventId(myhGpt);

    /***************************************************************************
     install timer interrupt
    ***************************************************************************/
    IRQ_clear(gpt12Evt_Id);
    install_interrupt (gpt12Evt_Id, Timer0Isr);
    IRQ_enable(gpt12Evt_Id);

    /***************************************************************************
     Setup timer
    ***************************************************************************/
    GPT_RSETH(myhGpt,GPTCNT1, 0x0000);
    GPT_RSETH(myhGpt,GPTCNT2, 0x0000);
    GPT_RSETH(myhGpt,GPTCNT3, 0x0000);
    GPT_RSETH(myhGpt,GPTCNT4, 0x0000);
    GPT_config(myhGpt, &myGptCfg);
    GPT_start(myhGpt);

    /***************************************************************************
     Enable interrupts globally
    ***************************************************************************/
    _enable_interrupts();

    LED_on (0);

    /***************************************************************************
     main loop
    ***************************************************************************/
    for ( ; ; )
    {
        net_isq ();

        if (trigger)
        {
            trigger = 0;
            LED_toggle(0);
            LED_toggle(1);

            /*******************************************************************
             print time
            *******************************************************************/
            CPrintf (" Current UTC time: %s", asctime (local_time));

            /*******************************************************************
             a NTP request only makes sense when a link is established
            *******************************************************************/
            if (_link)
            {
                ntp_client (HOST_NAME);
            }
        }
    }
}


