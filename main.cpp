#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cerrno>

#define CHAR_ARRAY_SIZE 27

char example(int socket, char data[]) {
  char inputBuffer[CHAR_ARRAY_SIZE];
  int recvResult;
  int i;

  recvResult = recv(socket, inputBuffer, CHAR_ARRAY_SIZE - 1, 0);
  if (recvResult < 0)
  {
    printf("Error: %s\n", strerror(errno));
    return -1;
  }

  inputBuffer[recvResult] = '\0';
  i = atoi(inputBuffer);

  printf("Received: %d\n", i);
  fflush(stdout);
  // BAD: i has not been validated.
  return data[i];
}

int main(int argc, char** argv)
{
    // Create a socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        // Error creating socket
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
        // Error binding socket
        return 1;
    }

    // Listen for incoming connections
    listen(sockfd, 5);

    // Accept an incoming connection
    int new_sockfd = accept(sockfd, NULL, NULL);

    // Receive a response
    char myString[] = "abcdefghijklmnopqrstuvwxyz";
    char selected = example(sockfd, myString);

    // Print the response
    printf("Selected: %c\n", selected);
}