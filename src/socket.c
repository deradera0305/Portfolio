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

    // 4, listen()で接続待ち状態にする

};

