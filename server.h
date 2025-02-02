#ifndef SERVER_H
#define SERVER_H

// Define server_gateway entry
extern void server_gateway(void);
// Define handle_request client
extern void handle_request(int client_socket);
// Define serve_file client
extern void serve_file(int client_socket, const char *file_path,
                       const char *content_type);

#endif // SERVER_H
