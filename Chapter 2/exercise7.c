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

/* Exercise 2-7. Write a function invert(x,p,n) that returns x with the n bits that begin at position p
 * inverted (i.e., 1 changed into 0 and vice versa), leaving the others unchanged. */

#include <stdio.h>

unsigned invert(unsigned x, unsigned p, unsigned n)
{
	return x ^ ((~(~0<<n))<< p+1-n);
}

int main(void)
{
	printf("%u\n", invert(3855, 7, 4));
	return 0;
}
