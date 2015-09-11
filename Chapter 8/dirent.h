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

#ifndef DIRENT_H
#define DIRENT_H
#endif 

#define NAME_MAX 14	/* longest filename component */
				/* system-dependent */

typedef struct {	/* portable directory entry: */
	long ino;		/* inode number */
	char name[NAME_MAX+1];	/* name + '\0' terminator */
} Dirent;

typedef struct {	/* minimal DIR: no buffering, etc */
	int fd;		/* file descriptor for directory */
	Dirent d;	/* the directory entry */
} DIR;

DIR *opendir(char *dirname);
Dirent *readdir(DIR *dfd);
void closedir(DIR *dfd);

char *name;
struct stat stbuf;

