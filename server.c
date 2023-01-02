#include <netinet/ip.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char **argv){
	

	//create socket data structures
	struct sockaddr_in server_info = {0};

	server_info.sin_family = AF_INET;
	server_info.sin_port = htons(1337);
	socklen_t sockaddr_len = sizeof(server_info);


	struct sockaddr client_info = {0};
	socklen_t client_info_len = sizeof(client_info);

	//create socket
	int socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);

	if(socket_file_descriptor < 0){
		perror("cannot create socket");
		return -1;
	}

	//bind (give socket a name)
	if (0 > bind(socket_file_descriptor, (struct sockaddr*)&server_info, sockaddr_len)){
		perror("binding problem");
		return -1;
	}


	//listen
	if(0 > listen(socket_file_descriptor, 0)){
		perror("socket failing to listen");
		return -1;
	}

	//accept connection
	int client_file_descriptor = accept(socket_file_descriptor, &client_info, &client_info_len);
	if (0 > client_file_descriptor){
		perror("failed to accept");
		return -1;
	}

	//server stuff
	char *welcome = "Hello from this completely meaningless endpoint!\r";
	ssize_t sent_message = send(client_file_descriptor, (void *)welcome, strlen(welcome), 0);
	close(client_file_descriptor);

	close(socket_file_descriptor);


}