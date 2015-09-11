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

/* Exercise 2-10. Rewrite the function lower, which converts upper case letters to lower case, with a
 * conditional expression instead of if-else.
 */

#include <stdio.h>

int lower (int c)
{
	return (c >= 'A' && c <= 'Z') ? c + 'a' - 'A' : c;
}
int main(void)
{
	int c;

	while (c = getchar(), c != EOF) {
		c = lower(c);
		putchar(c);
	}	
	return 0;
}	
