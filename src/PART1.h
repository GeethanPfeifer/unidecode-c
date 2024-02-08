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

PART1.h:
	validutf8 -- function that determines whether a string is valid utf8
	getnextutf8 -- function for getting next utf8 value

*/

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
