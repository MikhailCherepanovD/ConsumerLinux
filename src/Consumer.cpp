#include "Consumer.h"
#include <string.h>
#include <iostream>
#include <format>
using namespace std;
Consumer::Consumer ()
: nextByteIndex_ {0}
{
    std::cout << "Hi from consumer" << std::endl;

    fileWriter_ = new FileWriter {"/home/mikhail/Documents/tmp/OutputConsumerFile"};

    sharedData_ = (SharedData*)shmat(3309631, nullptr, 0);  // TODO: Поставить проверку, что такая память существует, иначе Sig Fault
}

Consumer::~Consumer ()
{
    delete fileWriter_;
}

void Consumer::work ()
{
    int size = 1;
    char * buffer = new char [SIZE_LIMIT];
    while (size > 0)
    {
        readBuffer (buffer, size);
        fileWriter_ -> writeNextBuffer (buffer, size);
    }
    cout <<"Прочитали все данные. Память будет отделена.\n";
    shmdt(sharedData_);
}

void Consumer::readBuffer (char* buffer, int& size)
{
    pthread_mutex_lock (&sharedData_->mutex); 

    while (sharedData_->numUsedBytes == 0)
    {
        pthread_cond_wait(&sharedData_->bufferNotEmpty, &sharedData_->mutex);
    }
    size  =  sharedData_->numUsedBytes;
    pthread_mutex_unlock (&sharedData_->mutex); 

    for (int i = 0; i < size; i ++)
    {
        buffer [i] = sharedData_->buffer[nextByteIndex_ % SIZE_LIMIT];
        nextByteIndex_ ++;
    }

    pthread_mutex_lock (&sharedData_->mutex);
    sharedData_->numUsedBytes -= size;
    pthread_cond_signal(&sharedData_->bufferNotFull);
    pthread_mutex_unlock (&sharedData_->mutex);


    //cout << "Записали буффер №" << writeCounter_ << endl;
    writeCounter_++;
}