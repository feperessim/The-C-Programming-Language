/* Copyright (C) 2015 Felipe de Lima Peressim
 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/* Exercise 1-20. Write a program detab that replaces tabs in the input with the proper number of blanks to space to
 * the next tab stop. Assume a fixed set of tab stops, say every n columns. Should n be a variable or a symbolic
 * parameter?
 */

#include <stdio.h>

#define TABSTOP 8 

int main(void)
{
	int c, n;

	n = 0;
	while (c = getchar(), c != EOF) {
		if (c != '\n' && c != '\t') {
			++n;;
			putchar(c);
		}	
		if (c == '\t') 
			while (n++ < TABSTOP) 
				putchar(' ');
		if (n >= TABSTOP || c == '\n')
 			n = 0;
	}
	return 0;
}

