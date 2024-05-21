#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cerrno>

#define TCP_PORT 8080

int receive(int socket) {
  printf("Receiving...");
  char inputBuffer[2];
  int recvResult;
  int i;

  recvResult = recv(socket, inputBuffer, 1, 0);
  if (recvResult < 0)
  {
    printf("Error: %s\n", strerror(errno));
    return -1;
  }

  inputBuffer[recvResult] = '\0';
  i = atoi(inputBuffer);

  return i;
}

int main(int argc, char** argv)
{
    setbuf(stdout, NULL);
    printf("Setting up a new socket on port %d, %d\n", TCP_PORT, "please wait...");

    char myString[] = "abcdefghijklmnopqrstuvwxyz";

    // Create a socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
      printf("Error: %s\n", strerror(errno));
      return 1;
    }

    // Initialize the socket address structure
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the address
    int bind_result = bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));
    if (bind_result < 0) {
        printf("Error: %s\n", strerror(errno));
        return 1;
    }

    // Listen for incoming connections
    listen(sockfd, 5);
    printf("Listening...");

    // Accept an incoming connection
    int new_sockfd = accept(sockfd, NULL, NULL);
    if (new_sockfd < 0) {
      printf("Error: %s\n", strerror(errno));
      return 1;
    }
    printf("Accepting...");

    // Receive a request
    int i = receive(new_sockfd);

    // Print the response
    printf("Selected: %c\n", myString[i-1]);
}