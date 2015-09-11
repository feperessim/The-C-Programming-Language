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

/* Exercise 7-2. Write a program that will print arbitrary input in a sensible way. As a minimum, it should
 * print non-graphic characters in octal or hexadecimal according to local custom, and break long text lines.*/

#include <stdio.h>
#include <ctype.h>

#define BREAK_POINT 5 

int main(void)
{
	int c, counter;

	counter = 0;
	while ((c = getchar()) != EOF) {
		if (!isgraph(c) && (c != ' ' && c != '\n'))
			printf("%x", c);
		else
			printf("%c", c);
		if (counter >= BREAK_POINT) {
			if (isblank(c)) {
				printf("\n");
				counter = 0;
			}
		}
		if (c == '\n') {
			counter = 0;
		}
		++counter;
	}
	return 0;
}
