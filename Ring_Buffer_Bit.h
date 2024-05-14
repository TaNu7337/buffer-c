/**
 * @file Ring_buffer_bit.h
 * @author JJ5RZN
 * @brief bit単位専用のリングバッファ
 * @version 0.1
 * @date 2023-08-08
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef _RING_BUFFER_BIT_H_
#define _RING_BUFFER_BIT_H_

#include <stdbool.h>

#include "Ring_buffer.h"

typedef struct
{
    // 8bitの普通のリングバッファを宣言
    Ring_Buffer ring_buffer;

    // 8bit分のバッファ
    uint8_t write_bit_buffer;
    // bit_bufferに何個bitがたまっているか
    uint8_t write_bit_count;
    
    // 8bit分のバッファ
    uint8_t read_bit_buffer;
    // bit_bufferに何個bitがたまっているか
    uint8_t read_bit_count;

}Ring_Buffer_Bit;

//環状バッファを初期化
//arg 1, Ring_Bufferの構造体ポインタ
//arg 2, リングバッファに使用する配列
//arg 3, リングバッファの長さ(byte単位)
void Ring_Buffer_Bit_init(Ring_Buffer_Bit *, uint8_t *, ring_buffer_index_t);

//書き込み上限に達しても書き込む
//arg 1, Ring_Bufferの構造体ポインタ
//arg 2, 書き込むデータ
void Ring_Buffer_Bit_Overwrite(Ring_Buffer_Bit *, bool);

//書き込み上限に達すると書き込まない
//arg 1, Ring_Bufferの構造体ポインタ
//arg 2, 書き込むデータ
//return true, 書き込めた
//return false, 書き込めない
bool Ring_Buffer_Bit_write(Ring_Buffer_Bit *, bool);

//環状バッファから読み取る
//arg 1, Ring_Bufferの構造体ポインタ
bool Ring_Buffer_Bit_read(Ring_Buffer_Bit *);

//リングバッファ配列をリセットする
void Ring_Buffer_Bit_reset(Ring_Buffer_Bit *);


//環状バッファが満タンならtrueを返す
//arg 1, Ring_Bufferの構造体ポインタ
bool Ring_Buffer_Bit_is_full(Ring_Buffer_Bit *);

//環状バッファに空きがあるならtureを返す
//arg 1, Ring_Bufferの構造体ポインタ
bool Ring_Buffer_Bit_is_space(Ring_Buffer_Bit *);

//環状バッファが「空っぽ」ならtrueを返す
//arg 1, Ring_Bufferの構造体ポインタ
bool Ring_Buffer_Bit_is_empty(Ring_Buffer_Bit *);

//環状バッファにデータがあるならtureを返す
//arg 1, Ring_Bufferの構造体ポインタ
bool Ring_Buffer_Bit_is_data(Ring_Buffer_Bit *);

//環状バッファ内のデータの長さを返す
//arg 1, Ring_Bufferの構造体ポインタ
uint32_t Ring_Buffer_Bit_is_length(Ring_Buffer_Bit *);

//環状バッファの最大長さを返す
uint32_t Ring_Buffer_Bit_is_max(Ring_Buffer_Bit *);
#endif