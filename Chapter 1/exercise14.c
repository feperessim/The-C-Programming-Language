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

/* Exercise 1-14. Write a program to print a histogram of the frequencies of different characters in its input.
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_CHARS 6

void bar_print(int, int);
void n_height_column(int *);
void frequence_of_chars(void);
int main(void)
{
	frequence_of_chars();
	return 0;
}
void frequence_of_chars(void)
{
	int c, i;
	int get_frequence[MAX_CHARS];

	for (i = 0; i < MAX_CHARS; i++)
		get_frequence[i] = 0;

	while ((c = getchar()) != EOF) {
		if (c == '\n')
			++get_frequence[0];
		else if (c == ' ')
			++get_frequence[1];
		else if (c == '\t')
			++get_frequence[2];
		else if (c >= '0' && c <= '9')
			++get_frequence[3];
		else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
			++get_frequence[4];
		else
			++get_frequence[5];
	}
	n_height_column(get_frequence);
}
void n_height_column(int *frequence)
{
	int i, biggest;
	
	biggest = 0;
	for (i = 0; i < MAX_CHARS; i++)
		if (biggest < frequence[i])
			biggest = frequence[i];
	while (biggest > 0) {		
		for (i = 0; i < MAX_CHARS; i++) {
			bar_print(biggest, frequence[i]);
		}
		putchar('\n');
		biggest--;	
	}
}	
void bar_print(int a, int n)
{
	if (a > n)
		printf(" ");
	else
		printf ("#");
}		

