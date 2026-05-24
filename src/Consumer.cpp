#include "Consumer.h"

#include <iostream>
#include <format>
#include <thread>
#include <chrono>


Consumer::Consumer ( int memoryId
                   , std::string outputPath
                   , bool decompressEnable)
: decompressEnable_ {decompressEnable}
{
    fileWriter_ = new FileWriter {outputPath};
    decompressor_ = new Decompressor {};

    sharedData_ = (SharedData*)shmat(memoryId, nullptr, 0);  

    if (sharedData_ == (void*)-1)
    {
        std::cerr << "Ошибка доступа к разделяемой памяти" << std::endl;
        exit(1);
    }

    std::cout << "Подключились к разделяемой памяти.\n";

    if (decompressEnable_)
    {
        std::cout <<"Режим сжатия включен.\n";
    }
    else
    {
        std::cout <<"Режим сжатия выключен.\n";
    }
}

Consumer::~Consumer ()
{
    delete fileWriter_;
    delete decompressor_;
}

void Consumer::launch ()
{
    int size = 1;
    float * floatBuffer = new float [BUFFER_SIZE * sizeof (float)];
    uint16_t* uint16Buffer = new uint16_t [BUFFER_SIZE * sizeof (uint16_t)];

    bool allDataReceived = false;

    while (true)
    {
        if (decompressEnable_)
        {
            allDataReceived = readBuffer(uint16Buffer, size);
            decompressor_->decompress (uint16Buffer, floatBuffer, size);
        }
        else
        {
            allDataReceived = readBuffer(floatBuffer, size);
        }
        

        if (allDataReceived)
            break;

        fileWriter_->writeNextBuffer(floatBuffer, size);
    }

    std::cout <<"Прочитали все данные. Память будет отделена.\n";

    delete[] floatBuffer;
    delete[] uint16Buffer;
    shmdt(sharedData_);
}
