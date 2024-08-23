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

#include <stdint.h>
#include <errno.h>
#include <string.h>

int validutf8(char *st){
	int i;
	for(i=0; st[i] != 0; i++){
		if(st[i] >= 248){
			return 0;
		} else if(st[i] >= 240){
			i++; if(st[i] < 128 || st[i] >= 192)return 0;
			i++; if(st[i] < 128 || st[i] >= 192)return 0;
			i++; if(st[i] < 128 || st[i] >= 192)return 0;
		} else if(st[i] >= 224){
			i++; if(st[i] < 128 || st[i] >= 192)return 0;
			i++; if(st[i] < 128 || st[i] >= 192)return 0;
		} else if(st[i] >= 192){
			i++; if(st[i] < 128 || st[i] >= 192)return 0;
		} else if(st[i] >= 128){
			return 0;
		}
	}
	return 1;
}





/*
	t: pointer to a string. increases to position of next char 
	
	does not care if invalid.
*/
uint32_t getnextutf8(char **t){
	uint32_t res = 0;
	
	if((unsigned char)(**t) < 128){	
		res = (unsigned char)(**t);
		(*t)++;
		
		return res;
	} else if((unsigned char)(**t)< 224){
		res = (unsigned char)(**t);
		(*t)++;
		res = res*256 + (unsigned char)(**t);
		(*t)++;
		
		return res;
	} else if((unsigned char)(**t) < 240){
		res = (unsigned char)(**t);
		(*t)++;
		res = res*256 + (unsigned char)(**t);
		(*t)++;
		res = res*256 + (unsigned char)(**t);
		(*t)++;
		
		return res;
	} else if((unsigned char)(**t) < 248){
		res = (unsigned char)(**t);
		(*t)++;
		res = res*256 + (unsigned char)(**t);
		(*t)++;
		res = res*256 + (unsigned char)(**t);
		(*t)++;
		res = res*256 + (unsigned char)(**t);
		(*t)++;
		
		return res;
	} else {
		/* return -1 (illegal) */
		
		return -1;
	}
}



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
		
		/* below line replaced */
		
		
		####
		
		
		/* in case for some reason an error is reached, halt. */
		/*
		case -1:
			return -1;
			break;
		*/
		default:
			return 0;
			break;
	}
	/* just in case somehow this is reached */
	return 0;
}

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
		/*  reads until at start of a unicode char  */
		
		/*
		if(bytesremoved < 0){
			do{
				(*src)--;
			}
			while(**src >= 128 && **src <= 191);
		}
		*/
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
		/* reads until at start of a unicode char */
		/*
		if(bytesremoved < 0){
			do{
				(*src)--;
			}
			while(**src >= 128 && **src <= 191);
		}
		*/
		bytesleft -= bytesremoved;
		
	}
	**dest = 0;
	return 1;
	
}



