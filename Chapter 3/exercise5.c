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

/* Exercise 3-5. Write the function itob(n,s,b) that converts the integer n into a base b character
 * representation in the string s. In particular, itob(n,s,16) formats s as a hexadecimal integer in s.
*/
#include <stdio.h>
#include <string.h>

void reverse(char s[])
{
        int c, i, j;

        for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
                c = s[i];
                s[i] = s[j];
                s[j] = c;
        }
}

void itob(int n, char s[], int b)
{
        int i = 0, sign = 1, temp;
	char *base = "0123456789ABCDEFGHIJKLMNOPQRSTUVXWYZ";

        if (n < 0)  /* record sign */
                sign *= -1;
        do {    /* generate digits in reverse order */
		temp = sign*n%b;	
                s[i++] = base[temp];  /* get next digit */
        } while ((n /= b) != 0); /* delete it */
        if (sign < 0)
                s[i++] = '-';
        s[i] = '\0';
        reverse(s);
}

int main(void)
{
        char s[1000];
	itob(18,s,2);
	printf("%s\n", s);
	return 0;
}

