*****************************************************************************
* File name: vectors.asm
*                                                                          
* Description:  Assembly file to set up interrupt vector table.
*                                                                          
* Copyright (C) 2011 Texas Instruments Incorporated - http://www.ti.com/ 
* Copyright (C) 2011 Spectrum Digital, Incorporated
*                                                                          
*                                                                          
*  Redistribution and use in source and binary forms, with or without      
*  modification, are permitted provided that the following conditions      
*  are met:                                                                
*                                                                          
*    Redistributions of source code must retain the above copyright        
*    notice, this list of conditions and the following disclaimer.         
*                                                                          
*    Redistributions in binary form must reproduce the above copyright     
*    notice, this list of conditions and the following disclaimer in the   
*    documentation and/or other materials provided with the                
*    distribution.                                                         
*                                                                          
*    Neither the name of Texas Instruments Incorporated nor the names of   
*    its contributors may be used to endorse or promote products derived   
*    from this software without specific prior written permission.         
*                                                                          
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS     
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT       
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR   
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT    
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,   
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT        
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,   
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY   
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT     
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE   
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.    
*                                                                          
*****************************************************************************

        .sect "vectors"
 
*------------------------------------------------------------------------------
* Global symbols defined here and exported out of this file
*------------------------------------------------------------------------------
        .global _vecs
*------------------------------------------------------------------------------
* Global symbols referenced in this file but defined somewhere else. 
* Remember that your interrupt service routines need to be referenced here.
*------------------------------------------------------------------------------
        .ref _c_int00
        
_vecs:  .ivec   _c_int00,use_reta

NMI:    .ivec  1
    
INT0:   .ivec  2

INT2:   .ivec  3        ;fir ISR

TINT0:  .ivec  4

RINT0:  .ivec  5

RINT1:  .ivec  6

XINT1:  .ivec  7

LCKINT: .ivec  8

DMAC1:  .ivec  9

DSPINT: .ivec 10

INT3:   .ivec 11

UART:   .ivec 12 ;_UART_ISRHandler

XINT2:  .ivec 13

DMAC4:  .ivec 14

DMAC5:  .ivec 15

INT1:   .ivec 16

XINT0:  .ivec 17

DMAC0:  .ivec 18

INT4:   .ivec 19

DMAC2:  .ivec 20

DMAC3:  .ivec 21

TINT1:  .ivec 22

INT5:   .ivec 23

*------------------------------------------------------------------------------
