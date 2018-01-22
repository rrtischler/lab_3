/***************************************************************************//**
 @file pserver.h
 @verbatim
                         ___ \    ___| _)              __ __|
                         |    | \    \  |   _     __ \   |
                         |    |  ---    | (   |  |   |   |
                        _____/_)_____/ _| \__,|  |  _|  _|
                                          |___/
                        Digital Signalprocessing Technology
 @endverbatim
 @brief     Concurrent server support

 @author    D.SignT GmbH & Co. KG, Claus Hermbusche
 @version   2.68

 @cond Software License Agreement
 Copyright (C) 2011 D.SignT GmbH & Co. KG - http://www.dsignt.de

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions
 are met:

   Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

   Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the
   distribution.

   Neither the name of D.SignT GmbH & Co. KG nor the names of its
   contributors may be used to endorse or promote products derived
   from this software without specific prior written permission.

 Disclaimer
 THIS SOFTWARE IS PROVIDED BY D.SIGNT GMBH & CO. KG "AS IS" AND ANY
 EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL D.SIGNT GMBH & CO. KG BE
 LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 @endcond

*******************************************************************************/

/*******************************************************************************
*                                                                              *
*    DEFINES                                                                   *
*                                                                              *
*******************************************************************************/

/***************************************************************************//**
  @addtogroup PServer Concurrent Server
  @{
*******************************************************************************/
/***************************************************************************//**
 @brief Parallel Server structure definition
 @details This structure contains all necessary information about a parallel
          server connection. The pointers 'next' and 'prev' are used to build
          a dynamic list of all connections.
*******************************************************************************/
struct _p_server
{
    struct _p_server *next; /**< double linked list next entry                */
    struct _p_server *prev; /**< double linked list privious entry            */

    void   *info;           /**< protocol information (FTP,HTTP,user defined) */
    SOCKET *server;         /**< listening socket                             */
    int32_t state;          /**< state for this server connection             */
    int32_t close;          /**< flag for closing connection                  */
    int32_t timer;          /**< timer                                        */
    u_int32_t age;          /**< aging                                        */

    void   **finfo;         /**< file information                             */
};

/***************************************************************************//**
 @brief creates a typename for Parallel Server
*******************************************************************************/
typedef struct _p_server _PARALLEL_SERVER;  /**< typename for parallel servers       */

/*@}*/


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

/***************************************************************************//**

 @addtogroup PServer Concurrent Server
 @{
*******************************************************************************/

/***************************************************************************//**

    @brief      Add a new concurrent server to the double linked list
    @details    This function adds a new listening server socket to the parallel
                server list. It must be called at least once for initialization
                and to have one socket listening. Any time a new connection from
                a client is established (SO_CONNECTION_ESTABLISHED in
                socket_struct::error_code) this function must be called to add a
                new listening socket and to maintain the socket list.
    @param      proto - IP-port for specific protocol
    @param      **pserver_head - user defined head of server list
    @return
                - Pointer to a new parallel server structure
                - or NULL - out of memory

*******************************************************************************/
_PARALLEL_SERVER *add_pserver (uint16_t proto,
                               _PARALLEL_SERVER **pserver_head);

/***************************************************************************//**

    @brief      Search pserver list for current socket
    @details    This function returns a pointer to the server connection the
                socket 'so' belongs to. It is useful in callback functions to
                get more information about the current connection.
    @note       Useful in callback function
    @param      *so           - connected socket
    @param      **pserver_head - user defined list head
    @return     Pointer to the next list entry

*******************************************************************************/
_PARALLEL_SERVER *get_current_pserver (SOCKET *so,
                                       _PARALLEL_SERVER **pserver_head);

/***************************************************************************//**

    @brief      Return the next connected client connection for processing
    @details    For quasi parallel processing all connections must be serviced
                one at a time. The main server function uses this routine to
                walk through the list of all connected clients to handle the
                next connection that is waiting for processing.
    @param      *pserver      - user pointer to server
    @param      **pserver_head - user defined list head
    @return     next waiting connection

*******************************************************************************/
_PARALLEL_SERVER *get_next_pserver (_PARALLEL_SERVER *pserver,
                                    _PARALLEL_SERVER **pserver_head);

/***************************************************************************//**

    @brief      Erase a node from a concurrent server list
    @details    If a connection was closed (or reset), the corresponding node
                in the list must be deleted. Use this function to close the socket
                and to free all associated memory.
    @param      *pserver      - server to close
    @param      **pserver_head - user defined list head
    @return     always NULL

*******************************************************************************/
_PARALLEL_SERVER *close_pserver (_PARALLEL_SERVER *pserver,
                                 _PARALLEL_SERVER **pserver_head);

/*@}*/

#ifdef __cplusplus
} // extern "C"
#endif
