/*
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/ld9040.h>
#include "u1-panel.h"


static const unsigned short SEQ_SM2_ELVSS_44[] = {
	0xB2, 0x15,

	DATA_ONLY, 0x15,
	DATA_ONLY, 0x15,
	DATA_ONLY, 0x15,
	ENDDEF, 0x00
};

static const unsigned short SEQ_SM2_ELVSS_37[] = {
	0xB2, 0x1C,

	DATA_ONLY, 0x1C,
	DATA_ONLY, 0x1C,
	DATA_ONLY, 0x1C,
	ENDDEF, 0x00
};

static const unsigned short SEQ_SM2_ELVSS_34[] = {
	0xB2, 0x1F,

	DATA_ONLY, 0x1F,
	DATA_ONLY, 0x1F,
	DATA_ONLY, 0x1F,
	ENDDEF, 0x00
};

static const unsigned short SEQ_SM2_ELVSS_30[] = {
	0xB2, 0x23,

	DATA_ONLY, 0x23,
	DATA_ONLY, 0x23,
	DATA_ONLY, 0x23,
	ENDDEF, 0x00
};

static const unsigned short *SEQ_SM2_ELVSS_set[] = {
	SEQ_SM2_ELVSS_30,
	SEQ_SM2_ELVSS_34,
	SEQ_SM2_ELVSS_37,
	SEQ_SM2_ELVSS_44,
};


static const unsigned short SEQ_PWR_CTRL_SM2_A2[] = {
	0xF4, 0x0A,

	DATA_ONLY, 0xA7,
	DATA_ONLY, 0x25,
	DATA_ONLY, 0x6A,
	DATA_ONLY, 0x44,
	DATA_ONLY, 0x02,
	ENDDEF, 0x00
};


/* LD9040, 4.27", SM2 A2 Panel Gamma Data */
static const unsigned short ld9040_sm2_a2_22_300[] = {
	0xF9, 0x0C,
	DATA_ONLY, 0xA9,
	DATA_ONLY, 0xAF,
	DATA_ONLY, 0xA9,
	DATA_ONLY, 0xBC,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0xAA,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xAB,
	DATA_ONLY, 0xAE,
	DATA_ONLY, 0xA6,
	DATA_ONLY, 0xBB,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0xC8,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xB5,
	DATA_ONLY, 0xB1,
	DATA_ONLY, 0xA7,
	DATA_ONLY, 0xBC,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0xCC,
	0xFB, 0x02,
	DATA_ONLY, 0x5A,
	ENDDEF, 0x00
};

static const unsigned short ld9040_sm2_a2_22_290[] = {
	0xF9, 0x0C,
	DATA_ONLY, 0xA6,
	DATA_ONLY, 0xB0,
	DATA_ONLY, 0xAA,
	DATA_ONLY, 0xBD,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0xA9,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xAA,
	DATA_ONLY, 0xAF,
	DATA_ONLY, 0xA7,
	DATA_ONLY, 0xBD,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0xC6,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xB5,
	DATA_ONLY, 0xB4,
	DATA_ONLY, 0xA8,
	DATA_ONLY, 0xBE,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0xCA,
	0xFB, 0x02,
	DATA_ONLY, 0x5A,
	ENDDEF, 0x00
};

static const unsigned short ld9040_sm2_a2_22_280[] = {
	0xF9, 0x0C,
	DATA_ONLY, 0xA7,
	DATA_ONLY, 0xB1,
	DATA_ONLY, 0xAA,
	DATA_ONLY, 0xBD,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0xA6,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xAB,
	DATA_ONLY, 0xAF,
	DATA_ONLY, 0xA7,
	DATA_ONLY, 0xBE,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0xC3,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xB6,
	DATA_ONLY, 0xB4,
	DATA_ONLY, 0xA8,
	DATA_ONLY, 0xBE,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0xC7,
	0xFB, 0x02,
	DATA_ONLY, 0x5A,
	ENDDEF, 0x00
};

static const unsigned short ld9040_sm2_a2_22_270[] = {
	0xF9, 0x0C,
	DATA_ONLY, 0xA8,
	DATA_ONLY, 0xB0,
	DATA_ONLY, 0xAA,
	DATA_ONLY, 0xBF,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0xA3,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xAB,
	DATA_ONLY, 0xAF,
	DATA_ONLY, 0xA8,
	DATA_ONLY, 0xBF,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0xC0,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xB6,
	DATA_ONLY, 0xB4,
	DATA_ONLY, 0xA8,
	DATA_ONLY, 0xBF,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0xC4,
	0xFB, 0x02,
	DATA_ONLY, 0x5A,
	ENDDEF, 0x00
};

static const unsigned short ld9040_sm2_a2_22_260[] = {
	0xF9, 0x0C,
	DATA_ONLY, 0xA7,
	DATA_ONLY, 0xB2,
	DATA_ONLY, 0xAA,
	DATA_ONLY, 0xBE,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0xA1,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xA9,
	DATA_ONLY, 0xB1,
	DATA_ONLY, 0xA7,
	DATA_ONLY, 0xBF,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0xBD,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xB5,
	DATA_ONLY, 0xB6,
	DATA_ONLY, 0xA8,
	DATA_ONLY, 0xBF,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0xC1,
	0xFB, 0x02,
	DATA_ONLY, 0x5A,
	ENDDEF, 0x00
};

