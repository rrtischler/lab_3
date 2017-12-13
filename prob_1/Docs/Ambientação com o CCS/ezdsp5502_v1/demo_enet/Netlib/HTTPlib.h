/***************************************************************************//**
 @file httplib.h
 @verbatim
                         ___ \    ___| _)              __ __|
                         |    | \    \  |   _     __ \   |
                         |    |  ---    | (   |  |   |   |
                        _____/_)_____/ _| \__,|  |  _|  _|
                                          |___/
                        Digital Signalprocessing Technology
 @endverbatim
 @brief     HTTP support library

 @author    D.SignT GmbH & Co. KG, Claus Hermbusche
 @version   2.68
 @date      2011-09-19
 @target    DSK-91C111, EVM DM642, DSK6455, EVM6437, EVM6737, D.Module.8900,
            D.Module.91C111, D.Module2.DM642, D.Module2.C6747

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
#ifndef _HTTPLIB_H
#define _HTTPLIB_H

/*******************************************************************************
*                                                                              *
*    DEFINES                                                                   *
*                                                                              *
*******************************************************************************/
/***************************************************************************//**
  @addtogroup HTTP  HTTP Server
  @{
*******************************************************************************/
#ifndef NULLCHAR
#define NULLCHAR  '\0'                 /**< Zero termination                  */
#endif

#ifndef CR
#define CR        '\r'                 /**< Carriage return identifier        */
#endif

#ifndef LF
#define LF        '\n'                 /**< Line feed identifier              */
#endif

#ifndef SP
#define SP        ' '                  /**< Space                             */
#endif

#ifndef HTTP_PORT
#define HTTP_PORT 80                   /**< Well known port for HTTP server   */
#endif

#ifndef INVALID_SOCKET
#define INVALID_SOCKET NULL            /**< Invalid socket identifier         */
#endif

#ifndef TCP_MAX_LEN
#define TCP_MAX_LEN 1460               /**< Max TCP packet length             */
#endif

#define _HTTP_KEEP_ALIVE          0    /**< http_interpreter() return value: keep connection alive @hideinitializer */
#define _HTTP_CLOSE_CONNECTION    1    /**< http_interpreter() return value: close connection      @hideinitializer */

/***************************************************************************//**
  @name HTTP Command Table
  @{
*******************************************************************************/
#define _HTTP_GET      0L                               /**< HTTP method GET @hideinitializer */
#define _HTTP_HEAD     1L                               /**< HTTP method HEAD @hideinitializer */
#define _HTTP_POST     2L                               /**< HTTP method POST @hideinitializer */
#define _HTTP_UNKNOWN -1L                               /**< HTTP method unknown @hideinitializer */
/*@}*/

/***************************************************************************//**
 @brief Used for information about current connection.
 @details
 Each HTTP request is parsed by the http_server(). All necessary information about
 the current request are stored in a structure of type httpserv_type and passed
 to user callback function http_interpreter(). The requested URI index is stored
 in member uri, the requested uri string is stored in uri_buffer. All parameters
 may be determined with argv and argc.
*******************************************************************************/
typedef struct
{
    SOCKET     *control;            /**< Connected socket                     */
    char       *control_buffer;     /**< Buffer for incoming data             */
    int32_t     len;                /**< Received length                      */
    int32_t     user_state;         /**< User defined state machine           */
    int32_t     header_end;         /**< End of header                        */
    int32_t     uri;                /**< Requested uri index                  */
    char       *uri_buffer;         /**< Requested uri string                 */
    int32_t     method;             /**< Requested method @see _HTTP_GET, _HTTP_HEAD, _HTTP_POST                    */
    int32_t     content_length;     /**< Content_length of last request       */
    char       *content_buffer;     /**< Content buffer of last request       */
#if defined(_TMS320C6X)
#define HTTP_MAX_ARG 100
#else
#define HTTP_MAX_ARG 20
#endif
    char       *argv[HTTP_MAX_ARG]; /**< Form result parameter list           */
    int32_t     argc;               /**< Argument count                       */
    direntry_type  *finfo;          /**< File information                     */
    int32_t     remaining;          /**< Remaining bytes                      */
#define _HTTP_LISTENING   0
#define _HTTP_ESTABLISHED 1
} httpserv_type ;

