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

/* Exercise 6-3. Write a cross-referencer that prints a list of all words in a document, and for each word, a
 * list of the line numbers on which it occurs. Remove noise words like ``the,'' ``and,'' and so on.
 */

#define MAX_LIST_SIZE 1000

struct tnode {  /* the tree node */
        char *word;     /* points to the text */
        char line_list[MAX_LIST_SIZE];      /* list os lines on each word occurs */
	int index;
        struct tnode *left;     /* left child */
        struct tnode *right;    /* right child */
};

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stddef.h>

#define MAXWORD 100

char *nw[] = {
	"a",
	"an",
	"and",
	"are",
	"I"
	"in",
	"is",
	"of",
	"or",
	"that",
	"the",
	"this",
	"to"
};		

#define NW_SIZE (sizeof nw/8)
int counter = 1;

int getword(char *word, int lim)
{
        int c, getch(void);
        void ungetch(int);
        char *w = word;

        while (isspace(c = getch()))
		if (c == '\n')
			++counter;
        if (c != EOF)
                *w++ = c;
        if (!isalpha(c)) {
                *w = '\0';
                return c;
        }
        for (; --lim > 0; w++)
                if (!isalnum(*w = getch())) {	
			if (*w != '\n')
                        	ungetch(*w);
                        break;
                }
	if (*w == '\n') {
        	*w = '\0';
		return '\n';
	}
	*w = '\0';
        return word[0];
}

int binsearch(char *word, int n)
{
        int cond;
        int low, high, mid;

        low = 0;
        high = n - 1;

        while (low <= high) {
                mid = (low+high) / 2;
                if ((cond = strcmp(word, nw[mid])) < 0)
                        high = mid - 1;
                else if (cond > 0)
                        low = mid + 1;
                else
                        return mid;
        }
        return -1;
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
struct tnode *addtree(struct tnode *p, char *w, char *line)
{
        int cond;	

        if (p == NULL) {        /* a new word has arrived */
                p = talloc();   /* make a new node */
                p->word = _strdup(w);
		p->index = 0;
		strcpy(p->line_list, line);		
                p->left = p->right = NULL;
        } else if ((cond = strcmp(w, p->word)) == 0 && p->index < MAX_LIST_SIZE ) {
		++(p->index);
                strcat(p->line_list, line);
	}
        else if (cond < 0)      /* less than into left subtree */
                p->left = addtree(p->left, w, line);
        else /* greater than into right subtree */
                p->right = addtree(p->right, w, line);
        return p;
}
/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p)
{
        if (p != NULL) {
                treeprint(p->left);
                printf("%s Line :%s\n", p->word, p->line_list);
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
void reverse(char *s)
{
	int c, i ,j;

	for (i = 0; j = strlen(s)-1, i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
	s[++i] = ' ';
	s[++i] = '\0';
}
int itoa(char *line, int n)
{
	int i = 0;

	do {
		line[i++] = (n % 10 + '0');
	} while ((n /= 10) > 0 && i < MAX_LIST_SIZE);
	line[i] = '\0';
	reverse(line);
	return 0;		
}
int main(void)
{
        struct tnode *root;
        char word[MAXWORD];
	char line[MAX_LIST_SIZE];
	int is_a_nline;
	
        root = NULL;
        while ((is_a_nline = getword(word, MAXWORD)) != EOF) {
                if (isalpha(word[0]) && ((binsearch(word, NW_SIZE)) < 0)) {
                        if (itoa(line, counter) >= 0)
				root = addtree(root, word, line);
			else
				return -1;
		}
		if (is_a_nline == '\n') {
			++counter;
		}
	}
        treeprint(root);
	return 0;
}
