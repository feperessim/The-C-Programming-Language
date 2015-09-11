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

/* Exercise 8-6. The standard library function calloc(n, size) returns a 
 * pointer to n objects of size 'size' with the storage initialized to zero. Write
 * calloc, by calling malloc or by modifying it. */

#include <stdio.h>
#include <stdlib.h>

void *my_calloc(size_t nmemb, size_t size)
{
	char *p = malloc(nmemb * size);

	if (p == NULL) {
		return NULL;
	}
	size_t i;
	for (i = 0; i < nmemb * size; ++i) {
		*(p+i) = 0;
	}
	return p;
}

int main(void)
{
	char *p;
	int i;

	p = (char *)my_calloc(10, sizeof (char));

	for (i = 0; i < 10; ++i) {
		printf("%d\n", *(p+i));
	}
	free(p);
	return 0;
}
