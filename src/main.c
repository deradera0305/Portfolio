#include <stdio.h>
#include <string.h>
#include "socket.h"

int main(void)
{
    int server_fd = socket_server_init(5000);
    if (server_fd < 0) {
        printf("server init failed\n");
        return -1;
    }

    printf("waiting for client...\n");
    int client_fd = socket_accept(server_fd);
    if (client_fd < 0) {
        printf("accept failed\n");
        return -1;
    }

    printf("client connected!\n");

    char buf[128];

    // --- 受信 ---
    int size = socket_recv(client_fd, buf, sizeof(buf));
    if (size < 0) {
        printf("recv failed\n");
        return -1;
    }
    buf[size] = '\0';
    printf("recv: %s\n", buf);

    // --- 送信 ---
    char msg[] = "Hello Client!";
    if (socket_send(client_fd, msg, strlen(msg)) < 0) {
        printf("send failed\n");
        return -1;
    }
    printf("send: %s\n", msg);

    return 0;
}