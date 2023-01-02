#include <netinet/ip.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char **argv){
	

	//create server data structures
	struct sockaddr_in server_info = {0};

	server_info.sin_family = AF_INET;
	server_info.sin_addr.s_addr = htonl(0x7f000001);
	server_info.sin_port = htons(1337);

	socklen_t server_info_len = sizeof(server_info);

	//create socket
	int socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
		if(socket_file_descriptor < 0){
		perror("cannot create socket");
		return -1;
	}

	//connect to server
	if(0 > connect(socket_file_descriptor, (struct sockaddr*)&server_info, server_info_len)){
		perror("connection problem");
		return -1;
	}

	//do client stuff
	char buffer[100];
	ssize_t message = recv(socket_file_descriptor, buffer, sizeof(buffer)-1, 0);
	
	//clean up message
	for(int i=0; i<sizeof(buffer)-1; i++){
		if(buffer[i] == '\r'){
			buffer[i] = '\0';
		}
	}
	printf("%s\n", buffer);

	//clean up
	close(socket_file_descriptor);
	return 0;
}

	
