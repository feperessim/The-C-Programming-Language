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

/* Exercise 1-2. Experiment to find out what happens when prints's argument string contains \c, where c is some
 * character not listed above.
 * */
#include<stdio.h>

int main(void)
{
	printf("hello, world\c");
	return 0;
}

/* gcc exercise2.c 
 * exercise2.c: In function ‘main’:
 * exercise2.c:8:9: warning: unknown escape sequence: '\c' [enabled by default]
 * felipe@felipe ~/C/K&R_Second_Edition/Exercises/Chapter 1 $ ./a.out 
 * hello, worldc
 * /
 *
