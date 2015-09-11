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

/* Exercise 3-3. Write a function expand(s1,s2) that expands shorthand notations like a-z in the
string s1 into the equivalent complete list abc...xyz in s2. Allow for letters of either case and digits,
and be prepared to handle cases like a-b-c and a-z0-9 and -a-z. Arrange that a leading or trailingis taken literally.
*/

#include <stdio.h>
#include <stdlib.h>

#define IN 1
#define OUT 0
#define MAX 1000
#define MATCH 2
#define IS_UPPER 3
#define IS_LOWER 4
#define IS_DIGIT 5

char *upper = "ABCDEFGHIJKLMNOPQRSTUVXWYZ";
char *lower = "abcdefghijklmnopqrstuvxwyz";
char *digit = "0123456789";

void expand(char *s1, char s2[])
{
	int i, j, k, pos[2], dash = OUT, state_dash = OUT, state = OUT;

	for (i = 0; s1[i] != '\0'; i++) 
		if (s1[i] == '-' && i >= 1)
			dash = IN;
	if (dash == OUT) {
		printf("%s\n", s1);
		exit(EXIT_SUCCESS);
	}
	for (i = 0, j = 0; s1[i] != '\0'; i++) {
 		if (s1[i] == '-' && i >= 1) {
			state_dash = IN;
			for (k = 0; upper[k] != '\0'; k++) {
				if (s1[i-1] == upper[k] && (s1[i-1] < s1[i+1] || s1[i-1] > s1[i+1])) {
					pos[0] = k;
					state++;
				}	
				if (s1[i+1] == upper[k] && (s1[i+1] < s1[i-1] || s1[i+1] > s1[i-1])) {
                                        pos[1] = k;
					state++;
				}
				if (state == MATCH)
					state = IS_UPPER;
				if (upper[k+1] == '\0' && state < MATCH && state > 0) {
					printf("Mismatch Characters !\n");
					exit(EXIT_FAILURE);	
				}
			}
			for (k = 0; lower[k] != '\0' && state != IS_UPPER; k++) {
                                if (s1[i-1] == lower[k] && (s1[i-1] < s1[i+1] || s1[i-1] > s1[i+1])) {
                                        pos[0] = k;
                                        state++;
                                }
                                if (s1[i+1] == lower[k] && (s1[i+1] < s1[i-1] || s1[i+1] > s1[i-1])) {
                                        pos[1] = k;
                                        state++;
                                }
                                if (state == MATCH)
                                        state = IS_LOWER;
                                if (lower[k+1] == '\0' && state < MATCH && state > 0) {
                                        printf("Mismatch Characters !\n");
                                        exit(EXIT_FAILURE);
                                }
                        }
			 for (k = 0; digit[k] != '\0' && (state != IS_UPPER || state != IS_LOWER); k++) {
                                if (s1[i-1] == digit[k] && (s1[i-1] < s1[i+1] || s1[i-1] > s1[i+1])) {
                                        pos[0] = k;
                                        state++;
                                }
                                if (s1[i+1] == digit[k] && (s1[i+1] < s1[i-1] || s1[i+1] > s1[i-1])) {
                                        pos[1] = k;
                                        state++;
                                }
                                if (state == MATCH)
                                        state = IS_DIGIT;
                                if (digit[k+1] == '\0' && state < MATCH && state > 0) {
                                        printf("Mismatch Characters !\n");
                                        exit(EXIT_FAILURE);
                                }
                        }

		}
		
		if (state == IS_UPPER && pos[0] < pos[1]) 
			for (k = pos[0]; k < pos[1]; k++)
				s2[j++] = upper[k+1];
		else if (state == IS_UPPER && pos[0] > pos[1]) 
                        for (k = pos[0]; k > pos[1]; k--)
                                s2[j++] = upper[k-1];
		if (state == IS_LOWER && pos[0] < pos[1])
                        for (k = pos[0]; k < pos[1]; k++)
                                s2[j++] = lower[k+1];
                else if (state == IS_LOWER && pos[0] > pos[1])
                        for (k = pos[0]; k > pos[1]; k--)
                                s2[j++] = lower[k-1];
		if (state == IS_DIGIT && pos[0] < pos[1])
                        for (k = pos[0]; k < pos[1]; k++)
                                s2[j++] = digit[k+1];
                else if (state == IS_DIGIT && pos[0] > pos[1])
                        for (k = pos[0]; k > pos[1]; k--)
                                s2[j++] = digit[k-1];
		if (state_dash == OUT)
			s2[j++] = s1[i];
		else if (state_dash == IN)
			i++;
		state_dash = state = OUT;		
	}
	s2[j] = '\0';
}
	
int main(int argc, char **argv)
{
	char s2[MAX];
	
	if (argc <= 1) {
		printf("No arguments at input !\nLeaving.......\n");
		exit(EXIT_FAILURE);
	}	
	expand(argv[1], s2);
	printf("%s\n", s2);
	return 0;
}	
