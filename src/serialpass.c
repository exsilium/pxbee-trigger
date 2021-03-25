/*-------------------------------------------------------
* Copyright (C) 2012 Digi International, All Rights Reserved.
*
*
* This software is provided as instructional material without charge
* by Digi International for use by its employees and customers
* subject to the following terms.
*
* PERMISSION
* Permission is hereby granted, free of charge, to any person obtaining
* a copy of this software, to deal with it without restriction,
* including without limitation the rights to use, copy,  modify, merge, publish,
* distribute, sublicense, and/or sell copies of it, and to permit persons to
* whom it is furnished to do so, provided the above copyright notice
* and this permission notice are included in all derived works
* and the use of this software is restricted to Digi products.
*
* WARRANTY
* THIS SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
* OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE, OR NONINFRINGEMENT.
*
* LIABILITY
* IN NO EVENT SHALL DIGI INTERNATIONAL BE LIABLE FOR ANY CLAIM, DAMAGES,
* OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT, OR OTHERWISE,
* ARISING FROM, OUT OF, OR IN CONNECTION WITH THE SOFTWARE, OR THE USE
* OR OTHER DEALINGS WITH THE SOFTWARE.
*
*-------------------------------------------------------*/
#include <hidef.h>      /*!< EnableInterrupts macro */

#include <xbee_config.h>

//#define BYPASS_RESET

#define   FSCALE_HOST_TX      PTBD_PTBD1
#define   FSCALE_HOST_RX      PTBD_PTBD0
#define   FSCALE_EM250_TX     PTCD_PTCD7
#define   FSCALE_EM250_RX     PTCD_PTCD6
#define   FSCALE_CFG_HOST_TX  PTBDD_PTBDD1
#define   FSCALE_CFG_EM250_TX PTCDD_PTCDD7


/*F***************************************************************
*
*   NAME:   DoPassThroughMode
*/
/*! \brief	Takes data coming into UART0 and reflects it out UART1
*           Takes data coming into UART1 and reflects it out UART0
*
*
*  Passes DIN, DOUT, RTS, CTS, from Computer to EM250
*  Has 0.9uS of jitter. (~10 samples per bit at 115k)
*/

#define RESET PTAD_PTAD5
#define RESET_DIR_EM250 PTCDD_PTCDD4
#define WDR() __RESET_WATCHDOG()

