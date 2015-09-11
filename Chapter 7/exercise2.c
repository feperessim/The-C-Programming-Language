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

/* Exercise 7-2. Write a program that will print arbitrary input in a sensible way. As a minimum, it should
 * print non-graphic characters in octal or hexadecimal according to local custom, and break long text lines.*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE 10000
#define DEFAULT_BREAK_LINE 0
#define LAST_LINE -1

struct lines {
	char *line;
	struct lines *next_line;	
};

int getvalue(char *argv)
{
	if (argv == NULL) { 
		return -1;
	}
	else if (argv[0] == '-') {
		return -1;
	}
	else if (argv[0] == '0') {
		return -1;
	}
	int value, i;

	for (value = 0, i = 0; argv[i] != '\0'; ++i) {
		if (!isdigit(argv[i])) {
			return -1;
		}
		value = value * 10 + argv[i] - '0';
	}
	return value; 
}

int read_line(char *line)
{
	int c, i;

	i = 0;
	while ((c = getchar()) != EOF) {
                line[i] = c;
                if (i == MAXLINE-1) {
                        line[i] = '\0';
			return 1;
		}
		if (c == '\n') {
			line[i++] = c;
			line[i] = '\0';
			return 1;
		}
		++i;
        }
	line[i] = '\0';
	if (i > 0) {
		return LAST_LINE;
	}
	return 0;
}

void save_line(struct lines *lineptr, char *line)
{
	while (lineptr->next_line != NULL) {
		lineptr = lineptr->next_line;
	}
	lineptr->line = malloc(strlen(line)+1);
	strcpy(lineptr->line, line);
	lineptr->next_line = malloc(sizeof *lineptr->next_line); 
}

void del_line(char *line)
{
	int i;

	for (i = 0; line[i] != '\0'; ++i) {
		line[i] = '\0';
	}
}

void line_sort(struct lines *lineptr, int lbreak)
{
	int i, latest_blank = 0, col_counter = 0;

	while (lineptr->next_line != NULL) {
		for (i = 0; lineptr->line[i] != '\0'; ++i) {
			if (isblank(lineptr->line[i])) {
				latest_blank = i;
			}
			if (col_counter >= lbreak) {
				if (latest_blank > 0) {
                                        lineptr->line[latest_blank] = '\n';
					col_counter = 0;
					latest_blank = 0;
				}
			}
			++col_counter;
		}
		lineptr = lineptr->next_line;
	}
}

void print(struct lines *lineptr)
{
	int i;

	while (lineptr->next_line != NULL) {
		for (i = 0; lineptr->line[i] != '\0'; ++i) {
			if (!isgraph(lineptr->line[i]) && !isspace(lineptr->line[i])) {
        			printf("%x", lineptr->line[i]);
        		}
        		else {
        			printf("%c", lineptr->line[i]);
        		}
		}
		lineptr = lineptr->next_line;
	}
}	

int main(int argc, char *argv[])
{
	int lbreak, last;
	char line[MAXLINE];
	struct lines saved_lines;

	saved_lines.next_line = NULL;
	if (argc == 1) {
		lbreak = DEFAULT_BREAK_LINE;
	}
	else {
		if (strcmp(argv[1], "-help") == 0) {
			printf("\nUsage: -help for help\n -bp n to break point where n is the size\nNo arguments a default value will be set\n");
			return 0;	
		}
		else if (strcmp(argv[1], "-bp") == 0) {
			lbreak = getvalue(argv[2]);
			if (lbreak < 0) {
				printf("Wrong argument\n");
				return -1;	
			}
		}	
		else {
			printf("Wrong argument\n");
			return -1;
		}
	}	
	while ((last = read_line(line))) {
		save_line(&saved_lines, line);
		del_line(line);
		if (last == LAST_LINE) {
			break;
		}
	}
	line_sort(&saved_lines, lbreak);
	print(&saved_lines);	
	return 0;
}
