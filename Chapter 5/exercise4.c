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

/* Exercise 5-4. Write the function strend(s,t), which returns 1 if the string t occurs at the end of the string s, and zero otherwise */

#include <stdio.h>
#include <string.h>

int strend(char *s, char *t)
{
	s += (strlen(s) - strlen(t));

	while (*s++ == *t++)
		if (*s == '\0')
			return 1;
	return 0;
}

int main(void)
{
	char s[] = {"AbCdEAgggE"};
	char t[] = {"AgggE"};

	if (strend(s, t))
		printf("s occur at the t end\n");
	else
		printf("s doesn't occur at the t end\n");
	return 0;
}	
