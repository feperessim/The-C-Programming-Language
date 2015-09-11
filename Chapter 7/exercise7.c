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

/* Exercise 7-7. Modify the pattern fiding program of Chapter 5 to take its input from a set of named files of, if no files
 * are named as arguments, from the standard input. Should the file name be printed when a matching line is found? */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_MAX_SIZE 1024

int find(char *pattern, FILE *fp)
{
	int found = 0;
	char line[LINE_MAX_SIZE];

	while (fgets(line, LINE_MAX_SIZE, fp) != NULL) {
		if (strstr(line, pattern) != NULL) {
                                fprintf(stdout, "%s", line);
				++found;
		}
	}
	return (found == 0) ? 0 : 1;
}
int main(int argc, char *argv[])
{
	char *pattern;
	int found = 0;	

	if (argc == 1) {
		printf("Pattern program usage: Pattern file_1, file_2, ...\n\n");
		return 0;
	}
	pattern = *++argv;
	if (*++argv == NULL) {
		found = find(pattern, stdin);
		if (found == 1) {
			printf("\nPattern found in stdin file\n");
		}
		exit(0);
	}
	else {
		FILE *fp;
		char *prog;
		while (--argc > 1) {
			prog = *argv;
			if ((fp = fopen(*argv++, "r")) == NULL) {
				fprintf(stderr, "can't open %s\n", prog);
				exit(1);
			}
			else {
				found = find(pattern, fp);
				if (found == 1) {
	                                printf("Pattern found in %s file\n\n", prog);
               		       }
			}
		}
	}
	if (ferror(stdout)) {
                fprintf(stderr, "%s: error writing stdout\n", argv[0]);
                exit(2);
        }
        exit(0);
}

