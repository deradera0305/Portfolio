#include "socket.h"      
#include <unistd.h>      // close()
#include <string.h>      // memset()
#include <arpa/inet.h>   // sockaddr_in, htons(), inet_pton()
#include <sys/socket.h>  // socket(), bind(), listen(), accept(), connect()

int socket_server_init(int port){

    // 1.ソケット作成
    // AF_INIT     : IPv4
    // SOCK_STREAM : TCP
    // 0           : プロトコル自動選択

    int server_fd = socket(AF_INET, SOCK_STREAM, 0); 
    if(server_fd < 0){
        return -1; // ソケット作成失敗時
    }

    // 2.サーバーのアドレス設定を設定
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr)); // 構造体をゼロ初期化！

    addr.sin_family = AF_INET;                // IPv4を利用
    addr.sin_addr.s_addr = htonl(INADDR_ANY); // すべてのIPで待ち受ける
    addr.sin_port = htons(port);              // ポート番号をネットワークバイトオーダーへ変換

    // 3.bind()でソケットにアドレスを割り当てる
    // server_fd: 割り当てる対象のソケット
    // addr     : IP/port情報
    if(bind(server_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0){
        close(server_fd); //ソケットを閉じる
        return -1; // ポート割り当て失敗
    }

    // 4.listen()で接続待ち状態にする
    // 第2引数　5: 待ち受けキューの最大数（今回は5に設定する）
    if(listen(server_fd, 5) < 0){
        close(server_fd);
        return -1; // 待ち受け状態への移行失敗
    }

    // 5.成功したらserver_fdを返す
    return server_fd;
}

int socket_accept(int server_fd){
    // 1.クライアントからの接続を受けとるための構造体を用意する
    struct sockaddr_in client_addr;
    socklen_t addr_len = sizeof(client_addr);

    // 2.接続を受け入れる（クライアントが来るまでブロックする）
    // server_fd : 待ち受け用ソケット
    // client_addr : クライアントのIP/portが入る
    // addr_len : 構造体のサイズ
    int client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &addr_len);
    if(client_fd < 0){
        return -1; // 受け入れ失敗
    }

    // 3.通信用のソケット番号を返す
    return client_fd;
}

int socket_client_init(const char* ip, int port){
    // 1.ソケット作成（IPV4/TCP）
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(client_fd < 0){
        return -1; // ソケット作成失敗
    }

    // 2.サーバーのアドレス設定
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr)); //構造体をゼロ初期化

    server_addr.sin_family = AF_INET; // IPv4
    server_addr.sin_port = htons(port); // ポート番号をネットワークバイトオーダーへ変換「

    // 3.IPアドレスをバイナリ変換
    if(inet_pton(AF_INET, ip, &server_addr.sin_addr) <= 0){
        close(client_fd);
        return -1; // IPアドレス変換失敗
    }

    // 4.connect()でサーバーに接続
    if(connect(client_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
        close(client_fd);
        return -1; // 接続失敗
    }

    // 5.成功したら通信用ソケットを返す
    return client_fd; 
}

int socket_recv(int fd, void* buf, size_t size){
    // fd: 受信に使用するソケット
    // buffer: 受信データを格納するバッファ

    int recv_size = recv(fd, buf, size, 0); // 受信

    if(recv_size < 0){
        return -1; // 受信失敗
    }
    return recv_size; // 受信したバイト数
}

int socket_send(int fd, const void *buf, size_t size)
{
    int send_size = send(fd, buf, size, 0);  // 送信

    if (send_size <= 0) {
        return -1;  // 送信失敗
    }

    return send_size;     // 送信バイト数
}
