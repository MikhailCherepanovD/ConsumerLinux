#include "FileWriter.h"

void print (char* buffer, int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << buffer [i];
    }
    //cout << endl;
}


FileWriter::FileWriter (string filePath)
    :  file_ {filePath, ios::out}
{
    if (! file_.is_open ())
    {
        cout << "Ошибка открытия файла" << endl;
    }
}

FileWriter::~FileWriter ()
{
    if (file_.is_open()) 
    {
        file_.close();
    }
}

void FileWriter::writeNextBuffer (char* buffer, int size)
{
    file_.write (buffer, size);
    print (buffer,size);
}
