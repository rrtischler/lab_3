/*******************************************************************************
*                                                                              *
*  @file      dskemif.c                                                        *
*  @verbatim                                                                   *
*                       ___ \    ___| _)              __ __|                   *
*                       |    | \    \  |   _     __ \   |                      *
*                       |    |  ---    | (   |  |   |   |                      *
*                      _____/_)_____/ _| \__,|  |  _|  _|                      *
*                                        |___/                                 *
*                      Digital Signalprocessing Technology                     *
*  @endverbatim                                                                *
*  @brief     Initialize EMIF                                                  *
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
/*******************************************************************************
  Runtime Source
*******************************************************************************/
#include <stdlib.h>

/*******************************************************************************
  defines and protoypes for this module
*******************************************************************************/
#include "dskemif.h"


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

 @brief   Initialize 5502 EMIF
 @details This function initializes the 5502 EMIF
 @target  TMS320VC5502

*******************************************************************************/
void init_emif (void)
{
    *(volatile ioport unsigned int *)0x6c00 = 1;  /* enable ext. bus */
    EMIF->gctl1   |= 0x0020;      /* enable ECLKOUT1                          */
    EMIF->gctl2    = 0x0001;      /* EMIF global control register             */

    EMIF->ce0_ctl1 = 0xFF33;      /* 32-bit SDRAM in CE0 space.               */
    EMIF->ce0_ctl2 = 0xFFFF;

    EMIF->sdctl_1  = 0xF000;      /* EMIF SDRAM Control Register 1            */
    EMIF->sdctl_2  = 0x4748;      /* EMIF SDRAM Control Register 2            */
    EMIF->sdref1   = 0x0001;
    EMIF->sdref2   = 0x0000;
/*  EMIF->sdext1   = 0xB528;
    EMIF->sdext2   = 0x0007; */
    EMIF->ce1_ctl1 = 0x8711;      /* 16-bit async in CE1 space.               */
    EMIF->ce1_ctl2 = 0x30B4;
    EMIF->ce3_ctl1 = 0x4310;      /* 16-bit async in CE3 space.               */
    EMIF->ce3_ctl2 = 0x11d1;

}


