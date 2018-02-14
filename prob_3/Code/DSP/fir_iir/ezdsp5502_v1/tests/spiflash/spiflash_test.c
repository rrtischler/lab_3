//////////////////////////////////////////////////////////////////////////////
// * File name: spiflash_test.c
// *                                                                          
// * Description:  SPI Flash header file.
// *                                                                          
// * Copyright (C) 2011 Texas Instruments Incorporated - http://www.ti.com/ 
// * Copyright (C) 2011 Spectrum Digital, Incorporated
// *                                                                          
// *                                                                          
// *  Redistribution and use in source and binary forms, with or without      
// *  modification, are permitted provided that the following conditions      
// *  are met:                                                                
// *                                                                          
// *    Redistributions of source code must retain the above copyright        
// *    notice, this list of conditions and the following disclaimer.         
// *                                                                          
// *    Redistributions in binary form must reproduce the above copyright     
// *    notice, this list of conditions and the following disclaimer in the   
// *    documentation and/or other materials provided with the                
// *    distribution.                                                         
// *                                                                          
// *    Neither the name of Texas Instruments Incorporated nor the names of   
// *    its contributors may be used to endorse or promote products derived   
// *    from this software without specific prior written permission.         
// *                                                                          
// *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS     
// *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT       
// *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR   
// *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT    
// *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,   
// *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT        
// *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,   
// *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY   
// *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT     
// *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE   
// *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.    
// *                                                                          
//////////////////////////////////////////////////////////////////////////////

#include "ezdsp5502.h"
#include "spiflash.h"

static Uint8 tx[spiflash_PAGESIZE];
static Uint8 rx[spiflash_PAGESIZE];

/*
 *  spiflash_test( )
 *      SPI Flash test, write then verify the contents of the first 4 pages 
 */
Int16 spiflash_test( )
{
    Uint32 i, j;
    Uint8* p8;

    /* Initialize the SPI interface */
    spiflash_init( );

    /* Erase target area in spiflash */
    spiflash_erase( ( Uint32 )0x3ffc * spiflash_PAGESIZE, 4 * spiflash_PAGESIZE);

    /* Write to spiflash */
    for ( i = 0x3ffc ; i < 0x4000 ; i++ )
    {
        /* Create the test pattern */
        p8 = ( Uint8* )tx;
        for ( j = 0 ; j < spiflash_PAGESIZE ; j++ )
            *p8++ = ( Uint8 )( j + i + 14 );

        /* Write a page */
        spiflash_write( ( Uint32 )tx, i * spiflash_PAGESIZE, spiflash_PAGESIZE );
    }

    /* Clear receive buffer */
    for ( j = 0 ; j < spiflash_PAGESIZE ; j++ )
        rx[j] = 0;

    /* Read and verify spiflash */
    for ( i = 0x3ffc ; i < 0x4000 ; i++ )
    {
        /* Read a page */
        spiflash_read(i * spiflash_PAGESIZE, ( Uint32 )rx, spiflash_PAGESIZE );

        /* Check the pattern */
        p8 = ( Uint8* )rx;
        for ( j = 0 ; j < spiflash_PAGESIZE ; j++ )
            if ( ( *p8++ ) != ( Uint8 )( (i + j + 14) & 0xff ) )
                return 1;  // Fail
    }

    /* Erase target area in spiflash */
    spiflash_erase( ( Uint32 )0x3ffc * spiflash_PAGESIZE, 4 * spiflash_PAGESIZE);

    return 0;
}
