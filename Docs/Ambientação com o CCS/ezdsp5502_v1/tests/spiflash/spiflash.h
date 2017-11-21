//////////////////////////////////////////////////////////////////////////////
// * File name: spiflash.h
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
#include "ezdsp5502_i2cgpio.h"
#include "ezdsp5502_gpio.h"
#include "csl.h"
#include "csl_mcbsp.h"
#include "csl_gpio.h"
#include "csl_chip.h"

/* ------------------------------------------------------------------------ *
 *  SPI Flash Definitions                                                   *
 * ------------------------------------------------------------------------ */
#define spiflash_SIZE               0x400000
#define spiflash_BASE               0x00000000
#define spiflash_PAGESIZE           256
#define spiflash_PAGEMASK           0xffffff00
#define spiflash_SECTORSIZE         4096
#define spiflash_SECTORMASK         0xfffff000

/* ------------------------------------------------------------------------ *
 *  SPI Flash Commands                                                      *
 * ------------------------------------------------------------------------ */
#define spiflash_CMD_WREN           0x06
#define spiflash_CMD_WRDI           0x04
#define spiflash_CMD_RDSR           0x05
#define spiflash_CMD_WRSR           0x01
#define spiflash_CMD_READ           0x03
#define spiflash_CMD_WRITE          0x02
#define spiflash_CMD_ERASEBLK       0xD8
#define spiflash_CMD_ERASESEC       0x20
#define spiflash_CMD_ERASECHIP      0xC7
#define spiflash_CMD_MFGID          0x90

/* ------------------------------------------------------------------------ *
 *  SPI Controller                                                          *
 * ------------------------------------------------------------------------ */
#define SPI_BASE                0x01F0E000            // SPI1 
#define SPI_SPIGCR0             *( volatile Uint32* )( SPI_BASE + 0x0 )
#define SPI_SPIGCR1             *( volatile Uint32* )( SPI_BASE + 0x4 )
#define SPI_SPIINT              *( volatile Uint32* )( SPI_BASE + 0x8 )
#define SPI_SPILVL              *( volatile Uint32* )( SPI_BASE + 0xc )
#define SPI_SPIFLG              *( volatile Uint32* )( SPI_BASE + 0x10 )
#define SPI_SPIPC0              *( volatile Uint32* )( SPI_BASE + 0x14 )
#define SPI_SPIPC2              *( volatile Uint32* )( SPI_BASE + 0x1c )
#define SPI_SPIDAT1_TOP         *( volatile Uint16* )( SPI_BASE + 0x3c )
#define SPI_SPIDAT1             *( volatile Uint32* )( SPI_BASE + 0x3c )
#define SPI_SPIDAT1_PTR16       *( volatile Uint16* )( SPI_BASE + 0x3e )
#define SPI_SPIDAT1_PTR8        *( volatile Uint8* ) ( SPI_BASE + 0x3f )
#define SPI_SPIBUF              *( volatile Uint32* )( SPI_BASE + 0x40 )
#define SPI_SPIBUF_PTR16        *( volatile Uint16* )( SPI_BASE + 0x42 )
#define SPI_SPIBUF_PTR8         *( volatile Uint8* ) ( SPI_BASE + 0x43 )
#define SPI_SPIEMU              *( volatile Uint32* )( SPI_BASE + 0x44 )
#define SPI_SPIDELAY            *( volatile Uint32* )( SPI_BASE + 0x48 )
#define SPI_SPIDEF              *( volatile Uint32* )( SPI_BASE + 0x4c )
#define SPI_SPIFMT0             *( volatile Uint32* )( SPI_BASE + 0x50 )
#define SPI_SPIFMT1             *( volatile Uint32* )( SPI_BASE + 0x54 )
#define SPI_SPIFMT2             *( volatile Uint32* )( SPI_BASE + 0x58 )
#define SPI_SPIFMT3             *( volatile Uint32* )( SPI_BASE + 0x5c )
#define SPI_INTVEC0             *( volatile Uint32* )( SPI_BASE + 0x60 )
#define SPI_INTVEC1             *( volatile Uint32* )( SPI_BASE + 0x64 )

/* ------------------------------------------------------------------------ *
 *  Prototype                                                               *
 * ------------------------------------------------------------------------ */
void spiflash_init( );
void spiflash_read( Uint32 src, Uint32 dst, Uint32 length );
void spiflash_write( Uint32 src, Uint32 dst, Uint32 length );
void spiflash_erase( Uint32 base, Uint32 length );
