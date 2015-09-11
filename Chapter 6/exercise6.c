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

/* Exercise 6-6. Implement a simple version of the #define processor (i.e., no arguments) suitable for
 * use with C programs, based on the routines of this section. You may also find getch and ungetch
 * helpful. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct nlist {	/*table entry: */
	struct nlist *next;	/* next entry in chain */
	char *name;		/* defined name */
	char *defn;		/* replacement text */
};

#define HASHSIZE 101

static struct nlist *hashtab[HASHSIZE];	/* pointer table */

/* hash: form hash value for string s */
unsigned hash(char *s)
{
	unsigned hashval;

	for (hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;
	return hashval % HASHSIZE;
}

/* lookup: look for s in hashtab */
struct nlist *lookup(char*s)
{
	struct nlist *np;

	for (np = hashtab[hash(s)]; np != NULL; np = np->next)
		if (strcmp(s, np->name) == 0)
			return np;	/* found */
	return NULL;			/* not found*/
}

char *_strdup(char *s)
{
	char *p;

	p = malloc(strlen(s)+1); 	/* +1 for '\0' */
	if (p != NULL)
		strcpy(p, s);
	return p;
}

/* install: put (name, defn) in hashtab */
struct nlist *install(char *name, char *defn)
{
	struct nlist *np;
	unsigned hashval;

	if ((np = lookup(name)) == NULL) {	/* not found */
		np = malloc(sizeof(*np));
		if (np == NULL || (np->name = _strdup(name)) == NULL)
			return NULL;
		hashval = hash(name);
		np->next = hashtab[hashval];
		hashtab[hashval] = np;
	} else	/* already there */
		free(np->defn);	/* free previous defn */
	if ((np->defn = _strdup(defn)) == NULL)
		return NULL;
	return np;
}

void print(struct nlist *ptr)
{
	if (ptr != NULL) {
		printf("Name: %s defn: %s\n", ptr->name, ptr->defn);
		print(ptr->next);
	}		
}

struct nlist *undef(char *name, struct nlist *first)
{
	struct nlist *ptr, *prev;
        int index = hash(name);

	ptr = hashtab[index];
	if (ptr == NULL) {
		printf("Name not found\n");
		return NULL;
	}
	if (first == ptr) {	
		free(ptr->name);
		free(ptr->defn);
		ptr = NULL;
		if (hashtab[index]->next != NULL)
			return hashtab[index] = hashtab[index]->next;
		return NULL;
	}
	prev = first;
	while (prev->next != ptr)
		prev = prev->next;
	if (prev->next->next == NULL) {	/* Is the last element */
		free(prev->next->name);
		free(prev->next->defn);
		prev->next = hashtab[index] = NULL;
		return first;
	}
	free(ptr->name);
        free(ptr->defn);
        ptr = hashtab[index] = NULL;
	prev->next = prev->next->next;
	return first;
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

#define MAXWORD 32

void getword(char word[])
{
	int c, i;

	while (isspace(c = getch()))
		;
	ungetch(c);
	for (i = 0; (c = getch()) != EOF && i < MAXWORD -1 && !isspace(c); ++i)
		word[i] = c;
	word[i] = '\0';
	return;	
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

struct nlist* preprocessor(void)
{
	int c, head_state;
	struct nlist *head, *ptr, *tmp, data;
	char word[MAXWORD];

	head_state = OUT;
	head = NULL;
	while ((c = getch()) != EOF) {
		if (c == '/' && (c = getch()) == '*') {	
			is_comment();
		}
		if (c == '"') {
			is_strlit();
		}
		if (c == '#') {
			getword(word);
			if (strcmp("define", word) == 0) {
				getword(word);
				data.name = malloc(strlen(word) + 1);
				strcpy(data.name, word);
				getword(word);
				data.defn = malloc(strlen(word) + 1);
                                strcpy(data.defn, word);
				tmp = install(data.name, data.defn);
				if (head_state == OUT && tmp != NULL) {
					head = ptr = tmp;
					head_state = IN;
				}
				if (tmp != NULL) {
					ptr->next = tmp;
					ptr = ptr->next;
				}
	                        free(data.name); 
                                free(data.defn); 
			}
		}
	}
	tmp->next = NULL;
	//ptr->next = NULL;	
	return head;
}	
int main(void)
{
	struct nlist *ptr;

	ptr = preprocessor();
	//ptr = install("A", "0");	/* head */
	//ptr->next = install("IN", "1");
	//ptr->next->next = install("O", "2");
	//ptr->next->next->next = install("D", "30");
	//ptr->next->next->next->next = install("C", "22");
	//ptr = undef("IN", ptr);
	//ptr = undef("A", ptr);
	//ptr = undef("A", ptr);
	print(ptr);
	return 0;
}

