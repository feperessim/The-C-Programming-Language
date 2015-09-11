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

#ifndef SYSCALLS_H
#define SYSCALLS_H
#endif

#ifdef NULL
#undef NULL
#endif

#define NULL	0
#define EOF	(-1)
#define BUFSIZ	1024
#define OPEN_MAX 20	/* max files open at once */

typedef struct {
	unsigned int is_read  : 1;
	unsigned int is_write : 1;
	unsigned int is_unbuf : 1;
	unsigned int is_eof   : 1;
	unsigned int is_err   : 1;
} flags;

typedef struct _iobuf {
	int cnt;	/* Characters left */
	char *ptr;	/* next character position */
	char *base;	/* location of buffer */
	flags flag;	/* mode of file access */
	int fd;	/* file descriptor */
} FILE;

extern FILE _iob[OPEN_MAX];

#define stdin 	(&_iob[0])
#define stdout	(&_iob[1])
#define stderr	(&_iob[2])

enum _flags {
	_READ	= 01,	/* file open for reading */
	_WRITE	= 02,	/* file open for writing */
	_UNBUF	= 04,	/* file is unbuffered */
	_EOF	= 010,	/* EOF has occurred on this file */
	_ERR	= 020	/* error occurred on this file */
};

int _fillbuf(FILE *);
int _flushbuf(int, FILE *);

#define feof(p)		(((p)->flag & _EOF) != 0)
#define ferror(p)	(((p)->flag & _ERR) != 0)
#define fileno(p)	((p)->fd)

#define getc(p)	(--(p)->cnt >= 0\
		? (unsigned char) *(p)->ptr++ : _fillbuf(p))
#define putc(x,p) (--(p)->cnt >= 0 \
		? *(p)->ptr++ = (x) : _flushbuf((x), p))

#define getchar()	getc(stdin)
#define putchar(x)	putc((x), stdout)

