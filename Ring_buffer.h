#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct
{
    //バッファ配列のポインタ
    volatile uint8_t *buffer;
    //データの先頭
    size_t head;
    
    //データの最後尾
    size_t tail;
    
    //格納できるデータ数
    size_t max;
    
    //現在格納中のデータ数
    size_t length;
}Ring_Buffer;

//環状バッファを初期化
//arg 1, Ring_Bufferの構造体ポインタ
//arg 2, リングバッファに使用する配列
//arg 3, リングバッファの長さ
void Ring_Buffer_init(Ring_Buffer *, uint8_t *, size_t);

//書き込み上限に達しても書き込む
//arg 1, Ring_Bufferの構造体ポインタ
//arg 2, 書き込むデータ
void Ring_Buffer_Overwrite(Ring_Buffer *, uint8_t);

//書き込み上限に達すると書き込まない
//arg 1, Ring_Bufferの構造体ポインタ
//arg 2, 書き込むデータ
//return true, 書き込めた
//return false, 書き込めない
bool Ring_Buffer_write(Ring_Buffer *, uint8_t);

//! 配列のデータを書き込む
bool Ring_Buffer_write_array(Ring_Buffer *, uint8_t*, size_t);

//! 文字列のデータを書き込む
bool Ring_Buffer_write_str(Ring_Buffer *, char*);

//環状バッファから読み取る
//arg 1, Ring_Bufferの構造体ポインタ
bool Ring_Buffer_read(Ring_Buffer*, uint8_t*);

//! 先頭のデータを取得するのみ(削除はしない)
bool Ring_Buffer_fetch(Ring_Buffer *, uint8_t *);

//! 配列に読み出す
bool Ring_Buffer_read_array(Ring_Buffer*, uint8_t*, size_t);

//! 文字配列に読み出す
bool Ring_Buffer_read_str(Ring_Buffer*, char*);

//リングバッファ配列をリセットする
void Ring_Buffer_reset(Ring_Buffer *);

//! リングバッファ内のデータをすべて消す
void Ring_Buffer_reset_force(Ring_Buffer *);

//環状バッファが満タンならtrueを返す
//arg 1, Ring_Bufferの構造体ポインタ
bool Ring_Buffer_is_full(Ring_Buffer *);

bool Ring_Buffer_is_space(Ring_Buffer *);

//環状バッファが「空っぽ」ならtrueを返す
//arg 1, Ring_Bufferの構造体ポインタ
bool Ring_Buffer_is_empty(Ring_Buffer *);

//環状バッファにデータがあるならtureを返す
//arg 1, Ring_Bufferの構造体ポインタ
bool Ring_Buffer_is_data(Ring_Buffer *);

//環状バッファ内のデータの長さを返す
//arg 1, Ring_Bufferの構造体ポインタ
size_t Ring_Buffer_is_length(Ring_Buffer *);

//環状バッファの最大長さを返す
size_t Ring_Buffer_is_max(Ring_Buffer *);

#endif