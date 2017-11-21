//////////////////////////////////////////////////////////////////////////////
// * File name: setmac.c
// *                                                                          
// * Description:  Set MAC address.
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

#include "stdio.h"
#include "ezdsp5502.h"
#include "enet.h"

void enet_eeprom_sendcmd(Uint16 cmdword)
{
    Uint16 bitnum, data;
    
    for (bitnum = 0; bitnum < 9; bitnum++)
    {
        if ((cmdword & 0x100) != 0)
            data = 0x04;
        else
            data = 0x00;
        cmdword = cmdword << 1;
                    
        enet_regwrite(0x22, 0x31 | data);       // Clock low, CS high
        EZDSP5502_waitusec(2);
        enet_regwrite(0x22, 0x33 | data);       // Clock high, CS high
        EZDSP5502_waitusec(2);        
    }
}

void enet_eeprom_busywait()
{
    enet_regwrite(0x22, enet_regread(0x22) & 0x1f);           // Read mode
    
    EZDSP5502_waitusec(1);                                    // Wait at least 250ns
    
    while((enet_regread(0x22) & 0x08) == 0);                  // Wait for busy high
    
    enet_regwrite(0x22, enet_regread(0x22) | 0x30);           // Back to write mode
    EZDSP5502_waitusec(10000);   
}

void enet_setmac(Uint16 *buf)
{
    Uint16 i, bitnum, databyte, data;

    enet_regwrite(0x22, 0x30);  // Set EEPCR initial state (CS, CLK low)

    /* EEPROM write enable */
    enet_regwrite(0x22, 0x31);                       // EEPROM CS high   
    enet_eeprom_sendcmd(0x130);                      // EEPROM write enable command
    enet_regwrite(0x22, 0x30);                       // EEPROM CS, CLK low
    EZDSP5502_waitusec(10);

    for (i = 0; i < 3; i++)
    {
        /* Erase byte */
        enet_regwrite(0x22, enet_regread(0x22) & 0xfd);  // Clock low
        enet_regwrite(0x22, enet_regread(0x22) | 1);     // EEPROM CS high
        enet_eeprom_sendcmd(0x1c0 | i + 1);              // EEPROM erase byte command
//        enet_eeprom_busywait();                        // Wait for completion
        enet_regwrite(0x22, enet_regread(0x22) & 0xfd);  // Clock low
        enet_regwrite(0x22, enet_regread(0x22) & 0xfe);  // EEPROM CS low   
        EZDSP5502_waitusec(10);
//        enet_regwrite(0x22, enet_regread(0x22) | 1);     // EEPROM CS high
        EZDSP5502_waitusec(20000); 
//        enet_regwrite(0x22, enet_regread(0x22) & 0xfe);  // EEPROM CS low

        /* Write byte */
        enet_regwrite(0x22, 0x31);                       // EEPROM CS high
        enet_eeprom_sendcmd(0x140 | (i + 1));            // EEPROM write byte command
    
    	databyte = buf[i];
//    	printf("   --> Writing %02x\n", databyte);
        for (bitnum = 0; bitnum < 16; bitnum++)    
        {
        	if ((databyte & 0x8000) != 0)
                data = 0x04;
            else
                data = 0x00;
            databyte = databyte << 1;
            enet_regwrite(0x22, 0x31 | data);                            // Clock low
            EZDSP5502_waitusec(2);
            enet_regwrite(0x22, 0x33 | data);                            // Clock high
            EZDSP5502_waitusec(2);        

        }
//        enet_eeprom_busywait();                          // Wait for completion
//        EZDSP5502_waitusec(20000);
        enet_regwrite(0x22, 0x31);                         // EEPROM CS high, CLK low
        EZDSP5502_waitusec(10);
        enet_regwrite(0x22, 0x30);                         // EEPROM CS, CLK low
        EZDSP5502_waitusec(10);
    }
}


void enet_readmac(Uint16 *buf)
{
    Uint16 i, bitnum, datain;

    enet_regwrite(0x22, 0x30);  // Set EEPCR initial state (CS low)
    
    for (i = 0; i < 3; i++)
    {    
        /* Read byte */
        enet_regwrite(0x22, 0x30);                       // EEPROM CS, CKL low
        enet_regwrite(0x22, 0x31);                       // EEPROM CS high
        enet_eeprom_sendcmd(0x180 | (i + 1));            // EEPROM read byte command
    
        datain = 0;
        for (bitnum = 0; bitnum < 16; bitnum++)    
        {
            enet_regwrite(0x22, 0x31);                   // Clock low
            EZDSP5502_waitusec(10);
            enet_regwrite(0x22, 0x33);                   // Clock high
            EZDSP5502_waitusec(10);
            enet_regwrite(0x22, 13);                     // Read mode
            
            if ((enet_regread(0x22) & 0x08) != 0)
                datain = (datain << 1) | 1;
            else
                datain = datain << 1;

            EZDSP5502_waitusec(1);
        }
        buf[i] = datain;
        enet_regwrite(0x22, 0x30);  // EEPROM CS, CLK low
        EZDSP5502_waitusec(10);       
    }
}

