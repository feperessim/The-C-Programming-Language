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
 * string s1 into the equivalent complete list abc...xyz in s2. Allow for letters of either case and digits,
 * and be prepared to handle cases like a-b-c and a-z0-9 and -a-z. Arrange that a leading or trailingis taken literally.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define DASH '-'

enum states {NONE, IS_LOWER, IS_UPPER, IS_DIGIT};

char *ch_str_cmp(char c, const char *str)
{
	while ((c != *str) && (*str != '\0'))
		++str;
	if (c == *str) {
		return (char *) str;
	}
	else
		return NULL;		
}

int expand(char *s1, char *s2)
{
	const char *upper = "ABCDEFGHIJKLMNOPQRSTUVXWYZ";
	const char *lower = "abcdefghijklmnopqrstuvxwyz";
	const char *digit = "0123456789";
	char *start, *end;
	int i, j,  state = NONE;

	for (i = 0, j = 0; s1[i] != '\0'; i++) {
		if (s1[i] == DASH && i > 0) {
			if (islower(s1[i-1]) && islower(s1[i+1])) { 
				state = IS_LOWER;
			}
			else if (isupper(s1[i-1]) && isupper(s1[i+1])) {
				state = IS_UPPER;
			}
			else if (isdigit(s1[i-1]) && isdigit(s1[i+1])) {
				state = IS_DIGIT;
			}
			else {
				printf("Cannot Expand!\n"); 
				exit(EXIT_FAILURE);
			}	
		}
		switch (state) {
			case NONE:
				s2[j++] = s1[i];
				break;
			case IS_UPPER:
				start = ch_str_cmp(s1[i-1], upper);
				end = ch_str_cmp(s1[i+1], upper);
				if (*start == *end) {
					s2[j++] = *start;
				}
				else if ((start && end != NULL) && (start < end)) {
					while ((start < end) && (*start != '\0')) {
						++start;
						s2[j++] = *start;	
					}
				}
				else if ((start && end != NULL) && (start > end)) {
					while ((start > end) && (*start != '\0')) {
						--start;
						s2[j++] = *start;
					}
				}
				else {
					printf("Unknown error:\n");
					exit(EXIT_FAILURE);
				}	
				state = NONE;
				i++;
				break;
			case IS_LOWER:
                                start = ch_str_cmp(s1[i-1], lower);
                                end = ch_str_cmp(s1[i+1], lower);
                                if (*start == *end) {
                                        s2[j++] = *start;
                                }
                                else if ((start && end != NULL) && (start < end)) {
                                        while ((start < end) && (*start != '\0')) {
                                                ++start;
                                                s2[j++] = *start;
                                        }
                                }
                                else if ((start && end != NULL) && (start > end)) {
                                        while ((start > end) && (*start != '\0')) {
                                                --start;
                                                s2[j++] = *start;
                                        }
                                }
                                else {
                                        printf("Unknown error:\n");
                                        exit(EXIT_FAILURE);
                                }
                                state = NONE;
                                i++;
                                break;
			case IS_DIGIT:
                                start = ch_str_cmp(s1[i-1], digit);
                                end = ch_str_cmp(s1[i+1], digit);
                                if (*start == *end) {
                                        s2[j++] = *start;
                                }
                                else if ((start && end != NULL) && (start < end)) {
                                        while ((start < end) && (*start != '\0')) {
                                                ++start;
                                                s2[j++] = *start;
                                        }
                                }
                                else if ((start && end != NULL) && (start > end)) {
                                        while ((start > end) && (*start != '\0')) {
                                                --start;
                                                s2[j++] = *start;
                                        }
                                }
                                else {
                                        printf("Unknown error:\n");
                                        exit(EXIT_FAILURE);
                                }
                                state = NONE;
                                i++;
                                break;
			default:
				printf("Unknown error:\n");
				exit(EXIT_FAILURE);

		}
	}
	s2[j] = '\0';
	return 0;					
}

int main(int argc, char *argv[])
{
	if (argc == 1)
		printf("Usage: ./a.out args\n");
	else {
		char s2[1000];
		while ((*++argv) != NULL) {
			expand(*argv, s2);
			printf("%s ", s2);
		}
		putchar('\n');
	}
	return 0;	
}
