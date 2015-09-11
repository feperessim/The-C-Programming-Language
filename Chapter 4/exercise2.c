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

/* Exercise 4-2. Extend atof to handle scientific notation of the form 123.45e-6
 * where a floating-point number may be followed by e or E and an optionally signed exponent.
 */
#include <stdio.h>
#include <ctype.h>

#define MAXLINE 100

/* atof: convert string s to double */
double atof(char s[])
{
        double val, power, pot, e = 1.0;
        int i, sign, sign_pot;

        for (i = 0; isspace(s[i]); i++) /* skip white space */
                ;
        sign = (s[i] == '-') ? -1 : 1;
        if (s[i] == '+' || s[i] == '-')
                i++;
        for (val = 0.0; isdigit(s[i]); i++)
                val = 10.0 * val + (s[i] - '0');
        if (s[i] == '.')
                i++;
        for (power = 1.0; isdigit(s[i]); i++) {
                val = 10.0* val + (s[i] - '0');
                power *= 10;
        }
	if (s[i] == 'e' || s[i] == 'E')
		i++;	
	else	
       		return sign * val / power;
	if (s[i] == '-' || s[i] == '+')
		sign_pot = s[i++];
	for (pot = 0.0; isdigit(s[i]); i++)
		pot = 10 * pot + (s[i] - '0');
	while (pot != 0) {
		e *= 10;
		pot--;
	}
	if (sign_pot == '-') 
		return sign * val/e/power; 
	else
		return sign * val * e / power;

}

int lgetline(char s[], int lim)
{
        int c, i;

        i = 0;
        while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
                s[i++] = c;
        if (c == '\n')
                s[i++] = c;
        s[i] = '\0';
        return i;
}

/* rudimentary calculator */
int main(void)
{
        double sum, atof(char[]);
        char line[MAXLINE];
        int lgetline(char line[], int max);

        sum = 0;
        while (lgetline(line, MAXLINE) > 0)
                printf("\t%g\n", sum += atof(line));
        return 0;
}

