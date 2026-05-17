#include <pthread.h>


const int SIZE_LIMIT = 256;

struct SharedData
{
    pthread_cond_t bufferNotEmpty;
    pthread_cond_t bufferNotFull;

    int numUsedBytes;

    pthread_mutex_t mutex;
    char buffer[SIZE_LIMIT];
};