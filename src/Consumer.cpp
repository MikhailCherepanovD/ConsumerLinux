#include "Consumer.h"
#include <string.h>
#include <iostream>
#include <format>
using namespace std;
Consumer::Consumer ()
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

    while (sharedData_->dataReady == false)
    {
        pthread_cond_wait(&sharedData_->condVar, &sharedData_->mutex);
    }

    memcpy (buffer, sharedData_->buffer, sharedData_->writedSize);
    size = sharedData_->writedSize;
    sharedData_->dataReady = false;


    pthread_cond_signal(&sharedData_->condVar);
    pthread_mutex_unlock (&sharedData_->mutex);

    //cout << "Прочитали буффер № " << writeCounter_ << endl;
    writeCounter_++;
}