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

/* Exercise 4-12. Adapt the ideas of printd to write a recursive version of itoa; that is, convert an integer into a string by calling a recursive
 * routine.
 */
#include <stdio.h>

#define MAX 1000

void itoa(int n, char s[])
{
        static int i = 0; 

        if (n < 0) { /* record sign */
                n = -n;
		s[i++] = '-';
	}	
        if (n / 10)
		itoa(n / 10, s);
	s[i++] =  n % 10 + '0';  /* get next digit */
        s[i] = '\0';
}

int main(void)
{
        int n;
	char s[MAX];

	scanf("%d", &n);
        itoa(n, s);
        printf("%s\n", s);
        return 0;
}

