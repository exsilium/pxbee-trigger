/* Based on CPU DB MC9S08QE32_48, version 3.00.026 (RegistersPrg V2.32) */
/* DataSheet : MC9S08QE32RM Rev. 3 Draft A 11/2009 */

#include <xbee_config.h>

#if CONFIG_XBEE_FLASH_LEN == 32

#include <mc9s08qe32.h>

/*lint -save -esym(765, *) */


/* * * * *  8-BIT REGISTERS  * * * * * * * * * * * * * * * */
volatile PTADSTR _PTAD;                                    /* Port A Data Register; 0x00000000 */
volatile PTADDSTR _PTADD;                                  /* Port A Data Direction Register; 0x00000001 */
volatile PTBDSTR _PTBD;                                    /* Port B Data Register; 0x00000002 */
volatile PTBDDSTR _PTBDD;                                  /* Port B Data Direction Register; 0x00000003 */
volatile PTCDSTR _PTCD;                                    /* Port C Data Register; 0x00000004 */
volatile PTCDDSTR _PTCDD;                                  /* Port C Data Direction Register; 0x00000005 */
volatile PTDDSTR _PTDD;                                    /* Port D Data Register; 0x00000006 */
volatile PTDDDSTR _PTDDD;                                  /* Port D Data Direction Register; 0x00000007 */
volatile PTEDSTR _PTED;                                    /* Port E Data Register; 0x00000008 */
volatile PTEDDSTR _PTEDD;                                  /* Port E Data Direction Register; 0x00000009 */
volatile KBI1SCSTR _KBI1SC;                                /* KBI1 Status and Control Register; 0x0000000C */
volatile KBI1PESTR _KBI1PE;                                /* KBI1 Pin Enable Register; 0x0000000D */
volatile KBI1ESSTR _KBI1ES;                                /* KBI1 Edge Select Register; 0x0000000E */
volatile IRQSCSTR _IRQSC;                                  /* Interrupt request status and control register; 0x0000000F */
volatile ADCSC1STR _ADCSC1;                                /* Status and Control Register 1; 0x00000010 */
volatile ADCSC2STR _ADCSC2;                                /* Status and Control Register 2; 0x00000011 */
volatile ADCCFGSTR _ADCCFG;                                /* Configuration Register; 0x00000016 */
volatile APCTL1STR _APCTL1;                                /* Pin Control 1 Register; 0x00000017 */
volatile APCTL2STR _APCTL2;                                /* Pin Control 2 Register; 0x00000018 */
volatile ACMP1SCSTR _ACMP1SC;                              /* ACMP1 Status and Control Register; 0x0000001A */
volatile ACMP2SCSTR _ACMP2SC;                              /* ACMP2 Status and Control Register; 0x0000001B */
volatile SCI1C1STR _SCI1C1;                                /* SCI1 Control Register 1; 0x00000022 */
volatile SCI1C2STR _SCI1C2;                                /* SCI1 Control Register 2; 0x00000023 */
volatile SCI1S1STR _SCI1S1;                                /* SCI1 Status Register 1; 0x00000024 */
volatile SCI1S2STR _SCI1S2;                                /* SCI1 Status Register 2; 0x00000025 */
volatile SCI1C3STR _SCI1C3;                                /* SCI1 Control Register 3; 0x00000026 */
volatile SCI1DSTR _SCI1D;                                  /* SCI1 Data Register; 0x00000027 */
volatile SPIC1STR _SPIC1;                                  /* SPI Control Register 1; 0x00000028 */
volatile SPIC2STR _SPIC2;                                  /* SPI Control Register 2; 0x00000029 */
volatile SPIBRSTR _SPIBR;                                  /* SPI Baud Rate Register; 0x0000002A */
volatile SPISSTR _SPIS;                                    /* SPI Status Register; 0x0000002B */
volatile SPIDSTR _SPID;                                    /* SPI Data Register; 0x0000002D */
volatile IICASTR _IICA;                                    /* IIC Address Register; 0x00000030 */
volatile IICFSTR _IICF;                                    /* IIC Frequency Divider Register; 0x00000031 */
volatile IICC1STR _IICC1;                                  /* IIC Control Register 1; 0x00000032 */
volatile IICSSTR _IICS;                                    /* IIC Status Register; 0x00000033 */
volatile IICDSTR _IICD;                                    /* IIC Data I/O Register; 0x00000034 */
volatile IICC2STR _IICC2;                                  /* IIC Control Register 2; 0x00000035 */
volatile ICSC1STR _ICSC1;                                  /* ICS Control Register 1; 0x00000038 */
volatile ICSC2STR _ICSC2;                                  /* ICS Control Register 2; 0x00000039 */
volatile ICSTRMSTR _ICSTRM;                                /* ICS Trim Register; 0x0000003A */
volatile ICSSCSTR _ICSSC;                                  /* ICS Status and Control Register; 0x0000003B */
volatile KBI2SCSTR _KBI2SC;                                /* KBI2 Status and Control Register; 0x0000003C */
volatile KBI2PESTR _KBI2PE;                                /* KBI2 Pin Enable Register; 0x0000003D */
volatile KBI2ESSTR _KBI2ES;                                /* KBI2 Edge Select Register; 0x0000003E */
volatile TPM1SCSTR _TPM1SC;                                /* TPM1 Status and Control Register; 0x00000040 */
volatile TPM1C0SCSTR _TPM1C0SC;                            /* TPM1 Timer Channel 0 Status and Control Register; 0x00000045 */
volatile TPM1C1SCSTR _TPM1C1SC;                            /* TPM1 Timer Channel 1 Status and Control Register; 0x00000048 */
volatile TPM1C2SCSTR _TPM1C2SC;                            /* TPM1 Timer Channel 2 Status and Control Register; 0x0000004B */
volatile TPM2SCSTR _TPM2SC;                                /* TPM2 Status and Control Register; 0x00000050 */
volatile TPM2C0SCSTR _TPM2C0SC;                            /* TPM2 Timer Channel 0 Status and Control Register; 0x00000055 */
volatile TPM2C1SCSTR _TPM2C1SC;                            /* TPM2 Timer Channel 1 Status and Control Register; 0x00000058 */
volatile TPM2C2SCSTR _TPM2C2SC;                            /* TPM2 Timer Channel 2 Status and Control Register; 0x0000005B */
volatile TPM3SCSTR _TPM3SC;                                /* TPM3 Status and Control Register; 0x00000060 */
volatile TPM3C0SCSTR _TPM3C0SC;                            /* TPM3 Timer Channel 0 Status and Control Register; 0x00000065 */
volatile TPM3C1SCSTR _TPM3C1SC;                            /* TPM3 Timer Channel 1 Status and Control Register; 0x00000068 */
volatile TPM3C2SCSTR _TPM3C2SC;                            /* TPM3 Timer Channel 2 Status and Control Register; 0x0000006B */
volatile TPM3C3SCSTR _TPM3C3SC;                            /* TPM3 Timer Channel 3 Status and Control Register; 0x0000006E */
volatile TPM3C4SCSTR _TPM3C4SC;                            /* TPM3 Timer Channel 4 Status and Control Register; 0x00000071 */
volatile TPM3C5SCSTR _TPM3C5SC;                            /* TPM3 Timer Channel 5 Status and Control Register; 0x00000074 */
volatile SRSSTR _SRS;                                      /* System Reset Status Register; 0x00001800 */
volatile SBDFRSTR _SBDFR;                                  /* System Background Debug Force Reset Register; 0x00001801 */
volatile SOPT1STR _SOPT1;                                  /* System Options Register 1; 0x00001802 */
volatile SOPT2STR _SOPT2;                                  /* System Options Register 2; 0x00001803 */
volatile SPMSC1STR _SPMSC1;                                /* System Power Management Status and Control 1 Register; 0x00001808 */
volatile SPMSC2STR _SPMSC2;                                /* System Power Management Status and Control 2 Register; 0x00001809 */
volatile SPMSC3STR _SPMSC3;                                /* System Power Management Status and Control 3 Register; 0x0000180B */
volatile SCGC1STR _SCGC1;                                  /* System Clock Gating Control 1 Register; 0x0000180E */
volatile SCGC2STR _SCGC2;                                  /* System Clock Gating Control 2 Register; 0x0000180F */
volatile DBGCAXSTR _DBGCAX;                                /* Debug Comparator A Extension Register; 0x00001818 */
volatile DBGCBXSTR _DBGCBX;                                /* Debug Comparator B Extension Register; 0x00001819 */
volatile DBGCCXSTR _DBGCCX;                                /* Debug Comparator C Extension Register; 0x0000181A */
volatile DBGCSTR _DBGC;                                    /* Debug Control Register; 0x0000181C */
volatile DBGTSTR _DBGT;                                    /* Debug Trigger Register; 0x0000181D */
volatile DBGSSTR _DBGS;                                    /* Debug Status Register; 0x0000181E */
volatile DBGCNTSTR _DBGCNT;                                /* Debug Count Status Register; 0x0000181F */
volatile FCDIVSTR _FCDIV;                                  /* FLASH Clock Divider Register; 0x00001820 */
volatile FOPTSTR _FOPT;                                    /* FLASH Options Register; 0x00001821 */
volatile FCNFGSTR _FCNFG;                                  /* FLASH Configuration Register; 0x00001823 */
volatile FPROTSTR _FPROT;                                  /* FLASH Protection Register; 0x00001824 */
volatile FSTATSTR _FSTAT;                                  /* Flash Status Register; 0x00001825 */
volatile FCMDSTR _FCMD;                                    /* FLASH Command Register; 0x00001826 */
volatile RTCSCSTR _RTCSC;                                  /* RTC Status and Control Register; 0x00001830 */
volatile RTCCNTSTR _RTCCNT;                                /* RTC Counter Register; 0x00001831 */
volatile RTCMODSTR _RTCMOD;                                /* RTC Modulo Register; 0x00001832 */
volatile PTAPESTR _PTAPE;                                  /* Port A Pull Enable Register; 0x00001840 */
volatile PTASESTR _PTASE;                                  /* Port A Slew Rate Enable Register; 0x00001841 */
volatile PTADSSTR _PTADS;                                  /* Port A Drive Strength Selection Register; 0x00001842 */
volatile PTBPESTR _PTBPE;                                  /* Port B Pull Enable Register; 0x00001844 */
volatile PTBSESTR _PTBSE;                                  /* Port B Slew Rate Enable Register; 0x00001845 */
volatile PTBDSSTR _PTBDS;                                  /* Port B Drive Strength Selection Register; 0x00001846 */
volatile PTCPESTR _PTCPE;                                  /* Port C Pull Enable Register; 0x00001848 */
volatile PTCSESTR _PTCSE;                                  /* Port C Slew Rate Enable Register; 0x00001849 */
volatile PTCDSSTR _PTCDS;                                  /* Port C Drive Strength Selection Register; 0x0000184A */
volatile PTDPESTR _PTDPE;                                  /* Port D Pull Enable Register; 0x0000184C */
volatile PTDSESTR _PTDSE;                                  /* Port D Slew Rate Enable Register; 0x0000184D */
volatile PTDDSSTR _PTDDS;                                  /* Port D Drive Strength Selection Register; 0x0000184E */
volatile PTEPESTR _PTEPE;                                  /* Port E Pull Enable Register; 0x00001850 */
volatile PTESESTR _PTESE;                                  /* Port E Slew Rate Enable Register; 0x00001851 */
volatile PTEDSSTR _PTEDS;                                  /* Port E Drive Strength Selection Register; 0x00001852 */
volatile SCI2C1STR _SCI2C1;                                /* SCI2 Control Register 1; 0x00001872 */
volatile SCI2C2STR _SCI2C2;                                /* SCI2 Control Register 2; 0x00001873 */
volatile SCI2S1STR _SCI2S1;                                /* SCI2 Status Register 1; 0x00001874 */
volatile SCI2S2STR _SCI2S2;                                /* SCI2 Status Register 2; 0x00001875 */
volatile SCI2C3STR _SCI2C3;                                /* SCI2 Control Register 3; 0x00001876 */
volatile SCI2DSTR _SCI2D;                                  /* SCI2 Data Register; 0x00001877 */
/* NVFTRIM - macro for reading non volatile register       Nonvolatile ICS Fine Trim; 0x0000FFAE */
/* Tip for register initialization in the user code:  const byte NVFTRIM_INIT @0x0000FFAE = <NVFTRIM_INITVAL>; */
/* NVICSTRM - macro for reading non volatile register      Nonvolatile ICS Trim Register; 0x0000FFAF */
/* Tip for register initialization in the user code:  const byte NVICSTRM_INIT @0x0000FFAF = <NVICSTRM_INITVAL>; */
/* NVBACKKEY0 - macro for reading non volatile register    Backdoor Comparison Key 0; 0x0000FFB0 */
/* Tip for register initialization in the user code:  const byte NVBACKKEY0_INIT @0x0000FFB0 = <NVBACKKEY0_INITVAL>; */
/* NVBACKKEY1 - macro for reading non volatile register    Backdoor Comparison Key 1; 0x0000FFB1 */
/* Tip for register initialization in the user code:  const byte NVBACKKEY1_INIT @0x0000FFB1 = <NVBACKKEY1_INITVAL>; */
/* NVBACKKEY2 - macro for reading non volatile register    Backdoor Comparison Key 2; 0x0000FFB2 */
/* Tip for register initialization in the user code:  const byte NVBACKKEY2_INIT @0x0000FFB2 = <NVBACKKEY2_INITVAL>; */
/* NVBACKKEY3 - macro for reading non volatile register    Backdoor Comparison Key 3; 0x0000FFB3 */
/* Tip for register initialization in the user code:  const byte NVBACKKEY3_INIT @0x0000FFB3 = <NVBACKKEY3_INITVAL>; */
/* NVBACKKEY4 - macro for reading non volatile register    Backdoor Comparison Key 4; 0x0000FFB4 */
/* Tip for register initialization in the user code:  const byte NVBACKKEY4_INIT @0x0000FFB4 = <NVBACKKEY4_INITVAL>; */
/* NVBACKKEY5 - macro for reading non volatile register    Backdoor Comparison Key 5; 0x0000FFB5 */
/* Tip for register initialization in the user code:  const byte NVBACKKEY5_INIT @0x0000FFB5 = <NVBACKKEY5_INITVAL>; */
/* NVBACKKEY6 - macro for reading non volatile register    Backdoor Comparison Key 6; 0x0000FFB6 */
/* Tip for register initialization in the user code:  const byte NVBACKKEY6_INIT @0x0000FFB6 = <NVBACKKEY6_INITVAL>; */
/* NVBACKKEY7 - macro for reading non volatile register    Backdoor Comparison Key 7; 0x0000FFB7 */
/* Tip for register initialization in the user code:  const byte NVBACKKEY7_INIT @0x0000FFB7 = <NVBACKKEY7_INITVAL>; */
/* NVPROT - macro for reading non volatile register        Nonvolatile FLASH Protection Register; 0x0000FFBD */
/* Tip for register initialization in the user code:  const byte NVPROT_INIT @0x0000FFBD = <NVPROT_INITVAL>; */
/* NVOPT - macro for reading non volatile register         Nonvolatile Flash Options Register; 0x0000FFBF */
/* Tip for register initialization in the user code:  const byte NVOPT_INIT @0x0000FFBF = <NVOPT_INITVAL>; */


