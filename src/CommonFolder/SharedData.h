#pragma once
#include <pthread.h>
#include <cstdint>

const int BUFFER_SIZE = 162; // Размер буффера. BUFFER_SIZE = 256 - BUFFER_ALIGN 

struct SharedData
{
    pthread_cond_t condVar;     
    pthread_mutex_t mutex;
    int writedSize;        // Актуальный размер записанных данных в буффер. Указывается в количестве записанных чисел
    
    bool dataReady;        // Флаг о готовности данных.
                           // True - Данные записаны продюсером и ждут прочтения консюмером.
                           // False - Данные уже прочитаны консюмером, продюсер может перезаписывать / Данные еще не готовы
    
    bool allDataSent;      // Флаг, обозначающий, что все данные отправлены

    uint8_t buffer[BUFFER_SIZE];  // Буффер для передачи данных
};