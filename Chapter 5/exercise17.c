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

/* Exercise 5-17. Add a field-searching capability, so sorting may bee done on fields within lines, each field sorted 
 * according to an independent set of options. (The index for this book was sorted with -df for the index category 
 * and -n for the page numbers.)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLINES 5000           /* max #lines to be sorted */
char *lineptr[MAXLINES];        /* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void lqsort(void *lineptr[], int left, int right, int (*comp) (void *, void*));
int numcmp_increase(char *, char  *);
int numcmp_decrease(char  *, char *);
int my_strcmp_decrease(char  *, char  *);
int my_strcmp_increase(char *s1, char *s2);
int read_input(char *s);
int decrease = 0;
int fold = 0;
int dir = 0;
int numeric = 0;
int flag = 0;
int field = 0;	

/* sort input lines */
int main(int argc, char *argv[])
{       
        int nlines;             /* number of input lines read */
	int i, j;
	unsigned int uargc;

	uargc = argc;
	for (i = uargc-1, j = 1 ; i > 0; i--, j++) {		/* Check for command line errors */
		if (read_input(argv[j]) != 0) 
			exit(EXIT_FAILURE);
	}
	j = 1;
        if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		while (--uargc) {
			read_input(argv[j]);
			if (decrease == 0)
                		lqsort((void **) lineptr, 0, nlines-1, (int (*)(void*,void*))(numeric ? numcmp_increase : my_strcmp_increase));
			else
				lqsort((void **) lineptr, 0, nlines-1, (int (*)(void*,void*))(numeric ? numcmp_decrease : my_strcmp_decrease));
			++j;
			flag = 0;
		}
                writelines(lineptr, nlines);
                return 0;
        } else {
                printf("input too big to sort\n");
                return 1;
        }
}
char *fillfld(char *s);
int read_input(char *s)
{
	decrease = 0;
	fold = 0;
	dir = 0;
	numeric = 0;
        if(s[0] != '-') {
		printf("usage: sort -dfnr\n");
                return 1;
	}
	while (*s) {
		++s;
               	switch(*s) {
                       	case 'n':
                               	numeric = 1;
                                break;
                        case 'f':
        	             	fold = 1;
                                break;
                        case 'r':
                	       	decrease = 1;
                                break;
                        case 'd':
                        	dir = 1;
                                break;
			case 'c':
				if (flag == 0) {
					s=fillfld(s);
					flag = 1;
				}
				else
					return 0;		 
				break;
			case '\0':
				break;
                        default:
                              	printf("usage: sort -dfnr\n");
	                       	return 1;
			}
		}
	return 0;
}
char *fillfld(char *s)
{
	int i;

	i = 0;
	while (*s) {
		++s;
		if ((!(isdigit(*s))) && *s != '-') {
			printf("Wrong args to field\n");
			exit(EXIT_FAILURE);
		}
		if (*s == '-')
			++s;
		if (isdigit(*s)) {
			while (isdigit(*s)) {
				field = field * 10 + (*s - '0');	
				++s;
			}
			++i;
		}
	}
	return s;
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
        for (i = left + 1; i <= right; i++)
                if ((*comp)(v[i], v[left]) < 0)
                        swap(v, ++last, i);
        swap(v, left, last);
        lqsort(v, left, last-1, comp);
        lqsort(v, last+1, right, comp);
}
int field_index(int fld, char *s);
int numcmp_decrease(char *s1, char *s2)
{
	int fld_idx_s1 = 0, fld_idx_s2 = 0;
	double v1 = 0, v2 = 0;

	if (flag != 0 && field != 0) {
		fld_idx_s1 = field_index(field, s1);
		fld_idx_s2 = field_index(field, s2);
	}
        v1 = atof(s1+ fld_idx_s1);
        v2 = atof(s2 + fld_idx_s2);
        if (v1 == v2)
                return 0;
        if (v1 < v2)
                return 1;
        else
                return -1;
}

/* numcmp: compare s1 and s2 numerically */
int numcmp_increase(char *s1, char *s2)
{
        int fld_idx_s1 = 0, fld_idx_s2 = 0;
        double v1, v2;

	if (flag != 0 && field != 0) {
                fld_idx_s1 = field_index(field, s1);
                fld_idx_s2 = field_index(field, s2);
        }
        v1 = atof(s1+ fld_idx_s1);
        v2 = atof(s2 + fld_idx_s2);
	if (v1 == v2)
		return 0;
        if (v1 < v2)
       	        return -1;
	else
               	return 1;
	
}

