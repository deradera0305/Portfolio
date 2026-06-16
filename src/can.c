#include <stdio.h>
#include "can.h"

//CANフレームを初期化
void can_init(CAN_Frame *frame, init id, int dlc){
    frame->id = id; // CAN IDを設定
    frame->dlc = dlc; //データ長の設定

    // データを0で初期化
    for(int i = 0; i < 8; i++){
        frame->data[i] = 0;
    }
}

// CANフレームの内容を表示
void can_print(const CAN_Frame *frame){
    printf("--- CAN Frame ---\n");
    printf("ID: 0x%X\n", frame->id); // 16進数で表示
    printf("DLC: %d\n", frame->dlc); // データ長表示

    printf("DATA: ");
    for(int i = 0; i < frame->dlc; i++){
        printf("%d ", frame->data[i]); // データを10進数で順に表示
    }
    printf("\n"); //最後に改行
}