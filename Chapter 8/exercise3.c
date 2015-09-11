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

/* Exercise 8-3. Design and write _flushbuf, fflush and fclose */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "syscalls.h"

int _flushbuf(int c, FILE *file)
{
	if (file < _iob || file >= _iob + OPEN_MAX) {
        	return EOF;
        }
	int bufsize;
	bufsize = (file->flag.is_unbuf == 1) ? 1 : BUFSIZ;
	if (file->flag.is_write != 1) {
		return EOF;
	}
	if (file->flag.is_eof == 1 || file->flag.is_err == 1) {
		return EOF;
	}
	if (file->base == NULL && file->flag.is_unbuf == 0) {   /* no buffer yet */
                if ((file->base = (char *) malloc(bufsize)) == NULL) {
			file->flag.is_unbuf = 1;
			file->flag.is_err = 1;
                        file->cnt = 0;
			file->ptr = file->base;
			return EOF;     /* can't get buffer */
		}
	}
	else {
		if (write(file->fd, file->base, bufsize) == -1) {
			file->flag.is_err = 1;
			return EOF;
		}
	}
	file->cnt = 0;
	file->ptr = file->base;
	*file->ptr++ = c;
	return c;
}

int fflush(FILE *stream)
{
	if (stream < _iob || stream >= _iob + OPEN_MAX) {
		return EOF;
	}
	int retval;
    	FILE *fp;

    	retval = 0;

    	if (stream == NULL) {
        	for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
            		if (fp->flag.is_write == 0 && fflush(fp) == -1)
                	retval = -1;
    	} 
	else {
        	if (stream->flag.is_write == 0) {
            		return -1;
		}
        	_flushbuf(EOF, stream);
        	if (stream->flag.is_err) {
            		retval = -1;
		}
   	 }
    return retval;
}

int fclose(FILE *file)
{
	int fd;

    	if (file == NULL) {
        	return -1;
	}
    	fd = file->fd;
    	fflush(file);
    	file->cnt = 0;
    	file->ptr = NULL;
    	if (file->base != NULL) {
       		free(file->base);
	}
    	file->base = NULL;
    	file->flag.is_write = 0;
	file->flag.is_read = 0;
	file->flag.is_unbuf = 0;
	file->flag.is_eof = 0;
	file->flag.is_err = 0;
    	file->fd = -1;
    	return close(fd);
}
	
int main(void)
{
	return 0;
}	
