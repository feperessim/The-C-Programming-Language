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

/* Exercise 5-12. Extend entab and detab to accept the shorthand
 * entab -m +n
 * to mean tab stops every n columns, starting at column m. Choose convenient (for the user) default behavior.
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define DEFAULT_N 8
#define DEFAULT_M 0

int detab(int TABSTOP, int m)
{
	int c, n, counter;
	
	n = counter = 0;
	while ((c = getchar()) != EOF) {
		if ((c != '\n' && c != '\t') && (counter >= m)) {
			++n;;
			putchar(c);
		}	
		if (c == '\t' && counter >= m) 
			while (n++ < TABSTOP) 
				putchar(' ');
		if (n >= TABSTOP || c == '\n') 
 			n = 0;
		if (c == '\n')
			counter = 0;
		if (counter < m) {
            		counter++;
                        putchar(c);
                }

	}
	putchar('\n');
	return 0;
}

int entab(int TABSTOP, int m)
{
        int c, spc, column, counter;
        
	spc = column = counter = 0;
        while ((c = getchar()) != EOF) {
                if (spc == 0 && c != '\n' && c != ' ' && counter >= m) {
                        column++;
                        putchar(c);
                }
                if(spc > 0 && c != ' ' && spc >= TABSTOP && counter >= m) {
                        while (spc >= TABSTOP) {
                                putchar('\t');
                                spc-= TABSTOP;
                        }
                        while(column > 0) {
                                putchar(' ');
                                column--;
                        }
                        if (spc == 0)
                                putchar(c);
                }
                if (spc > 0 && c != ' ' && spc < TABSTOP && counter >= m) {
                        while (spc > 0 && spc < TABSTOP) {
                                putchar(' ');
                                spc--;
                        }
                        putchar(c);
                }
                if (c == ' ' && counter >= m)
                        spc++;
                if (column >= TABSTOP || c == '\n' || c == '\t')
                        column = 0;
		if (c == '\n')
			counter = 0;
		if (counter < m) {
                	counter++;
                	putchar(c);
                }
		
        }
	putchar('\n');
        return 0;
}

int check_arg(char *s)
{
	int digit = 0;
	
	if (*s != '-' && *s != '+') {
		printf("Wrong Input: Usage ./program -n +m\n");
		exit(EXIT_FAILURE);
	}
	++s;
	while (*s != '\0') {
		if (isdigit(*s))
			digit = digit * 10 + (*s - '0');
		else {
			printf("Input must contain only the characters '-' and '+' and digits\nLeaving......\n");
			exit(EXIT_FAILURE);
		}
		s++;
	}
	return digit;
}

int main(int argc, char *argv[])
{
	int i;

	if (argc == 1) {
		printf("Usage: ./program.out -n +m\nDefault value has been setup\n");
		printf("Testing detab func\n");
		detab(DEFAULT_N, DEFAULT_M);
		printf("\nTesting entab func\n");
		entab(DEFAULT_N, DEFAULT_M);
	}
	else if ((argc > 1 && argc < 3) || (argc > 3))
		printf ("Wrong input. Usage ./program.out -n +m\n");
	else {
		for (i = 1; argv[i] != NULL; i++) {
			detab(check_arg(argv[i]), check_arg(argv[i+1]));
			++i;
		}
                for (i = 1; argv[i] != NULL; i++) {
			entab (check_arg(argv[i]), check_arg(argv[i+1]));
			++i;
		}
	}
	return 0;		
}
