/* 
* 	Copyright (C) 2020 by Doug McLain AD8DP
* 	
* 	Based on code from https://github.com/travisgoodspeed/md380tools
*
*   This program is free software; you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation; either version 2 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program; if not, write to the Free Software
*   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#include <string.h>
#include <inttypes.h>

int ambe_decode_wav(int16_t *wavbuf,int eighty,int16_t *bitbuf,int a4,int16_t a5,int16_t a6,int a7);
int ambe_encode_thing(int16_t *bitbuf,int a2,int16_t *wavbuf,int eighty,int,int16_t a6,int16_t a7,int);                     
extern int ambe_inbuffer, ambe_outbuffer0, ambe_outbuffer1, ambe_mystery;
extern int ambe_outbuffer, wav_inbuffer0, wav_inbuffer1, ambe_en_mystery;

int ambe_encode_thing2(int16_t *bitbuf,int a2,int16_t *wavbuf,int eighty,int a5,int16_t a6,int16_t a7,uint32_t a8){
    ambe_encode_thing(bitbuf,a2,wavbuf, eighty, a5,a6,a7,a8);
    return 0;
}

void md380_encode(uint8_t *ambe49, int16_t *pcm)
{
	int16_t *inbuf0 = (int16_t*) &wav_inbuffer0;
	int16_t *inbuf1 = (int16_t*) &wav_inbuffer1;
	int16_t *ambe   = (int16_t*) &ambe_outbuffer;
	
	memset(ambe,0,50);

	for (int i=0;i<80;i++) inbuf0[i] = pcm[i];
	for (int i=0;i<80;i++) inbuf1[i] = pcm[i+80];

	ambe_encode_thing2(ambe, 0, inbuf0, 0x50, 0x1840, 0, 0x2000, (int) &ambe_en_mystery);
	ambe_encode_thing2(ambe, 0, inbuf1,0x50, 0x1840, 0x1, 0x2000, (int) &ambe_en_mystery);

	for(int i = 0; i < 6; ++i){
		for(int j = 0; j < 8; ++j){
			ambe49[i] |= (ambe[(i * 8) + (7 - j)] << j);
		}
	}
    ambe49[6] = ambe[48] ? 0x80 : 0;
}

void md380_decode(uint8_t *ambe49, int16_t *pcm)
{
	int16_t *ambe=(int16_t*) &ambe_inbuffer;
	int16_t *outbuf0=(int16_t*) &ambe_outbuffer0; 
	int16_t *outbuf1=(int16_t*) &ambe_outbuffer1;

    int ambei=0;
    for(int i=0;i<6;i++){
      for(int j=0;j<8;j++){
        ambe[ambei++]=(ambe49[i]>>(7-j))&1;
      }
    }
    ambe[ambei++]=ambe49[6] ? 1 : 0;

    ambe_decode_wav(outbuf0, 80, ambe, 0, 0, 0, (int) &ambe_mystery);
    ambe_decode_wav(outbuf1, 80, ambe, 0, 0, 1, (int) &ambe_mystery);
    memmove(pcm, outbuf0, 160);
    memmove(&pcm[80], outbuf1, 160);
}
