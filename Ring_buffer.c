#include "Ring_Buffer.h"

// 環状バッファを初期化
// arg 1, Ring_Bufferの構造体ポインタ
// arg 2, リングバッファに使用する配列
// arg 3, リングバッファの長さ

void Ring_Buffer_init(Ring_Buffer *_this, uint8_t *_array, size_t _length)
{
    _this->buffer = _array;

    _this->head = 0;
    _this->tail = 0;
    _this->max = _length;
    _this->length = 0;
}

// 書き込み上限に達しても書き込む
// arg 1, Ring_Bufferの構造体ポインタ
// arg 2, 書き込むデータ
void Ring_Buffer_Overwrite(Ring_Buffer *_this, uint8_t _data)
{
    // バッファに書き込む
    _this->buffer[_this->tail] = _data;

    // 終端を前進する
    _this->tail++;

    // 終端が最後の地点なら０番地に戻る
    //  _this->tail = _this->tail % _this->max;
    if (_this->tail == _this->max)
    {
        _this->tail = 0;
    }

    // 長さを足す（制限あり）
    if (_this->length < _this->max)
    {
        _this->length++;
    }
    else
    {
        // 上限値に達した場合
        // headがtailに押されて前に進む
        _this->head++;
        if (_this->head == _this->max)
        {
            _this->head = 0;
        }
    }
}

// 書き込み上限に達すると書き込まない
// arg 1, Ring_Bufferの構造体ポインタ
// arg 2, 書き込むデータ
// return true, 書き込めた
// return false, 書き込めない
bool Ring_Buffer_write(Ring_Buffer *_this, uint8_t _data)
{
    // 書き込み上限に達しているなら実行しない
    if (_this->length < _this->max)
    { // 書き込む
        Ring_Buffer_Overwrite(_this, _data);
        return true;
    }
    else
    {
        return false;
    }
}

//! 配列のデータを書き込む
bool Ring_Buffer_write_array(Ring_Buffer *_this, uint8_t *_array, size_t _length)
{
    for (size_t i = 0; i < _length; i++)
    {
        //! 書き込めなかった場合
        if (!Ring_Buffer_write(_this, _array[i]))
        {
            return false;
        }
    }
    return true;
}

//! 文字列のデータを書き込む
bool Ring_Buffer_write_str(Ring_Buffer *_this, char *_string)
{
    for (size_t i = 0; _string[i] != '\0'; i++)
    {
        //! 書き込めなかった場合
        if (!Ring_Buffer_write(_this, (uint8_t)_string[i]))
        {
            return false;
        }
    }
    //! 終端文字を書き込む
    if (!Ring_Buffer_write(_this, '\0'))
    {
        return false;
    }

    return true;
}

// 環状バッファから読み取る
// arg 1, Ring_Bufferの構造体ポインタ
//  return uint8_t, 読み取ったデータ
bool Ring_Buffer_read(Ring_Buffer *_this, uint8_t *_data)
{
    // 返り値を初期化する
    bool _return_data = false;

    if (0 < _this->length)
    {
        // 先頭のデータを入れる
        *_data = _this->buffer[_this->head];
        // 取り出した地点に０を代入する
        //  _this->buffer[_this->head] = 0;

        // 先頭を次の読み出し位置に移動する
        _this->head++;

        // 先頭が最後の地点なら0番地に戻す
        if (_this->head == _this->max)
        {
            _this->head = 0;
        }

        // 長さを１引く
        _this->length--;

        //! 正常に読み出せたため
        _return_data = true;
    }

    return _return_data;
}

bool Ring_Buffer_fetch(Ring_Buffer *_this, uint8_t *_data)
{
    // 返り値を初期化する
    bool _return_data = false;

    if (0 < _this->length)
    {
        // 先頭のデータを入れる
        *_data = _this->buffer[_this->head];

        //! 正常に読み出せたため
        _return_data = true;
    }

    return _return_data;
}

//! 配列に読み出す
bool Ring_Buffer_read_array(Ring_Buffer *_this, uint8_t *_array, size_t _length)
{
    for (size_t i = 0; i < _length; i++)
    {
        //! 書き込めなかった場合
        if (!Ring_Buffer_read(_this, &_array[i]))
        {
            return false;
        }
    }
    return true;
}

//! 文字配列に読み出す
bool Ring_Buffer_read_str(Ring_Buffer *_this, char *_string)
{
    //! 正常に読み出せたか
    bool _return_data = false;

    //! iをインクリメントするだけ
    for (size_t i = 0;; i++)
    {
        //! 読み出した文字が入る変数
        char _read_data;

        //! 一文字読み出す
        Ring_Buffer_read(_this, &_read_data);

        //! 終端文字だった場合
        if (_read_data == '\0')
        {
            //! 読み出し成功
            _return_data = true;

            // forループから抜け出す
            break;
        }

        //! 文字配列にデータを入れる
        _string[i] = _read_data;
    }

    return _return_data;
}

void Ring_Buffer_reset(Ring_Buffer *_this)
{
    _this->head = 0;
    _this->tail = 0;
    _this->length = 0;
}

void Ring_Buffer_reset_force(Ring_Buffer *_this)
{
    Ring_Buffer_reset(_this);

    //! データもすべて0にする
    for (size_t i = 0; i < _this->max; i++)
    {
        _this->buffer[i] = 0;
    }
}

// 環状バッファが満タンならtrueを返す
// arg 1, Ring_Bufferの構造体ポインタ
bool Ring_Buffer_is_full(Ring_Buffer *_this)
{
    if (_this->length == _this->max)
    {
        return true;
    }
    return false;
}

bool Ring_Buffer_is_space(Ring_Buffer *_this)
{
    if (_this->length < _this->max)
    {
        return true;
    }
    return false;
}

// 環状バッファが空ならtrueを返す
// arg 1, Ring_Bufferの構造体ポインタ
bool Ring_Buffer_is_empty(Ring_Buffer *_this)
{
    if (0 == _this->length)
    {
        return true;
    }
    return false;
}

bool Ring_Buffer_is_data(Ring_Buffer *_this)
{
    if (0 < _this->length)
    {
        return true;
    }
    return false;
}

// 環状バッファ内のデータの長さを返す
// arg 1, Ring_Bufferの構造体ポインタ
size_t Ring_Buffer_is_length(Ring_Buffer *_this)
{
    return _this->length;
}

size_t Ring_Buffer_is_max(Ring_Buffer *_this)
{
    return _this->length;
}