int my_strcmp_decrease(char *s1, char *s2)
{
	int fld_idx_s1 = 0, fld_idx_s2 = 0;

	if (flag != 0 && field != 0) {
                fld_idx_s1 = field_index(field, s1);
                fld_idx_s2 = field_index(field, s2);
        }
	while (s1[fld_idx_s1] == s2[fld_idx_s2]) {
		++fld_idx_s1;
		++fld_idx_s2;
	}          
        if (s1[fld_idx_s1] == '\0' && s2[fld_idx_s2] == '\0') {
                if (dir == 0)
                        return s1 - s2;
                else if ((isalnum(s1[fld_idx_s1]) || isspace(s1[fld_idx_s1])) && (isalnum(s2[fld_idx_s2]) || isspace(s2[fld_idx_s2])))
                        return s1-s2;
                else
                        exit(EXIT_FAILURE);
        }
        if (fold == 0 && dir == 0) {
                if (s1[fld_idx_s1] < s2[fld_idx_s2])
                        return 1;
                else
                        return -1;
        }
        else if (fold == 0 && dir == 1) {
                 if ((isalnum(s1[fld_idx_s1]) || isspace(s1[fld_idx_s1])) && (isalnum(s2[fld_idx_s2]) || isspace(s2[fld_idx_s2]))) {
                        if (s1[fld_idx_s1] < s2[fld_idx_s2])
                                return 1;
                        else
                                return -1;
                }
                else
                        exit(EXIT_FAILURE);
        }
        else if (fold == 1 && dir == 0)
                return (tolower(s1[fld_idx_s1]) < tolower(s2[fld_idx_s2])) ? 1 : -1;
        else {
                if ((isalnum(s1[fld_idx_s1]) || isspace(s1[fld_idx_s1])) && (isalnum(s2[fld_idx_s2]) || isspace(s2[fld_idx_s2])))
                        return (tolower(s1[fld_idx_s1]) < tolower(s2[fld_idx_s1])) ? 1 : -1;
                else
                        exit(EXIT_FAILURE);
        }

}
int my_strcmp_increase(char *s1, char *s2)
{
        int fld_idx_s1 = 0, fld_idx_s2 = 0;

        if (flag != 0 && field != 0) {
                fld_idx_s1 = field_index(field, s1);
                fld_idx_s2 = field_index(field, s2);
        }
        while (s1[fld_idx_s1] == s2[fld_idx_s2]) {
                ++fld_idx_s1;
                ++fld_idx_s2;
        }
        if (s1[fld_idx_s1] == '\0' && s2[fld_idx_s2] == '\0') {
                if (dir == 0)
                        return s1 - s2;
                else if ((isalnum(s1[fld_idx_s1]) || isspace(s1[fld_idx_s1])) && (isalnum(s2[fld_idx_s2]) || isspace(s2[fld_idx_s2])))
                        return s1-s2;
                else
                        exit(EXIT_FAILURE);
        }
        if (fold == 0 && dir == 0) {
                if (s1[fld_idx_s1] < s2[fld_idx_s2])
                        return -1;
                else
                        return 1;
        }
        else if (fold == 0 && dir == 1) {
                 if ((isalnum(s1[fld_idx_s1]) || isspace(s1[fld_idx_s1])) && (isalnum(s2[fld_idx_s2]) || isspace(s2[fld_idx_s2]))) {
                        if (s1[fld_idx_s1] < s2[fld_idx_s2])
                                return -1;
                        else
                                return 1;
                }
                else
                        exit(EXIT_FAILURE);
        }
        else if (fold == 1 && dir == 0)
                return (tolower(s1[fld_idx_s1]) < tolower(s2[fld_idx_s2])) ? -1 : 1;
        else {
                if ((isalnum(s1[fld_idx_s1]) || isspace(s1[fld_idx_s1])) && (isalnum(s2[fld_idx_s2]) || isspace(s2[fld_idx_s2])))
                        return (tolower(s1[fld_idx_s1]) < tolower(s2[fld_idx_s1])) ? -1 : 1;
                else
                        exit(EXIT_FAILURE);
        }
	
}
int field_index(int fld, char *s)
{
	int i, count_words = 0;
	
	for (i = 0; s[i] != '\0'; i++) {
		if (isspace(s[i])) {
			++count_words;
		}
		if (count_words == fld) {
			return i+1;
		}
	}
	return 0;	
}              
void swap(void *v[], int i, int j)
{
        void *temp;

        temp = v[i];
        v[i] = v[j];
        v[j] = temp;
}
