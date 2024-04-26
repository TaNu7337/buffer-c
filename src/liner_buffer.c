#include "liner_buffer.h"

void Nomal_buffer_init(struct Nomal_buffer *_this, uint8_t *_array, uint16_t _length)
{
    _this->buffer = _array;
    _this->head = 0;
    _this->length = 0;
    _this->max = _length;
}

void Nomal_buffer_reset(struct Nomal_buffer *_this)
{
    _this->head = 0;
    _this->length = 0;
}

bool Nomal_buffer_write(struct Nomal_buffer *_this, uint8_t _data)
{
    if (_this->length < _this->max)
    {
        _this->buffer[_this->length] = _data;
        _this->length++;
        return true;
    }
    return false;
}

uint8_t Nomal_buffer_read(struct Nomal_buffer *_this)
{
    if(_this->head < _this->max)
    {
        return _this->buffer[_this->head++];
    }
    return 0;
}

bool Nomal_buffer_is_data(const struct Nomal_buffer *_this)
{
    if (_this->head < _this->length)
    {
        return true;
    }else{
        return false;
    }
    
}

bool Nomal_buffer_is_full(const struct Nomal_buffer *_this)
{
    if (_this->max <= _this->length)
    {
        return true;
    }else{
        return false;
    }
    
}