#ifndef SOCKET_H
#define SOCKET_H

#include <stddef.h>

//--サーバー側--
int socket_server_init(int port); // サーバーソケットの初期化
int socket_accept(int server_fd); // クライアントからの接続を受け入れる

//--クライアント側--
int socket_client_connect(const char* ip, int port); // クライアントソケットの初期化とサーバーへの接続

//--データ送受信
int socket_send(int fd, const void* buf, size_t len); // データ送信
int socket_recv(int fd, void* buf, size_t len);       // データ受信

/* --- 終了処理 --- */
void socket_close(int fd);          // ソケットを閉じる

#endif // SOCKET_H