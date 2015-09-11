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

/* Exercise 5-14. Modify the sort program to handle a -r flag, which indicates sorting in reverse (decreasing) order. Be sure that -r works with -n. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 5000           /* max #lines to be sorted */
char *lineptr[MAXLINES];        /* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void lqsort(void *lineptr[], int left, int right, int (*comp) (void *, void*));
int numcmp(char *, char *);
int my_strcmp(char *s1, char *s2);
int decrease = 0;

/* sort input lines */
int main(int argc, char *argv[])
{       
        int nlines;             /* number of input lines read */
        int numeric = 0;        /* 1 if numeric sort */

        if (argc > 1 && strcmp(argv[1], "-n") == 0)
                numeric = 1;
	else if (argc > 1 && strcmp(argv[1], "-r") == 0)
		decrease = 1;
	else if (argc > 1 && (strcmp(argv[1], "-nr") == 0 || strcmp(argv[1], "-rn") == 0)) {
		numeric = 1;
		decrease = 1;
	}
	else if (argc > 1) {
		printf("Options: -n\tNumeric comparrision\n\t -r\tPrint in reverse order\nUsage: ./a.out -flags\n");
		return 1;
	}
        if ((nlines = readlines(lineptr, MAXLINES)) >= 0) { 
                lqsort((void **) lineptr, 0, nlines-1, (int (*)(void*,void*))(numeric ? numcmp : my_strcmp));
                writelines(lineptr, nlines);
                return 0;
        } else {
                printf("input too big to sort\n");
                return 1;
        }
}
#define MAXLEN 1000     /* max lenght of any input line */
int lgetline(char *, int);
char *alloc(int);

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines)
{       
        int len, nlines;
        char *p, line[MAXLEN];
        
        nlines = 0; 
        while ((len = lgetline(line, MAXLEN)) > 0)
                if (nlines >= maxlines || (p = alloc(len)) == NULL)
                        return -1;
                else {  
                        line[len-1] = '\0';     /* delete newline */
                        strcpy(p, line);
                        lineptr[nlines++] = p;
                }
	lineptr[nlines] = NULL;
        return nlines;
}

/* writelines: write output line */
void writelines(char *lineptr[], int nlines)
{
	while ( nlines-- > 0) {
               	printf("%s\n", *lineptr++); 
	}	
}

int lgetline(char *s, int lim)
{
        int c, i;

        for (i = 0; i < lim-1 && (c=getchar()) != EOF && c != '\n'; ++i)
                *(s++) = c;
        if (c == '\n') {
                *(s++) = c;
                ++i;
        }
        *s = '\0';
        return i;
}
#define ALLOCSIZE 10000 /* size of available space */

static char allocbuf[ALLOCSIZE];        /* storage for alloc */
static char *allocp = allocbuf;         /* next free position */

char *alloc(int n)      /* return pointer to n characters */
{
        if (allocbuf + ALLOCSIZE - allocp >= n) { /* it fits */
                allocp += n;
                return allocp - n;      /* old p */
        } else  /* not enough room */
                return 0;
}

void afree(char *p)     /* free storage pointed to by p */
{
        if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
                allocp = p;
}

/* qsort: sort v[left]...v[right] onto increasing order */
void lqsort(void *v[], int left, int right, int (*comp) (void *, void *))
{
        int i, last;
        void swap(void *v[], int, int);

        if (left >= right)      /* do nothing if array contains */
                return;         /* fewer than two elements */
        swap(v, left, (left + right) / 2);
        last = left;
        for (i = left+1; i <= right; i++)
        last = left;
        for (i = left+1; i <= right; i++)
                if ((*comp)(v[i], v[left]) < 0)
                        swap(v, ++last, i);
        swap(v, left, last);
        lqsort(v, left, last-1, comp);
        lqsort(v, last+1, right, comp);
}

/* numcmp: compare s1 and s2 numerically */
int numcmp(char *s1, char *s2)
{
        double v1, v2;

        v1 = atof(s1);
        v2 = atof(s2);
	if (v1 == v2)
		return 0;
 	if (decrease == 0) {
	        if (v1 < v2)
        	        return -1;
		else
                	return 1;
	}
	else {
		if (v1 < v2)
                	return 1;
                else
			return -1;
	}
}

int my_strcmp(char *s1, char *s2)
{
	while (*s1++ == *s2++)
		;
	if (*s1 == '\0' && *s2 == '\0')
		return s1 - s2;
	if (decrease == 0) {
		if (*s1 < *s2)
			return -1;
		else 
			return 1;
	}
	else {
		if (*s1 < *s2)
                        return 1;
                else
			return -1;
	}
}

void swap(void *v[], int i, int j)
{
        void *temp;

        temp = v[i];
        v[i] = v[j];
        v[j] = temp;
}
