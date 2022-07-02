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
#define PORT 80

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


/*
GET / HTTP/1.1
Host: localhost:4444
User-Agent: curl/7.81.0
Accept: 

*/

	/*Sending a message to the server*/
	char *message="GET /flag HTTP/1.1\r\nHost: localhost:4444\r\nUser-Agent: curl\r\nConnection: close\r\n\r\n";
	int sendmessage=send(sock,message,strlen(message),0);
	printf("The value for send message is %d\n", sendmessage);	
	printf("\n\n===================MESSAGE================\n");
	printf("%s\n",message );



	/*Receiving a message*/

    /* Read the response. */
	printf("\n\n===================RESPONSE================\n");
	#define BUFFER 130897
	int nbytes_total=0;
	char received[BUFFER];

	while ((nbytes_total = recv(sock,received,BUFFER,0)) > 0){
		// printf("nbytes=%d %d\n",nbytes_total ,strlen(received));
		write(1,received,nbytes_total);
	}



	close(sock);
	return 0;
}
