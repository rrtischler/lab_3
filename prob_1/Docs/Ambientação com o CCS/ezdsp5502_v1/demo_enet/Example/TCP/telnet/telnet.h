/*******************************************************************************
 @file      telnet.h
 @verbatim
                         ___ \    ___| _)              __ __| 
                         |    | \    \  |   _     __ \   |    
                         |    |  ---    | (   |  |   |   |    
                        _____/_)_____/ _| \__,|  |  _|  _|    
                                          |___/               
                        Digital Signalprocessing Technology   
 @endverbatim 
 @brief     Process Telnet protocol

 @author    D.SignT GmbH & Co. KG, Claus Hermbusche
 @version   2.41
 @date      2009-10-21

*******************************************************************************/
#ifndef _TELNET_H_DEF
#define _TELNET_H_DEF


/*******************************************************************************
*                                                                              *
*    DEFINES                                                                   *
*                                                                              *
*******************************************************************************/
/*******************************************************************************
 defines for telnet protocol
*******************************************************************************/
#define TELNET_IAC   255
#define TELNET_WILL  251
#define TELNET_WONT  252
#define TELNET_DO    253
#define TELNET_DONT  254


#define MAX_BUFFER  1460                          /* max TCP packet size      */
typedef struct
{
    SOCKET      *server;                    /* telnet connection */
    char        *buffer;                    /* buffer pointer for incoming data */

    unsigned int so_state;                  /* current socket connection status */
/*******************************************************************************
 defines for socket connection state
*******************************************************************************/
#define SOCKET_DISCONNECTED   0
#define SOCKET_CONNECTED      1

    unsigned int state;                     /* current telnet state */
/*******************************************************************************
 defines for telnet server state
*******************************************************************************/
#define TSTATE_NORMAL 0
#define TSTATE_IAC    1
#define TSTATE_WILL   2
#define TSTATE_WONT   3
#define TSTATE_DO     4
#define TSTATE_DONT   5
#define TSTATE_CLOSE  6


} telnet_server_type;

/*******************************************************************************
 defines for socket state
*******************************************************************************/
#define TCP_STATE_CLOSED      0
#define TCP_STATE_LISTEN      1
#define TCP_STATE_SYNSENT     2
#define TCP_STATE_SYNREC      3
#define TCP_STATE_ESTABLISHED 4


/*******************************************************************************
*                                                                              *
*    GLOBALS                                                                   *
*                                                                              *
*******************************************************************************/
/* - */


/*******************************************************************************
*                                                                              *
*    PROTOTYPES                                                                *
*                                                                              *
*******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif /* !__cplusplus */

#ifdef __cplusplus
} // extern "C"
#endif

#endif
