/*******************************************************************************

  net.cmd - TMS320V5502 ezdsp

  Revision  1.0
  Company   D.SignT
  Author    Claus Hermbusche
  Created   1 Mar 2011

  Hardware  TMS320V5502 ezdsp
  Compiler
  Options

*******************************************************************************/
-lrts55x.lib          /* Runtime library large memory model                   */


/* SPECIFY THE SYSTEM MEMORY MAP */
MEMORY
{
  PAGE 0:     /* ---- Unified Program/Data Address Space ---- */

    MMR    (RWIX):  origin = 0x000000, length = 0x0000C0  /* MMRs */
    BTRSVD (RWIX):  origin = 0x0000C0, length = 0x000240  /* Reserved for Boot Loader */
    DARAM  (RWIX):  origin = 0x000300, length = 0x00FB00  /* 64KB - MMRs - VECS*/
    VECS   (RWIX):  origin = 0x00FE00, length = 0x000200  /* 256 bytes Vector Table */

    SDRAMTEXT:      origin = 0x10000,  length = 0x10000
    SDRAMSYSMEM:    origin = 0x20000,  length = 0x10000
    SDRAMDATA:      origin = 0x30000,  length = 0x10000
    SDRAMCIO:       origin = 0x40000,  length = 0x10000
    SDRAMRTSTEXT:   origin = 0x50000,  length = 0x10000
    SDRAMRTSDATA:   origin = 0x60000,  length = 0x10000
    SDRAMFREE:      origin = 0x70000,  length = 0x340000
    SDRAMINIT:      origin = 0x3b0000, length = 0x10000

    PDROM   (RIX):  origin = 0xFF8000, length = 0x008000  /*  32KB */


  PAGE 2:    /* -------- 64K-word I/O Address Space -------- */

    IOPORT (RWI):   origin = 0x000000, length = 0x020000

}

/* SPECIFY THE SECTIONS ALLOCATION INTO MEMORY */
SECTIONS
{
   /* Vectors */
    vectors     >  VECS    PAGE 0           /* Interrupt vectors              */

   /* Both stacks must be on same physical memory page                        */
   .stack       >  DARAM           fill = 0 /* Primary system stack           */
   .sysstack    >  DARAM           fill = 0 /* Secondary system stack         */
/*   .sysmem      >  DARAM           fill = 0  heap intern                    */
   .sysmem      >  SDRAMSYSMEM     fill = 0 /* heap extern                    */

   /* put all code sections into external memory, when I-Cache is on
     (see SPRA924a.pdf for more details)                                      */
   .text        >  SDRAMTEXT                /* Code                           */
   .nettextfast >  SDRAMTEXT
   .nettextslow >  SDRAMTEXT
   .cprintfsect >  SDRAMTEXT                /* CPrintf support                */
   .commonsect  >  SDRAMTEXT                /* common functions               */

   /* user buffer */
/*   .databuffer  >  DARAM                     buffer intern                  */
   .databuffer  >  SDRAMDATA                /* buffer extern                  */

   /* data segments */
   .bss         >  DARAM          fill = 0  /* Global & static vars           */
   .data        >  SDRAMDATA      fill = 0  /* Initialized vars               */
   .const       >  SDRAMDATA      fill = 0  /* Constant data                  */
   .switch      >  SDRAMDATA                /* Switch statement tables        */
   .csldata     >  SDRAMDATA
   .cio         >  SDRAMCIO                 /* C I/O buffers                  */

   /* initialization */
   .cinit       >  SDRAMINIT      fill = 0  /* Auto-initialization tables     */
   .pinit       >  SDRAMINIT                /* Initialization fn tables       */

   /* RTS */
   .rtstext { -lrts55x.lib(.text)   } > SDRAMRTSTEXT
   .rtsbss  { -lrts55x.lib(.bss)    } > SDRAMRTSDATA
   .rtsdata { -lrts55x.lib(.const)  } > SDRAMRTSDATA

   .ioport      >  IOPORT PAGE 2            /* Global & static ioport vars    */
}
