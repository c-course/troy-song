#include <iostream>
#include <fstream>
#include <sys/socket.h>
#include <unistd.h>
#include <strings.h>
#include <arpa/inet.h>

#define PORT 8888
#define DATASIZE 1024

int main(int argc, char *argv[])
{
	if (argc != 2) {
		std::cout << "usage: mycurl filename\n";
		exit(1);
	}

	// Create socket
	int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	// Connect IP, ADDR
	struct sockaddr_in serv_addr;
	//    const char *server_ip = argv[1];
	bzero(&serv_addr, sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);
	connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

	std::cout << "------ server access succesfully ------" << std::endl;

	// send file name
	char buf[DATASIZE];
	bzero(buf, DATASIZE);
	const char *fn = argv[1];
	send(sock, fn, strlen(fn) + 1, 0);

	// receive file
	std::ofstream dist(fn);
	int l = recv(sock, buf, DATASIZE, 0);
	dist.write(buf, DATASIZE);

	dist.close();
	close(sock);
	return 0;
}
