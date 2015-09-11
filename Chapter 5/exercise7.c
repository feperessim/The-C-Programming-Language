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

/* Exercise 5-7. Rewrite readlines to store lines in an array supplied by main, rather than calling alloc to maintain storage. How much faster is the 
 * program ?
 */

#include <stdio.h>
#include <string.h>
 
#define MAXLINES 5000   /* max #lines to be sorted */
#define ALLOCSIZE 10000
 
char *lineptr[MAXLINES];        /* pointers to text lines */
 
int readlines(char *lineptr[], char *alloc_lines, int nlines);
void writelines(char *lineptr[], int nlines);
 
void qsort(char *lineptr[], int left, int right);
 
/* sort input lines */
int main(void)
{
        int nlines;     /* number of input lines read */
	char alloc_lines[ALLOCSIZE];

        if ((nlines = readlines(lineptr, alloc_lines, MAXLINES)) >= 0) {
                qsort(lineptr, 0, nlines-1);
                writelines(lineptr,nlines);
                return 0;
        } else {
                printf("error: input too big to sort\n");
                return 1;
        }
}
 
#define MAXLEN 1000     /* max lenght of any input line */
int lgetline(char *, int);
char *alloc(int);
 
/* readlines: read input lines */
int readlines(char *lineptr[], char *alloc_lines, int maxlines)
{
        int len, nlines;
        char *p, line[MAXLEN];
	
	p = alloc_lines;
        nlines = 0;
        while ((len = lgetline(line, MAXLEN)) > 0)
                if (nlines >= maxlines || (ALLOCSIZE + alloc_lines - p < len))
                        return -1;
                else {
                        line[len-1] = '\0';     /* delete newline */
                        strcpy(p, line);
                        lineptr[nlines++] = p;
			p += len;
                }
        return nlines;
}
 
/* writelines: write output line */
void writelines(char *lineptr[], int nlines)
{
        while ( nlines-- > 0)
                printf("%s\n", *lineptr++);
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
/* qsort: sort v[left]...v[right] into increasing order */
void qsort(char *v[], int left, int right)
{
        int i, last;
        void swap(char *v[], int i, int j);
 
        if (left >= right)      /* do nothing if array contains */
                return;         /* fewer than two elements */
        swap(v, left,   (left + right) / 2);
        last = left;
        for (i = left+1; i <= right; i++)
                if (strcmp(v[i], v[left]) < 0)
                        swap(v, ++last, i);
        swap(v, left, last);
        qsort(v, left, last-1);
        qsort(v, last+1, right);
}
/* swap: interchange v[i] and v[j] */
void swap(char *v[], int i, int j)     
{
        char *temp;
 
        temp = v[i];
        v[i] = v[j];
        v[j] = temp;
}

/* Before: 
[felipe@localhost Chapter 5]$ time ./a.out 
ddd
ddd

real    0m1.448s
user    0m0.001s
sys     0m0.000s

* After:

felipe@localhost Chapter 5]$ time ./a.out  
ddd
ddd                                                                                                                                                          
                                                                                                                                                             
real    0m1.256s                                                                                                                                             
user    0m0.000s                                                                                                                                             
sys     0m0.002s
*/
