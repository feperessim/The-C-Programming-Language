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

/* Exercise 1-10. Write a program to copy its input to its output, replacing each tab by \t, each backspace by \b,
 * and each backslash by \\. This makes tabs and backspaces visible in an unambiguous way.
 */

#include <stdio.h>

int main(void)
{
	int c;

	while ((c = getchar()) != EOF){
		switch(c){
			case '\t': printf("\\t");break;
			case '\\': printf("\\\\");break;
			case '\b': printf("\\b");break;
			default: putchar(c);
		}
	}
	return 0;
}	
