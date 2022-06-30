/*
*  @author: zerofrost🦊
*  @date: 2022-6-30
*  @compilation: gcc simple_http_client.c -o simple_http_client
*  @description: This is a simple http client similar to curl created to understand how sockets work
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h> 
// #include <arpa/netinet.h>
#include <netinet/in.h>

#define HOST "127.0.0.1"
#define PORT 4444

int main(int argc,char **argv){

	int sock=socket(AF_INET,SOCK_STREAM,0); 
	/*Setting the server information*/
	struct sockaddr_in server_addr;
	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=inet_addr(HOST);
	server_addr.sin_port=htons(PORT);


	/*Connecting to the server*/
	int conn=connect(sock, (struct sockaddr *)&server_addr ,sizeof(server_addr));
	if (conn < 0) {
		fprintf(stderr, "Connecting to server failed. Error %d\n",conn);
		exit(-1);
	}
	printf("Connection to server succeeded\n");


	/*Sending a message to the server*/
	

	return 0;
}