static const unsigned short ld9040_sm2_a2_22_250[] = {
	0xF9, 0x0C,
	DATA_ONLY, 0xA6,
	DATA_ONLY, 0xB2,
	DATA_ONLY, 0xAB,
	DATA_ONLY, 0xC0,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x9E,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xA9,
	DATA_ONLY, 0xB0,
	DATA_ONLY, 0xA9,
	DATA_ONLY, 0xC0,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0xBA,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xB4,
	DATA_ONLY, 0xB6,
	DATA_ONLY, 0xA9,
	DATA_ONLY, 0xC0,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0xBE,
	0xFB, 0x02,
	DATA_ONLY, 0x5A,
	ENDDEF, 0x00
};

static const unsigned short ld9040_sm2_a2_22_240[] = {
	0xF9, 0x0C,
	DATA_ONLY, 0xA7,
	DATA_ONLY, 0xB3,
	DATA_ONLY, 0xAA,
	DATA_ONLY, 0xC0,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x9C,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xA9,
	DATA_ONLY, 0xB1,
	DATA_ONLY, 0xA9,
	DATA_ONLY, 0xC0,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0xB7,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xB5,
	DATA_ONLY, 0xB6,
	DATA_ONLY, 0xA9,
	DATA_ONLY, 0xC0,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0xBB,
	0xFB, 0x02,
	DATA_ONLY, 0x5A,
	ENDDEF, 0x00
};

static const unsigned short ld9040_sm2_a2_22_230[] = {
	0xF9, 0x0C,
	DATA_ONLY, 0xA7,
	DATA_ONLY, 0xB3,
	DATA_ONLY, 0xAB,
	DATA_ONLY, 0xC0,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x99,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xA8,
	DATA_ONLY, 0xB2,
	DATA_ONLY, 0xA9,
	DATA_ONLY, 0xC1,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0xB4,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xB5,
	DATA_ONLY, 0xB7,
	DATA_ONLY, 0xAA,
	DATA_ONLY, 0xC1,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0xB7,
	0xFB, 0x02,
	DATA_ONLY, 0x5A,
	ENDDEF, 0x00
};

static const unsigned short ld9040_sm2_a2_22_220[] = {
	0xF9, 0x0C,
	DATA_ONLY, 0xA7,
	DATA_ONLY, 0xB3,
	DATA_ONLY, 0xAD,
	DATA_ONLY, 0xC1,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x96,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xA7,
	DATA_ONLY, 0xB2,
	DATA_ONLY, 0xAA,
	DATA_ONLY, 0xC2,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0xB0,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xB4,
	DATA_ONLY, 0xB6,
	DATA_ONLY, 0xAB,
	DATA_ONLY, 0xC3,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0xB4,
	0xFB, 0x02,
	DATA_ONLY, 0x5A,
	ENDDEF, 0x00
};

static const unsigned short ld9040_sm2_a2_22_210[] = {
	0xF9, 0x0C,
	DATA_ONLY, 0xA6,
	DATA_ONLY, 0xB3,
	DATA_ONLY, 0xAD,
	DATA_ONLY, 0xC2,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x94,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xA7,
	DATA_ONLY, 0xB2,
	DATA_ONLY, 0xAB,
	DATA_ONLY, 0xC2,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0xAD,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xB3,
	DATA_ONLY, 0xB8,
	DATA_ONLY, 0xAB,
	DATA_ONLY, 0xC3,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0xB1,
	0xFB, 0x02,
	DATA_ONLY, 0x5A,
	ENDDEF, 0x00
};

static const unsigned short ld9040_sm2_a2_22_200[] = {
	0xF9, 0x0C,
	DATA_ONLY, 0xA7,
	DATA_ONLY, 0xB3,
	DATA_ONLY, 0xAD,
	DATA_ONLY, 0xC2,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x91,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xA7,
	DATA_ONLY, 0xB3,
	DATA_ONLY, 0xAA,
	DATA_ONLY, 0xC3,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0xAB,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xB4,
	DATA_ONLY, 0xB9,
	DATA_ONLY, 0xAB,
	DATA_ONLY, 0xC3,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0xAE,
	0xFB, 0x02,
	DATA_ONLY, 0x5A,
	ENDDEF, 0x00
};

static const unsigned short ld9040_sm2_a2_22_190[] = {
	0xF9, 0x0C,
	DATA_ONLY, 0xA6,
	DATA_ONLY, 0xB4,
	DATA_ONLY, 0xAD,
	DATA_ONLY, 0xC3,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x8E,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xA6,
	DATA_ONLY, 0xB3,
	DATA_ONLY, 0xAB,
	DATA_ONLY, 0xC4,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0xA8,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xB2,
	DATA_ONLY, 0xB9,
	DATA_ONLY, 0xAD,
	DATA_ONLY, 0xC3,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0xAB,
	0xFB, 0x02,
	DATA_ONLY, 0x5A,
	ENDDEF, 0x00
};

static const unsigned short ld9040_sm2_a2_22_180[] = {
	0xF9, 0x0C,
	DATA_ONLY, 0xA6,
	DATA_ONLY, 0xB4,
	DATA_ONLY, 0xAE,
	DATA_ONLY, 0xC4,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x8B,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xA5,
	DATA_ONLY, 0xB5,
	DATA_ONLY, 0xAB,
	DATA_ONLY, 0xC5,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0xA4,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xB2,
	DATA_ONLY, 0xB9,
	DATA_ONLY, 0xAD,
	DATA_ONLY, 0xC5,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0xA7,
	0xFB, 0x02,
	DATA_ONLY, 0x5A,
	ENDDEF, 0x00
};

