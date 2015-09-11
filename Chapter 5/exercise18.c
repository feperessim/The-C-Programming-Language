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

/* Exercise 5.18  make dcl recover from input errors */
 
#include <stdio.h>
#include <string.h>
#include <ctype.h>
 
#define MAXTOKEN 100
 
enum { NAME, PARENS, BRACKETS, ERR };
 
void dcl(void);
void dirdcl(void);
 
int gettoken(void);
int tokentype;                  /* type of last token */
char token[MAXTOKEN];           /* last token string */
char name[MAXTOKEN];            /* identifier name */
char datatype[MAXTOKEN];        /* data type = char, int, etc */
char out[1000];                 /* output string*/
 
int main(void)  /* convert declaration to words */
{      
        while (gettoken() != EOF) {             /* 1st token on line */
                strcpy(datatype, token);        /*is the datatype*/
                out[0] = '\0';
                dcl();  /* parse rest of line */
                if (tokentype == ']') {
                        printf("syntax error, missing ]\n");
			//while ((c =  getchar()) != EOF && c != '\n')
                        //	;
		}
	         printf("%s: %s %s\n", name, out, datatype);
        }
        return 0;
}
int gettoken(void)      /* return next token */
{      
        int c, getch(void);
        void ungetch(int);
        char *p = token;
 
        while ((c = getch()) == ' ' || c == '\t')
                ;
        if (c == '(' ) {
                if ((c = getch()) == ')') {
                        strcpy(token, "()");
                        return tokentype = PARENS;
                } else {
                        ungetch(c);
                        return tokentype = '(';
                }
        } else if (c == '[') {
                for (*p++ = c; (*p++ = getch()) != ']' && (*(p-1) != '\n'); )
                        ;
                *p = '\0';
		if ((*(p-1)) == ']')
	        	return tokentype = BRACKETS;
		else 
			return tokentype = ']';
		
        } else if (isalpha(c)) {
                for (*p++ = c; isalnum(c = getch()); )
                        *p++ = c;
                *p = '\0';
                ungetch(c);
                return tokentype = NAME;
        } else
                return tokentype = c;
                printf("%c", tokentype);
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
void dcl(void)
{
        int ns;
 
        for (ns = 0; gettoken() == '*'; )       /* count *'s */
                ns++;
        dirdcl();
        while (ns-- > 0)
                strcat(out, " pointer to");
}
/* dirdcl: parse a direct declarator */
void dirdcl(void)
{
        int type;
 
        if (tokentype == '(') {         /* ( dcl ) */
                dcl();
                if (tokentype != ')') {
                        printf("error: missing )\n");
                        printf("syntax error\n");
			tokentype = ERR;
                        return;
                }
        } else if (tokentype == NAME)   /* variable name */
                strcpy(name, token);
        else {
                printf("error: expected name or (dcl)\n");
                printf("syntax error\n");
  	        tokentype = ERR;
                return;
        }
        while ((type=gettoken()) == PARENS || type == BRACKETS)
                if (type == PARENS)
                        strcat(out, " function returning");
                else {
                        strcat(out, " array");
                        strcat(out, token);
                        strcat(out, " of");
                }
}
