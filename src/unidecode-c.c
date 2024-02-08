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

unidecode-c.c: basic interface to unidecode-c.h
Aims to emulate the unidecode utility

*/

#include <ctype.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include <unidecode-c.h>

#define BUFFER_SIZE 8192

int main(int argc, char **argv){
	FILE* in ;
	char (inbuf)[BUFFER_SIZE];
	char (outbuf)[BUFFER_SIZE];
	char *(inbuft[0]), *(outbuft[0]), *(outbuftt[0]);				/* temporary values for use with unidecode */
	int complete;
	int gv;				/* value for reading from getc */
	unsigned char nb;		/* critical that this is unsigned! */
	int possiblyinvalid;
	int i;
	int sr;
	
	
	if(argc > 2){
		fprintf(stderr, "Error: too many arguments. Run `unidecode-c -h' for help.\n");
		return 1;
	}
	if(argc == 1){
		in = stdin;
	}
	if(argc == 2){
		if(!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")){
			printf(
"usage: unidecode [OPTION] [FILE]\n\
Transliterates FILE from UTF-8 to ASCII, outputting to stdout.\n\
\n\
If FILE is not specified, uses stdin.\n\
\n\
-h, --help\t\tdisplays this help message\n");
			return 0;
		}
		
		in = fopen(argv[1], "r");
		if(!in){
			fprintf(stderr, "Error: file does not exist.\n");
			return 1;
		}
	}
	
	nb = 0;
	complete=0;
	possiblyinvalid = 0;
	while(!complete){
		/* read until any of the following are satisfied:
			- inbuf has buffer - 4 elements or greater.
			- EOF or NULL reached
			
			then, read characters until end of next ascii character
			*/
		i = 0;
		if(nb){		/* if first byte  is already read*/
			(inbuf)[i] = nb;
		} else {
			gv = fgetc(in);
			if(gv == EOF){
				complete = 1;
				goto NEXT;
			}
			(inbuf)[i] = gv; /* truncation */
		}
		for(i=1; i<BUFFER_SIZE-4; i++){
			gv = fgetc(in);
			if(gv == EOF){
				complete = 1;
				goto NEXT;
			}
			(inbuf)[i] = gv;
		}
		
		/*note: following does not catch all errors, some will be caught by validutf8 */
		/* next byte */
		gv = fgetc(in);
		nb = gv;
		if(gv == EOF){
			complete = 1;
			goto NEXT;
		}
		if(nb >= 248){		/* greater than 248? invalid */
			errno = EILSEQ;
			fprintf(stderr, "Error: invalid UTF-8.\n");
			return 1;
		} else if(nb >= 192){	/* start of unicode seq: save for next sequence */
			/* noop */
			
		} else if(nb >= 128){ /* middle of utf-8 sequence: copy rest of bytes */
			(inbuf)[i] = nb;				/* BUFFERSIZE - 4*/
			
			i++;						/* BUFFERSIZE - 3*/
			gv = fgetc(in);
			nb = gv;
			if(gv == EOF){
				complete = 1;
				goto NEXT;
			}
			if(nb < 128)goto NEXT;
			if(nb >= 248){
				errno = EILSEQ;
				fprintf(stderr, "Error: invalid UTF-8.\n");
				return 1;
			}
			if(nb >= 192)goto NEXT;
			(inbuf)[i] = nb;
			/* note how by elimination, 128 <= nb < 192 */
			
			i++;						/* BUFFERSIZE - 2*/
			gv = fgetc(in);
			nb = gv;
			if(gv == EOF){
				complete = 1;
				goto NEXT;
			}
			if(nb < 128)goto NEXT;
			if(nb >= 248){
				errno = EILSEQ;
				fprintf(stderr, "Error: invalid UTF-8.\n");
				return 1;
			}
			if(nb >= 192)goto NEXT;
			(inbuf)[i] = nb;
			
			i++;						/* BUFFERSIZE - 1*/
			gv = fgetc(in);
			nb = gv;
			if(gv == EOF){
				complete = 1;
				goto NEXT;
			}
			if(nb < 128)goto NEXT;		
			if(nb >= 248){
				errno = EILSEQ;
				fprintf(stderr, "Error: invalid UTF-8.\n");
				return 1;
			}
			if(nb >= 192)goto NEXT;		
			
			/* MUST BE INVALID */
			errno = EILSEQ;
			fprintf(stderr, "Error: invalid UTF-8.\n");
			return 1;
			
		}
		NEXT:; /* at worst: BUFFERSIZE - 1 */
		(inbuf)[i] = 0;
		
		
		
		/* ALL IS READ: now continuously write to outbuf until no input is left, then flush */
		sr = 1;
		*inbuft = inbuf;
		while(sr){
			*outbuft = outbuf;
			unidecode(outbuft, inbuft, BUFFER_SIZE);
			if(errno == EILSEQ){
				fprintf(stderr, "Error: invalid UTF-8.\n");
				return 1;
			}
			sr = *outbuft - outbuf;		/* if this is 0, it has reached the end of the string */
			fputs(outbuf, stdout);
		}
		
	}
	
	
	
}