static const unsigned short ld9040_sm2_a2_22_170[] = {
	0xF9, 0x0C,
	DATA_ONLY, 0xA5,
	DATA_ONLY, 0xB4,
	DATA_ONLY, 0xAF,
	DATA_ONLY, 0xC4,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x89,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xA3,
	DATA_ONLY, 0xB6,
	DATA_ONLY, 0xAC,
	DATA_ONLY, 0xC6,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0xA1,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xB1,
	DATA_ONLY, 0xB9,
	DATA_ONLY, 0xAF,
	DATA_ONLY, 0xC5,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0xA4,
	0xFB, 0x02,
	DATA_ONLY, 0x5A,
	ENDDEF, 0x00
};

static const unsigned short ld9040_sm2_a2_22_160[] = {
	0xF9, 0x0C,
	DATA_ONLY, 0xA5,
	DATA_ONLY, 0xB3,
	DATA_ONLY, 0xB1,
	DATA_ONLY, 0xC4,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x85,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xA2,
	DATA_ONLY, 0xB5,
	DATA_ONLY, 0xAD,
	DATA_ONLY, 0xC6,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x9D,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xB1,
	DATA_ONLY, 0xB9,
	DATA_ONLY, 0xB0,
	DATA_ONLY, 0xC6,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x9F,
	0xFB, 0x02,
	DATA_ONLY, 0x5A,
	ENDDEF, 0x00
};

static const unsigned short ld9040_sm2_a2_22_150[] = {
	0xF9, 0x0C,
	DATA_ONLY, 0xA6,
	DATA_ONLY, 0xB3,
	DATA_ONLY, 0xB0,
	DATA_ONLY, 0xC5,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x82,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xA1,
	DATA_ONLY, 0xB6,
	DATA_ONLY, 0xAD,
	DATA_ONLY, 0xC8,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x99,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xB2,
	DATA_ONLY, 0xBA,
	DATA_ONLY, 0xAF,
	DATA_ONLY, 0xC7,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x9B,
	0xFB, 0x02,
	DATA_ONLY, 0x5A,
	ENDDEF, 0x00
};

static const unsigned short ld9040_sm2_a2_22_140[] = {
	0xF9, 0x0C,
	DATA_ONLY, 0xA5,
	DATA_ONLY, 0xB5,
	DATA_ONLY, 0xB1,
	DATA_ONLY, 0xC5,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x7F,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xA0,
	DATA_ONLY, 0xB7,
	DATA_ONLY, 0xAE,
	DATA_ONLY, 0xC8,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x95,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xB0,
	DATA_ONLY, 0xBB,
	DATA_ONLY, 0xB1,
	DATA_ONLY, 0xC8,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x97,
	0xFB, 0x02,
	DATA_ONLY, 0x5A,
	ENDDEF, 0x00
};

static const unsigned short ld9040_sm2_a2_22_130[] = {
	0xF9, 0x0C,
	DATA_ONLY, 0xA5,
	DATA_ONLY, 0xB5,
	DATA_ONLY, 0xB1,
	DATA_ONLY, 0xC5,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x7C,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0x9F,
	DATA_ONLY, 0xB7,
	DATA_ONLY, 0xAF,
	DATA_ONLY, 0xC9,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x91,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xB0,
	DATA_ONLY, 0xBA,
	DATA_ONLY, 0xB2,
	DATA_ONLY, 0xC8,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x93,
	0xFB, 0x02,
	DATA_ONLY, 0x5A,
	ENDDEF, 0x00
};

static const unsigned short ld9040_sm2_a2_22_120[] = {
	0xF9, 0x0C,
	DATA_ONLY, 0xA4,
	DATA_ONLY, 0xB6,
	DATA_ONLY, 0xB2,
	DATA_ONLY, 0xC7,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x77,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0x9D,
	DATA_ONLY, 0xB8,
	DATA_ONLY, 0xAF,
	DATA_ONLY, 0xCA,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x8C,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xAF,
	DATA_ONLY, 0xBA,
	DATA_ONLY, 0xB3,
	DATA_ONLY, 0xCA,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x8E,
	0xFB, 0x02,
	DATA_ONLY, 0x5A,
	ENDDEF, 0x00
};

static const unsigned short ld9040_sm2_a2_22_110[] = {
	0xF9, 0x0C,
	DATA_ONLY, 0xA4,
	DATA_ONLY, 0xB5,
	DATA_ONLY, 0xB3,
	DATA_ONLY, 0xC8,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x73,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0x9C,
	DATA_ONLY, 0xB7,
	DATA_ONLY, 0xB1,
	DATA_ONLY, 0xCA,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x88,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xB0,
	DATA_ONLY, 0xBA,
	DATA_ONLY, 0xB4,
	DATA_ONLY, 0xCB,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x89,
	0xFB, 0x02,
	DATA_ONLY, 0x5A,
	ENDDEF, 0x00
};

static const unsigned short ld9040_sm2_a2_22_100[] = {
	0xF9, 0x0C,
	DATA_ONLY, 0xA4,
	DATA_ONLY, 0xB6,
	DATA_ONLY, 0xB3,
	DATA_ONLY, 0xC9,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x70,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0x9B,
	DATA_ONLY, 0xB7,
	DATA_ONLY, 0xB2,
	DATA_ONLY, 0xCA,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x85,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xB0,
	DATA_ONLY, 0xBA,
	DATA_ONLY, 0xB4,
	DATA_ONLY, 0xCB,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x86,
	0xFB, 0x02,
	DATA_ONLY, 0x5A,
	ENDDEF, 0x00
};

