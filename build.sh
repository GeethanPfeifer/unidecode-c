#!/bin/bash

#
#
#    	This file is part of unidecode-c.
#	Copyright (C) 2024 Geethan Pfeifer
#
#   	This program is free software; you can redistribute it and/or modify
#    	it under the terms of the GNU General Public License as published by
#    	the Free Software Foundation; either version 2 of the License, or
#    	(at your option) any later version.
#
#    	This program is distributed in the hope that it will be useful,
#    	but WITHOUT ANY WARRANTY; without even the implied warranty of
#   	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    	GNU General Public License for more details.
#
#    	You should have received a copy of the GNU General Public License along
#    	with this program; if not, write to the Free Software Foundation, Inc.,
#    	51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
#    
#


#	Building header
cd src
python generate_parts.py
cd ..
cat src/PART0.h src/PART1.h src/PART2.h src/PART3.h src/PART4.h src/PART5.h > unidecode-c.h

#	GCC major version.
#	This should work for all recent versions of GCC.
gmv=$(gcc -dumpfullversion -dumpversion | grep -o "[0-9]*" | head -n1)

if [ $gmv -lt 8 ] || [ $gmv -gt 10 ]; then
	time gcc src/unidecode-c.c -o unidecode-c -I.
else
#	Tries gcc-11 then gcc-7.
#	If neither of them are available, prompt user to see if they want to try anyways
	time gcc-11 src/unidecode-c.c -o unidecode-c -I. || time gcc-7 src/unidecode-c.c -o unidecode-c -I. || {
		echo The installed version\(s\) of GCC have a flaw where compilation may not terminate.
		echo It is recommended to install GCC-7 or GCC-11+.
		read -p Would you like to continue? \(Enter \'y\'.\) cnf
		if [ $cnf = "y" ]; then
			time gcc src/unidecode-c.c -o unidecode-c -I.
		fi
	}
fi