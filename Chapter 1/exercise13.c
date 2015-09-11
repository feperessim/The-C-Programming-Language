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

/* Exercise 1-13. Write a program to print a histogram of the lengths of words in its input. It is easy to draw the
 * histogram with the bars horizontal; a vertical orientation is more challenging.
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_WORD 10 

void print_histogram_horizontal(int size_of_words[]);
void print_histogram_vertical(int size_of_words[]);
int main(void)
{
	int c, words, flag;
	int size_of_words[MAX_WORD];

	words = flag = 0;
	while (flag < MAX_WORD) {
		c = getchar();
        	if (c == ' ' || c == '\n' || c == '\t' || (c >= '0' && c <= '9')) { 
			if (words > 0) {
				size_of_words[flag] = words;
				flag++;
				words = 0;
			}
		}	
                else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
			words++;
		}
	}
	print_histogram_horizontal(size_of_words);
	print_histogram_vertical(size_of_words);
	return 0;
}
void print_histogram_horizontal(int size_of_words[])
{
	int size, i;

	for (i = 0; i < MAX_WORD; i++) {
		size = size_of_words[i];
		while (size > 0) {
			printf("#");
			size--;
		}
		putchar('\n');
	}
	putchar('\n');
	return;	
}
void print_histogram_vertical(int size_of_words[])
{
	int i, biggest;

	biggest = 0;
	for (i = 0; i < MAX_WORD; i++) {
		if (biggest < size_of_words[i])
			biggest = size_of_words[i];
	}
	while (biggest > 0) {
		for (i = 0; i < MAX_WORD; i++) {
			if (size_of_words[i] < biggest)
				printf(" ");
			else if (biggest == size_of_words[i]) {
				printf("#");
				--size_of_words[i];
			}
		}
		biggest--;
		putchar('\n');
	}
	putchar('\n');
	return;	
}	
