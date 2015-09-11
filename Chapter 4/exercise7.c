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

/* Exercise 4-7. Write a routine ungets(s) that will push back an entire string onto the input. Should ungets know about buf and bufp, or
 * should it just use ungetch?
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int bufp = 0;   /* next free position in buf */
int getch(void);
void ungetch(int);
void ungets(char []);

int main(void)
{
	int c;

	ungets("String to test : ) \n");
	while (bufp > 0) {
		c = getch();
		putchar(c);
	}	
	return 0;
}	
#define BUFSIZE 100

char buf[BUFSIZE];      /* buffer for ungetch */
int getch(void) /* get a (possibly pushed-back) character */
{
        return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)     /* push character back on input */
{
        if (bufp >= BUFSIZE)
                printf("ungetch: too many characters\n");
        else
                buf[bufp++] = c;
}

void ungets(char s[]) /* Ungets() routine doesn't need to know about bufp */
{
	int len;
	
	if ((len = strlen(s)) > BUFSIZE) {
		printf("string too long to buffer\n");
		exit(EXIT_FAILURE);
	}	
	while (len > 0)
		ungetch(s[--len]);
}		
		
