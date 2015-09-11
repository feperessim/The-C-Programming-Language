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

/* Exercise 5-10. Write the program expr, which evaluates a reverse Polish expression from the command line, where each operator or operand is a separate 
 * argument. For example,
 * expr 2 3 4 + *
 * evaluates 2 * (3+4).
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAXOP 100       /* max size of operand or operator */
#define NUMBER '0'      /* signal that a number was found */
#define MAXVAL 100      /* maximum depth of val stack */

int getop(char *s);
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
                return val[--sp];
        else {
                printf("error: stack empty\n");
                return 0.0;
        }
}

int operations(char *s[])
{
        int type;
        double op2;

        while (*++s != NULL) {
		type = getop(*s); 
                switch (type) {
                case NUMBER:
                        push(atof(*s));
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
                                push(fmod(pop(),  op2));
                        else
                                printf("error: zero divisor\n");
                        break;
		case '\"':
			printf("Error: Mismatch argument\n");
			exit(EXIT_FAILURE);
			break;
                default:
                        printf("error: unknown command %s\n", *s);
                        break;
                }
	}
	printf("\t%.8g\n", pop());
        return 0;
}
#include <ctype.h>

int getop(char *s)
{
        if (!isdigit(*s) && (*s != '.' && *s != '-'))
                return *s;       /* not a number */
        if (*s == '-' && (!isdigit(*++s)))
			return '-';
        if (isdigit(*s)) /* collect integer part */
                while (isdigit(*s))
			s++;
        if (*s == '.') {   /* collect fractional part */
		s++;
                while (isdigit(*s))
			s++;
	}
       	return NUMBER;
}

int main(int argc, char *argv[])
{
	if (argc == 1)
		printf("Usage: a b c + * / %%\n");
	else
		operations(argv);
	return 0;	
}

