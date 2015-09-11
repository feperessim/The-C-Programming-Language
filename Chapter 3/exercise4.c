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

/* Exercise 3-4. In a two's complement number representation, our version of itoa does not handle the
 * largest negative number, that is, the value of n equal to -(2wordsize-1). Explain why not. Modify it to print
 * that value correctly, regardless of the machine on which it runs.
 */

/* Because the largest positive is equal to (2^wordsize-1)-1, so when the program make n positive the object can't handle the largest negative value 
 * to positive */

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

void itoa(int n, char s[])
{
        int i = 0, sign = 1;

	if (n < 0)  /* record sign */
        	sign *= -1;
	do {    /* generate digits in reverse order */
                s[i++] = sign*(n % 10) + '0';  /* get next digit */
        } while ((n /= 10) != 0); /* delete it */
        if (sign < 0)
                s[i++] = '-';
        s[i] = '\0';
        reverse(s);
}

int main(void)
{
        int n;
        char s[1000];

        scanf("%d", &n);
        itoa(n, s);
        printf("%s\n", s);
        return 0;
}

