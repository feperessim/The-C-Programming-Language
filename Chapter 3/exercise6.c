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

/*Exercise 3-6. Write a version of itoa that accepts three arguments instead of two. The third argument is
a minimum field width; the converted number must be padded with blanks on the left if necessary to
make it wide enough.
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

void itoa(int n, char s[], int width)
{
        int i = 0, sign = 1;

        if (n < 0)  /* record sign */
                sign *= -1;
        do {    /* generate digits in reverse order */
                s[i++] = sign*(n % 10) + '0';  /* get next digit */
        } while ((n /= 10) != 0); /* delete it */
        if (sign < 0)
                s[i++] = '-';
	while (width--)
		s[i++] = ' ';
        s[i] = '\0';
        reverse(s);
}

int main(void)
{
        int n;
        char s[1000];

        scanf("%d", &n);
        itoa(n, s, 1);
        printf("%s\n", s);
        return 0;
}

