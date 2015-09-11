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

/* Exercise 1-24. Write a program to check a C program for rudimentarpace syntax errors like unmatched parentheses,
brackets and braces. Don't forget about quotes, both single and double, escape sequences, and comments. (This
program is hard if you do it in full generality.)
*/

#include <stdio.h>
#include <stdlib.h>

#define IN 1
#define OUT 0

int inside_comment(void);
int inside_string(void);
int inside_single_quote(void);
int escape_sequence(void);
int check_braces(int);
int is_brackets(int *); 
int is_parentheses(int *);
int main(void)
{
        int c, is_braces;

	is_braces = 0;
        while (c = getchar(), c!= EOF) {
		if (c != '/' && c != '"' && c != '\\')
                        putchar(c);
                if (c == '/')
                        inside_comment();
                if (c == '"')
                        inside_string();
                if (c == '\\')
                        escape_sequence();
		if (c == '\'')
			inside_single_quote();
		if (c == '{' || c == '}')	
			is_braces++;
		if (c == '[' || c == ']')
			is_brackets(&c);
		if (c == '(' || c == ')')
			is_parentheses(&c);
	}
	check_braces(is_braces);
        return 0;
}
int inside_comment(void)
{
	int c;

        c = getchar();
        if (c != '*') {
                putchar('/');
                putchar(c);
        }
        if (c == '*') {
                while (c = getchar()) {
                	if (c == '*' && (c = getchar()) == '/')
               			return 0;
			else if (c == EOF) {
				printf("\nError: unterminated comment\n");
				exit(EXIT_FAILURE);
			}	
				
	       }
	}
	return 0;
}
int inside_string(void)
{
	int c;

	putchar('"');	
        while (c = getchar()) {
		switch (c) {
			case '\\': 
				escape_sequence();
				break;
			case '"':
				putchar(c);
                       		return 0; 
			case EOF: 
				printf("\nUnmatch double quotes\n");
				exit(EXIT_FAILURE);
			default:
				putchar(c);
		}	
        }
	return 0;
}
int escape_sequence(void)
{
	int c;

	c = getchar();
	switch (c) {
		case '\\':
		case '\'':
		case 'n':
		case 't':
		case 'a':
		case 'b':
		case 'v':
		case '"':
		case '?':
		case '0':
			putchar('\\');
			putchar(c);
			return 0;	
		default:	
			printf("\nEscape Sequence unknown\n");
			exit(EXIT_FAILURE);
	}
}
int inside_single_quote(void)
{
	int c, state;

	state = OUT;
	while (c = getchar()) {
		if (c == '\'' && state) {
			putchar(c);
			return 0;
		}	
		else if (c != '\'' && state) {
			printf ("\nError: missing terminating ' character\n");
			exit(EXIT_FAILURE);
		}	
			
		if (c == '\\') {
			escape_sequence();
			state = IN;
		}	
			
		else if (c != '\\') {
			putchar(c);
			state = IN;
		}	
	}
	return 0;		
}
int check_braces(int i)
{
	if (i == 0) {
		printf("\nError: There is no braces\n");
		exit(EXIT_FAILURE);
	}	
	if (i % 2 != 0) {
		printf("\nError: Unmatch braces\n");
		exit(EXIT_FAILURE);
	}	
	else {
		return 0;
	}
}
int is_brackets(int *c)
{
	int state;

	state = OUT;
	if (*c == '[') {
		while ((*c = getchar()) != EOF) {
			putchar(*c);
			if (*c != ']') {
				state = IN;
			}
			if (*c == ']' && state == IN) {
					//putchar(*c);
					return 0;
			}		
			if (*c == ']' && state == OUT) {
				printf ("\nError: array size missing in ‘araay’\n");
				exit(EXIT_FAILURE);
			}	
		}
	}	
	if (*c == ']') {
		printf("\nError: unitialized brackets. | missing '[' character\n");
		exit(EXIT_FAILURE);
	}
	return 0;
}
int is_parentheses(int *c)
{
	if (*c == ')') {
		printf("\nUnitialized parentheses | missing ( token");
		exit(EXIT_FAILURE);
	}
	if (*c == '(') {
		while ((*c = getchar()) != EOF) {
			putchar(*c);
			if (*c == ')')	
				return 0;
			if (*c == EOF) {	
				printf("\nError: Terminated token ) missing\n");
				exit(EXIT_FAILURE);
			}
			if (*c == '(')
				is_parentheses(&*c);
			if (*c == '\\')
				escape_sequence();
			if (*c == '\'')
				inside_single_quote();
			if (*c == '"')
				inside_string();
		}		
	}
	return 0;
}