static const unsigned short ld9040_sm2_a2_22_90[] = {
	0xF9, 0x0C,
	DATA_ONLY, 0xA3,
	DATA_ONLY, 0xB7,
	DATA_ONLY, 0xB2,
	DATA_ONLY, 0xCC,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x6B,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0x97,
	DATA_ONLY, 0xB8,
	DATA_ONLY, 0xB2,
	DATA_ONLY, 0xCD,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x7F,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xAF,
	DATA_ONLY, 0xBA,
	DATA_ONLY, 0xB5,
	DATA_ONLY, 0xCE,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x80,
	0xFB, 0x02,
	DATA_ONLY, 0x5A,
	ENDDEF, 0x00
};

static const unsigned short ld9040_sm2_a2_22_80[] = {
	0xF9, 0x0C,
	DATA_ONLY, 0xA2,
	DATA_ONLY, 0xB7,
	DATA_ONLY, 0xB3,
	DATA_ONLY, 0xCC,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x67,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0x95,
	DATA_ONLY, 0xB8,
	DATA_ONLY, 0xB3,
	DATA_ONLY, 0xCE,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x7A,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xB1,
	DATA_ONLY, 0xB8,
	DATA_ONLY, 0xB7,
	DATA_ONLY, 0xCE,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x7B,
	0xFB, 0x02,
	DATA_ONLY, 0x5A,
	ENDDEF, 0x00
};

static const unsigned short ld9040_sm2_a2_22_70[] = {
	0xF9, 0x0C,
	DATA_ONLY, 0xA2,
	DATA_ONLY, 0xB6,
	DATA_ONLY, 0xB6,
	DATA_ONLY, 0xCC,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x62,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0x94,
	DATA_ONLY, 0xB7,
	DATA_ONLY, 0xB5,
	DATA_ONLY, 0xCE,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x74,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xB3,
	DATA_ONLY, 0xB6,
	DATA_ONLY, 0xBA,
	DATA_ONLY, 0xCF,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x75,
	0xFB, 0x02,
	DATA_ONLY, 0x5A,
	ENDDEF, 0x00
};

static const unsigned short ld9040_sm2_a2_22_60[] = {
	0xF9, 0x0C,
	DATA_ONLY, 0xA0,
	DATA_ONLY, 0xB5,
	DATA_ONLY, 0xB7,
	DATA_ONLY, 0xCE,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x5C,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0x8E,
	DATA_ONLY, 0xB6,
	DATA_ONLY, 0xB6,
	DATA_ONLY, 0xCF,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x6E,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xB4,
	DATA_ONLY, 0xB4,
	DATA_ONLY, 0xBC,
	DATA_ONLY, 0xD1,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x6E,
	0xFB, 0x02,
	DATA_ONLY, 0x5A,
	ENDDEF, 0x00
};

static const unsigned short ld9040_sm2_a2_22_50[] = {
	0xF9, 0x0C,
	DATA_ONLY, 0xA0,
	DATA_ONLY, 0xB4,
	DATA_ONLY, 0xB8,
	DATA_ONLY, 0xCE,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x57,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0x8C,
	DATA_ONLY, 0xB5,
	DATA_ONLY, 0xB8,
	DATA_ONLY, 0xD0,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x68,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xB6,
	DATA_ONLY, 0xB0,
	DATA_ONLY, 0xBF,
	DATA_ONLY, 0xD1,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x68,
	0xFB, 0x02,
	DATA_ONLY, 0x5A,
	ENDDEF, 0x00
};

static const unsigned short ld9040_sm2_a2_22_40[] = {
	0xF9, 0x0C,
	DATA_ONLY, 0x9D,
	DATA_ONLY, 0xB4,
	DATA_ONLY, 0xB9,
	DATA_ONLY, 0xCF,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x50,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0x88,
	DATA_ONLY, 0xB1,
	DATA_ONLY, 0xBA,
	DATA_ONLY, 0xD1,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x60,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xB9,
	DATA_ONLY, 0xAE,
	DATA_ONLY, 0xC1,
	DATA_ONLY, 0xD3,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x60,
	0xFB, 0x02,
	DATA_ONLY, 0x5A,
	ENDDEF, 0x00
};

static const unsigned short ld9040_sm2_a2_22_30_dimming[] = {
	0xF9, 0x0C,
	DATA_ONLY, 0x91,
	DATA_ONLY, 0xB4,
	DATA_ONLY, 0xB8,
	DATA_ONLY, 0xD1,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x48,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0x7A,
	DATA_ONLY, 0xAD,
	DATA_ONLY, 0xBD,
	DATA_ONLY, 0xD4,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x57,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xBB,
	DATA_ONLY, 0xAE,
	DATA_ONLY, 0xC3,
	DATA_ONLY, 0xD5,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x56,
	0xFB, 0x02,
	DATA_ONLY, 0x5A,
	ENDDEF, 0x00
};

static const unsigned short ld9040_sm2_a2_19_300[] = {
	0xF9, 0x0C,
	DATA_ONLY, 0xB2,
	DATA_ONLY, 0xB4,
	DATA_ONLY, 0xA7,
	DATA_ONLY, 0xC4,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0xA9,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xB3,
	DATA_ONLY, 0xB4,
	DATA_ONLY, 0xA6,
	DATA_ONLY, 0xC3,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0xC8,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xB8,
	DATA_ONLY, 0xB6,
	DATA_ONLY, 0xA7,
	DATA_ONLY, 0xC4,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0xCC,
	0xFB, 0x02,
	DATA_ONLY, 0x5A,
	ENDDEF, 0x00
};

