#include <pthread.h>


const int SIZE_LIMIT = 256;

struct SharedData
{
    pthread_cond_t condVar;
    pthread_mutex_t mutex;
    int writedSize;
    bool dataReady;
    char buffer[SIZE_LIMIT];
};