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

/* Exercise 6-2. Write a program that reads a C program and prints in alphabetical order each group of
 * variable names that are identical in the first 6 characters, but different somewhere thereafter. Don't count
 * words within strings and comments. Make 6 a parameter that can be set from the command line.
 */

struct var_group {
	char *word; 
} var_arr[] = {
	{"char"},
	{"double"},
 	{"float"},
	{"int"},
	{"long"},
	{"struct"},
	{"unsigned"}
};

struct tnode {  /* the tree node */
        char *word;     /* points to the text */
        int count;      /* number os occurrences */
        struct tnode *left;     /* left child */
        struct tnode *right;    /* right child */
};

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stddef.h>

#define DEFAULT 6
#define MAXWORD 100
#define MAXVAR 500

#define VAR_SIZE (sizeof var_arr / sizeof var_arr[0])

char *vgroup[MAXVAR];
int getword(char *word, int lim)
{
        int c, getch(void);
        void ungetch(int);
        char *w = word;

        while (isspace(c = getch()))
                ;
        if (c != EOF)
                *w++ = c;
        if (!isalpha(c)) {
                *w = '\0';
                return c;
        }
        for (; --lim > 0; w++)
                if (!isalnum(*w = getch())) {
                        ungetch(*w);
                        break;
                }
        *w = '\0';
        return word[0];
}
int binsearch(char *word, struct var_group var_arr[], int n)
{
        int cond;
        int low, high, mid;

        low = 0;
        high = n - 1;

        while (low <= high) {
                mid = (low+high) / 2;
                if ((cond = strcmp(word, var_arr[mid].word)) < 0)
                        high = mid - 1;
                else if (cond > 0)
                        low = mid + 1;
                else
                        return mid;
        }
        return -1;
}
int vg_index = 0;	
/* getvar: Checks is a var is valid and compare whether the n characters are equal */
void getvar(struct var_group *p, int index, int n)
{
	int c, getch(void);
	int i = 0;
        void ungetch(int);
	char word[MAXWORD];

	while (isspace(c = getch()))
                ;
	ungetch(c);
	while ((c = getch()) != EOF) {
		if (isalnum(c) || c == '_') {
			word[i++] = c; 
		}
		else {
			word[i] = '\0';
			if (i >= n && binsearch(word, var_arr, VAR_SIZE) < 0 ) {
				vgroup[vg_index] = malloc(i);
				strcpy(vgroup[vg_index], word);
				++vg_index;
			}
			i = 0;
			while(isspace(c = getch()))
				;
			if (c != ',') {
				ungetch(c);
				break;
			}
		}
	}
	return;
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
struct tnode *talloc(void);
char *_strdup(char *);

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w)
{       
        int cond;
        
        if (p == NULL) {        /* a new word has arrived */
                p = talloc();   /* make a new node */
                p->word = _strdup(w);
                p->count = 1;
                p->left = p->right = NULL;
        } else if ((cond = strcmp(w, p->word)) == 0)
                p->count++;     /* repeated word */
        else if (cond < 0)      /* less than into left subtree */
                p->left = addtree(p->left, w);
        else /* greater than into right subtree */
                p->right = addtree(p->right, w);
        return p;
}
/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p)
{       
        if (p != NULL) {
                treeprint(p->left);
                printf("%4d %s\n", p->count, p->word);
                treeprint(p->right);
        }
}
/* talloc; make a tnode */
struct tnode *talloc(void)
{
        return (struct tnode *) malloc(sizeof(struct tnode));
}
char *_strdup(char *s)  /* make a duplicate of s */
{
        char *p;

        p = (char *) malloc(strlen(s) +1);      /* +1 for '\0' */
        if (p != NULL)
                strcpy(p, s);
        return p;
}
                                    
int main(int argc, char *argv[])
{
	int index;
	int n = DEFAULT;
	struct tnode *root;
	
	if (argc == 1) {
		printf("Usage: ./program -n, a default value has been setted\n");
	} 
	else {
		while (!isdigit(*++argv[0]))
			;
		n = atoi(*argv);
	}
	char word[MAXWORD];
        while (getword(word, MAXWORD) != EOF) {
		if (isalpha(word[0]))
                        if (((index = binsearch(word, var_arr, VAR_SIZE)) >= 0) && vg_index < MAXVAR)
				getvar(var_arr, index, n);
	}
	vgroup[vg_index] = NULL;
        root = NULL;
	for (index = 0; index < vg_index-1; index++) { 
	        root = addtree(root, vgroup[index]);
	}
        treeprint(root);
	return 0;	
}

