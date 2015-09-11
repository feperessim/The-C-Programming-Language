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

/* Exercise 8-5. Modify the fsize program to print the other information contained in the inode entry. */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>	/* flags for read and write */
#include <sys/types.h>	/* typdefs */
#include <sys/stat.h>	/* structure returned by stat */
#include <unistd.h>
#include "dirent.h"

void fsize(char *);

/* print file sizes */
int main(int argc, char **argv)
{
	if (argc == 1)	/* default: current directory */
		fsize(".");
	else
		while (--argc > 0)
			fsize(*++argv);
	return 0;
}

//int stat(char *, struct stat *);
void dirwalk(char *, void (*fcn)(char *));

/* fsize: print size of file "name" */
void fsize(char *name)
{
	struct stat stbuf;

	if (stat(name, &stbuf) == -1) {
		fprintf(stderr, "fsize: can't access %s\n", name);
		return;
	}
	if ((stbuf.st_mode & S_IFMT) == S_IFDIR)
		dirwalk(name, fsize);
	printf("\n%8s %8s %8s %8s %8s %8s %8s %8s %8s %8s %8s %8s %8s %8s",
		"size", "blocks", "blksize", "nlink", "dev", "ino",
		"mode", "uid", "gid", "rdev", "atime", "mtime","ctime", "name\n");
	printf("%8ld %8ld %8ld %8ld %8ld %8lu %8u %8u %8u %8lu %8ld %8ld %8ld %s\n", 
		stbuf.st_size, stbuf.st_blocks, stbuf.st_blksize, 
		stbuf.st_nlink, stbuf.st_dev, stbuf.st_ino,
		stbuf.st_mode, stbuf.st_uid, stbuf.st_gid, 
		stbuf.st_rdev, stbuf.st_atime, stbuf.st_mtime, 
		stbuf.st_ctime, name);
}

#define MAX_PATH 1024

/* dirwalk:	apply fcn to all files in dir */
void dirwalk(char *dir, void (*fcn)(char *))
{
	char name[MAX_PATH];
	Dirent *dp;
	DIR *dfd;

	if ((dfd = opendir(dir)) == NULL) {
		fprintf(stderr, "dirwalk: can't open %s\n", dir);
		return;
	}
	while ((dp = readdir(dfd)) != NULL) {
		if (strcmp(dp->name, ".") == 0
		|| strcmp(dp->name, "..") == 0)
			continue;	/* skip self and parent */
		if (strlen(dir)+strlen(dp->name)+2 > sizeof(name))
			fprintf(stderr, "dirwalk: name %s/%s too long\n",
				dir, dp->name);
		else {
			sprintf(name, "%s/%s", dir, dp->name);
			(*fcn)(name);
		}
	}
	closedir(dfd);
}
#ifndef DIRSIZ
#define DIRSIZ 14
#endif

struct direct {
	/* directory entry */
	ino_t d_ino;
	/* inode number */
	char d_name[DIRSIZ]; /* long name does not have '\0' */
};

/* opendir: open a directory for readdir calls */
DIR *opendir(char *dirname)
{
	int fd;
	struct stat stbuf;
	DIR *dp;

	if ((fd = open(dirname, O_RDONLY, 0)) == -1
		|| fstat(fd, &stbuf) == -1
		|| (stbuf.st_mode & S_IFMT) != S_IFDIR
		|| (dp = (DIR *) malloc(sizeof(DIR))) == NULL)
		return NULL;
	dp->fd = fd;
	return dp;
}


/* local directory structure */
/* readdir: read directory entries in sequence */
Dirent *readdir(DIR *dp)
{
	struct direct dirbuf; /* local directory structure */
	static Dirent d;

	/* return: portable structure */
	while (read(dp->fd, (char *) &dirbuf, sizeof(dirbuf))
		== sizeof(dirbuf)) {
		if (dirbuf.d_ino == 0) /* slot not in use */
			continue;
		d.ino = dirbuf.d_ino;
		strncpy(d.name, dirbuf.d_name, DIRSIZ);
		d.name[DIRSIZ] = '\0'; /* ensure termination */
		return &d;
	}
	return NULL;
}
/* closedir: close directory opened by opendir */
void closedir(DIR *dp)
{
	if (dp) {
		close(dp->fd);
		free(dp);
	}
}
