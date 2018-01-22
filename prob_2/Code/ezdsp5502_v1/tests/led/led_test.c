//////////////////////////////////////////////////////////////////////////////
// * File name: led_test.c
// *                                                                          
// * Description:  LED Test.
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

/*
 *
 *  led_test( )
 *    Displays patterns with LEDs
 *
 */
Int16 led_test( )
{
    Uint16 i, j;

    /* Initialize LEDs */
    /* Setup I2C GPIO directions by line*/
    EZDSP5502_I2CGPIO_configLine(  LED0, OUT );
    EZDSP5502_I2CGPIO_configLine(  LED1, OUT );
    EZDSP5502_I2CGPIO_configLine(  LED2, OUT );
    EZDSP5502_I2CGPIO_configLine(  LED3, OUT );

    /* Turn off all LEDs by line*/
    EZDSP5502_I2CGPIO_writeLine(   LED0, HIGH );
    EZDSP5502_I2CGPIO_writeLine(   LED1, HIGH );
    EZDSP5502_I2CGPIO_writeLine(   LED2, HIGH );
    EZDSP5502_I2CGPIO_writeLine(   LED3, HIGH );
    
    /* Test with first pattern */
    for ( i = 0 ; i < 3 ; i++ )
    {
        for ( j = 7 ; j > 3 ; j-- )
        {   // Line values are defined in ezdsp5502_i2cgpio.h
            EZDSP5502_I2CGPIO_writeLine(   j, LOW ); 
            EZDSP5502_waitusec( 150000 );
            EZDSP5502_I2CGPIO_writeLine(   j, HIGH );
            EZDSP5502_waitusec( 150000 );
        }
    }

    /* Turn on all LEDs */
    EZDSP5502_I2CGPIO_writeLine(   LED0, LOW );
    EZDSP5502_I2CGPIO_writeLine(   LED1, LOW );
    EZDSP5502_I2CGPIO_writeLine(   LED2, LOW );
    EZDSP5502_I2CGPIO_writeLine(   LED3, LOW );
    EZDSP5502_waitusec( 250000 );
    
    /* Test with second pattern */
    for ( i = 0 ; i < 6 ; i++ )
    {
        for ( j = 7 ; j > 3 ; j-- )
        {
            EZDSP5502_I2CGPIO_writeLine( j, (~EZDSP5502_I2CGPIO_readLine(j) & 0x01) );
            EZDSP5502_waitusec( 200000 );
        }
    }

    /* Turn off LED by register to end test */
    EZDSP5502_I2CGPIO_read(  0x00, &j );       // Read I2C GPIO input register
    EZDSP5502_I2CGPIO_write( 0x02, j | 0xF0 ); // Write value to output register with LEDs off

    return 0;
}