/*
 *
 *  main( )
 *      Set MAC Address to EEPROM
 *
 */
void main( )
{
    Int16 i;
#if(0)
    Uint16 MAC[8]     = { 0, 0, 0, 0, 0, 0 };
#endif
    Uint16 verify[8]  = { 0, 0, 0, 0, 0, 0 };
    Uint16 input[6]  = { 0x00, 0x00, 0x00, 0x99, 0x0E, 0x00 };
    Uint16 buf[3];
    
	enet_regwrite(0x26, 0x0003);  // Global reset
	EZDSP5502_waitusec(1000);
	enet_regwrite(0x26, 0x0000);  // Deassert global reset
	EZDSP5502_waitusec(10000);

    printf("reg[0x10] = %04x\n", enet_regread(0x10));
    printf("reg[0x12] = %04x\n", enet_regread(0x12));
    printf("reg[0x14] = %04x\n", enet_regread(0x14));
    
    verify[0] = enet_regread(0x10) & 0xff;
    verify[1] = enet_regread(0x10) >> 8;
    verify[2] = enet_regread(0x12) & 0xff;  
    verify[3] = enet_regread(0x12) >> 8;
    verify[4] = enet_regread(0x14) & 0xff;  
    verify[5] = enet_regread(0x14) >> 8;

    printf( "\n\nCurrent MAC address: ( %02X-%02X-%02X-%02X-%02X-%02X )\n",
        verify[5], verify[4], verify[3], verify[2], verify[1], verify[0] );
        	
    /* Input MAC address */
  //fflush( stdin );
    printf( "\nEnter new MAC address:   ( 00-0E-99-xx-xx-xx ) ( Last 3 numbers only )\n");
    scanf( "%x-%x-%x", &input[2], &input[1], &input[0] );
    printf( "\n" );

    /* Check Input */
    for ( i = 0 ; i < 6 ; i++ )
    {
        if ( input[i] > 255 )
        {
            printf( " ***Failed. Bad input: %x-%x-%x*** \n", input[2], input[1], input[0] );
            return;
        }
    }

    /* Store input into MAC[] */
 //   for ( i = 0 ; i < 6 ; i++ )
 //       MAC[i] = ( Uint8 )input[i];

    buf[0] = (input[1] << 8) | input[0];
    buf[1] = (input[3] << 8) | input[2];
    buf[2] = (input[5] << 8) | input[4];
    
    /* ---------------------------------------------------------------- *
     *                                                                  *
     *  Set MAC address to the [first six bytes] of the [last page]     *
     *                                                                  *
     * ---------------------------------------------------------------- */
    printf( "Writing MAC address: ( 00-0E-99-%02X-%02X-%02X )\n", input[2], input[1], input[0] );

    enet_setmac(buf);

#if(0)
    verify[0] = enet_regread(0x10) >> 8;
    verify[1] = enet_regread(0x10) & 0xff;
    verify[2] = enet_regread(0x12) >> 8;
    verify[3] = enet_regread(0x12) & 0xff;    
    verify[4] = enet_regread(0x14) >> 8;
    verify[5] = enet_regread(0x14) & 0xff;
    
    buf[0] = 0;
    buf[1] = 0;
    buf[2] = 0;
    enet_readmac(buf);
    printf("readbuf = (0x%04x, 0x%04x, 0x%04x)\n", buf[0], buf[1], buf[2]);
    printf( "MAC address read: ( %02X-%02X-%02X-%02X-%02X-%02X )\n",
        verify[0], verify[1], verify[2], verify[3], verify[4], verify[5] );
        
    /* Verify the MAC address in EEPROM */
    for ( i = 0 ; i < 6 ; i++ )
        if ( verify[i] != MAC[i] )
        {
            printf( "\n ***Failed Setting MAC address*** \n" );
            return;
        }

    printf( "MAC address set: ( %02X-%02X-%02X-%02X-%02X-%02X ) - Good!\n",
        MAC[0], MAC[1], MAC[2], MAC[3], MAC[4], MAC[5] );
#endif

    printf( "\n*** Please power cycle board ***\n");
    printf( "\nPASS.\n" );

    return;
}
