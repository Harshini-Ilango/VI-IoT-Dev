#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 9000

int main(void)
{
    int sock_fd;

    struct sockaddr_in server;
    struct sockaddr_in client;

    char buffer[100];

    sock_fd = socket(AF_INET, SOCK_DGRAM, 0);

    if (sock_fd == -1)
    {
        perror("socket");
        return 1;
    }

    memset(&server, 0, sizeof(server));

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    server.sin_port = htons(PORT);

    if (bind(sock_fd,
             (struct sockaddr *)&server,
             sizeof(server)) == -1)
    {
        perror("bind");
        close(sock_fd);
        return 1;
    }

    printf("UDP server waiting on 127.0.0.1:%d\n", PORT);

    socklen_t client_len = sizeof(client);

    int n = recvfrom(sock_fd,
                     buffer,
                     sizeof(buffer) - 1,
                     0,
                     (struct sockaddr *)&client,
                     &client_len);

    if (n > 0)
    {
        buffer[n] = '\0';

        printf("Received: %s\n", buffer);

        const char *response = "UDP response\n";

        sendto(sock_fd,
               response,
               strlen(response),
               0,
               (struct sockaddr *)&client,
               client_len);
    }

    close(sock_fd);

    return 0;
}
