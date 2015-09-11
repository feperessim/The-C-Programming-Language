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

/* Exercise 4-1. Write the function strindex(s,t) which returns the position of the rightmost occurrence of t in s, or -1 if there is none.
*/

#include <stdio.h>

#define MAXLINE 1000	/* maximum input line length */

int lgetline(char line[], int max);
int strindex(char source[], char searchfor);

/* find all lines matching patern */
int main(void)
{
        char line[MAXLINE];
        int found = 0;

        while (lgetline(line, MAXLINE) > 0) {
        	if ((found = strindex(line, 'a')) >= 0)
                	printf("found at %d\n", found);
		else if (found < 0)	
                        printf("There isn't an occurence of t in s\n");
	}	       
        return 0;
}

/* getline: get line into s, return lenght */
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

/* strindex: return index of t in s, -1 if none */
int strindex(char s[], char t)
{
        int i,  k;

        for (i = 0, k = -1; s[i] != '\0'; i++)
                if (s[i] == t)
			k = i;
    	if (k >= 0)
        	return k;
        return k;
}