static const unsigned short ld9040_sm2_a2_19_290[] = {
	0xF9, 0x0C,
	DATA_ONLY, 0xB4,
	DATA_ONLY, 0xB5,
	DATA_ONLY, 0xA7,
	DATA_ONLY, 0xC5,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0xA5,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xB4,
	DATA_ONLY, 0xB5,
	DATA_ONLY, 0xA6,
	DATA_ONLY, 0xC4,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0xC4,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xB9,
	DATA_ONLY, 0xB6,
	DATA_ONLY, 0xA8,
	DATA_ONLY, 0xC4,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0xCA,
	0xFB, 0x02,
	DATA_ONLY, 0x5A,
	ENDDEF, 0x00
};

static const unsigned short ld9040_sm2_a2_19_280[] = {
	0xF9, 0x0C,
	DATA_ONLY, 0xB4,
	DATA_ONLY, 0xB4,
	DATA_ONLY, 0xA8,
	DATA_ONLY, 0xC6,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0xA2,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xB5,
	DATA_ONLY, 0xB5,
	DATA_ONLY, 0xA6,
	DATA_ONLY, 0xC4,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0xC1,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xB9,
	DATA_ONLY, 0xB5,
	DATA_ONLY, 0xA8,
	DATA_ONLY, 0xC4,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0xC8,
	0xFB, 0x02,
	DATA_ONLY, 0x5A,
	ENDDEF, 0x00
};

static const unsigned short ld9040_sm2_a2_19_270[] = {
	0xF9, 0x0C,
	DATA_ONLY, 0xB3,
	DATA_ONLY, 0xB4,
	DATA_ONLY, 0xA7,
	DATA_ONLY, 0xC6,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0xA0,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xB5,
	DATA_ONLY, 0xB6,
	DATA_ONLY, 0xA6,
	DATA_ONLY, 0xC5,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0xBE,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xB9,
	DATA_ONLY, 0xB7,
	DATA_ONLY, 0xA7,
	DATA_ONLY, 0xC4,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0xC5,
	0xFB, 0x02,
	DATA_ONLY, 0x5A,
	ENDDEF, 0x00
};

static const unsigned short ld9040_sm2_a2_19_260[] = {
	0xF9, 0x0C,
	DATA_ONLY, 0xB4,
	DATA_ONLY, 0xB4,
	DATA_ONLY, 0xA8,
	DATA_ONLY, 0xC6,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x9D,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xB5,
	DATA_ONLY, 0xB5,
	DATA_ONLY, 0xA8,
	DATA_ONLY, 0xC4,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0xBB,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xBA,
	DATA_ONLY, 0xB7,
	DATA_ONLY, 0xA9,
	DATA_ONLY, 0xC4,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0xC1,
	0xFB, 0x02,
	DATA_ONLY, 0x5A,
	ENDDEF, 0x00
};

static const unsigned short ld9040_sm2_a2_19_250[] = {
	0xF9, 0x0C,
	DATA_ONLY, 0xB5,
	DATA_ONLY, 0xB5,
	DATA_ONLY, 0xA8,
	DATA_ONLY, 0xC7,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x9A,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xB5,
	DATA_ONLY, 0xB5,
	DATA_ONLY, 0xA7,
	DATA_ONLY, 0xC6,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0xB8,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xBA,
	DATA_ONLY, 0xB8,
	DATA_ONLY, 0xA9,
	DATA_ONLY, 0xC5,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0xBD,
	0xFB, 0x02,
	DATA_ONLY, 0x5A,
	ENDDEF, 0x00
};

static const unsigned short ld9040_sm2_a2_19_240[] = {
	0xF9, 0x0C,
	DATA_ONLY, 0xB4,
	DATA_ONLY, 0xB5,
	DATA_ONLY, 0xA8,
	DATA_ONLY, 0xC8,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x97,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xB5,
	DATA_ONLY, 0xB6,
	DATA_ONLY, 0xA8,
	DATA_ONLY, 0xC6,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0xB4,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xBA,
	DATA_ONLY, 0xB8,
	DATA_ONLY, 0xA9,
	DATA_ONLY, 0xC5,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0xBA,
	0xFB, 0x02,
	DATA_ONLY, 0x5A,
	ENDDEF, 0x00
};

static const unsigned short ld9040_sm2_a2_19_230[] = {
	0xF9, 0x0C,
	DATA_ONLY, 0xB3,
	DATA_ONLY, 0xB6,
	DATA_ONLY, 0xA9,
	DATA_ONLY, 0xC7,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x95,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xB5,
	DATA_ONLY, 0xB6,
	DATA_ONLY, 0xA9,
	DATA_ONLY, 0xC6,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0xB1,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xB9,
	DATA_ONLY, 0xB9,
	DATA_ONLY, 0xAB,
	DATA_ONLY, 0xC4,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0xB7,
	0xFB, 0x02,
	DATA_ONLY, 0x5A,
	ENDDEF, 0x00
};

static const unsigned short ld9040_sm2_a2_19_220[] = {
	0xF9, 0x0C,
	DATA_ONLY, 0xB5,
	DATA_ONLY, 0xB6,
	DATA_ONLY, 0xAA,
	DATA_ONLY, 0xC7,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x91,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xB6,
	DATA_ONLY, 0xB5,
	DATA_ONLY, 0xA9,
	DATA_ONLY, 0xC7,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0xAE,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xB4,
	DATA_ONLY, 0xB8,
	DATA_ONLY, 0xAC,
	DATA_ONLY, 0xC5,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0xB3,
	0xFB, 0x02,
	DATA_ONLY, 0x5A,
	ENDDEF, 0x00
};

