#include <stdio.h>
#include <sys/types.h>
#include <grp.h>
#include <unistd.h>

int main(void) {
  struct group	*gr;
  gid_t		gid_list[1024];
  int		ci;
  int		max_groups;

  max_groups = getgroups (0, NULL);

  if ((char *)getgroups(max_groups, gid_list) == NULL) {
    perror("getgroups()");
    exit(-1);
  }

  for (ci = 0; ci < max_groups; ci++) {
    gr = getgrgid(gid_list[ci]);
    printf("%s ", gr->gr_name);
  }
  printf("\n");
  
  return(0);
  
}
