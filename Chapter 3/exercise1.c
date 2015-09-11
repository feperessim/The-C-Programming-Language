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

/* Exercise 2-1. Our binary search makes two tests inside the loop, when one would suffice (at the price of
more tests outside.) Write a version with only one test inside the loop and measure the difference in run-
time. */

#include <stdio.h>

int binsearch(int x, int v[], int n)
{
        int low, high, mid;

        low = 0;
        high = n - 1;
        mid = (low+high)/2;
        while (low <= high && x != v[mid] ) {
		if (x < v[mid])
                        high = mid - 1;
                else
                        low = mid + 1;
                mid = (low+high)/2;
        }
	if (x == mid)
		return mid;

	return -1; /* no match */
}

int main(void)
{
        int v[10], x, i;

        x = 40;
        for (i = 0; i < 10; i++)
                v[i] = i;
        printf("%d\n", binsearch(x, v, 10));
        return 0;
}

