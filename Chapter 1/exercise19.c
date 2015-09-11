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

/* Exercise 1-19. Write a function reverse(s) that reverses the character string s. Use it to write a program that
 * reverses its input a line at a time.
 */

#include <stdio.h>
#define MAXLINE 1000

int lgetline(char line[], int maxline);
int reverse(char line[], int len);
int main(void)
{
        char line[MAXLINE];
        int len;
	int max;

	max = 0;
        while ((len = lgetline(line, MAXLINE)) > 0)
                if (len > max) {
                        reverse(line, len);
			printf("%s\n", line);
		}
	return 0;
}
int lgetline(char s[], int lim)
{
        int c, i;

        for (i = 0; i < lim-1 && (c = getchar())!=EOF && c!='\n'; ++i)
                s[i] = c;
        if (c == '\n') {
                s[i] = c;
                ++i;
        }
        s[i] = '\0';
        return i;
}
int reverse(char s[], int len)
{
	int i, j;
	char copy[MAXLINE];

	for (i = len - 1, j = 0; i >=  0; --i, j++)
		copy[j] = s[i];
	copy[j] = '\0';
	for (i = 0; copy[i] != '\0'; i++) {
		s[i] = copy[i];
	}
	s[i] = '\0';

	return j;
}
