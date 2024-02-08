/*

    This file is part of unidecode-c.h.
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

PART1.h:
	unidecode

*/


/*
returns 1 on success, 0 on failure

copies from pointer in src to pointer in dest, writing a maximum of maxbytes.
*/
int unidecode(char **dest, char **src, int maxbytes){
	/* flag */
	int bytesleft = maxbytes;
	int bytesremoved = 0;
	
	
	/* invalid UTF-8, return 0 and set errno to EILSEQ */
	if(!validutf8(*src)){
		errno = EILSEQ;
		return 0;
	}
	
	while(bytesremoved >= 0 && **src != 0){
		bytesremoved = cpysingledecoded(dest, src, bytesleft);
		bytesleft -= bytesremoved;
	}
	**dest = 0;
	return 1;
	
}

/*
same as the above, but doesn't check if the string is valid
*/ 
int unidecode_u(char **dest, char **src, int maxbytes){
	/* flag */
	int bytesleft = maxbytes;
	int bytesremoved = 0;
	
	while(bytesremoved >= 0 && **src != 0){
		bytesremoved = cpysingledecoded(dest, src, bytesleft);
		bytesleft -= bytesremoved;
	}
	**dest = 0;
	return 1;
	
}



