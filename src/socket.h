#ifndef SOCKET_H
#define SOCKET_H

#include <stddef.h>

//--サーバー側--
int socket_server_init(int port); // サーバーソケットの初期化
int socket_accept(int server_fd); // クライアントからの接続を受け入れる

//--クライアント側--
int socket_client_connect(const char*　ip, int port); // クライアントソケットの初期化とサーバーへの接続

#endif // SOCKET_H