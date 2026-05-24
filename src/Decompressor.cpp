#include "Decompressor.h"
#include <cstring>

Decompressor::Decompressor ()
{
    bitAlign_ = 16;
}

void Decompressor::decompress (uint16_t* inputBufferUint16, float* outputBufferFloat, int size)
{   
    uint32_t tmpValue = 0;

    for (int i = 0; i < size; i++)
    {
        tmpValue = inputBufferUint16[i];
        tmpValue = tmpValue << 16;
        memcpy (outputBufferFloat + i, &tmpValue, sizeof(tmpValue));
    }
}