static const unsigned short ld9040_sm2_a2_19_210[] = {
	0xF9, 0x0C,
	DATA_ONLY, 0xB5,
	DATA_ONLY, 0xB7,
	DATA_ONLY, 0xAA,
	DATA_ONLY, 0xC7,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x8E,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xB7,
	DATA_ONLY, 0xB5,
	DATA_ONLY, 0xAA,
	DATA_ONLY, 0xC6,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0xAB,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xBA,
	DATA_ONLY, 0xB8,
	DATA_ONLY, 0xAD,
	DATA_ONLY, 0xC5,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0xAF,
	0xFB, 0x02,
	DATA_ONLY, 0x5A,
	ENDDEF, 0x00
};

static const unsigned short ld9040_sm2_a2_19_200[] = {
	0xF9, 0x0C,
	DATA_ONLY, 0xB5,
	DATA_ONLY, 0xB7,
	DATA_ONLY, 0xAA,
	DATA_ONLY, 0xC9,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x8B,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xB7,
	DATA_ONLY, 0xB6,
	DATA_ONLY, 0xAA,
	DATA_ONLY, 0xC7,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0xA7,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xBA,
	DATA_ONLY, 0xB8,
	DATA_ONLY, 0xAC,
	DATA_ONLY, 0xC7,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0xAB,
	0xFB, 0x02,
	DATA_ONLY, 0x5A,
	ENDDEF, 0x00
};

static const unsigned short ld9040_sm2_a2_19_190[] = {
	0xF9, 0x0C,
	DATA_ONLY, 0xB4,
	DATA_ONLY, 0xB6,
	DATA_ONLY, 0xAB,
	DATA_ONLY, 0xC9,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x88,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xB7,
	DATA_ONLY, 0xB6,
	DATA_ONLY, 0xAA,
	DATA_ONLY, 0xC8,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0xA3,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xBB,
	DATA_ONLY, 0xB7,
	DATA_ONLY, 0xAD,
	DATA_ONLY, 0xC7,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0xA8,
	0xFB, 0x02,
	DATA_ONLY, 0x5A,
	ENDDEF, 0x00
};

static const unsigned short ld9040_sm2_a2_19_180[] = {
	0xF9, 0x0C,
	DATA_ONLY, 0xB3,
	DATA_ONLY, 0xB6,
	DATA_ONLY, 0xAC,
	DATA_ONLY, 0xC9,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x85,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xB7,
	DATA_ONLY, 0xB6,
	DATA_ONLY, 0xAA,
	DATA_ONLY, 0xC9,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x9F,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xBB,
	DATA_ONLY, 0xB9,
	DATA_ONLY, 0xAD,
	DATA_ONLY, 0xC7,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0xA4,
	0xFB, 0x02,
	DATA_ONLY, 0x5A,
	ENDDEF, 0x00
};

static const unsigned short ld9040_sm2_a2_19_170[] = {
	0xF9, 0x0C,
	DATA_ONLY, 0xB3,
	DATA_ONLY, 0xB7,
	DATA_ONLY, 0xAB,
	DATA_ONLY, 0xC9,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x82,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xB6,
	DATA_ONLY, 0xB7,
	DATA_ONLY, 0xAA,
	DATA_ONLY, 0xCA,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x9B,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xBB,
	DATA_ONLY, 0xBB,
	DATA_ONLY, 0xAC,
	DATA_ONLY, 0xC8,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0xA0,
	0xFB, 0x02,
	DATA_ONLY, 0x5A,
	ENDDEF, 0x00
};

static const unsigned short ld9040_sm2_a2_19_160[] = {
	0xF9, 0x0C,
	DATA_ONLY, 0xB3,
	DATA_ONLY, 0xB6,
	DATA_ONLY, 0xAB,
	DATA_ONLY, 0xCA,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x7F,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xB7,
	DATA_ONLY, 0xB7,
	DATA_ONLY, 0xAB,
	DATA_ONLY, 0xCA,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x97,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xBC,
	DATA_ONLY, 0xBA,
	DATA_ONLY, 0xAC,
	DATA_ONLY, 0xC9,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x9C,
	0xFB, 0x02,
	DATA_ONLY, 0x5A,
	ENDDEF, 0x00
};

static const unsigned short ld9040_sm2_a2_19_150[] = {
	0xF9, 0x0C,
	DATA_ONLY, 0xB4,
	DATA_ONLY, 0xB7,
	DATA_ONLY, 0xAB,
	DATA_ONLY, 0xCA,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x7B,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xB7,
	DATA_ONLY, 0xB7,
	DATA_ONLY, 0xAB,
	DATA_ONLY, 0xCB,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x93,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xBD,
	DATA_ONLY, 0xBB,
	DATA_ONLY, 0xAD,
	DATA_ONLY, 0xC9,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x97,
	0xFB, 0x02,
	DATA_ONLY, 0x5A,
	ENDDEF, 0x00
};

static const unsigned short ld9040_sm2_a2_19_140[] = {
	0xF9, 0x0C,
	DATA_ONLY, 0xB3,
	DATA_ONLY, 0xB8,
	DATA_ONLY, 0xAD,
	DATA_ONLY, 0xCA,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x77,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xB7,
	DATA_ONLY, 0xB7,
	DATA_ONLY, 0xAC,
	DATA_ONLY, 0xCB,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x8F,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xBC,
	DATA_ONLY, 0xBB,
	DATA_ONLY, 0xAF,
	DATA_ONLY, 0xCA,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x92,
	0xFB, 0x02,
	DATA_ONLY, 0x5A,
	ENDDEF, 0x00
};