/*@}*/


/*******************************************************************************

  FUNCTION PROTOTYPES

*******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif /* !__cplusplus */


/***************************************************************************//**

 @addtogroup HTTP  HTTP Server
 @{
*******************************************************************************/
/***************************************************************************//**

    @brief      Initialize HTTP server
    @param      *user            - used for authorize users for HTTP access
    @param      *d8900_init_mmc  - not available on DSK
    @param      max_connections - specifies the maximum concurrent connections
    @return
                - TRUE  =>  HTTP server was successfully installed
                - FALSE =>  out of memory

    @details    This function is the main HTTP server initialization function.
                It must be called once after net_init() to install the HTTP service.
                The user list must contain the keyword "webserver" as user name
                for a valid service name. Any other or additional user names are
                not allowed.
                d8900_init_mmc() is an old and obsolete MMC initialization function
                for the D.Module.CS8900.
                Any webpage access can lead to a number of parallel opened connections.
                All sockets and all temporary information for each connection
                is taken from heap. If you want to limit the heap consumption,
                use parameter max_connection.

*******************************************************************************/
int32_t http_server_init (user_type *user,
                          mmc_function_type *(*d8900_init_mmc) (void),
                          int32_t max_connections );

/***************************************************************************//**

    @brief      Define a user callback function for HTTP requests
    @param      (*callback_func)()     - pointer to user callback function
    @return     -
    @details This function installs a user callback function. It must be called
             at least once or any time the callback function has to be changed.

*******************************************************************************/
void http_define_callback (int32_t (*callback_func)(httpserv_type *));

/***************************************************************************//**

    @brief User defined callback function
    @param     http_server - current http server connection
    @return
               - _HTTP_CLOSE_CONNECTION   =>  close connection
               - _HTTP_KEEP_ALIVE         =>  keep alive

    @note  This callback function must be implemented by user. It is called each
           time a web page is requested or data is received. Definition in main():
    @code
    "http_define_callback ( http_interpreter);"
    @endcode
    Skeleton function:
    @code
    int32_t http_interpreter (httpserv_type *http_server)
    {
        // *********************************************************************
        // locals
        // *********************************************************************
        int32_t  ret = _HTTP_CLOSE_CONNECTION;

        // *********************************************************************
        // Execute specific method
        // *********************************************************************
        switch (http_server -> method)
        {
            case _HTTP_GET:
                if ( http_server -> uri == -1 )
                {
                    // *********************************************************
                    // uri not found: send user defined not-found-message
                    // *********************************************************

                    http_send_uri (http_server, &e404);
                }
                else
                {
                    // *********************************************************
                    // send the requested page
                    // *********************************************************
                    if ( http_send_user_page (http_server,
                                              user,
                                              http_server -> uri ) <= 0)
                    {
                        // *****************************************************
                        // uri not found: send user defined not-found-message
                        // *****************************************************
                        http_send_uri (http_server, &e404);
                    }
                }
                break;

            case _HTTP_UNKNOWN :                 // unknown method
                // *************************************************************
                // method not implemented or syntax error
                // *************************************************************
                http_send_uri (http_server, &e501);
                break;
        }

        // *********************************************************************
        // back to http server
        // *********************************************************************
        return (ret);
    }
    @endcode

*******************************************************************************/
int32_t http_interpreter (httpserv_type *http_server);

/***************************************************************************//**

    @brief      Initialize a secure web page
    @param      auth_name   - web page name
    @param      auth_key    - authentication username and password
    @param      err401      - user defined 'Authentication required' message
    @param      dir_list    - list of secure web pages
    @return     nothing
    @note       The dir list must be terminated with a double zero:
    @code
    http_set_authentication ("Secure Webpage", authentication_key, &e401,
                             &secure_page, 0, 0 );
    @endcode
    @details If one or more webpages should be authenticated before the content
             is transmitted, use http_set_authentication(). The authentication
             name and key are case sensitive. The first page must be the user
             defined authentification failed message err401.

*******************************************************************************/
void http_set_authentication (char *auth_name, char *auth_key
                             , direntry_type *err401, direntry_type *dir_list, ...);

