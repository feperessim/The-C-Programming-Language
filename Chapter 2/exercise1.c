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

/* Exercise 2-1. Write a program to determine the ranges of char, short, int, and long variables, both
 * signed and unsigned, by printing appropriate values from standard headers  and by direct computation. 
 * Harder if you compute them: determine the ranges of the various floating-point types.
 */

#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <math.h>

int main(void)
{
	printf("Char min: %i\n", CHAR_MIN);
	printf("Char max: %i\n", CHAR_MAX);
	printf("Signed Char min: %d\n", SCHAR_MIN);
	printf("Signed Char max: %d\n", SCHAR_MAX);
	printf("Unsigned Char max: %d\n", UCHAR_MAX);
	printf("Int min: %d\n", INT_MIN);
	printf("Int max: %d\n", INT_MAX);
	printf("Unsigned Int max: %u\n", UINT_MAX);
	printf("Short Int min: %d\n", SHRT_MIN);
	printf("Short Int max: %d\n", SHRT_MAX);
	printf("Unsigned short Int max: %d\n", USHRT_MAX);
	printf("Long Int min: %ld\n", LONG_MIN);
	printf("Long Int max: %ld\n", LONG_MAX);
	printf("Unsigned Long Int max: %lu\n", ULONG_MAX);
	printf("Range of Float min: %E\n", FLT_MIN);
	printf("Range of Float max: %E\n", FLT_MAX);
	printf("Range of double min: %E\n", DBL_MIN);
        printf("Range of double max: %E\n", DBL_MAX);
	printf("Range of long double min: %LE\n", LDBL_MIN);
        printf("Range of long double max: %LE\n", LDBL_MAX);
	printf("Size of Float: %lu Bytes\n", ((unsigned long) sizeof(float)));
	printf("Size of Double: %lu Bytes\n",((unsigned long) sizeof(double)));
	printf("Size of Long Double: %lu Bytes\n", ( sizeof(long double)));
	putchar('\n');
	printf("The size of CHAR max by computation is: %d\n", ((int)pow(2,(sizeof (char) * CHAR_BIT) -1)));
        printf("The size of Signed CHAR max by computation is: %d\n",((signed)pow(2,(sizeof (signed char) * CHAR_BIT) -1)));
	printf("The size of Unsigned CHAR max by computation is: %u\n", ((unsigned)pow(2,(sizeof (unsigned char) * CHAR_BIT))-1));
	printf("The size of INT max by computation is: %d\n", ((int) pow(2,(sizeof (int) * CHAR_BIT) -1)));
	printf("The size of Unsigned INT max by computation is: %u\n",((unsigned) pow(2,(sizeof (unsigned) * CHAR_BIT))));
	printf("The size of Short INT max by computation is: %d\n", ((short)pow(2,(sizeof (short) * CHAR_BIT) -1)));
	printf("The size of Long INT max by computation is: %ld\n", ((long) pow(2,(sizeof (long) * CHAR_BIT) -1)));
	printf("The size of Unsigned Long INT max by computation is: %lu\n",((unsigned long) pow(2,(sizeof (unsigned long) * CHAR_BIT))));
	
	printf("The size of Float max by computation is: %E\n", pow(2, (sizeof (float) * sizeof (float) * CHAR_BIT)));		 
	return 0;
}
