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

/* Exercise 7-5. Rewrite the postfix calculator of Chapter 4 to use scanf and/or sscanf to do the input and number conversion */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXOP 100       /* max size of operand or operator */
#define NUMBER '0'      /* signal that a number was found */

int getop(char []);
void push(double);
double pop(void);
void clear(void);
double top = 0;
/* reverse Polish calculator */
int main(void)
{
        int type;
        double op1, op2;
        char s[MAXOP];

        while ((type = getop(s)) != EOF) {
                switch (type) {
                case NUMBER:
                        push(atof(s));
                        break;
                case '+':
                        push(pop() + pop());
                        break;
                case '*':
                        push(pop() * pop());
                        break;
                case '-':
                        op2 = pop();
                        push(pop() - op2);
                        break;
                case '/':
                        op2 = pop();
				if (op2 != 0.0)
                                push(pop() / op2);
                        else
                                printf("error: zero divisor\n");
                        break;
                case '%':
                        op2 = pop();
                        if (op2 != 0.0)
                                push(fmod(pop(), op2));
                        else
                                printf("error: zero divisor\n");
                        break;
                case '\n':
                        printf("\t%.8g\n", pop());
                        break;
                case 'p':
                        if (top <= 0)
                                printf("No elements on the top of stack\n");
                        else
                                push(top);
                        break;
                case 'c':
                        clear();
                        break;
                case 's':
                        op1 = pop();
                        op2 = pop();
                        push(op1);
                        push(op2);
                        break;
                default:
                        printf("error: unknown command %s\n", s);
                        break;
                }
        }
        return 0;
}
#define MAXVAL 100      /* maximum depth of val stack */

int sp = 0;     /* next free stack position */
double val[MAXVAL];     /* value stack */
/* push: push f onto value stack */
void push(double f)
{
        if (sp < MAXVAL)
                val[sp++] = f;
        else
                printf("error: stack full, can't push %g\n", f);
}
/* pop: pop and return top value from stack */
double pop(void)
{
        if (sp > 0)
                return top = val[--sp];
        else {
                printf("error: stack empty\n");
                return top = 0.0;
        }
}
void clear(void)
{
        while (sp > 0)
                val[sp--] = 0.0;
                ;
        val[sp] = top = 0.0;
}
#include <ctype.h>

int getch(void);
void ungetch(int);
/* getop: get next character or numeric operand */
int getop(char s[])
{
        int i; 
	char c;
	
	scanf("%c", &c);
        while ((s[0] = c)  == ' ' || c == '\t')
		scanf("%c", &c);
        s[1] = '\0';
        if (!isdigit(c) && (c != '.' &&  c != '-'))
                return c;       /* not a number */
        i = 0;
        if (c == '-') {
                while ((scanf("%c",&c))) {
                        if (c == '\n') {
                                ungetch(c);
                                return '-';
                        }
                        if (isdigit(c)) {
                                s[++i] = '-';
                                s[i] = c;
                                break;
                        }
                }
        }
        if (isdigit(c)) /* collect integer part */
                while (isdigit(s[++i] = c = getch()))
                        ;
        if (c == '.')   /* collect fractional part */
                while (isdigit(s[++i] = c = getch()))
                        ;
        s[i] = '\0';
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

