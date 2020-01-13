#include <iostream>
#include <fstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <unistd.h>

#define PORT 8888
#define BACKLOG 10
#define DATASIZE 1024

int main(int argc, char *argv[])
{
	if (argc != 2) {
		std::cout << "usage: myserver 'server/root/path/' " << std::endl;
	}

	// creat socket
	int serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	// bind IP, ADDR
	struct sockaddr_in serv_addr;
	bzero(&serv_addr, sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(PORT);
	bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

	// listen
	listen(serv_sock, BACKLOG);
	std::cout << "------ waitting for connectting ------" << std::endl;

	// create client socket
	struct sockaddr_in clie_addr;
	socklen_t clie_addr_size = sizeof(clie_addr);
	int clie_sock =
		accept(serv_sock, (struct sockaddr *)&clie_addr, &clie_addr_size);

	std::cout << "------ client access successfully ------" << std::endl;

	// get file name
	char buf[DATASIZE];
	char path[DATASIZE];
	bzero(buf, DATASIZE);
	strcat(path, argv[1]);
	recv(clie_sock, buf, DATASIZE, 0);
	strcat(path, buf);
	bzero(buf, DATASIZE);

	// send file
	std::ifstream fn(path, std::ios::binary);
	fn.read(buf, DATASIZE);
	send(clie_sock, buf, DATASIZE, 0);

	fn.close();
	close(clie_sock);
	close(serv_sock);
	return 0;
}
