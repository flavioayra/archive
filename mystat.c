/* $Id: mystat.c,v 1.3 2000/02/12 15:45:45 flv Exp $ */
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <pwd.h>
#include <grp.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>


int main (int argc, char **argv)
{
	char		*file, *owner, *group, tipo[100], perm[11];
	int		dev_mnr, dev_mjr;
	struct stat	st;
	struct passwd	*pw;
	struct group	*gr;
	
	if (argc != 2) {
		fprintf(stderr, "uso: %s nomedoarquivo\n", *(argv + 0)); 
		exit(-1); 
	} 
	
	file = *(argv + 1); 
	
	if (stat(file, &st) == -1) {
		perror("stat()");
		exit(-1);
	}
	
	dev_mnr = minor(st.st_dev);
	dev_mjr = major(st.st_dev);
	
	if ((pw = getpwuid(st.st_uid)) == NULL) {
		perror("gepwuid()");
		exit(-1);
	}
	owner = pw->pw_name;
    
	if ((gr = getgrgid(st.st_gid)) == NULL) {
		perror("getgrgid()");
		exit(-1);
	}
	group = gr->gr_name;
	
	strcpy(perm, "----------");
	
	/* Descobri o tipo do arquivo e suas permissoes */
	switch (st.st_mode & S_IFMT) {
	case S_IFSOCK:
		strncpy(tipo, "socket", sizeof(tipo));
		perm[0]	= 's';
		break;
	case S_IFLNK:
		strncpy(tipo, "symbolic link", sizeof(tipo));
		perm[0]	= 'l';
		break;
	case S_IFREG:
		strncpy(tipo, "regular file", sizeof(tipo));
		break;
	case S_IFBLK:
		strncpy(tipo, "block device", sizeof(tipo));
		perm[0]	= 'b';
		break;
	case S_IFDIR:
		strncpy(tipo, "directory", sizeof(tipo));
		perm[0]	= 'd';
		break;
	case S_IFCHR:
		strncpy(tipo, "character device", sizeof(tipo));
		perm[0]	= 'c';
		break;
	case S_IFIFO:
		strncpy(tipo, "fifo", sizeof(tipo));
		perm[0]	= 'f';
		break;
	default:
		strncpy(tipo, "???????", sizeof(tipo));
		perm[0]	= '?';
	}
    
	if (st.st_mode & S_IREAD)
		perm[1] = 'r';

	if (st.st_mode & S_IWRITE)
		perm[2] = 'w';

	if (st.st_mode & S_IEXEC) {
		if (st.st_mode & S_ISUID)
			perm[3] = 's';
		else
			perm[3] = 'x';
	}

	if (st.st_mode & (S_IREAD >> 3))
		perm[4] = 'r';

	if (st.st_mode & (S_IWRITE >> 3))
		perm[5] = 'w';

	if (st.st_mode & (S_IEXEC >> 3)) {
		if (st.st_mode & S_ISGID)
			perm[6] = 's';
		else
			perm[6] = 'x';
	}

	if (st.st_mode & (S_IREAD >> 6))
		perm[7] = 'r';

	if (st.st_mode & (S_IWRITE >> 6))
		perm[8] = 'w';

	if (st.st_mode & (S_IEXEC >> 6))
		perm[9] = 'x';
    
	printf("file:\t \"%s\" -> %s\n", file, tipo);
	printf("size:\t %d bytes\n", (int)st.st_size);
	printf("device:\t %d,%d\n", dev_mjr, dev_mnr);
	printf("mode:\t %o (%s)   uid: %d (%s)   gid: %d (%s)\n", 
	       st.st_mode & 07777, perm, st.st_uid, owner, st.st_gid, group);
    
	return(0);
}
