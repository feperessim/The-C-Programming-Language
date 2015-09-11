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

/* Exercise 7-9. Functions like isupper can be implemented to save space or to save time. Explore both possibilities */

#include <stdio.h>

#define ISUPPER(c) (c >= 'A' && c <= 'Z') ? 1 : 0	/* To save time */

int is_upper(int c)	/* To save space */
{
	if (c >= 'A' && c <= 'Z')
		return 1;
	else
		return 0;
}

int main(void)
{
	printf("%d\n", ISUPPER('A'));
	printf("%d\n", ISUPPER('g'));
	printf("%d\n", is_upper('A'));
        printf("%d\n", is_upper('g'));

	return 0;
}

