/* $Id: mypidof.c,v 1.2 1999/11/15 23:58:24 flavio Exp $ */
/*
 * pidof.c - flv@javali.com.br
 *
 * compile with:
 *  gcc -Wall -O2 -o pidof pidof.c -lkvm
 *  chgrp kmem pidof
 *  chown g+s pidof
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#include <fcntl.h>
#include <sys/param.h>
#include <sys/sysctl.h>
#include <kvm.h>
#include <limits.h>


int find_cmd(char *c, char *d);

int main(int argc, char **argv)
{
	register kvm_t	*k;
	register struct	kinfo_proc	*kp;
	char		**name;
	int		num;

	if (argc != 2)
		exit(0);

	if ((k = kvm_openfiles(NULL, NULL, NULL, O_RDONLY, NULL)) == NULL) {
		perror("kvm_openfiles()");
		exit(-1);
	}
  
	if (k == NULL) {
		perror("kvm_open()");
		exit(-1);
	}

	kp = kvm_getprocs(k, KERN_PROC_ALL, 0, &num);

	for (; num >= 0; --num)
		if ((name = kvm_getargv(k, kp++, 0)) != NULL)
			if (find_cmd(*name, *(argv + 1)) == 0)
				printf("%d ", kp->kp_proc.p_pid);

	fputc('\n', stdout);

	kvm_close(k);
	return(0);
}

int find_cmd(char *c, char *d)
{
	register char	*p;

	if ((p = strrchr(c, '/')) == NULL)
		p = c;
	else
		p++;
	
	/*
	 * Select only argv[0] of the proccess
	 */
	p = strtok(p, " ");

	
	/*
	 * Cut off the nom alpha numeric character on the end and 
	 * beggining of the program name
	 * example: cut off the '-' off -tcsh
	 *          and cut off the ':' of sendmail: accepcting (...)
	 */
	while (!isalpha(p[0]))
		p++;
	
	if (isupper(p[strlen(p) - 1]) == 0 && islower(p[strlen(p) - 1]) == 0)
		snprintf(p, strlen(p), "%s", p);

	return(strcmp(p, d));
}
