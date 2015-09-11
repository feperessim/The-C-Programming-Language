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

/* Exercise 8-2. Rewrite fopen and _fillbuf with fields instead of explicit bit operations.
 * Compare code size and execution speed */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "syscalls.h"

#define PERMS 0666      /* RW for owner, group, others */

/* fopen: open file, return file ptr */
FILE *fopen(char *name, char *mode)
{
        int fd;
        FILE *fp;

        if (*mode != 'r' && *mode != 'w' && *mode != 'a')
                return NULL;
        for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
                if ((fp->flag.is_read  == 0) && (fp->flag.is_write == 0))
                        break;  /* found free slots */
        if (fp >= _iob + OPEN_MAX)      /* no free slots */
                return NULL;
        if (*mode == 'w')
                fd = creat(name, PERMS);
        else if (*mode == 'a') {
                if ((fd = open(name, O_WRONLY, 0)) == -1)
                        fd = creat(name, PERMS);
                lseek(fd, 0L, 2);
        } else
                fd = open(name, O_RDONLY, 0);
        if (fd == -1)   /* couldn't access name */
                return NULL;
        fp->fd = fd;
        fp->cnt = 0;
        fp->base = NULL;
	fp->flag.is_read = 0;
        fp->flag.is_write = 0;
        fp->flag.is_unbuf = 0;
        fp->flag.is_eof = 0;
        fp->flag.is_err = 0;
        if (*mode == 'r') {
		fp->flag.is_read = 1;
		fp->flag.is_write = 0;
	}
	else {
		fp->flag.is_read = 0;
                fp->flag.is_write = 1;
	}
        return fp;
}

int _fillbuff(FILE *fp)
{
        int bufsize;

        if ((fp->flag.is_read == 0 ) || (fp->flag.is_eof == 1) || (fp->flag.is_err == 1))
                return EOF;
        bufsize = (fp->flag.is_unbuf == 1) ? 1 : BUFSIZ;
        if (fp->base == NULL)   /* no buffer yet */
                if ((fp->base = (char *) malloc(bufsize)) == NULL)
                        return EOF;     /* can't get buffer */
        fp->ptr = fp->base;
        fp->cnt = read(fp->fd, fp->ptr, bufsize);
        if (--fp->cnt < 0) {
                if (fp->cnt == -1)
                        fp->flag.is_eof = 1;
                else
                        fp->flag.is_err = 1;
                fp->cnt = 0;
                return EOF;
        }
        return (unsigned char) *fp->ptr++;
}

int main(void)
{
	FILE *fp = fopen("exercise2.c", "r");
	return 0;
}
