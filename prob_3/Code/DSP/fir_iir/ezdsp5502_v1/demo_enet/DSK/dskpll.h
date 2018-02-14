/***************************************************************************//**
*                                                                              *
*  @file      dskpll.h                                                         *
*  @verbatim                                                                   *
*                       ___ \    ___| _)              __ __|                   *
*                       |    | \    \  |   _     __ \   |                      *
*                       |    |  ---    | (   |  |   |   |                      *
*                      _____/_)_____/ _| \__,|  |  _|  _|                      *
*                                        |___/                                 *
*                      Digital Signalprocessing Technology                     *
*  @endverbatim                                                                *
*  @brief     Defines and prototypes for PLL initialization                    *
*                                                                              *
*  @author    D.SignT GmbH & Co. KG, Claus Hermbusche                          *
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

/******************************************************************************/
/*                                                                            */
/*   DEFINES                                                                  */
/*                                                                            */
/******************************************************************************/

/*******************************************************************************
 PLL register structure
*******************************************************************************/
typedef struct
{
    volatile unsigned int csr;
    volatile unsigned int res1;
    volatile unsigned int clk3sel;
    volatile unsigned int res2;
    volatile unsigned int res3;
    volatile unsigned int res4;
    volatile unsigned int res5;
    volatile unsigned int res6;
    volatile unsigned int multi;
    volatile unsigned int res7;
    volatile unsigned int div0;
    volatile unsigned int res8;
    volatile unsigned int div1;
    volatile unsigned int res9;
    volatile unsigned int div2;
    volatile unsigned int res10;
    volatile unsigned int div3;
    volatile unsigned int res11;
    volatile unsigned int oscdiv1;
    volatile unsigned int res[2];
    volatile unsigned int wakeup;
} dsp_pll_struct;

#define PLL_BASE_ADDR          0x1C80
#define PLL ((volatile ioport dsp_pll_struct *) (( volatile unsigned int *)PLL_BASE_ADDR))

#define CSR_PLLEN            0x0001
#define CSR_PLLPWRDN         0x0002
#define CSR_OSCPWRDN         0x0004
#define CSR_PLLRST           0x0008
#define CSR_LOCK             0x0020
#define CSR_STABLE           0x0040

/******************************************************************************/
/*                                                                            */
/*   PROTOTYPES                                                               */
/*                                                                            */
/******************************************************************************/
#ifdef __cplusplus
  extern "C" {
#endif

/*******************************************************************************

    Function init_pll()    Initialize PLL

*******************************************************************************/
void init_pll (void);


#ifdef __cplusplus
}
#endif

