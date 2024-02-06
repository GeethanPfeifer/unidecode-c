# unidecode-c

This is my attempt at a reimplementation of unidecode in C.

It is currently very early in development, and unlikely to work too well.

## Building

To build, run `./build.sh` in the directory you downloaded the source code to.

To clean, run `./clean.sh` in the directory you downloaded the source code to.

Building will create the header file `unicode-c.h` in this directory.

## Functions

### validutf8

`validutf8(char *st)`

Returns 0 if a string is invalid, 1 if it is valid. Assumes that the string is null-terminating.

### unidecode

`int unidecode(char **dest, char **src, int maxbytes)`

Takes a pointer to a destination string, a pointer to a source string, and the maximum number of bytes to write.

This function:

* runs validutf8 on *src and raises EILSEQ (returning 0) if the string is invalid

* "decodes" from \*src to \*dest for a maximum of int maxbytes

* sets *src to the one byte after the last character "decoded" (the last character of the string if it is at the end of the string.)

* sets *dest to the last byte written (which will be the end of the string)

* returns 1 if successful

## Dependencies

List of dependencies

* python-3

* unidecode

* **gcc-7**

Note: The header file has a very long switch statement, [which gcc-8,9,10 struggle with.](https://gcc.gnu.org/bugzilla/show_bug.cgi?id=100393) Presumably this is fixed in gcc-11.

## Licensing

This program is licensed under the GNU GPL v2 (or later).

## Original copyright notices:

This program doesn't use anycode from Burke or Šolc, however it definitely copies the character transliteration tables in some manner: it uses unidecode to generate the program by trying every unicode code point.

The folllowing is taken verbatim from https://github.com/avian2/unidecode/tree/master

### Copyright

Original character transliteration tables:

Copyright 2001, Sean M. Burke <sburke@cpan.org>, all rights reserved.

Python code and later additions:

Copyright 2024, Tomaž Šolc <tomaz.solc@tablix.org>

This program is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the Free
Software Foundation; either version 2 of the License, or (at your option)
any later version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc., 51
Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.  The programs and
documentation in this dist are distributed in the hope that they will be
useful, but without any warranty; without even the implied warranty of
merchantability or fitness for a particular purpose.


