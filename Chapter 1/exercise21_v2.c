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

/* Exercise 1-21. Write a program entab that replaces strings of blanks by the minimum number of tabs and blanks
 * to achieve the same spacing. Use the same tab stops as for detab. When either a tab or a single blank would
 * suffice to reach a tab stop, which should be given preference?
 */

#include <stdio.h>

#define TABSTOP 8

int main(void)
{
	int c, column, blanks;

	column = blanks = 0;
	while (c = getchar(), c != EOF) {
		if (blanks == 0 && c != '\n' && c != ' ') {
			putchar(c);
			column++;
		}
		if (c == ' ')
			blanks++;
		if (blanks >= TABSTOP && c != ' ') {
			while (blanks >= TABSTOP) {
				putchar('\t');
				blanks -= TABSTOP;
			}
			while (column > 0) {
				putchar(' ');
				column--;
			}
			if (blanks == 0)	
				putchar(c);
		}
		if (blanks > 0 && blanks < TABSTOP && c != ' ') {
			while (blanks > 0) {
				putchar(' ');
				blanks--;
			}
			putchar(c);
		}	
		if (c == '\n' || c == '\t' || column >= TABSTOP)
			column = 0;
	}
	return 0;
}	
