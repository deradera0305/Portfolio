#ifndef CAN_H
#define CAN_H

typedef struct{
    int id;                 // CAN ID
    int dlc;                // データ長
    unsigned char data[8];  // データ（最大8バイト）
} CAN_Frame;

void can_init(CAN_Frame *frame, int id, int dlc); //CANフレームの初期化
void can_print(const CAN_Frame *frame); //CANフレームの表示

#endif // CAN_H