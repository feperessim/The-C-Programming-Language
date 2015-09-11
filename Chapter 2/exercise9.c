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

/* Exercise 2-9. In a two's complement number system, x &= (x-1) deletes the rightmost 1-bit in x.
 * Explain why. Use this observation to write a faster version of bitcount. */

/* Since every binary digit is a power of two, when you do x - 1 you are moving the rightmost bit on to the right and placing a 0 in that place, with the &
operator then you can remove the rightmost bit, using x &= (x-1) acts directly to the rightmost bit on instead of shift all bits to the right this makes 
this operation be much faster than the previous one, besides you don't have to make a test every time the loop runs to determiner whether there is a bit on */

#include <stdio.h>

int bitcount(unsigned x)
{
	int b;

	for (b = 0; x != 0; x &= (x - 1)) {
		++b;
	}
	return b;
}

int main(void)
{
	printf("%d\n", bitcount(~0));
	return 0;
}