static const unsigned short ld9040_sm2_a2_19_130[] = {
	0xF9, 0x0C,
	DATA_ONLY, 0xB3,
	DATA_ONLY, 0xB8,
	DATA_ONLY, 0xAD,
	DATA_ONLY, 0xCB,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x73,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xB6,
	DATA_ONLY, 0xB8,
	DATA_ONLY, 0xAC,
	DATA_ONLY, 0xCB,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x8B,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xBC,
	DATA_ONLY, 0xBB,
	DATA_ONLY, 0xB0,
	DATA_ONLY, 0xCB,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x8D,
	0xFB, 0x02,
	DATA_ONLY, 0x5A,
	ENDDEF, 0x00
};

static const unsigned short ld9040_sm2_a2_19_120[] = {
	0xF9, 0x0C,
	DATA_ONLY, 0xB2,
	DATA_ONLY, 0xB8,
	DATA_ONLY, 0xAD,
	DATA_ONLY, 0xCD,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x6F,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xB6,
	DATA_ONLY, 0xB9,
	DATA_ONLY, 0xAC,
	DATA_ONLY, 0xCC,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x86,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xBC,
	DATA_ONLY, 0xBB,
	DATA_ONLY, 0xAF,
	DATA_ONLY, 0xCC,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x89,
	0xFB, 0x02,
	DATA_ONLY, 0x5A,
	ENDDEF, 0x00
};

static const unsigned short ld9040_sm2_a2_19_110[] = {
	0xF9, 0x0C,
	DATA_ONLY, 0xB3,
	DATA_ONLY, 0xB7,
	DATA_ONLY, 0xAD,
	DATA_ONLY, 0xCD,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x6B,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xB6,
	DATA_ONLY, 0xB8,
	DATA_ONLY, 0xAD,
	DATA_ONLY, 0xCD,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x81,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xBF,
	DATA_ONLY, 0xBB,
	DATA_ONLY, 0xAF,
	DATA_ONLY, 0xCC,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x84,
	0xFB, 0x02,
	DATA_ONLY, 0x5A,
	ENDDEF, 0x00
};

static const unsigned short ld9040_sm2_a2_19_100[] = {
	0xF9, 0x0C,
	DATA_ONLY, 0xB2,
	DATA_ONLY, 0xB8,
	DATA_ONLY, 0xAE,
	DATA_ONLY, 0xCD,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x66,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xB4,
	DATA_ONLY, 0xB9,
	DATA_ONLY, 0xAD,
	DATA_ONLY, 0xCE,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x7C,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xBE,
	DATA_ONLY, 0xBD,
	DATA_ONLY, 0xB0,
	DATA_ONLY, 0xCD,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x7E,
	0xFB, 0x02,
	DATA_ONLY, 0x5A,
	ENDDEF, 0x00
};

static const unsigned short ld9040_sm2_a2_19_90[] = {
	0xF9, 0x0C,
	DATA_ONLY, 0xB2,
	DATA_ONLY, 0xB9,
	DATA_ONLY, 0xAE,
	DATA_ONLY, 0xCE,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x61,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xB3,
	DATA_ONLY, 0xB9,
	DATA_ONLY, 0xAE,
	DATA_ONLY, 0xCE,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x77,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xBE,
	DATA_ONLY, 0xBE,
	DATA_ONLY, 0xB1,
	DATA_ONLY, 0xCE,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x78,
	0xFB, 0x02,
	DATA_ONLY, 0x5A,
	ENDDEF, 0x00
};

static const unsigned short ld9040_sm2_a2_19_80[] = {
	0xF9, 0x0C,
	DATA_ONLY, 0xB2,
	DATA_ONLY, 0xBA,
	DATA_ONLY, 0xAF,
	DATA_ONLY, 0xCE,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x5B,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xB3,
	DATA_ONLY, 0xBA,
	DATA_ONLY, 0xAF,
	DATA_ONLY, 0xCE,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x71,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xBE,
	DATA_ONLY, 0xBF,
	DATA_ONLY, 0xB2,
	DATA_ONLY, 0xCE,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x72,
	0xFB, 0x02,
	DATA_ONLY, 0x5A,
	ENDDEF, 0x00
};

static const unsigned short ld9040_sm2_a2_19_70[] = {
	0xF9, 0x0C,
	DATA_ONLY, 0xB2,
	DATA_ONLY, 0xBA,
	DATA_ONLY, 0xAF,
	DATA_ONLY, 0xCF,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x56,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xB1,
	DATA_ONLY, 0xBB,
	DATA_ONLY, 0xAF,
	DATA_ONLY, 0xCF,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x6B,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xBE,
	DATA_ONLY, 0xBF,
	DATA_ONLY, 0xB3,
	DATA_ONLY, 0xCE,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x6C,
	0xFB, 0x02,
	DATA_ONLY, 0x5A,
	ENDDEF, 0x00
};

static const unsigned short ld9040_sm2_a2_19_60[] = {
	0xF9, 0x0C,
	DATA_ONLY, 0xB1,
	DATA_ONLY, 0xB9,
	DATA_ONLY, 0xB0,
	DATA_ONLY, 0xD0,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x50,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xAC,
	DATA_ONLY, 0xBB,
	DATA_ONLY, 0xB0,
	DATA_ONLY, 0xD0,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x64,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xBE,
	DATA_ONLY, 0xBE,
	DATA_ONLY, 0xB3,
	DATA_ONLY, 0xD0,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x65,
	0xFB, 0x02,
	DATA_ONLY, 0x5A,
	ENDDEF, 0x00
};

