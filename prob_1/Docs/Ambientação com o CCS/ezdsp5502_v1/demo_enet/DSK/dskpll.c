/*******************************************************************************
*                                                                              *
*  @file      dskpll.c                                                         *
*  @verbatim                                                                   *
*                       ___ \    ___| _)              __ __|                   *
*                       |    | \    \  |   _     __ \   |                      *
*                       |    |  ---    | (   |  |   |   |                      *
*                      _____/_)_____/ _| \__,|  |  _|  _|                      *
*                                        |___/                                 *
*                      Digital Signalprocessing Technology                     *
*  @endverbatim                                                                *
*  @brief     Initialize PLL                                                   *
*                                                                              *
*  @author    D.SignT GmbH & Co. KG, Claus Hermbusche                          *
*  @date      2011-09-19
*                                                                              *
*  @cond Software License Agreement                                            *
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
*  @endcond                                                                    *
*******************************************************************************/
/*******************************************************************************
*                                                                              *
*    INCLUDES                                                                  *
*                                                                              *
*******************************************************************************/
#include "dskpll.h"


/******************************************************************************/
/*                                                                            */
/*   DEFINES                                                                  */
/*                                                                            */
/******************************************************************************/


/******************************************************************************/
/*                                                                            */
/*   GLOBALS                                                                  */
/*                                                                            */
/******************************************************************************/


/******************************************************************************/
/*                                                                            */
/*   FUNCTIONS                                                                */
/*                                                                            */
/******************************************************************************/
/***************************************************************************//**

 @brief   Initialize 5502 PLL
 @details This function initializes the 5502 PLL
 @target  TMS320VC5502

*******************************************************************************/
void init_pll (void)
{
    /***************************************************************************
     Turn the PLL off
    ***************************************************************************/
    PLL->csr &= ~CSR_PLLEN;

    /***************************************************************************
     reset the PLL
    ***************************************************************************/
    PLL->csr |= CSR_PLLRST;

    /***************************************************************************
     wait for unlock
    ***************************************************************************/
    while (PLL->csr & CSR_LOCK);

    /***************************************************************************
     take out of reset
    ***************************************************************************/
    PLL->csr &= ~CSR_PLLRST;

    /***************************************************************************
      Initialize PLL
    ***************************************************************************/
    PLL->multi = 0x000F;        /* 20MHz x 15 == 300MHz */
    PLL->div0  = 0x8000;        /* :1                   */
    PLL->div1  = 0x8000;        /* Set fast peripheral clock to divide by 1 */
    PLL->div2  = 0x8003;        /* Set slow peripheral clock to divide by 4 */
    PLL->div3  = 0x8003;        /* : 4            */

    /***************************************************************************
     Turn the PLL on
    ***************************************************************************/
    PLL->csr |= CSR_PLLEN;

    /***************************************************************************
     wait for lock
    ***************************************************************************/
    while (! (PLL->csr & CSR_LOCK));
}

