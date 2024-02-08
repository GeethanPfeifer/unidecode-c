/*

    This file is part of unidecode-c.
    Copyright (C) 2024 Geethan Pfeifer

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
    
*/

/*

NOTE: This header file is not complete! It needs to be joined with PART3.h and PART4.h.

PART2.h:
	Beginning of cpydecoded

*/



/*
	Copies a single decoded character.
	
	orig is a pointer to a string, so a getnextutf8 can be used.
	does not test for validity
	
	dest also a pointer to a string, incremented by dest. returns number of chars written.
	-1 is exceeds maxchars.
	
	maxchars includes null terminating char
*/
int cpysingledecoded(char **dest, char **orig, int maxchars){
	uint32_t uv = getnextutf8(orig);
	switch(uv){
		
