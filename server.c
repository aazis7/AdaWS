#include "server.h"
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include "sock.h"

void server_gateway(void)
{
  // Initialize server
  int                server_socket, client_socket;
  struct sockaddr_in server_addr, client_addr;
  socklen_t          client_addr_len = sizeof(client_addr);

  // Create socket TCP
  if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  {
    perror("Socket creation failed");
    exit(EXIT_FAILURE);
  }

  // Allow to reuse the address using SO_REUSEADDR
  int opt = 1;
  if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) !=
      0)
  {
    perror("setsockopt(SO_REUSEADDR) failed");
    close(server_socket);
    exit(EXIT_FAILURE);
  }

  // Append server address
  server_addr.sin_family      = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port        = htons(PORT);

  // Bind socket with server address
  if (bind(server_socket, (struct sockaddr *) &server_addr,
           sizeof(server_addr)) == -1)
  {
    perror("Bind failed");
    close(server_socket);
    exit(EXIT_FAILURE);
  }

  // Listening connection
  if (listen(server_socket, MAX_CONN) == -1)
  {
    perror("Listen failed");
    close(server_socket);
    exit(EXIT_FAILURE);
  }

  printf("Server listening on port %d...\n", PORT);

  while (1)
  {
    // Get client connection
    if ((client_socket = accept(server_socket, (struct sockaddr *) &client_addr,
                                &client_addr_len)) == -1)
    {
      perror("Accept failed");
      continue;
    }

    // Handle request from client
    handle_request(client_socket);

    // Close socket client after request
    close(client_socket);
  }

  // Close socket server
  close(server_socket);
}

void handle_request(int client_socket)
{
  char buffer[1024];
  int  read_size;

  // Read permission from client
  read_size = read(client_socket, buffer, sizeof(buffer) - 1);
  if (read_size < 0)
  {
    perror("Read failed");
    return;
  }
  buffer[read_size] = '\0'; // Null-terminate the string

  printf("Request:\n%s\n", buffer); // Print the request for debugging

  // Serves file based on GET Request
  if (strstr(buffer, "GET / HTTP/1.1") != NULL)
  {
    serve_file(client_socket, "static/index.html", "text/html");
  }
  else if (strstr(buffer, "GET /about HTTP/1.1") != NULL)
  {
    serve_file(client_socket, "static/about.html", "text/html");
  }
  else if (strstr(buffer, "GET /purpose HTTP/1.1") != NULL)
  {
    serve_file(client_socket, "static/purpose.html", "text/html");
  }
  else
  {
    // If file not found
    char *response =
        "HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\n\r\n"
        "<html><body><h1>404 Not Found</h1></body></html>";
    write(client_socket, response, strlen(response));
  }
}

void serve_file(int client_socket, const char *file_path,
                const char *content_type)
{
  FILE *file = fopen(file_path, "r");

  // Check file is undefined or NULL
  if (file == NULL)
  {
    perror("File not found");
    char *response =
        "HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\n\r\n"
        "<html><body><h1>404 Not Found</h1></body></html>";
    write(client_socket, response, strlen(response));
    return;
  }

  // Read file content
  fseek(file, 0, SEEK_END);
  long file_size = ftell(file);
  fseek(file, 0, SEEK_SET);

  char *file_content = malloc(file_size + 1);
  fread(file_content, 1, file_size, file);
  fclose(file);
  file_content[file_size] = '\0';

  // Sending HTTP Header and content file
  char header[256];
  snprintf(header, sizeof(header),
           "HTTP/1.1 200 OK\r\n"
           "Content-Type: %s\r\n"
           "Content-Length: %ld\r\n\r\n",
           content_type, file_size);

  write(client_socket, header, strlen(header));
  write(client_socket, file_content, file_size);

  free(file_content); // free memory allocation
}
