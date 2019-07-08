/* $Id: restrict_login.c,v 1.2 1999/11/15 23:58:25 flavio Exp $ */
/*
 * h4@elvis.locked.org
 * 
 * Sun Sep 26 01:40:22 EST 1999
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <utmp.h>
#include <pwd.h>
#include <signal.h>

#define ALLOW_LOGINS 1

char	*get_user(void);
void	killme(int sig);

int main(void)
{
	struct utmp	*u;
	char	*me;
	int	count = 0;

	me = get_user();

	utmpname(UTMP_FILE);
	setutent();
	while ((u = getutent())) {
		if (u->ut_type == USER_PROCESS && !strcmp(me, u->ut_user)) {
			count++;
			if (count > ALLOW_LOGINS)
				killme(SIGKILL);
		}
	}

	return(0);
}

char *get_user(void) 
{
	struct passwd	*pwd;
	pwd = getpwuid(geteuid());
	
	return(pwd->pw_name);
}

void killme(int sig)
{
	pid_t pid;
  
	kill(getppid(), sig);
}
<Paste>
