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

/* Exercise 6-1. Our version of getword does not properly handle underscores, string constants,
 * comments, or preprocessor control lines. Write a better version.
 */
struct key {
        char *word;
        int count;
} keytab[] = {
	"#define", 0,
        "#include", 0,
	"auto", 0,
        "break", 0,
        "case", 0,
        "char", 0,
        "const", 0,
        "continue", 0,
        "default", 0,
	"for", 0,
        "unsigned", 0,
        "void", 0,
        "volatile", 0,
        "while", 0
        };

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stddef.h>

#define MAXWORD 100
#define NKEYS (sizeof keytab / sizeof keytab[0])


int getword(char *, int);
int binsearch(char *, struct key *, int);

/* count C keywords */
int main(void)
{
        int n;
        char word[MAXWORD];

        while (getword(word, MAXWORD) != EOF) 
                if (isalpha(word[0]) || word[0] == '#' || word[0] == '_')
                        if ((n = binsearch(word, keytab, NKEYS)) >= 0)
                                keytab[n].count++;
        for (n = 0; n < NKEYS; n++)
                if (keytab[n].count > 0)
                        printf("%4d %s\n", keytab[n].count, keytab[n].word);
        return 0;
}

/* binsearch: find word in tab[0]....tab[n-1] */
int binsearch(char *word, struct key tab[], int n)
{
        int cond;
        int low, high, mid;

        low = 0;
        high = n - 1;

        while (low <= high) {
                mid = (low+high) / 2;
                if ((cond = strcmp(word, tab[mid].word)) < 0)
                        high = mid - 1;
                else if (cond > 0)
                        low = mid + 1;
                else
                        return mid;
        }
        return -1;
}

/* getword: get next word or character from input */
int getword(char *word, int lim)
{
        int c, d, getch(void), is_comment(void), is_strlit(void);
        void ungetch(int);
        char *w = word;

        while (isspace(c = getch()))
                ;
        if (c != EOF && c != '"' && c != '/') {
        	if (c == '\\') {
			if ((d = getch()) != '\\') {
	       			*w++ = c;
				ungetch(d);
			}
		}
		else
			*w++ = c;

	}
        if (!isalpha(c)) {
		if ((c != '#' &&  c != '/') && (c != '\\' && c != '"')) {
			if (c != '_') {
				*w = '\0';
                		return c;
			}
		}
        }
	if (c == '/') {
		d = getch();
		if (d == '*')
			is_comment();
		else
			ungetch(d);
	}
	if (c == '"')
		is_strlit();
        for (; --lim > 0; w++) {
	        if (!isalnum(c = getch())) {
			ungetch(c);
                	break;
                }
		if (c == '/') {
               		d = getch();
                	if (d == '*') {
                		is_comment();
				break;
			}
			else  
       				ungetch(d);
        	}
        	if (c == '"') 
                	is_strlit();
		if (c == '\\') {
			if ((d = getch()) != '\\') {
				*w = c;
				ungetch(d);
			}
		}
		else
			*w = c;	
	}
        *w = '\0';
        return word[0];
}

#define BUFSIZE 100

char buf[BUFSIZE];      /* buffer for ungetch */
int bufp = 0;   /* next free position in buf */

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

#define IN 1
#define OUT 0

int is_comment(void)
{
	int c, state = OUT;

	while ((c = getch()) != EOF) {
		if (c == '*')
			state = IN;
		if (state == IN && c == '/')
			return c;
		if (c != '*')
			state = OUT;
	}		
	return c;
}

int is_strlit(void)
{
	int c;

	while ((c = getch()) != EOF && c != '"')
		;
	return c; 	
}

