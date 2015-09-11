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

/* Exercise 1-18. Write a program to remove trailing blanks and tabs from each line of input, and to delete entirely
 * blank lines. */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXLINE 1000

int lgetline(char line[], int maxline);
int remove_blanks(char line[]);

int main(void)
{
        char line[MAXLINE];
        int len;

        while ((len = lgetline(line, MAXLINE)) > 0) {
                        remove_blanks(line);
			printf("%s", line);
	}
	return 0;
}

int lgetline(char s[], int lim)
{
        int c, i;

        for (i = 0; i < lim-1 && (c = getchar()) !=EOF && c!='\n'; ++i)
                s[i] = c;
        if (c == '\n') {
                s[i] = c;
                ++i;
        }
        s[i] = '\0';
        return i;
}

int remove_blanks(char s[])
{
	int i, j;
	char copy[MAXLINE];
	
	i = j = 0; 
	while (isspace(s[i]) || s[i] == '\n') {
		++i;
	}
	while (s[i] != '\0') {
		if (s[i] == '\n') {
			copy[j++] = s[i++];
			i += strspn(&s[i], "\n");
		}
		else if (s[i] == ' ') {
		        copy[j++] = s[i++];
                        i += strspn(&s[i], " ");
		}
		else if (s[i] == '\t') {
			copy[j++] = s[i++];
			i += strspn(&s[i], "\t");
		}
		else {
			copy[j++] = s[i++];
		}
	}
	copy[j] = '\0';
	for (i = 0; copy[i] != '\0'; i++) {
		s[i] = copy[i];
	}
	s[i] = '\0';
	return j;
}
