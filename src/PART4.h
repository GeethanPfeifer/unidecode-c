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

NOTE: This header file is not complete! It needs to be joined with PART2.h and PART3.h.

PART4.h:
	End of cpydecoded

*/


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