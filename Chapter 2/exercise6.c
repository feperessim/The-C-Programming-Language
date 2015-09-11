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

/* Exercise 2-6. Write a function setbits(x,p,n,y) that returns x with the n bits that begin at position
 * p set to the rightmost n bits of y, leaving the other bits unchanged.
 */

#include <stdio.h>
#include <limits.h>

unsigned setbits(unsigned x, int p, int n, unsigned y)
{
	return x | ((y << (sizeof (int) * CHAR_BIT -n)) >> (sizeof (int) * CHAR_BIT -n)) << (p + 1 - n);
}

int main(void)
{
	printf("%u\n", setbits(463, 5, 4, 10));
	return 0;
}
