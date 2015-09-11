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

/* Exercise 2-8: Write a function rightrot(x, n) that returns the value  of the integer x rotated to the right by n positions.  */

#include <stdio.h>
#include <limits.h>

unsigned rightrot(unsigned x, int n)
{
	if (n <= 0) {
		return x;
	}
	unsigned rmbit;
	unsigned wordsize = sizeof (unsigned) * CHAR_BIT -1; 
	
	while (n > 0) {
		rmbit = x & 01;		/* Get the rightmost bit */
		rmbit <<= wordsize;	/* move the rightmost bit to the leftmost place in the word */
		x >>= 1;		/* Shift all bits to right to get a place at the left to place the rightmost bit there */
		x = (rmbit | x);	/* add the rightmost bit in the leftmost position */
		--n;
	}
	return x;
}

int main(void)
{
	unsigned x = 3;
	printf("%u", rightrot(3, 33));
	return 0;
}