/***************************************************************************//**

    @brief      Search user defined Uniform Resource Identifiers (URI) list for requested uri
    @param      http_server - current http connection referenced by user callback function
    @return
                - (-1) the requested URI was not found
                - (0..n) index of web page specified in urilist
    @note       The URI is index of the specified webpage in user list:

    @code
    user_type user[] =
    {
        {"webserver", "*" , &URI0, &URI1, &URI2, &URI3, .... , 0},
        //  index             0      1      2      3  ...
    };
    @endcode

*******************************************************************************/
int32_t http_get_uri (httpserv_type *http_server);

/***************************************************************************//**

    @brief      Send user defined webpage.
    @param      http_info - current http connection referenced by user callback function
    @param      puser     - is a pointer to current user directory
    @param      uri       - specifies the URI (referenced by index) to send
    @return
               - (-1) if out of memory
               - ( 0) the URI is invalid
               - ( 1) on success

    @note       uri is the index of the specified webpage in user list:

    @code
    user_type user[] =
    {
        {"webserver", "*" , &URI0, &URI1, &URI2, &URI3, .... , 0},
        //  index             0      1      2      3  ...
    };
    @endcode
    @details This function transmits a requested webpage or element referenced
             by index. The index is used to access the requested webpage from
             the user list.

*******************************************************************************/
int32_t http_send_user_page (httpserv_type *http_info,
                             user_type *puser,
                             int32_t uri);

/***************************************************************************//**

    @brief      Send URI using the specified URI without looking up in user list.
    @param      http_server - current http connection referenced by user callback function
    @param      *uri      - specifies the URI to send
    @return
               - (-1) if out of memory
               - ( 0) the URI is invalid
               - ( 1) on success

    @note       Useful for sending error messages. E.g.:

    @code
    direntry_type E404 = {"e404" , "e404.htm" , sizeof(e404_c) ,
                          FTP_RW | FTP_RAM, 'A',
                          (uint32_t)e404_c };
    .
    .
    http_send_uri (http_info, &E404);
    @endcode
    @details Use this function to send a webpage for a given direntry. It is also
             useful to send pages not included with the user list (e.g. error messages).

*******************************************************************************/
int32_t http_send_uri (httpserv_type *http_server, direntry_type *uri);

/***************************************************************************//**

    @brief      The main polling function for concurrent HTTP server.
    @param      -
    @return
                - (-1) server out of memory
                - ( 0) normal return
    @note       Must be called regulary with net_isq() in the main loop.

*******************************************************************************/
int32_t http_server (void);

/***************************************************************************//**

    @brief  Force all connections to close
    @param  -
    @return nothing

*******************************************************************************/
void http_close_all (void);

/***************************************************************************//**

    @brief  Define index page
    @param  page     - index page
    @return nothing

    @code
    user_type user[] =
    {
        {"webserver", "*" , &URI0, &URI1, &URI2, &URI3, .... , 0},
        //  index             0      1      2      3  ...
    };
    @endcode
    @details The default index page is the first specified uri with index 0. If
             another uri should be the default index page call http_set_index_page().

*******************************************************************************/
void http_set_index_page (uint32_t page);

/***************************************************************************//**

    @brief  Dynamically add a webpage during runtime
    @param  uri   - webpage or element to add
    @return
             - (0) success
             - (-1) error, no webserver available or max directory limit reached

    @code
    direntry_type E404 = {"e404" , "e404.htm" , sizeof(e404_c) ,
                          FTP_RW | FTP_RAM, 'A',
                          (uint32_t)e404_c };
    .
    .
    http_add_page (&E404);
    @endcode

*******************************************************************************/
int32_t http_add_page (direntry_type *uri);


/*@}*/

#ifdef __cplusplus
} // extern "C"
#endif

#endif  // #ifndef _HTTPLIB_H


