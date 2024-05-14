#ifndef LINER_BUFFER_H
#define LINER_BUFFER_H

#include <stdint.h>
#include <stdbool.h>

#if defined(NOMAL_BUFFER_LENGTH_2_BYTE)
typedef uint16_t nomal_buffer_index_t;
#elif defined(NOMAL_BUFFER_LENGTH_1_BYTE)
typedef uint8_t nomal_buffer_index_t;
#else
    typedef uint8_t nomal_buffer_index_t;
#endif


struct Nomal_buffer
{
    //バッファ配列のポインタ
    uint8_t *buffer;

    //データの先頭
    nomal_buffer_index_t head;
    
    //現在格納中のデータ数
    nomal_buffer_index_t length;

    //格納できるデータ数
    nomal_buffer_index_t max;
};

void Nomal_buffer_init(struct Nomal_buffer *, uint8_t *, uint16_t);

void Nomal_buffer_reset(struct Nomal_buffer *);

bool Nomal_buffer_write(struct Nomal_buffer *, uint8_t);

uint8_t Nomal_buffer_read(struct Nomal_buffer *);

bool Nomal_buffer_is_data(const struct Nomal_buffer *);

bool Nomal_buffer_is_full(const struct Nomal_buffer *);

#endif