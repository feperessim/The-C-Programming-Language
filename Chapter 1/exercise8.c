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

/* Exercise 1-8. Write a program to count blanks, tabs, and newlines.
 */

#include <stdio.h>

int main(void)
{
	int nl, tabs, blanks;
	int c;

	nl = tabs = blanks = 0;
	while((c = getchar()) != EOF) {
		if(c == '\n')
			++nl;
		if(c == '\t')
			++tabs;
		if(c == ' ')
			++blanks;
	}
	printf("New Line: %d\nTabulation: %d\nBlanks: %d\n",nl, tabs, blanks);
	return 0;
}	
