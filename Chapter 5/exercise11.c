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

/* Exercise 5-11. Modify the programs entab and detab (written as exercises in Chapter 1) to accept a list of tab stops as arguments. 
 * Use the default tab settings if there are no arguments. */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define DEFAULT 8

int detab(int TABSTOP)
{
	int c, n;

	n = 0;
	while ((c = getchar()) != EOF && c != '\n') {
		if (c != '\n' && c != '\t') {
			++n;;
			putchar(c);
		}	
		if (c == '\t') 
			while (n++ < TABSTOP) 
				putchar(' ');
		if (n >= TABSTOP || c == '\n') 
 			n = 0;
	}
	return 0;
}

int entab(int TABSTOP)
{
        int c, spc, column;

        spc = column = 0;
        while ((c = getchar()) != EOF && c != '\n') {
                if (spc == 0 && c != '\n' && c != ' ') {
                        column++;
                        putchar(c);
                }
                if(spc > 0 && c != ' ' && spc >= TABSTOP) {
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
                if (spc > 0 && c != ' ' && spc < TABSTOP) {
                        while (spc > 0 && spc < TABSTOP) {
                                putchar(' ');
                                spc--;
                        }
                        putchar(c);
                }
                if (c == ' ')
                        spc++;
                if (column >= TABSTOP || c == '\n' || c == '\t')
                        column = 0;
        }
        return 0;
}

int check_arg(char *s)
{
	int digit = 0;
	
	while (*s != '\0') {
		if (isdigit(*s)) 
			digit = digit * 10 + (*s - '0');
		else {
			printf("Input must contain only digits\nLeaving......\n");
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
		printf("Usage: ./a.out arg1 arg2 arg3\nDefault value has been setup\n");
		printf("Testing detab func\n");
		detab(DEFAULT);
		printf("\nTesting entab func\n");
		entab(DEFAULT);
	}
	else {
		for (i = 1; argv[i] != NULL; i++) {
			printf("\nTesting detab func TABSTOP set = %s\n", argv[i]);
			detab(check_arg(argv[i]));
		}
                for (i = 1; argv[i] != NULL; i++) {
			printf("\nTesting entab func TABSTOP set = %s\n", argv[i]);
			entab(check_arg(argv[i]));
		}
	}
	return 0;		
}
