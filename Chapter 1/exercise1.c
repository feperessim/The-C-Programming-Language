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

/* Exercise 1-1. Run the ``hello, world'' program on your system. Experiment with leaving out parts of the
 * program, to see what error messages you get.
 */

#include <stdio.h>

int main(void)
{
	printf("hello, world\n");
	return 0;
}


/* Without closer } braces 
 * gcc exercise1.c 
 * exercise1.c: In function ‘main’:
 * exercise1.c:8:2: error: expected declaration or statement at end of input
 */

/* Without include standard input/output library
 * gcc exercise1.c 
 * exercise1.c: In function ‘main’:
 * exercise1.c:7:2: warning: incompatible implicit declaration of built-in function ‘printf’ [enabled by default]
 */

/* Without declare 'main()' 
 * gcc exercise1.c 
 * exercise1.c:7:1: error: expected identifier or ‘(’ before ‘{’ token
 */