static const unsigned short ld9040_sm2_a2_19_50[] = {
	0xF9, 0x0C,
	DATA_ONLY, 0xB1,
	DATA_ONLY, 0xBA,
	DATA_ONLY, 0xAF,
	DATA_ONLY, 0xD0,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x4A,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xA7,
	DATA_ONLY, 0xBD,
	DATA_ONLY, 0xB0,
	DATA_ONLY, 0xD1,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x5C,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xBE,
	DATA_ONLY, 0xC0,
	DATA_ONLY, 0xB3,
	DATA_ONLY, 0xD0,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x5D,
	0xFB, 0x02,
	DATA_ONLY, 0x5A,
	ENDDEF, 0x00
};

static const unsigned short ld9040_sm2_a2_19_40[] = {
	0xF9, 0x0C,
	DATA_ONLY, 0xB1,
	DATA_ONLY, 0xBA,
	DATA_ONLY, 0xB0,
	DATA_ONLY, 0xD0,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x42,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xA4,
	DATA_ONLY, 0xBD,
	DATA_ONLY, 0xB1,
	DATA_ONLY, 0xD2,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x53,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xBE,
	DATA_ONLY, 0xC1,
	DATA_ONLY, 0xB5,
	DATA_ONLY, 0xD1,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x53,
	0xFB, 0x02,
	DATA_ONLY, 0x5A,
	ENDDEF, 0x00
};

static const unsigned short ld9040_sm2_a2_19_30_dimming[] = {
	0xF9, 0x0C,
	DATA_ONLY, 0xB0,
	DATA_ONLY, 0xB9,
	DATA_ONLY, 0xB1,
	DATA_ONLY, 0xD1,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x38,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0x97,
	DATA_ONLY, 0xBE,
	DATA_ONLY, 0xB2,
	DATA_ONLY, 0xD3,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x49,
	DATA_ONLY, 0x0C,
	DATA_ONLY, 0xBC,
	DATA_ONLY, 0xC2,
	DATA_ONLY, 0xB7,
	DATA_ONLY, 0xD2,
	DATA_ONLY, 0x00,
	DATA_ONLY, 0x48,
	0xFB, 0x02,
	DATA_ONLY, 0x5A,
	ENDDEF, 0x00
};

/* LD9040, 4.27", SM2 A2 Panel Gamma Table */
static const unsigned short *psm2_a2_22Gamma_set[] = {
#if defined(CONFIG_TARGET_LOCALE_NAATT)
	ld9040_sm2_a2_22_50,
	ld9040_sm2_a2_22_60,
#else
	ld9040_sm2_a2_22_30_dimming,
	ld9040_sm2_a2_22_40,
#endif
	ld9040_sm2_a2_22_70,
	ld9040_sm2_a2_22_90,
	ld9040_sm2_a2_22_100,
	ld9040_sm2_a2_22_110,
	ld9040_sm2_a2_22_120,
	ld9040_sm2_a2_22_130,
	ld9040_sm2_a2_22_140,
	ld9040_sm2_a2_22_150,
	ld9040_sm2_a2_22_160,
	ld9040_sm2_a2_22_170,
	ld9040_sm2_a2_22_180,
	ld9040_sm2_a2_22_190,
	ld9040_sm2_a2_22_200,
	ld9040_sm2_a2_22_210,
	ld9040_sm2_a2_22_220,
	ld9040_sm2_a2_22_230,
	ld9040_sm2_a2_22_240,
	ld9040_sm2_a2_22_250,
	ld9040_sm2_a2_22_300,
};

static const unsigned short *psm2_a2_19Gamma_set[] = {
#if defined(CONFIG_TARGET_LOCALE_NAATT)
	ld9040_sm2_a2_19_50,
	ld9040_sm2_a2_19_60,
#else
	ld9040_sm2_a2_19_30_dimming,
	ld9040_sm2_a2_19_40,
#endif
	ld9040_sm2_a2_19_70,
	ld9040_sm2_a2_19_90,
	ld9040_sm2_a2_19_100,
	ld9040_sm2_a2_19_110,
	ld9040_sm2_a2_19_120,
	ld9040_sm2_a2_19_130,
	ld9040_sm2_a2_19_140,
	ld9040_sm2_a2_19_150,
	ld9040_sm2_a2_19_160,
	ld9040_sm2_a2_19_170,
	ld9040_sm2_a2_19_180,
	ld9040_sm2_a2_19_190,
	ld9040_sm2_a2_19_200,
	ld9040_sm2_a2_19_210,
	ld9040_sm2_a2_19_220,
	ld9040_sm2_a2_19_230,
	ld9040_sm2_a2_19_240,
	ld9040_sm2_a2_19_250,
	ld9040_sm2_a2_19_300,
};

struct ld9040_panel_data u1_panel_data_a2 = {
	.seq_user_set = SEQ_USER_SETTING,
	.seq_displayctl_set = SEQ_DISPCTL,
	.seq_gtcon_set = SEQ_GTCON,
	.seq_panelcondition_set = SEQ_PANEL_CONDITION,
	.seq_pwrctl_set = SEQ_PWR_CTRL_SM2_A2,
	.display_on = SEQ_DISPON,
	.display_off = SEQ_DISPOFF,
	.sleep_in = SEQ_SLPIN,
	.sleep_out = SEQ_SLPOUT,
	.acl_on = SEQ_ACL_ON,
	.acl_table = ACL_cutoff_set,
	.elvss_on = SEQ_ELVSS_ON,
	.elvss_table = SEQ_SM2_ELVSS_set,
	.gamma19_table = psm2_a2_19Gamma_set,
	.gamma22_table = psm2_a2_22Gamma_set,
	.lcdtype = LCDTYPE_SM2_A2,
};