/* * * * *  16-BIT REGISTERS  * * * * * * * * * * * * * * * */
volatile ADCRSTR _ADCR;                                    /* Data Result Register; 0x00000012 */
volatile ADCCVSTR _ADCCV;                                  /* Compare Value Register; 0x00000014 */
volatile SCI1BDSTR _SCI1BD;                                /* SCI1 Baud Rate Register; 0x00000020 */
volatile TPM1CNTSTR _TPM1CNT;                              /* TPM1 Timer Counter Register; 0x00000041 */
volatile TPM1MODSTR _TPM1MOD;                              /* TPM1 Timer Counter Modulo Register; 0x00000043 */
volatile TPM1C0VSTR _TPM1C0V;                              /* TPM1 Timer Channel 0 Value Register; 0x00000046 */
volatile TPM1C1VSTR _TPM1C1V;                              /* TPM1 Timer Channel 1 Value Register; 0x00000049 */
volatile TPM1C2VSTR _TPM1C2V;                              /* TPM1 Timer Channel 2 Value Register; 0x0000004C */
volatile TPM2CNTSTR _TPM2CNT;                              /* TPM2 Timer Counter Register; 0x00000051 */
volatile TPM2MODSTR _TPM2MOD;                              /* TPM2 Timer Counter Modulo Register; 0x00000053 */
volatile TPM2C0VSTR _TPM2C0V;                              /* TPM2 Timer Channel 0 Value Register; 0x00000056 */
volatile TPM2C1VSTR _TPM2C1V;                              /* TPM2 Timer Channel 1 Value Register; 0x00000059 */
volatile TPM2C2VSTR _TPM2C2V;                              /* TPM2 Timer Channel 2 Value Register; 0x0000005C */
volatile TPM3CNTSTR _TPM3CNT;                              /* TPM3 Timer Counter Register; 0x00000061 */
volatile TPM3MODSTR _TPM3MOD;                              /* TPM3 Timer Counter Modulo Register; 0x00000063 */
volatile TPM3C0VSTR _TPM3C0V;                              /* TPM3 Timer Channel 0 Value Register; 0x00000066 */
volatile TPM3C1VSTR _TPM3C1V;                              /* TPM3 Timer Channel 1 Value Register; 0x00000069 */
volatile TPM3C2VSTR _TPM3C2V;                              /* TPM3 Timer Channel 2 Value Register; 0x0000006C */
volatile TPM3C3VSTR _TPM3C3V;                              /* TPM3 Timer Channel 3 Value Register; 0x0000006F */
volatile TPM3C4VSTR _TPM3C4V;                              /* TPM3 Timer Channel 4 Value Register; 0x00000072 */
volatile TPM3C5VSTR _TPM3C5V;                              /* TPM3 Timer Channel 5 Value Register; 0x00000075 */
volatile SDIDSTR _SDID;                                    /* System Device Identification Register; 0x00001806 */
volatile DBGCASTR _DBGCA;                                  /* Debug Comparator A Register; 0x00001810 */
volatile DBGCBSTR _DBGCB;                                  /* Debug Comparator B Register; 0x00001812 */
volatile DBGCCSTR _DBGCC;                                  /* Debug Comparator C Register; 0x00001814 */
volatile DBGFSTR _DBGF;                                    /* Debug FIFO Register; 0x00001816 */
volatile SCI2BDSTR _SCI2BD;                                /* SCI2 Baud Rate Register; 0x00001870 */

/*lint -restore */
#endif /* CONFIG_XBEE_FLASH_LEN == 32 */

/* EOF */
