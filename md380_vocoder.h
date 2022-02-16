/* 
* 	Copyright (C) 2020-2021 by Doug McLain AD8DP
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

#ifdef __cplusplus

extern "C" {
#endif
#include <inttypes.h>

int md380_init();
void md380_decode(uint8_t *ambe49, int16_t *pcm); // reads 49 bits (packed into 7 uint8_t elements in MSB order) of AMBE+2 from ambe49, writes 160 int16_t elements to pcm, 
void md380_encode(uint8_t *ambe49, int16_t *pcm); // reads 160 int16_t elements from pcm, writes 49 bits (packed into 7 uint8_t elements in MSB order) of AMBE+2 to ambe49.
void md380_decode_fec(const uint8_t *ambe, int16_t *pcm);
void md380_encode_fec(uint8_t *ambe, const int16_t *pcm);
                      
#ifdef __cplusplus
}
#endif
