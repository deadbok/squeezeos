/* linux/include/asm/arch-s3c2413/regs-rtc.h
 *
 * Copyright (c) 2003 Simtec Electronics <linux@simtec.co.uk>
 *		      http://www.simtec.co.uk/products/SWLINUX/
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * S3C2413 Internal RTC register definition
 *
 *  Changelog:
 *    19-06-2003     BJD     Created file
 *    12-03-2004     BJD     Updated include protection
*/

#ifndef __ASM_ARCH_REGS_RTC_H
#define __ASM_ARCH_REGS_RTC_H __FILE__

#define S3C2413_RTCREG(x) ((x) + S3C2413_VA_RTC)

#define S3C2413_RTCCON	      S3C2413_RTCREG(0x40)
#define S3C2413_RTCCON_RTCEN  (1<<0)
#define S3C2413_RTCCON_CLKSEL (1<<1)
#define S3C2413_RTCCON_CNTSEL (1<<2)
#define S3C2413_RTCCON_CLKRST (1<<3)

#define S3C2413_TICNT	      S3C2413_RTCREG(0x44)
#define S3C2413_TICNT_ENABLE  (1<<7)
#define S3C2413_TICNT1	      S3C2413_RTCREG(0x4c)

#define S3C2413_RTCALM	      S3C2413_RTCREG(0x50)
#define S3C2413_RTCALM_ALMEN  (1<<6)
#define S3C2413_RTCALM_YEAREN (1<<5)
#define S3C2413_RTCALM_MONEN  (1<<4)
#define S3C2413_RTCALM_DAYEN  (1<<3)
#define S3C2413_RTCALM_HOUREN (1<<2)
#define S3C2413_RTCALM_MINEN  (1<<1)
#define S3C2413_RTCALM_SECEN  (1<<0)

#define S3C2413_RTCALM_ALL \
  S3C2413_RTCALM_ALMEN | S3C2413_RTCALM_YEAREN | S3C2413_RTCALM_MONEN |\
  S3C2413_RTCALM_DAYEN | S3C2413_RTCALM_HOUREN | S3C2413_RTCALM_MINEN |\
  S3C2413_RTCALM_SECEN


#define S3C2413_ALMSEC	      S3C2413_RTCREG(0x54)
#define S3C2413_ALMMIN	      S3C2413_RTCREG(0x58)
#define S3C2413_ALMHOUR	      S3C2413_RTCREG(0x5c)

#define S3C2413_ALMDATE	      S3C2413_RTCREG(0x60)
#define S3C2413_ALMMON	      S3C2413_RTCREG(0x64)
#define S3C2413_ALMYEAR	      S3C2413_RTCREG(0x68)

#define S3C2413_RTCRST	      S3C2413_RTCREG(0x6c)

#define S3C2413_RTCSEC	      S3C2413_RTCREG(0x70)
#define S3C2413_RTCMIN	      S3C2413_RTCREG(0x74)
#define S3C2413_RTCHOUR	      S3C2413_RTCREG(0x78)
#define S3C2413_RTCDATE	      S3C2413_RTCREG(0x7c)
#define S3C2413_RTCDAY	      S3C2413_RTCREG(0x80)
#define S3C2413_RTCMON	      S3C2413_RTCREG(0x84)
#define S3C2413_RTCYEAR	      S3C2413_RTCREG(0x88)


#endif /* __ASM_ARCH_REGS_RTC_H */