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

/* Exercise 5-6. Rewrite appropriate programs from earlier chapters and exercises with pointers instead of array indexing. Good possibilities include 
 * getline (Chapters 1 and 4), atoi, itoa, and their variants (Chapters 2, 3, and 4), reverse (Chapter 3), and strindex and getop (Chapter 4).
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE 1000 
#define MAX_NUMBER 20

int lgetline(char *s, int lim)
{
        int c, i;

        for (i=0; i < lim-1 && (c=getchar()) != EOF && c!='\n'; ++i)
                *(s++) = c;
        if (c == '\n') {
                *(s++) = c;
                ++i;
        }
        *s = '\0';
        return i;
}

/* strindex: return index of t in s, -1 if none */
int strindex(char *s, char t)
{
	int i, k;
	
	i = 0;
	k = -1;
	while (*s) {
		if (*s++ == t)
			k = i;
		i++;
	}
	return k;
}

void reverse(char *s)
{
        int c;
        char *t;

        for (t = s + (strlen(s)-1); s < t; s++, t--) {
                c = *s;
                *s = *t;
                *t = c;
        }
}

void itoa(int n, char *s)
{
        int sign = 1;

        if (n < 0)  /* record sign */
                sign *= -1;
        do {    /* generate digits in reverse order */
                *s++ = sign*(n % 10) + '0';  /* get next digit */
        } while ((n /= 10) != 0); /* delete it */
        if (sign < 0)
                *s++ = '-';
        *s = '\0';
}

int atoi(char *s)
{
	int n = 0;

	while  (*s >= '0' && *s <= '9') {
		n = 10 * n + (*s - '0');
		s++;
	}
	return n;
}

double atof(char *s)
{
        double val, power, pot, e = 1.0;
        int sign, sign_pot;

        while (isspace(*s)) /* skip white space */
                s++;
        sign = (*s == '-') ? -1 : 1;
        if (*s == '+' || *s == '-')
                s++;
        for (val = 0.0; isdigit(*s); s++)
                val = 10.0 * val + (*s - '0');
        if (*s == '.')
                s++;
        for (power = 1.0; isdigit(*s); s++) {
                val = 10.0* val + (*s - '0');
                power *= 10;
        }
        if (*s == 'e' || *s == 'E')
                s++;
        else
                return sign * val / power;
        if (*s == '-' || *s == '+')
                sign_pot = *s++;
        for (pot = 0.0; isdigit(*s); s++)
                pot = 10 * pot + (*s - '0');
        while (pot != 0) {
                e *= 10;
                pot--;
        }
        if (sign_pot == '-')
                return sign * val/e/power;
        else
                return sign * val * e / power;

}
#include <ctype.h>

#define NUMBER '0'

int getch(void);
void ungetch(int);
/* getop: get next character or numeric operand */
int getop(char *s)
{
        int c;

        while ((*s = c = getch()) == ' ' || c == '\t')
                ;
        *(s + 1) = '\0';
        if (!isdigit(c) && (c != '.' &&  c != '-'))
                return c;       /* not a number */
        if (c == '-') {
                while ((c = getch())) {
                        if (c == '\n') {
                                ungetch(c);
                                return '-';
                        }
                        if (isdigit(c)) {
                                *s = '-';
                                *(++s) = c;
                                break;
                        }
                }
        }
        if (isdigit(c)) /* collect integer part */
                while (isdigit(*++s = c = getch()))
                        ;
        if (c == '.')   /* collect fractional part */
                while (isdigit(*++s = c = getch()))
                        ;
        *s = '\0';
        if (c != EOF)
              ungetch(c);
        return NUMBER;
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

int main(void)
{
	char line[MAX_LINE];
	char s[MAX_NUMBER];
	char op[MAX_NUMBER];
	int found;

	while (lgetline(line, MAX_LINE) > 0) {	/* testing getline routine */
		printf("Line: %s\n", line);
		if ((found =  strindex(line, 'a')) >= 0)	/*testing strindex routine */
			printf("stindex:Char 'a' found at %d\n", found);
		else if (found < 0)
			printf("There isn't an occurence of t in s\n");
	}
	itoa(5296, s);	/* testing itoa function */
	reverse(s);
	printf("\nitoa result = %s\n", s);
	printf("\natoi result = %d\n", atoi(s));	/* testing atoi routine */
	printf("\natof result = %g\n", atof("123e-1"));	/* testing atof routine */
	if (getop(op) == NUMBER)	/* testing getop routine */
		printf("\nA number was found %s\n", op);
	else
		printf("\nAn operator or something else was found\n");	
	return 0;
}
