#include "Consumer.h"
#include "PMutexLocker.h"

#include <string.h>
#include <iostream>
#include <format>
#include <thread>
#include <chrono>
using namespace std;



int readNumberFromFile()
{
    std::ifstream file("/home/mikhail/Documents/tmp/consumer_producer/process_id.txt");

    if (!file.is_open())
    {
        std::cerr << "Ошибка открытия файла\n";
        return -1;
    }

    int number;
    file >> number;

    return number;
}




Consumer::Consumer ()
: nextByteIndex_ {0}
{
    std::cout << "Hi from consumer" << std::endl;

    fileWriter_ = new FileWriter {"/home/mikhail/Documents/tmp/consumer_producer/OutputConsumer_source_data.bin"};

    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    int id = readNumberFromFile();
    sharedData_ = (SharedData*)shmat(id, nullptr, 0);  // TODO: Поставить проверку, что такая память существует, иначе Sig Fault
    cout << format("Подключились к разделенной памяти. ID = {}\n", id);
}

Consumer::~Consumer ()
{
    delete fileWriter_;
}

void Consumer::work ()
{
    int size = 1;
    char * buffer = new char [SIZE_LIMIT];
    bool allDataReceived = false;
    while (allDataReceived == false) // TODO: Сейчас корректно не завершится, ввести знак конца - isFinished.
    {
        allDataReceived = readBuffer (buffer, size);
        fileWriter_ -> writeNextBuffer (buffer, size);
    }
    cout <<"Прочитали все данные. Память будет отделена.\n";

    delete[] buffer;
    shmdt(sharedData_);
}


bool Consumer::readBuffer (char* buffer, int& size)
{
    bool result;
    {
        //cout << "Перед блокировкой №1\n";
        PMutexLocker locker {&sharedData_->mutex};
        //cout << "Заблокировали Мьютекс №1\n";
        while (sharedData_->numFilledBytes == 0)
        {
            if (sharedData_->allDataSent == true)
            {
                size = 0;
                return true;
            }
            //cout << "Перед отпусканием переменной №1\n";
            pthread_cond_wait(&sharedData_->newDataAppeared, &sharedData_->mutex);
            //cout << "Переменная №1 вернулась\n";
        }
        size  =  sharedData_->numFilledBytes;
        result = sharedData_->allDataSent;
        //cout << "В конце блокировки№1\n";
    } 

    for (int i = 0; i < size; i ++)
    {
        buffer [i] = sharedData_->buffer[nextByteIndex_ % SIZE_LIMIT];
        nextByteIndex_ ++;
    }

    {
        //cout << "Перед блокировкой №2\n";
        PMutexLocker locker {&sharedData_->mutex};
        sharedData_->numFilledBytes -= size;
        pthread_cond_signal(&sharedData_->newSpaceAppeared);
        //cout << "В конце блокировки№2\n";
    }
    return result;
}
