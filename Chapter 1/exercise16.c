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

/* Exercise 1-16. Revise the main routine of the longest-line program so it will correctly print the length of arbitrary long input lines, 
 * and as much as possible of the text.
*/
#include <stdio.h>
#define MAXLINE 1000	/* maximum input line length */

int lgetline(char line[], int maxline);
void copy (char to[], char from[]);

/* print the longest input line */
int main(void)
{
	int len;	/* current line length */
	int max;	/* maximum length seen so far */
	char line[MAXLINE];	/*current input line */
	char longest[MAXLINE];	/* longest line saved here */

	max = 0;
	while ((len = lgetline(line, MAXLINE)) > 0) { 
		if (len > max) {
			max = len;
			copy(longest, line);
		}
		printf("The size of actual line: %d %s", len - 1, line);
	}
	if (max > 0) 	/* there was a line */
		printf("%s", longest);

	return 0;
}
/* getline: read a line into s, return length */
int lgetline(char s[], int lim)
{
	int c, i;

	for (i=0; i < lim-1 && (c=getchar()) != EOF && c!='\n'; ++i)
		s[i] = c;
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}

/* copy: copy 'from' into 'to'; assume to is big enough */
void copy(char to[], char from[])
{
	int i;

	i= 0;
	while ((to[i] = from[i]) != '\0')
		++i;
}			

