#include "Consumer.h"
#include <string.h>
#include <iostream>
#include <format>
using namespace std;
Consumer::Consumer ()
{
    std::cout << "Hi from consumer" << std::endl;

    fileWriter_ = new FileWriter {"/home/mikhail/Documents/tmp/OutputConsumerFile"};

    sharedData_ = (SharedData*)shmat(1048629, nullptr, 0);
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
    while (true)
    {
        pthread_mutex_lock (&sharedData_->mutex); // TODO: Проверить, нет ли ошибки
        if (sharedData_->dataReady == false)
        {
            pthread_mutex_unlock (&sharedData_->mutex);
            continue;
        }

        memcpy (buffer, sharedData_->buffer, sharedData_->writedSize);
        size = sharedData_->writedSize;
        sharedData_->dataReady = false;

        pthread_mutex_unlock (&sharedData_->mutex);
        break;
    }
    cout << format ("Прочитали буффер № {}\n", writeCounter_);
    writeCounter_++;
}