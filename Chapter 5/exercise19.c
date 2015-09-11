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

/* Exercise 5.19  Modify undcl so that it does not add redundant parentheses to declarations. */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };
enum { NO, YES };

int tokentype;
int pretoken = NO;
int posttoken(void);
int gettoken(void);
char token[MAXTOKEN];           /* last token string */
char out[1000];                 /* output string*/


/* undlc: convert word description to declaration */
int main(void)
{       
        int type;
        char temp[MAXTOKEN];
	void ungetch(int c);	

	while (gettoken() != EOF) {             /* 1st token on line */
                strcpy(out, token);             /*is the datatype*/
                while ((type = gettoken()) != '\n') 
                        if (type == PARENS || type == BRACKETS)
                                strcat(out, token);
                        else if (type == '*') {
					 if((type = posttoken()) == PARENS || type == BRACKETS)
                    				sprintf(temp, "(*%s)", out);
                			 else
                    				sprintf(temp, "*%s", out);
                		strcpy(out, temp);
			}
			else if(type == NAME) {
				sprintf(temp, "%s %s", token, out);
				strcpy(out, temp);
            		}
                        else  
                       		 printf("invalid input at %s\n", token);
                 printf("%s\n", out);
	}       
        return 0;
}
int gettoken(void)
{
    int c, getch(void);
    void ungetch(int);
    char *p = token;

    if(pretoken == YES)
    {
        pretoken = NO;
        return tokentype;
    }
    while((c = getch()) == ' ' || c == '\t')
        ;
    if(c == '(')
    {
        if((c = getch()) == ')')
        {
            strcpy(token, "()");
            return tokentype = PARENS;
        }
        else
        {
            ungetch(c);
            return tokentype = '(';
        }
    }
    else if(c == '[')
    {
        for(*p++ = c; (*p++ = getch()) != ']';)
            ;
        *p = '\0';
        return tokentype = BRACKETS;
    }
    else if(isalpha(c))
    {
        for(*p++ = c; isalnum(c = getch());)
            *p++ = c;
        *p = '\0';
        ungetch(c);
        return tokentype = NAME;
    }
    else
        return tokentype = c;
}


#define BUFSIZE 100
char buf[BUFSIZE];

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
int posttoken(void)
{
    int nexttype;
    
    nexttype = gettoken();
    pretoken = YES;
    return nexttype;
}
