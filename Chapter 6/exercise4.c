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

/* Exercise 6-4. Write a program that prints the distinct words in its input sorted into decreasing order of
 * frequency of occurrence. Precede each word by its count.
 */

struct tnode {	/* the tree node */
	char *word;	/* points to the text */
	int count;	/* number os occurrences */
	struct tnode *left;	/* left child */
	struct tnode *right;	/* right child */
};

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stddef.h>

#define MAXWORD 100
struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);
int llsort(struct tnode *);
int tpoint_alloc(struct tnode *p);
void max_depth(struct tnode *p, int *counter);
void create_array(struct tnode *p);
void sort_list(int maxsize);
void printlistp(int);
/* word frequency count */

struct tnode **pointer;

int main(void)
{
	struct tnode *root;
	char word[MAXWORD];
	int maxsize = 0;

	root = NULL;
	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]))
			root = addtree(root, word);
	maxsize = llsort(root);
	printlistp(maxsize);
	return 0;
}
void printlistp(int maxsize)
{
	int i;

	for (i = 0; i < maxsize; i++) 
		printf("%4d %s\n", pointer[i]->count, pointer[i]->word);
	return;	
}
int indx = 0;
void create_array(struct tnode *p)
{
	 if (p != NULL) {
                create_array(p->left);
		pointer[indx++] = p;
		create_array(p->right);
        }
}
void sort_list(int maxsize)
{
	int i, j;
	struct tnode *tmp = NULL;

	for (i = 0; i < maxsize; i++) {
		for (j = 0; j < maxsize; j++) {
			if (pointer[i]->count > pointer[j]->count) {
				tmp = pointer[i];
				pointer[i] = pointer[j];
				pointer[j] = tmp;
			}
		}
	}
	return;
}
int llsort(struct tnode *p)
{	
	int maxsize = tpoint_alloc(p);
	create_array(p);
	sort_list(maxsize);
	return maxsize;
}
int tpoint_alloc(struct tnode *p)
{
	int depthsize = 0;

	max_depth(p, &depthsize);
	pointer = malloc(depthsize * sizeof (struct tnode *));
	return depthsize;
}
void max_depth(struct tnode *p, int *counter)
{
	
        if (p != NULL) {
                max_depth(p->left, counter);
                max_depth(p->right, counter);
		++*counter;
        }
}

struct tnode *talloc(void);
char *_strdup(char *);

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w)
{
	int cond;

	if (p == NULL) {	/* a new word has arrived */
		p = talloc();	/* make a new node */	
		p->word = _strdup(w);
		p->count = 1;
		p->left = p->right = NULL;
	} else if ((cond = strcmp(w, p->word)) == 0)
		p->count++;	/* repeated word */
	else if (cond < 0)	/* less than into left subtree */
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
char *_strdup(char *s)	/* make a duplicate of s */
{
	char *p;

	p = (char *) malloc(strlen(s) +1);	/* +1 for '\0' */
	if (p != NULL)
		strcpy(p, s);
	return p;
}
/* getword: get next word or character from input */
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
