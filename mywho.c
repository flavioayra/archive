/* $Id */
/*
 * h4@elvis.locked.org
 * 
 * Sat Sep 25 22:41:51 EST 1999
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <utmp.h>
#include <pwd.h>

/* frescura :> */
typedef struct utmp utmp_t;

char *get_user(void);

int main(void)
{
	utmp_t	*u;
	char	*me;
	int	count = 0;

	me = get_user();

	utmpname(UTMP_FILE);
	setutent();
	while ((u = getutent())) 
		if (u->ut_type == USER_PROCESS && !strcmp(me, u->ut_user))
			count++;
  
	if (count != 0)
		printf("%s is logged %d %s!\n", me, count, 
		       (count > 1) ? "times": "time");


	return(0);
}

char *get_user(void) 
{
	struct passwd	*pwd;
	uid_t		uid;
  
	uid	= geteuid();
	pwd	= getpwuid(uid);

	return(pwd->pw_name);
}
