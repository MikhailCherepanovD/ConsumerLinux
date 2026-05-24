#include "FileWriter.h"
#include <iostream>
#include <format>

FileWriter::FileWriter (std::string filePath)
    :  file_ {filePath, std::ios::out | std::ios::binary}
    ,  separator_ {'\n'}
{
    if (! file_.is_open ())
    {
        std::cerr << std::format("Ошибка открытия файла: {}\n",filePath);
        exit(1);
    }
}

FileWriter::~FileWriter ()
{
    if (file_.is_open()) 
    {
        file_.close();
    }
}

void FileWriter::writeNextBuffer (float* buffer, int size)
{
    for (int i = 0; i < size; i++)
    {
        file_.write(
            reinterpret_cast<char*>(&buffer[i]),
            sizeof(float)
        );
    }
}
