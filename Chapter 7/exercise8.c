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

/* Exercise7-8. Write a program to print a set of files, starting each new one on a new page, with a title and running page count for each file */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* filecopy: copy file ifp to file ofp */
void filecopy(FILE *ifp, FILE *ofp)
{
        int c;

        while ((c = getc(ifp)) != EOF)
                putc(c, ofp);
}

int main(int argc, char *argv[])
{
	if (argc == 1) {
		fprintf(stdout, "Usage: ./prog.out file_1, file_2, ...\n");
		return 0;
	}
	char *prog = argv[0];
	FILE *fp;
	unsigned page = 1;
	char *title = "\f#################################################\n\tFile: %s Page: %u\t\t\n#################################################\n\n";
	
	 while (--argc > 0) {
                        if ((fp = fopen(*++argv, "r")) == NULL) {
                                fprintf(stderr, "can't open %s\n", *argv);
                                exit(1);
                        } else {
				printf(title, *argv, page);
                                filecopy(fp, stdout);
                                fclose(fp);
				++page;
                        }
	}
        if (ferror(stdout)) {
                fprintf(stderr, "%s: error writing stdout\n", prog);
                exit(2);
        }
        exit(0);
}
