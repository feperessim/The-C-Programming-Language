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

/* Exercise 1-22. Write a program to ``fold'' long input lines into two or more shorter lines after the last non-blank
character that occurs before the n-th column of input. Make sure your program does something intelligent with
very long lines, and if there are no blanks or tabs before the specified column.
*/

#include <stdio.h>

#define MAX 4 

int main(void)
{
	int c, column;

	column = 0;
	while (c = getchar(), c != EOF) {
		column++;
		if (c != '\n') {
			if (column < MAX)
				putchar(c);
			if (column == MAX && c != ' ' && c != '\t') {
				putchar(c);
				putchar('\n');
			}
			if (column >= MAX && (c == ' ' || c == '\t')) {
				while (c = getchar(), c == ' ' || c == '\t');
				if (c != ' ' && c != '\t') {
					putchar('\n');
					putchar(c);
					column = 1;
				}	
			}
		}
		if (c == '\n' || column >= MAX)
			column = 0;
	}
	return 0;
}	
