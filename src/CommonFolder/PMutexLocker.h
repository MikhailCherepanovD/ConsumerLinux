#pragma once
#include <pthread.h>

/*!
 *   \brief RAII Wrapper для pthread_mutex_t
 */
class PMutexLocker 
{
public:
    PMutexLocker (pthread_mutex_t* mutex)
    : mutex_ {mutex}
    {
        pthread_mutex_lock (mutex_);
    }
    ~PMutexLocker ()
    {
        pthread_mutex_unlock (mutex_); 
    }

private:
    pthread_mutex_t* mutex_;
};

// TODO: Вынести в папку под названием общая папка.