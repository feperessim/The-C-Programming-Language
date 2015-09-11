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

/* Exercise 1-23. Write a program to remove all comments from a C program. Don't forget to handle quoted strings
and character constants properly. C comments don't nest. */

#include <stdio.h>

#define IN 1
#define OUT 0

void inside_comment(int *);
void inside_string(int *);
int main(void)
{
	int c;

	while (c = getchar(), c!= EOF) {
		if (c != '/')
			putchar(c);
		if (c == '/')
			inside_comment(&c);
		if (c == '"') 
			inside_string(&c);
	}	
	return 0;	
}
void inside_comment(int *c)
{
	int state;

	state = IN;
	*c = getchar();
	if (*c != '*') {
		putchar('/');
		putchar(*c);
	}
	if (*c == '*')
		while (state) {
			*c = getchar();
			if (*c == '*' && (*c = getchar()) == '/')
				state = OUT;
		}
}
void inside_string(int *c)
{
	int state;
	
	state = IN;
	while (state) {
		*c = getchar();
		putchar(*c);
		if (*c == '"');
			state = OUT;
	}		
}


