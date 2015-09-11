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

/* Exercise 2-4. Write an alternative version of squeeze(s1,s2) that deletes each character in s1 that
 * matches any character in the string s2. */

#include <stdio.h>
#include <string.h>

#define IN 1
#define OUT 0

void squeeze(char s1[], char s2[])
{
        int i, j, k, state = OUT;

	for (i = k = state = OUT; s1[i] != '\0'; i++) {
		for (j = 0; s2[j] != '\0'; j++)
			if (s1[i] == s2[j])
				state = IN;	
		if (state == OUT)
			s1[k++] = s1[i];
		state = OUT;	
	}
	s1[k] = '\0';
}		
int main(void)
{
	char s1[] = "aBCDEFghi"; 
	squeeze(s1,"ABCdefGhI");
	printf("%s\n", s1);
	return 0;
}
	
