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

/* Exercise 7-6. Write a program to compare two files, priting the first line where they differ. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_MAX_SIZE 1024

int main(int argc, char *argv[])
{
        FILE *fp;
	char line_1[LINE_MAX_SIZE];
	char line_2[LINE_MAX_SIZE];
        char *prog = argv[0];   /* program name for errors */


	if (argc == 1) {
		while (1) {
			if ((fgets(line_1, LINE_MAX_SIZE, stdin) != NULL) && (fgets(line_2, LINE_MAX_SIZE, stdin) != NULL)) {
				if (strcmp(line_1, line_2) != 0) {
					fputs(line_1, stdout);
					fputs(line_2, stdout);
					break;
				}
			}
			else {
				break;
			}
		}
	}
	else {
        	if ((fp = fopen(*++argv, "r")) == NULL) {
                	fprintf(stderr, "%s: can't open %s\n", prog, *argv);
                        exit(1);
                } 
		else {
			FILE *fp_2;
			if (*++argv == NULL) {
				fp_2 = stdin;
			}
			else if ((fp_2 = fopen(*argv, "r")) == NULL) {
				fprintf(stderr, "%s: can't open %s\n", prog, *argv);
	                        exit(1);
			}
			while (1) {
				if ((fgets(line_1, LINE_MAX_SIZE, fp) != NULL) && (fgets(line_2, LINE_MAX_SIZE, fp_2) != NULL)) {
					if (strcmp(line_1, line_2) != 0) {
                                        	fputs(line_1, stdout);
                                        	fputs(line_2, stdout);
						break;
                                	}
                        	}
                        	else {
                                	break;
                       		}
			}
		}
	}
        if (ferror(stdout)) {
                fprintf(stderr, "%s: error writing stdout\n", prog);
                exit(2);
        }
        exit(0);
}
