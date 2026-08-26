#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "/tmp/ap_intern_ctrl.sock"

int main(void)
{
    int server_fd;
    int client_fd;

    struct sockaddr_un address;

    char buffer[100];

    /* Create Unix socket */
    server_fd = socket(AF_UNIX, SOCK_STREAM, 0);

    if (server_fd == -1)
    {
        perror("socket");
        return 1;
    }

    /* Remove old socket file if it exists */
    unlink(SOCKET_PATH);

    memset(&address, 0, sizeof(address));

    address.sun_family = AF_UNIX;
    strcpy(address.sun_path, SOCKET_PATH);

    /* Bind socket to path */
    if (bind(server_fd,
             (struct sockaddr *)&address,
             sizeof(address)) == -1)
    {
        perror("bind");
        close(server_fd);
        return 1;
    }

    /* Listen for clients */
    if (listen(server_fd, 5) == -1)
    {
        perror("listen");
        close(server_fd);
        return 1;
    }

    printf("Unix socket server waiting...\n");

    /* Wait for client */
    client_fd = accept(server_fd, NULL, NULL);

    if (client_fd == -1)
    {
        perror("accept");
        close(server_fd);
        return 1;
    }

    /* Read client message */
    int n = read(client_fd, buffer, sizeof(buffer) - 1);

    if (n > 0)
    {
        buffer[n] = '\0';

        printf("Received: %s", buffer);

        /* Send response */
        const char *response = "STATUS: AP is running\n";

        write(client_fd, response, strlen(response));
    }

    close(client_fd);
    close(server_fd);

    unlink(SOCKET_PATH);

    return 0;
}