void  DoPassThroughMode(void)
{
  ICSC2_BDIV0 = 0;//bus clock div by 1

#if 1   //Always do the assembly code so the compiler can't change the optimization.
  __asm{                        // instruction

  // Disable UARTS - we're going to manually control the lines from now on.

  //_SCI1C2.Byte = 0;
  CLR   _SCI1C2
  //_SCI2C2.Byte = 0;
  CLRA
  STA   _SCI2C2

  //                      Freescale
  //                      ---------
  //    Tx_U1  - PTB-D1 - Output
  //    Rx_U1  - PTB-D0 - Input
  //    Tx_U2  - PTC-D7 - Output = DIN_XBEE
  //    Rx_U2  - PTC-D6 - Input  = DOUT_XBEE
  //
  //    CTS_U1 - PTD6 -  Input
  //    RTS_U1 - PTC1 -  Output
  //    CTS_U2 - PTD7 -  Input
  //    RTS_U2 - PTC0 -  Output

  // Configure port pins for output mode

  // //PTCDD_PTCDD0        = 1;
  // //PTCDD_PTCDD1        = 1;

  // //-----------------------------------------
  // // Reconfigure clocks;
  // // ICSSC_DRST_DRS1 = 1;
  // // ICSSC_DMX32 = 1;
  // // ICSSC_FTRIM = 1;


  //PTDDD =0; // set all Port D to an input
  CLR   _PTDDD
  //FSCALE_CFG_HOST_TX  = 1;
  BSET  1,_PTBDD

  ////vResetEM250(); // reset EM250 before entering pass through mode
  //                              JSR   vResetEM250

  //PTCDD =(1<<7) | 3; // bit 7, 1, 0 are outputs, others are treated as inputs.(Reset is set to an input)
  MOV   #-125,_PTCDD
#ifdef BYPASS_RESET
  //Reset propagation from FSL cpu to radio: RESET# configured as input and RESET_Radio# as output high
                                BCLR  5,_PTADD	// RESET# as input
                                BSET  4,_PTCD	// RESET_Radio# as output high
                                BSET  4,_PTCDD
#endif
  //FSCALE_HOST_TX  = 1;
  BSET  1,_PTBD
  //FSCALE_EM250_TX = 1;
  BSET  7,_PTCD



  //==================================================
  // First Set
  //==================================================

  // Goal: Sample Tx and Rx more frequently than RST, RTS and CTS since the
  //       flow control signals change less frequently than the data pins.

  // Read data from Host and write it to XBee (U1:Rx -> U2:Tx)
  /**********************************************************************
   *State Machine
   * State 11 = Host_RX = 1 and EM250_RX = 1
   * State 01 = Host_RX = 0 and EM250_RX = 1
   * State 10 = Host_RX = 1 and EM250_RX = 0
   * State 00 = Host_RX = 0 and EM250_RX = 0
   *
   * With states the loop can be faster, because we are checking to see if the state
   * of the line changes. Therefore it is only 1 instruction to check the line for a
   * change rather than 3 instructions each loop to copy the state.
   * Only copy the state after it changes.
   *
   *
   **********************************************************************/

  // Note: Do not rewrite - this sequence produces the fastest code!



  //for(;;){
  L11Loop:

//L11:
  //  if (!FSCALE_HOST_RX) { //(5 clocks)       //1 instruction  (3 instructions during transition)
  L27:                            BRCLR 0,_PTBD,L3F ;abs = 003f
  //    FSCALE_EM250_TX = 0;
  //    goto L01E; //change to State 01, sample EM250 next
  //  }
//L11E:
  //  if (!FSCALE_EM250_RX) {                  //1 instruction
  L2A:                            BRCLR 6,_PTCD,L46 ;abs = 0046
  //    FSCALE_HOST_TX = 0;
  //    goto L10; //change to State 10, sample Host next
  //  }


  //  PTCD_PTCD1 = PTDD_PTDD7;
  LDA PTDD       // get RTS/CTS  PTDD_PTDD6/7    (4 clocks)
  ROLA           //bit shift rotate through carry
  ROLA           //(1 clock * 3)
  ROLA           //
//note that if HOST_RX or EM250_RX changes,in the next 2 instructions the RTS/CTS sample will be dropped. sampling will be done next loop (saves code space)

  //  if (!FSCALE_HOST_RX) {                  //1 instruction
//                                BRCLR 0,_PTBD,L3F ;abs = 003f
  //    FSCALE_EM250_TX = 0;
  //    goto L01E;
  //  }
  //  if (!FSCALE_EM250_RX) {                 //1 instruction
//                                BRCLR 6,_PTCD,L46 ;abs = 0046
  //    FSCALE_HOST_TX = 0;
  //    goto L10;
  //  }
/*moved up */
  //  if (!FSCALE_HOST_RX) {                  //1 instruction
  BRSET 0,_PTBD,L43 ;abs = 0043
  //    FSCALE_EM250_TX = 0;
  L3F:                            BCLR  7,_PTCD
  BRA   L56 ;abs = 0056
  //    goto L01E;
  //    }
  //  if (!FSCALE_EM250_RX) {                 //1 instruction
  L43:                            BRSET 6,_PTCD,L4A ;abs = 004a
  //    FSCALE_HOST_TX = 0;
  L46:                            BCLR  1,_PTBD
  BRA   L75 ;abs = 0075
  //    goto L10;
  //  }
/*end move up*/
  L4A:   //this was moved from STA _SRS to include the items below
  //  PTCD_PTCD0 = PTDD_PTDD6;
#ifndef BYPASS_RESET
  ORA #0x80;     // set EM250_TX  (2 clocks)
#else
  ORA #0x90;	   // set EM250_TX  (2 clocks)	and RESET_Ratio# to 1
  //  PTCD_PTCD4 = PTAD_PTAD5;
                                BRSET 5,_PTAD,L4A_r
                                AND #0xEF      //RESET_Ratio# to 0
L4A_r:
#endif
  STA PTCD;     //write RTS/CTS   (4 clocks)


  //          WDR(); // 2 instructions overhead (watchdog and branch)
  STA   _SRS
  BRA   L11Loop ;abs = 0027
  //  }//for

  //for(;;){
  L01Loop:

//L01:
  //  if (FSCALE_HOST_RX) {
  L4F:                            BRSET 0,_PTBD,LD56 ;abs = 0056 //changed to delete the duplicate code
//                                BRCLR 0,_PTBD,L56 ;abs = 0056
  //    FSCALE_EM250_TX = 1;
//duplicate                                BSET  7,_PTCD
  //    goto L11E;
//duplicate                                BRA   L2A ;abs = 002a
  //    }
//L01E:
  //  if (!FSCALE_EM250_RX) {
  L56:                            BRCLR 6,_PTCD,L68 ;abs = 0068
  //    FSCALE_HOST_TX = 0;
  //    goto L00;
  //  }


//    PTCD_PTCD1 = PTDD_PTDD7;
  LDA PTDD
  ROLA
  ROLA
  ROLA

  //  if (FSCALE_HOST_RX) {
  BRCLR 0,_PTBD,L65 ;abs = 0065
  //    FSCALE_EM250_TX = 1;
  LD56:                           BSET  7,_PTCD
  //    goto L11E;
  BRA   L2A ;abs = 002a
  //  }
  //  if (!FSCALE_EM250_RX) {
  L65:                            BRSET 6,_PTCD,L6C ;abs = 006c
  //    FSCALE_HOST_TX = 0;
  L68:                            BCLR  1,_PTBD
  BRA   L97 ;abs = 0097
  //    goto L00;
  //  }
  //  PTCD_PTCD0 = PTDD_PTDD6;
  L6C:                            AND #0x3       // clear EM250_TX (Based on state of Host_RX)
#ifdef BYPASS_RESET
  //  PTCD_PTCD4 = PTAD_PTAD5;
                                BRCLR 5,_PTAD,L6C_r	//RESET_Ratio# set to 0 above
                                ORA #0x10      //RESET_Ratio# to 1
L6C_r:
#endif
  STA PTCD;
  //  WDR();
  STA   _SRS
  BRA   L01Loop ;abs = 004f
  //}//for

  //for(;;){
  L10Loop:

//L10:
  //  if (!FSCALE_HOST_RX) {
  L75:                            BRCLR 0,_PTBD,L83 ;abs = 0083
  //    FSCALE_EM250_TX = 0;
  //    goto L00E;
  //  }
//L10E:
  //  if (FSCALE_EM250_RX) {
  L78:                            BRSET 6,_PTCD,L8A ;abs = 008a
  //    FSCALE_HOST_TX = 1;
  //    goto L11;
  //  }


  //  PTCD_PTCD1 = PTDD_PTDD7;
  LDA PTDD
  ROLA
  ROLA
  ROLA
  //  if (!FSCALE_HOST_RX) {
  BRSET 0,_PTBD,L87 ;abs = 0087
  //    FSCALE_EM250_TX = 0;
  L83:                            BCLR  7,_PTCD
  BRA   L9E ;abs = 009e
  //    goto L00E;
  //  }
  //  if (FSCALE_EM250_RX) {
  L87:                            BRCLR 6,_PTCD,L8E ;abs = 008e
  //    FSCALE_HOST_TX = 1;
  L8A:                            BSET  1,_PTBD
  //    goto L11;
  BRA   L27 ;abs = 0027
  //  }
  //  PTCD_PTCD0 = PTDD_PTDD6;
#ifndef BYPASS_RESET
  L8E:                            ORA #0x80      // set EM250_TX (Based on state of Host_RX)
#else
  L8E:                            ORA #0x90      // set EM250_TX (Based on state of Host_RX) and RESET_Ratio# to 1
  //  PTCD_PTCD4 = PTAD_PTAD5;
                                BRSET 5,_PTAD,L8E_r
                                AND #0xEF      //RESET_Ratio# to 0
L8E_r:
#endif
  STA PTCD
  //  WDR();
  STA   _SRS
  BRA   L10Loop ;abs = 0075
  //} //for

  //for(;;){
  L00Loop:

//L00:
  //  if (FSCALE_HOST_RX) {
  L97:                            BRCLR 0,_PTBD,L9E ;abs = 009e
  //    FSCALE_EM250_TX = 1;
  BSET  7,_PTCD
  //    goto L10E;
  BRA   L78 ;abs = 0078
  //  }
//L00E:
  //  if (FSCALE_EM250_RX) {
  L9E:                            BRCLR 6,_PTCD,LA5 ;abs = 00a5
  //    FSCALE_HOST_TX = 1;
  BSET  1,_PTBD
  //    goto L01;
  BRA   L4F ;abs = 004f
  //  }

  LA5:
  //  PTCD_PTCD1 = PTDD_PTDD7;

  LDA PTDD
  ROLA
  ROLA
  ROLA
  //  if (FSCALE_HOST_RX) {
  BRCLR 0,_PTBD,LB1 ;abs = 00b1
  //    FSCALE_EM250_TX = 1;
  BSET  7,_PTCD
  //    goto L10E;
  BRA   L78 ;abs = 0078
  //  }
  //  if (FSCALE_EM250_RX) {
  LB1:                            BRCLR 6,_PTCD,LB8 ;abs = 00b8
  //    FSCALE_HOST_TX = 1;
  BSET  1,_PTBD
  //    goto L01;
  BRA   L4F ;abs = 004f
  //  }
  //  PTCD_PTCD0 = PTDD_PTDD6;
  LB8:                            AND #0x3       // clear EM250_TX (Based on state of Host_RX)
#ifdef BYPASS_RESET
  //  PTCD_PTCD4 = PTAD_PTAD5;
                                BRCLR 5,_PTAD,LB8_r	//RESET_Ratio# set to 0 above
                                ORA #0x10      //RESET_Ratio# to 1
LB8_r:
#endif

  STA PTCD
  //  WDR();
  STA   _SRS
  BRA   L00Loop ;abs = 0097
  //} //for

  } // asm()

#else
  //==================================================
        // Code without all the asembly in the middle
        // This is for reference only
        //==================================================

    // Disable UARTS - we're going to manually control the lines from now on.
    _SCI1C2.Byte = 0;
    _SCI2C2.Byte = 0;



    //                      Freescale
    //                      ---------
    //    Tx_U1  - PTB-D1 - Output
    //    Rx_U1  - PTB-D0 - Input
    //    Tx_U2  - PTC-D7 - Output = DIN_XBEE
    //    Rx_U2  - PTC-D6 - Input  = DOUT_XBEE
    //
    //    CTS_U1 - PTD6 -  Input
    //    RTS_U1 - PTC1 -  Output
    //    CTS_U2 - PTD7 -  Input
    //    RTS_U2 - PTC0 -  Output

    // Configure port pins for output mode

    //PTCDD_PTCDD0        = 1;
    //PTCDD_PTCDD1        = 1;

    //-----------------------------------------
    // Reconfigure clocks;
   // ICSSC_DRST_DRS1 = 1;
   // ICSSC_DMX32 = 1;
   // ICSSC_FTRIM = 1;



    PTDDD =0; // set all Port D to an input
    FSCALE_CFG_HOST_TX  = 1;
    //FSCALE_CFG_EM250_TX = 1; this is done in Setting Port C directions

  //  vResetEM250(); // reset EM250 before entering pass through mode

    PTCDD =(1<<7) | 3; // bit 7, 1, 0 are outputs, others are treated as inputs.(Reset is treated as an input when not in reset)


#ifdef BYPASS_RESET
  //Reset propagation from FSL cpu to radio: RESET# configured as input and RESET_Radio# as output high
    PTADD_PTADD5 = 0;	// RESET# as input

    PTCD_PTCD4 = 1;	// RESET_Radio# as output high
    PTCDD_PTCDD4 = 1;
#endif

    FSCALE_HOST_TX  = 1;//initialize state to 11
    FSCALE_EM250_TX = 1;//


        //==================================================
        // First Set
        //==================================================

        // Goal: Sample Tx and Rx more frequently than RTS and CTS since the
        //       flow control signals change less frequently than the data pins.

        // Read data from Host and write it to XBee (U1:Rx -> U2:Tx)
        // Note: Do not rewrite - this sequence produces the fastest code (so far)!

          for(;;){

L11:        if (!FSCALE_HOST_RX) { //(5 clocks)       //1 instruction  (3 instructions during transition)
              FSCALE_EM250_TX = 0;
              goto L01E;//change state to 01;sample EM250 next
            }
L11E:       if (!FSCALE_EM250_RX) {                  //1 instruction
              FSCALE_HOST_TX = 0;
              goto L10;//change state to 10
            }

            //PTCD_PTCD1= PTDD_PTDD7 ;               //3 instructions
            asm {                                    //equal to 1.5 instructions
             LDA PTDD; // get RTS/CTS  PTDD_PTDD6/7    (4 clocks)
             ROLA;     //bit shift rotate through carry
             ROLA;     //(1 clock * 3)
             ROLA;     //
            }
//note that if HOST_RX or EM250_RX changes,in the next 2 instructions the RTS/CTS sample will be dropped. sampling will be done next loop (saves code space)

            if (!FSCALE_HOST_RX) {                  //1 instruction
              FSCALE_EM250_TX = 0;
              goto L01E;
            }
            if (!FSCALE_EM250_RX) {                 //1 instruction
              FSCALE_HOST_TX = 0;
              goto L10;
            }
            //PTCD_PTCD0 = PTDD_PTDD6;              //3 instructions
            asm {
              ORA #0x80; // set EM250_TX  (2 clocks)
#ifdef BYPASS_RESET
              //  PTCD_PTCD4 = PTAD_PTAD5;			//4 instructions
              BRSET 5,_PTAD,L11_r1
              AND #0xEF      //RESET_Ratio# to 0
              BRA L11_r0
L11_r1:
              ORA #0x10      //RESET_Ratio# to 1
L11_r0:
#endif
              STA PTCD;//write RTS/CTS   (4 clocks)   //1 instruction
            }

            WDR(); // 2 instructions overhead
          }//for

          for(;;){



L01:        if (FSCALE_HOST_RX) {
              FSCALE_EM250_TX = 1;
              goto L11E;
            }
L01E:       if (!FSCALE_EM250_RX) {
              FSCALE_HOST_TX = 0;
              goto L00;
            }
//            PTCD_PTCD1= PTDD_PTDD7 ;
            asm {
             LDA PTDD;
             ROLA;
             ROLA;
             ROLA;
            }

            if (FSCALE_HOST_RX) {
              FSCALE_EM250_TX = 1;
              goto L11E;
            }
            if (!FSCALE_EM250_RX) {
              FSCALE_HOST_TX = 0;
              goto L00;
            }
            //PTCD_PTCD0 = PTDD_PTDD6;
            asm {
              AND #0x3; // clear EM250_TX (Based on state of Host_RX)
#ifdef BYPASS_RESET
              //  PTCD_PTCD4 = PTAD_PTAD5;			//4 instructions
              BRSET 5,_PTAD,L01_r1
              AND #0xEF      //RESET_Ratio# to 0
              BRA L01_r0
L01_r1:
              ORA #0x10      //RESET_Ratio# to 1
L01_r0:
#endif
              STA PTCD;
            }
            WDR();
          }//for

          for(;;){

L10:
            if (!FSCALE_HOST_RX) {
              FSCALE_EM250_TX = 0;
              goto L00E;
            }
L10E:
            if (FSCALE_EM250_RX) {
              FSCALE_HOST_TX = 1;
              goto L11;
            }

//            PTCD_PTCD1= PTDD_PTDD7 ;
            asm {
             LDA PTDD;
             ROLA;
             ROLA;
             ROLA;
            }
            if (!FSCALE_HOST_RX) {
              FSCALE_EM250_TX = 0;
              goto L00E;
            }
            if (FSCALE_EM250_RX) {
              FSCALE_HOST_TX = 1;
              goto L11;
            }
            //PTCD_PTCD0 = PTDD_PTDD6;
            asm {
              ORA #0x80; // set EM250_TX (Based on state of Host_RX)
#ifdef BYPASS_RESET
              //  PTCD_PTCD4 = PTAD_PTAD5;			//4 instructions
              BRSET 5,_PTAD,L10_r1
              AND #0xEF      //RESET_Ratio# to 0
              BRA L10_r0
L10_r1:
              ORA #0x10      //RESET_Ratio# to 1
L10_r0:
#endif
              STA PTCD;
            }
            WDR();
          }//for

          for(;;){


L00:        if (FSCALE_HOST_RX) {
              FSCALE_EM250_TX = 1;
              goto L10E;
            }
L00E:       if (FSCALE_EM250_RX) {
              FSCALE_HOST_TX = 1;
              goto L01;
            }
//            PTCD_PTCD1= PTDD_PTDD7 ;
            asm {
             LDA PTDD;
             ROLA;
             ROLA;
             ROLA;
            }

            if (FSCALE_HOST_RX) {
              FSCALE_EM250_TX = 1;
              goto L10E;
            }
            if (FSCALE_EM250_RX) {
              FSCALE_HOST_TX = 1;
              goto L01;
            }
            //PTCD_PTCD0 = PTDD_PTDD6;
            asm {
              AND #0x3; // clear EM250_TX (Based on state of Host_RX)
#ifdef BYPASS_RESET
              //  PTCD_PTCD4 = PTAD_PTAD5;			//4 instructions
              BRSET 5,_PTAD,L00_r1
              AND #0xEF      //RESET_Ratio# to 0
              BRA L00_r0
L00_r1:
              ORA #0x10      //RESET_Ratio# to 1
L00_r0:
#endif
              STA PTCD;
            }
            WDR();
          }//for

#endif
  }