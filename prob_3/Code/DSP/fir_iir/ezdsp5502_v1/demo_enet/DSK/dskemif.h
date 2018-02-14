/***************************************************************************//**
*                                                                              *
*  @file      dskemif.h                                                        *
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

/***********************************************************************
   type definitions for access to DSP on-chip peripherals
***********************************************************************/
typedef struct
{
    volatile unsigned int gctl1;
    volatile unsigned int gctl2;
    volatile unsigned int ce1_ctl1;
    volatile unsigned int ce1_ctl2;
    volatile unsigned int ce0_ctl1;
    volatile unsigned int ce0_ctl2;
    volatile unsigned int res[2];
    volatile unsigned int ce2_ctl1;
    volatile unsigned int ce2_ctl2;
    volatile unsigned int ce3_ctl1;
    volatile unsigned int ce3_ctl2;
    volatile unsigned int sdctl_1;
    volatile unsigned int sdctl_2;
    volatile unsigned int sdref1;
    volatile unsigned int sdref2;
    volatile unsigned int sdext1;
    volatile unsigned int sdext2;
} dsp_emif_struct;
#define EMIF_BASE_ADDR          0x0800
#define EMIF ((ioport volatile dsp_emif_struct *) ((volatile unsigned int *) EMIF_BASE_ADDR))


/******************************************************************************/
/*                                                                            */
/*   PROTOTYPES                                                               */
/*                                                                            */
/******************************************************************************/
#ifdef __cplusplus
  extern "C" {
#endif

/*******************************************************************************

    Function init_emif()    Initialize EMIF

*******************************************************************************/
void init_emif (void);

#ifdef __cplusplus
}
#endif

