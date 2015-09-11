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

/* Exercise 3-2. Write a function escape(s,t) that converts characters like newline and tab into visible
escape sequences like \n and \t as it copies the string t to s. Use a switch. Write a function for the
other direction as well, converting escape sequences into the real characters.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int escape(char s[], char *t)
{
	int i, j;

	for (i = 0, j = 0; t[i] != '\0'; i++, j++)
		switch (t[i]) {
			case '\t':
				s[j] = '\\';
				s[++j] = 't';
				break;
			case '\n':
				s[j] = '\\';
				s[++j] = 'n';
				break;
			case '\b':
				s[j] = '\\';
				s[++j] = 'b';
				break;
			default:
				s[j] = t[i];
		}
	s[j] = '\0';
	printf("%s\n", s);
	return 0;	
}

int main(void)
{
	char s[MAX], t[MAX];
	int c, i;

	for (i = 0; (c = getchar()) != EOF && i < MAX; i++)
		t[i] = c;
	t[i] = '\0';
	escape(s, t);
	return 0;
}

