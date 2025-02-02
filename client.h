#ifndef CLIENT_H
#define CLIENT_H

// Define client_gateway entry
extern void client_gateway(void);
// Define send_request to server
extern void send_request(int sock, const char *request);
// Define receive_response from server
extern void receive_response(int sock);

#endif // CLIENT_H
