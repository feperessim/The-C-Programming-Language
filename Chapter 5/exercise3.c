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

/* Exercise 5-3. Write a pointer version of the function strcat that we showed in Chapter 2: strcat(s,t) copies the string t to the end of s.
 */
#include <stdio.h>

#define MAX 20

void pstrcat(char *s, char *t)
{
	while (*s++) /* find end of s */
		;
	s--;
	while ((*s++ = *t++)) /* copy t */
		;
}

int main(void)
{
	char s[MAX] = {"Awesome"};
	char t[] = {" and nice"};

	pstrcat(s,t);
	printf("%s\n", s);
	return 0;
} 
