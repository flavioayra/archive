/* 
 * Wed Mar  3 16:21:48 EST 1999 - 
 * h4 <h4@locked.org>
 */

#include <stdio.h>
#include <errno.h>  
#include <string.h>

#include <sys/stat.h> /* socket() */
#include <sys/types.h> /* socket() */
#include <sys/ioctl.h> /* socket() */
#include <sys/socket.h> /* socket() */
#include <linux/if.h> /* ifreq */
#include <linux/in.h> /* sockaddr_in */

int main(int argc, char **argv)
{
  struct sockaddr_in *sk8;
  struct ifreq        r0x;

  int sockfd;

  if (argc != 2) {
    fprintf(stderr, "usage: %s <interface>\n", argv[0]);
    exit(1);
  }
  
  /* 
   * linux/if.h
   * #define ifr_name   ifr_ifrn.ifrn_name
   */
  strncpy(r0x.ifr_name, argv[1], sizeof(r0x.ifr_name));

  if ((sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_IP)) == -1) {
    fprintf(stderr, "socket(): %s\n", strerror(errno));
    exit(1);
  }

  if (ioctl(sockfd, SIOCGIFADDR, &r0x) != 0) {
    fprintf(stderr, "ioctl(): %s\n", strerror(errno));
    exit(1);
  }

  /*
   * linux/if.h
   * #define ifr_addr        ifr_ifru.ifru_addr
   */
  sk8 = (struct sockaddr_in *)&r0x.ifr_addr;

  fprintf(stdout, "interface : %s\n", r0x.ifr_name);
  fprintf(stdout, "endereco  : %s\n", inet_ntoa(sk8->sin_addr.s_addr));

  return(0);
}
