#include <avr/io.h>

#include <stdbool.h>
#include "Ring_buffer.h"
#include "Ring_buffer_Bit.h"

// 環状バッファを初期化
// arg 1, Ring_Bufferの構造体ポインタ
// arg 2, リングバッファに使用する配列
// arg 3, リングバッファの長さ(byte単位)
void Ring_Buffer_Bit_init(Ring_Buffer_Bit *_this, uint8_t *_array, ring_buffer_index_t _length)
{
    Ring_Buffer_init(&_this->ring_buffer, _array, _length);

    // 変数を初期化する
    _this->write_bit_buffer = 0;
    _this->write_bit_count = 0;

    _this->read_bit_buffer = 0;
    _this->read_bit_count = 0;
}

// 書き込み上限に達しても書き込む
// arg 1, Ring_Bufferの構造体ポインタ
// arg 2, 書き込むデータ
void Ring_Buffer_Bit_Overwrite(Ring_Buffer_Bit *_this, bool _data)
{
    // データを入れる
    _this->write_bit_buffer = (_this->write_bit_buffer << 1) | _data;
    _this->write_bit_count++;

    // bit_bufferに8bitデータが貯まった
    if (8 <= _this->write_bit_count)
    {
        // 1byte型のリングバッファに書き込む
        Ring_Buffer_Overwrite(&_this->ring_buffer, _this->write_bit_buffer);

        // 変数を初期化する
        _this->write_bit_buffer = 0;
        _this->write_bit_count = 0;
    }
}

// 書き込み上限に達すると書き込まない
// arg 1, Ring_Bufferの構造体ポインタ
// arg 2, 書き込むデータ
// return true, 書き込めた
// return false, 書き込めない
bool Ring_Buffer_Bit_write(Ring_Buffer_Bit *_this, bool _data)
{
    // bit_bufferと1byte型リングバッファに空きがある場合、書き込む
    if (_this->write_bit_count < 8 && Ring_Buffer_is_space(&_this->ring_buffer))
    {
        Ring_Buffer_Bit_Overwrite(_this, _data);
        return true;
    }
    return false;
}

// 環状バッファから読み取る
// arg 1, Ring_Bufferの構造体ポインタ
bool Ring_Buffer_Bit_read(Ring_Buffer_Bit *_this)
{
    // read_bit_countにデータが入っていない場合
    if (_this->read_bit_count == 0)
    {
        // 1byte型リングバッファにデータがある場合
        if (Ring_Buffer_is_data(&_this->ring_buffer))
        {
            // read_bit_bufferに1byteデータを入れる
            Ring_Buffer_read(&_this->ring_buffer, &_this->read_bit_buffer);
            // read_bit_countにビット数を入れる
            _this->read_bit_count = 8;
        }
        // read側にデータが無かった場合、write側からデータを取ってくる
        else if (0 < _this->write_bit_count)
        {
            // write側のデータをread側に移す
            _this->read_bit_buffer = _this->write_bit_buffer;
            _this->read_bit_count = _this->write_bit_count;

            // write側を初期化する
            _this->write_bit_buffer = 0;
            _this->write_bit_count = 0;
        }
        else // データが無い場合
        {
            return 0;
        }
    }

    // read_bit_bufferから1ビット取り出す
    _this->read_bit_count--;
    return (_this->read_bit_buffer >> _this->read_bit_count) & 1;
}

// リングバッファ配列をリセットする
void Ring_Buffer_Bit_reset(Ring_Buffer_Bit *_this)
{
    Ring_Buffer_reset(&_this->ring_buffer);

    _this->write_bit_buffer = 0;
    _this->write_bit_count = 0;

    _this->read_bit_buffer = 0;
    _this->read_bit_count = 0;
}

// 環状バッファが満タンならtrueを返す
// arg 1, Ring_Bufferの構造体ポインタ
bool Ring_Buffer_Bit_is_full(Ring_Buffer_Bit *_this)
{
    if (8 <= _this->write_bit_count && Ring_Buffer_is_full(&_this->ring_buffer))
    {
        return true;
    }
    return false;
}

// 環状バッファに空きがあるならtureを返す
// arg 1, Ring_Bufferの構造体ポインタ
bool Ring_Buffer_Bit_is_space(Ring_Buffer_Bit *_this)
{
    return !Ring_Buffer_Bit_is_full(_this);
}

// 環状バッファが「空っぽ」ならtrueを返す
// arg 1, Ring_Bufferの構造体ポインタ
bool Ring_Buffer_Bit_is_empty(Ring_Buffer_Bit *_this)
{
    if (0 == _this->read_bit_count && Ring_Buffer_is_empty(&_this->ring_buffer) && 0 == _this->write_bit_count)
    {
        return true;
    }
    return false;
}

// 環状バッファにデータがあるならtureを返す
// arg 1, Ring_Bufferの構造体ポインタ
bool Ring_Buffer_Bit_is_data(Ring_Buffer_Bit *_this)
{
    return !Ring_Buffer_Bit_is_empty(_this);
}

// リングバッファ内のデータの数を返す（bit単位）
// arg 1, Ring_Bufferの構造体ポインタ
uint32_t Ring_Buffer_Bit_is_length(Ring_Buffer_Bit *_this)
{
    return _this->read_bit_count + _this->write_bit_count + Ring_Buffer_is_length(&_this->ring_buffer) * 8;
}

// 環状バッファの最大長さを返す
uint32_t Ring_Buffer_Bit_is_max(Ring_Buffer_Bit *_this)
{
    return 8 + Ring_Buffer_is_max(&_this->ring_buffer) * 8;
}