/* $Id: mypromisc.c,v 1.3 2000/01/23 16:52:52 flv Exp $ */
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include <unistd.h>
#include <errno.h>
#include <sys/ioctl.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <net/if.h>

int main(int argc, char **argv) {

	struct ifreq	i;  
	int		fd;
	int		oldflags;


	if (argc < 3 || argc > 4) {
		fprintf(stderr, "uso %s <-s <on|off> | -g> <interface>\n",
			*(argv + 0));
		exit(-1);
	}
    

	if (strcmp(*(argv + 1), "-g") == 0) {
		strncpy(i.ifr_name, *(argv + 2), sizeof(i.ifr_name));

		if (strcmp(*(argv + 1), "-g") == 0) {
			
			if ((i.ifr_flags & IFF_PROMISC) != 0)
				printf("Interface em modo promiscuo\n");
			else
				printf("Interface em modo nao promiscuo\n");

			return(0);
		}

	} else if (strcmp(*(argv + 1), "-s") == 0) {
		strncpy(i.ifr_name, *(argv + 3), sizeof(i.ifr_name));
	
		if ((fd = socket(PF_INET, SOCK_DGRAM, 0)) == -1) {
			perror("socket()");
			exit(-1);
		}

		if (ioctl(fd, SIOCGIFFLAGS, &i) == -1) {
			perror("ioctl()");
			exit(-1);
		}
	
		oldflags = i.ifr_flags & (IFF_UP|IFF_BROADCAST|IFF_DEBUG|IFF_LOOPBACK|IFF_POINTOPOINT|IFF_NOTRAILERS|IFF_RUNNING|IFF_NOARP|IFF_ALLMULTI|IFF_MULTICAST);
    
		if (strcmp(*(argv + 2), "on") == 0)
			i.ifr_flags |= IFF_PROMISC;
		else if (strcmp(*(argv + 2), "off") == 0)
			i.ifr_flags = oldflags;
		else
			printf("use 'on' ou 'off'"), exit(-1);
    
		if (ioctl(fd, SIOCSIFFLAGS, &i) == -1) {
			perror("ioctl()");
			exit(-1);
		} else
			printf("Modo promisco setado para %s\n", *(argv + 2));
    
	}

	return(0);
}	      
	      
