#ifndef _HEAD_REGS_H_
#define _HEAD_REGS_H_

#define WT_BASE_ADDR		(0x44100000)

#define INT_BASE_ADDR		(0x40200000)
#define oINTMOD			(0x04)
#define oINTMSK			(0x08)
#define oINTSUBMSK		(0x1C)

#if defined (CONFIG_S3C2413)
#define LCD_BASE_ADDR		(0x4D000000)
#define oLCDINTMSK		(0x2C)
#else
#define LCD_BASE_ADDR		(0x4A000000)
#define oLCDINTMSK		(0x5C)
#endif

#if defined (CONFIG_S3C2413)
#define CLK_BASE_ADDR		(0x4C000000)
#else
#define CLK_BASE_ADDR		(0x40000000)
#endif
#define oLOCKTIME0		(0x00)
#define oLOCKTIME		(0x00)
#define oLOCKTIME1		(0x04)

#if defined (CONFIG_S3C2413)
#define oMPLLCON		(0x04)
#else
#define oMPLLCON		(0x10)
#endif

#if defined(CONFIG_S3C2413)
#define oCLKSRC			(0x1C) /*added for 2413*/
#define oCLKDIV			(0x14) /*added for 2413*/
#elif defined(CONFIG_S3C2460x)
#define oCLKSRC			(0x20) /*added for 2460*/
#define oCLKDIV			(0x24) /*added for 2460*/
#else
#define oCLKDIV			(0x28) /**/
#endif

#define SROM_BASE_ADDR		(0x40C20000)
#define oSROMBW			(0x00)
#define oSROMBC0		(0x04)
#define oSROMBC1		(0x08)
#define oSROMBC2		(0x0C)

#if defined (CONFIG_S3C2413)
#define SDRAM1_BASE_ADDR	(0x48000000)
#define oBANKCFG		(0x00)
#define oBANKCON1		(0x04)
#define oBANKCON2		(0x08)
#define oBANKCON3		(0x0C)
#define oREFRESH		(0x10)
#define oTIMEOUT		(0x14)
#else
#define SDRAM1_BASE_ADDR	(0x40C40000)
#define oP1BANKCFG		(0x00)
#define oP1BANKCON		(0x04)
#define oP1REFRESH		(0x08)
#define oP1TIMEOUT		(0x0C)
#endif

#if defined (CONFIG_S3C2460x)
#define SDRAM2_BASE_ADDR	(0x40C80000)
#else
#define SDRAM2_BASE_ADDR	(0x40C60000)
#endif

#define oP2BANKCFG		(0x00)
#define oP2BANKCON		(0x04)
#define oP2REFRESH		(0x08)
#define oP2TIMEOUT		(0x0C)

#define UART0_BASE_ADDR		(0x44400000)
#define oULCON			(0x00)
#define oUCON			(0x04)
#define oUFCON			(0x08)
#define oUMCON			(0x0C)
#define oUTRSTAT		(0x10)
#define oUERSTAT		(0x14)
#define oUFSTAT			(0x18)
#define oUMSTAT			(0x1C)
#define oUTXH			(0x20)
#define oURXH			(0x24)
#define oUBRDIV			(0x28)

#endif /* _HEAD_REGS_H_ */