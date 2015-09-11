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

/* Exercise 7-1. Write a program that converts upper case to lower or lower case to upper, depending on the
 * name it is invoked with, as found in argv[0].
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define DEFAULT 1

int main(int argc, char *argv[])
{
	int state = 0;
	int c;
	int (* convert)(int);


	if (argc == 1) {
		printf("usage \"./program -lower\" to lower case or \"./programa -upper\" to upper case and \"./program -default\" to no conversion\n");
		return 0;
	}
	else {
		if (strcmp("-lower", argv[1]) == 0)
			convert = tolower;
		else if (strcmp("-upper", argv[1]) == 0)
			convert = toupper;
		else if (strcmp("-default", argv[1]) == 0)
			state = DEFAULT;
		else {
			printf("Wrong option\n");
			return -1;
		}
	}
	if (state == DEFAULT)
		while ((c = getchar()) != EOF)
			putchar(c);
	else
		while ((c = getchar()) != EOF)
			putchar(convert(c));
	return 0;
}
