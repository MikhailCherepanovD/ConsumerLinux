#include <iostream>
#include "Consumer.h"
#include <format>

const std::string compress_enable = "compress_enable";
const std::string compress_disable = "compress_disable";

int main (int argc, char *argv[])
{
    if (argc < 4)
    {
        std::cerr << std::format(
                     "Ошибка запуска приложения. При запуске необходиимо указать три параметра:\n"
                     "1. Режим запуска: {} / {}\n"
                     "2. ID разделяемой памяти;\n"
                     "3. Путь записи выходного файла.\n"
                     , compress_enable, compress_disable);

        std::cerr << std::format(
                     "Примеры запуска программы:\n"
                     "./Consumer {} <ID> <file_path> \n"
                     "./Consumer {} <ID> <file_path> \n"
                     , compress_enable, compress_disable); 
        return 0;
    }
    std::string mode = argv[1];
    if (mode != compress_enable && mode != compress_disable)
    {
        std::cerr << std::format ("Аргумент {} не распознан. Возможные режимы: {}, {}.\n", mode, compress_enable, compress_disable);
        return 0;
    }

    int id = atoi(argv[2]);
    if (id == 0)
    {
        std::cerr << "Значение ID памяти указано неверно\n";
        return 0;
    }
    std::string filePath = argv[3];

    Consumer consumer{
        id,
        filePath,
        mode == compress_enable ? true : false
    };

    consumer.launch ();
    return 0;
}

