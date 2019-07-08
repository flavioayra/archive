#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <ifaddrs.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>

struct sockaddr *get_iface_addr(const char *iface_name)
{
	struct ifaddrs *ifaddr;
	struct sockaddr_in *s;

	if (getifaddrs(&ifaddr) == -1) {
		fprintf(stderr, "get_iface_addr(): getifaddrs(): %s\n", 
			strerror(errno));
		return NULL;
	}

	while (ifaddr) {
		if (!strcmp(iface_name, ifaddr->ifa_name) && 
		    ifaddr->ifa_addr->sa_family == AF_INET) 
			return ifaddr->ifa_addr;
		
		ifaddr = ifaddr->ifa_next;
	}

	fprintf(stderr, "%s: inet address not found\n", iface_name);
	return NULL;
}

int main(int argc, char **argv)
{
	struct sockaddr *saddr;
	struct sockaddr_in *s;
	char ip[14];

	if (argc != 2) {
		fprintf(stderr, "uso: %s <iface_name>\n", *argv);
		exit(-1);
	}

	saddr = get_iface_addr(argv[1]);
	if (saddr == NULL) 
		exit(-1);

	s = (struct sockaddr_in *)saddr;

	fprintf(stderr, "%s: %s\n", argv[1], inet_ntoa(s->sin_addr));

	return 0;
}
