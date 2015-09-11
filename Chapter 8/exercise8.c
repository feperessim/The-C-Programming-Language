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

/* Exercise 8-8 Write a routine bfree(p,n) that will free an arbitrary block p
 * of n characters into the free list maintained by malloc and free. By using
 * bfree, a user can add a static or external array to the free list at any time */

#include "syscalls.h"

typedef long Align;

union header {
        struct {
                union header *ptr;  /* next block if on free list */
                unsigned size;      /* size of this block */
        } s;
};

typedef union header Header;

/* bfree: free an arbitrary block p of n chars */
unsigned bfree(char *p, unsigned n)
{
	Header *hp;

	if (n < sizeof(Header))
		return 0;	/* too small */
	hp = (Header *) p;
	hp->s.size = n / sizeof(Header);
	free((void *)(hp+1));
	return hp->s.size;
}
