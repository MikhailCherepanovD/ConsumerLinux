#include <pthread.h>


const int SIZE_LIMIT = 256;

struct SharedData
{
    pthread_cond_t newDataAppeared;
    pthread_cond_t newSpaceAppeared;

    int numFilledBytes;

    pthread_mutex_t mutex;
    char buffer[SIZE_LIMIT];

    bool allDataSent;
};