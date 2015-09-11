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

/* Exercise 8-4. The standard library function int fseek(FILE *fp, long offset, int origin) is identical to lseek except that fp 
 * is a file pointer instead of a file descriptor and return value is an int status, not a position. Write fseek. Make sure that 
 * your fseek coordinates properly with the buffering done for the other functions of the library.
 */

#include "syscalls.h"
#include <unistd.h>

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2


int fseek(FILE *fp, long offset, int origin)
{
	if (fp->flag.is_read == 0) {
		return -1;
	}
	if (origin == SEEK_SET) {
		if (offset < fp->cnt) {
			fp->ptr = fp->base + offset;
			fp->cnt = offset;
			lseek(fp->fd, offset, origin);
			fp->flag.is_eof = 0;
		}
		else {
			return fp->cnt - offset;
		}
	}
	else if (origin == SEEK_CUR) {
	        if (offset < fp->cnt) {
			fp->ptr += fp->cnt - (fp->cnt - offset);
                        fp->cnt = offset;
                        lseek(fp->fd, offset, origin);
                        fp->flag.is_eof = 0;
		}
		else {
			return fp->cnt - offset;
		}
	}
	else if (origin == SEEK_END) {
		if (offset <= 0 && fp->ptr + offset >= fp->base) {
			fp->ptr += offset;
                        fp->cnt = lseek(fp->fd, offset, origin);
                        fp->flag.is_eof = 0;
		}
	}
	else {
		return -1;
	}
	return 0;
}


