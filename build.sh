#!/bin/bash

#
#
#    	This file is part of unidecode-c.h.
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


#	Build script
cd src
python generate_parts.py
cd ..
cat src/PART0.h src/PART1.h src/PART2.h src/PART3.h src/PART4.h src/PART5.h > unidecode-c.h