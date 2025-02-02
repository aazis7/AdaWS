#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include "client.h"
#include "server.h"

int main(int argc, char *argv[])
{
  // Check arguments to run server or client
  if (argc < 2)
  {
    fprintf(stderr, "Usage: %s <server|client>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  if (strcmp(argv[1], "server") == 0)
  {
    // Running server
    server_gateway();
  }
  else if (strcmp(argv[1], "client") == 0)
  {
    // Running client
    client_gateway();
  }
  else
  {
    // If there's no arguments
    fprintf(stderr, "Usage: %s <server|client>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  return 0;
}
