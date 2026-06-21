#include <stdio.h>
#include <string.h>
#include "socket.h"
#include "can.h"

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

    // CANフレームの送信
    CAN_Frame frame;
    frame.id = 0x100;
    frame.dlc = 3;
    frame.data[0] = 10;
    frame.data[1] = 20;
    frame.data[2] = 30;

    if(socket_send(client_fd, &frame, sizeof(CAN_Frame)) < 0){
        printf("send failed\n");
        return -1;
    }

    printf("send CAN frame\n");

    // サーバーへ接続
    int fd = socket_client_init("127.0.0.1", 5000);
    if(fd < 0){
        printf("connect failed\n");
        return -1;
    }

    printf("connected to server\n");

    // CANフレーム受信用の変数を用意
    CAN_Frame recv_frame;

    // CANフレームを受信
    int recv_size = socket_recv(fd, &recv_frame, sizeof(CAN_Frame));
    if(recv_size < 0){
        printf("recv failed\n");
        return -1;
    }

    // 受信したCANフレームを表示
    can_print(&recv_frame);

    return 0;
}