//////////////////////////////////////////////////////////////////////////////
// * File name: spiflash.c
// *                                                                          
// * Description:  SPI Flash interface.
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

#include "spiflash.h"
#include "ezdsp5502.h"
#include "ezdsp5502_gpio.h"

static Uint8 spiflashbuf[spiflash_PAGESIZE + 6];
static Uint8 statusbuf[8];

#define SPCR1 *(ioport volatile unsigned int *)0x2804
#define SPCR2 *(ioport volatile unsigned int *)0x2805
#define PCR   *(ioport volatile unsigned int *)0x2812

/*
 *  spiflash_init( )
 *
 *    Initialize McBSP for SPI Flash
 */
void spiflash_init( )
{
    /* Configure McBSP pins as GPIO */
    SPCR1 = 0x1800;  // McBSP receiver in reset
    SPCR2 = 0x0242;  // McBSP transmitter in reset
    PCR   = 0x3200;  // DX, DR and CLKX as GPIO.  CLKX and DX are outputs.  DR is an input.

    /* Use GPIO4 as SPI Flash chip select */
    EZDSP5502_GPIO_init(GPIO_GPIO_PIN4);
    EZDSP5502_GPIO_setDirection(GPIO_GPIO_PIN4, GPIO_GPIO_PIN4_OUTPUT);
}


/* 
 *  spiflash_cycle(buf, len)
 *
 *  Execute a SPI spiflash data transfer cycle.  Each byte in buf is shifted
 *  out and replaced with data coming back from the spiflash.
 */
void spiflash_cycle(Uint8 *buf, Uint16 len)
{
    Uint16 i, bitnum, datain, dataout;

    /* Set chip select high */
    EZDSP5502_GPIO_setOutput( GPIO_GPIO_PIN4, 1 );

    PCR = PCR & 0xfffd;  // CLKX low

    /* Drop chip select low */
    EZDSP5502_GPIO_setOutput( GPIO_GPIO_PIN4, 0 );

    /* Generate SPI flash access cycle */
    for (i = 0; i <= len; i++)
    {
        dataout = buf[i];
        datain = 0;
        for (bitnum = 0; bitnum < 8; bitnum++)
        {
            /* Output DX, shift dataout out high bit first */
            PCR = PCR & 0xfffd;      // CLKX low
            if ((dataout & 0x80) != 0)
                PCR = PCR | 0x0020;  // DX high
            else
                PCR = PCR & 0xffdf;  // DX low
            PCR = PCR | 0x0002;      // CLKX high

            /* Read DR, shift in sampled value */
            datain = datain << 1;
            if ((PCR & 0x0010) != 0)
                datain = datain | 1;
   
            dataout = dataout << 1;            
        }
        buf[i] = datain;
    }

    PCR = PCR & 0xfffd;                // CLKX low

    /* Return chip select high */
    EZDSP5502_GPIO_setOutput( GPIO_GPIO_PIN4, 1 );
}

/*
 *  spiflash_status( )
 */
Uint8 spiflash_status( )
{
    /* Issue read status command */
    statusbuf[0] = spiflash_CMD_RDSR;
    statusbuf[1] = 0;

    spiflash_cycle(statusbuf, 2);

    return statusbuf[1];
}

/*
 *  spiflash_read( src, dst, len )
 */
void spiflash_read( Uint32 src, Uint32 dst, Uint32 length )
{
    Int32 i;
    Uint8 *psrc, *pdst;

    // Setup command
    spiflashbuf[0] = spiflash_CMD_READ;
    spiflashbuf[1] = ( src >> 16);
    spiflashbuf[2] = ( src >> 8 );
    spiflashbuf[3] = ( src >> 0 );

    // Execute spiflash read cycle
    spiflash_cycle(spiflashbuf, length + 5);

    // Copy returned data
    pdst = ( Uint8 * )dst;
    psrc = spiflashbuf + 4;
    for ( i = 0 ; i < length ; i++ )
        *pdst++ = *psrc++;
}


/*
 *  spiflash_erase( base, len )
 */
void spiflash_erase( Uint32 base, Uint32 length )
{
    Int32 bytes_left, bytes_to_erase, eraseaddr;

    eraseaddr = base;
    bytes_left = length;

    while (bytes_left > 0 )
    {
        /* Limit erase unit to sector size */
        bytes_to_erase = bytes_left;
        if (bytes_to_erase > spiflash_SECTORSIZE)
            bytes_to_erase = spiflash_SECTORSIZE;

        /* Align to sector boundaries */
        if ((eraseaddr & spiflash_SECTORMASK) != ((eraseaddr + bytes_to_erase) & spiflash_SECTORMASK))
            bytes_to_erase -= (eraseaddr + bytes_to_erase) - ((eraseaddr + bytes_to_erase) & spiflash_SECTORMASK);

        /* Issue WPEN */
        spiflashbuf[0] = spiflash_CMD_WREN;
        spiflash_cycle(spiflashbuf, 0);

        /* Issue erase */
        spiflashbuf[0] = spiflash_CMD_ERASESEC;
        spiflashbuf[1] = ( Uint8 )( eraseaddr >> 16 );
        spiflashbuf[2] = ( Uint8 )( eraseaddr >> 8 );
        spiflashbuf[3] = ( Uint8 )( eraseaddr );
        spiflash_cycle(spiflashbuf, 3);
 
        /* Wait while busy */
        while( ( spiflash_status( ) & 0x01 ) );

        /* Get ready for next iteration */
        bytes_left -= bytes_to_erase;
        eraseaddr += bytes_to_erase;
    }
}

/*
 *  spiflash_write( src, dst, len )
 */
void spiflash_write( Uint32 src, Uint32 dst, Uint32 length )
{
    Uint32 i;
    Uint32 bytes_left;
    Uint32 bytes_to_program;
    Uint8 *psrc;

    /* Establish source */
    psrc = ( Uint8 * )src;
    bytes_left = length;

    while ( bytes_left > 0 )
    {
        bytes_to_program = bytes_left;

        /* Most to program is spiflash_CMD_BLOCKSIZE */
        if ( bytes_to_program > spiflash_PAGESIZE )
             bytes_to_program = spiflash_PAGESIZE;

        /* Make sure you don't run off the end of a page */
        if ( ( dst & spiflash_PAGEMASK ) != ( ( dst + bytes_to_program ) & spiflash_PAGEMASK ) )
            bytes_to_program -= ( dst + bytes_to_program ) - ( ( dst + bytes_to_program ) & spiflash_PAGEMASK );

        /* Issue WPEN */
        spiflashbuf[0] = spiflash_CMD_WREN;
        spiflash_cycle(spiflashbuf, 0);

        /* Create command block for program operation */
        spiflashbuf[0] = spiflash_CMD_WRITE;
        spiflashbuf[1] = ( Uint8 )( dst >> 16 );
        spiflashbuf[2] = ( Uint8 )( dst >> 8 );
        spiflashbuf[3] = ( Uint8 )( dst );

        for ( i = 0 ; i < bytes_to_program ; i++ )
            spiflashbuf[4+i] = *psrc++;

        /* Execute write command */
        spiflash_cycle(spiflashbuf, bytes_to_program + 3 );

        /* Wait while busy */
        while( ( spiflash_status( ) & 0x01 ) );

        /* Get ready for next iteration */
        bytes_left -= bytes_to_program;
        dst += bytes_to_program;
    }
}

