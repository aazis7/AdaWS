#include "client.h"
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include "sock.h"

void client_gateway(void)
{
  // Initialize client
  int                sock;
  struct sockaddr_in server_addr;

  // Create socket TCP
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  {
    perror("Socket creation failed");
    exit(EXIT_FAILURE);
  }

  server_addr.sin_family = AF_INET;
  server_addr.sin_port   = htons(PORT);

  // Convert IP Address into numeric
  if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0)
  {
    perror("Invalid address or address not supported");
    close(sock);
    exit(EXIT_FAILURE);
  }

  // Trying to connect to server
  if (connect(sock, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0)
  {
    perror("Connection failed");
    close(sock);
    exit(EXIT_FAILURE);
  }

  printf("Connected to server at %s:%d\n", SERVER_IP, PORT);

  // Sending HTTP GET request to server
  send_request(sock, "GET / HTTP/1.1\r\nHost: localhost\r\n\r\n");
  receive_response(sock);

  // Sending request for /about
  send_request(sock, "GET /about HTTP/1.1\r\nHost: localhost\r\n\r\n");
  receive_response(sock);

  // Sending request for /purpose
  send_request(sock, "GET /purpose HTTP/1.1\r\nHost: localhost\r\n\r\n");
  receive_response(sock);

  // Close koneksi
  close(sock);
}

void send_request(int sock, const char *request)
{
  // Sending HTTP Request to server
  if (send(sock, request, strlen(request), 0) < 0)
  {
    perror("Send failed");
    close(sock);
    exit(EXIT_FAILURE);
  }
  printf("Request sent:\n%s\n", request);
}

void receive_response(int sock)
{
  char buffer[1024];
  int  bytes_received;

  // Receive response from server
  bytes_received = recv(sock, buffer, sizeof(buffer) - 1, 0);
  if (bytes_received < 0)
  {
    perror("Receive failed");
    close(sock);
    exit(EXIT_FAILURE);
  }

  buffer[bytes_received] = '\0'; // Null-terminate the string
  printf("Response received:\n%s\n", buffer);
}
