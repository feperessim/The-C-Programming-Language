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

/* Exercise 5-5. Write versions of the library functions strncpy, strncat, and strncmp, which operate on at most the first n characters of their argument 
 * strings. For example, strncpy(s,t,n) copies at most n characters of t to s. Full descriptions are in Appendix B.
 */

#include <stdio.h>

#define MAX_SIZE 30

char *Sstrncpy(char *s, char *ct, int n);		/* copy at most n characters of string ct to s; return s. Pad with '\0''s
							 * if ct has fewer than n characters. */

char *Sstrncat(char *s, char *ct, int n);		/* concatenate at most n characters of string ct to string s, terminate s
							 * with '\0'; return s. */

int Sstrncmp(char *cs, char *ct, int n);		/* compare at most n characters of string cs to string ct; return <0 if
							 * cs<ct, 0 if cs==ct, or>0 if cs>ct. */
int main(void)
{
	char s1[MAX_SIZE] = {0};
	char s2[MAX_SIZE] = {"zSome Stringza"};
	char ct[MAX_SIZE] = {"zzzzzzzz"};

	Sstrncpy(s1, ct, 10);
	printf("s1 = %s\n", s1);
	Sstrncat(s2, ct, 5);
	printf("s2 = %s\n", s2);
	printf("Return of Sstrncmp = %d\n", Sstrncmp(s2, ct, 1));
	return 0;
}

char *Sstrncpy(char *s, char *ct, int n)
{
	int counter = n;
	while (*ct != '\0' && counter != 0) {
		*s++ = *ct++;	
		counter--;
	}
	if (*ct == '\0' && counter > 0) {
		while (counter > 0) {
			*s++ = '\0';
			counter--;
		}
	}
	return s;		
}

char *Sstrncat(char *s, char *ct, int n)
{
        while (*s != '\0') /* find end of s */
       		s++;
        while (*ct != 0 && n > 0) /* copy t */
		*s++ = *ct++;
        s = '\0';
	return s;
}

int Sstrncmp(char *cs, char *ct, int n)
{
	for (; n > 0; cs++, ct++, --n)
		if (*cs != *ct)
			return ((*cs < *ct) ? -1 : 1);
		else if (*cs == '\0')
			return 0;
	return 0;
}
