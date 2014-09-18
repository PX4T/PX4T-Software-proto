/*
 * server.c
 *  uses to send msg back after connection
 *  Created on: Sep 18, 2014
 *      Author: root
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define PORTNUM 2343
#define MAXRCVLEN 500

int main(int argc, char *argv[])
{
	char msg[] = "Hello World !\n";
	char buffer[MAXRCVLEN + 1];

	struct sockaddr_in dest; /* socket info machine con to us */
	struct sockaddr_in serv; /* socket info server */
	int mysocket,len;
	socklen_t socksize = sizeof(struct sockaddr_in);

	memset(&serv, 0, sizeof(serv));
	serv.sin_family = AF_INET;                /* connection to TCP/IP */
	serv.sin_addr.s_addr = htonl(INADDR_ANY); /* any interface */
	serv.sin_port = htons(PORTNUM);           /* port number */

	mysocket = socket(AF_INET, SOCK_STREAM, 0);

	bind(mysocket, (struct sockaddr *)&serv, sizeof(struct sockaddr));

	listen(mysocket, 1);
	int consocket = accept(mysocket, (struct sockaddr *)&dest, &socksize);

	while(consocket)
	{



		printf("Incoming connection from %s - sending welcome\n", inet_ntoa(dest.sin_addr));
		send(consocket, msg, strlen(msg), 0);
		consocket = accept(mysocket, (struct sockaddr *)&dest, &socksize);
	}

	close(consocket);
	close(mysocket);
	return EXIT_SUCCESS;
}
