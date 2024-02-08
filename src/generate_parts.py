"""

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
	
"""

"""
I am not too concerned with the efficiency of the generation script itself.
"""


from unidecode import unidecode
import codecs
import binascii

def escape_string(str):
	nstr = ""
	for c in str:
		hexed = hex(ord(c))
		if(len(hexed) == 3):
			nstr += "\\x" + hexed[2]
		else:
			nstr += "\\x" + hexed[2] + hexed[3]
	return nstr
	



""" tuple of values:
	(number, str, srcbytes)
"""
replacevals = []



n = -1
""" initial asciis (1-byte) """
for i in range(0, 127 + 1):
	n += 1
	x = unidecode(chr(n))
	
	if x:
		replacevals.append((i, x, 1))

n = -1
""" 2-byte """
for i in range(192, 223 + 1):
	for j in range(128, 191 + 1):
		n += 1
		
		if(n >= 128):
			x = unidecode(chr(n))
			
			if x:
				replacevals.append((256*i + j, x, 2))

n = -1
""" 3-byte """
for i in range(224, 239 + 1):
	for j in range(128, 191 + 1):
		for k in range(128, 191 + 1):
			n += 1
			
			if(n >= 2048):
				x = unidecode(chr(n))
				
				if x:
					replacevals.append((65536 * i + 256 * j + k, x, 3))

""" 4-byte """

n = -1
"""nastiness"""
b = False 

for i in range(240, 247 + 1):
	for j in range(128, 191 + 1):
		for k in range(128, 191 + 1):
			for l in range(128, 191 + 1):
				n += 1
				
				"""if only python had goto!"""
				if(n == 1112064):
					b = True
					break
				
				if(n >= 65536):
					x = unidecode(chr(n))
				
					if x:
						replacevals.append((16777216 * i + 65536 * j + 256 * k + l, x, 4))
			if(b):
				break
		if(b):
			break
	if(b):
		break
"""gotophobia considered harmful"""
				
				
f = open("PART3.h", "w")

f.write("/* This file was created automatically, it is not a source file. */")

for p in replacevals:
	f.write("case " + str(p[0]) + ": ")
	"""no space: return -1 """
	f.write("if(maxchars < " + str(len(p[1]) + 1) + "){(*orig)-=" + str(p[2]) + ";return -1;}")
	f.write("strcpy(*dest, \"" + escape_string(p[1]) + "\"); (*dest)+= " + str(len(p[1])) + ";return " +   str(len(p[1])) + "; break;")














