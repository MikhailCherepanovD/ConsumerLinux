#pragma once
#include <string>
#include <fstream>
#include <iostream>

/*!
 *   \brief Класс записи выходного файла
 */
class FileWriter
{

public:

    /*!
     * \brief Конструктор
     * \param filePath - Путь до выходного файла
     */
    FileWriter (std::string filePath);

    /*!
     * \brief Деструктор
     */
    ~FileWriter ();

    /*!
     * \brief Метод записи следующего буффера в файл
     *
     * \param buffer - Указатель на буффер с данными
     * \param size   - Количество чисел для записи
     */
    void writeNextBuffer (float* buffer, int size);

private:

    std::fstream file_; //!< Объект записи файла
    char separator_;    //!< Разделитель между числами
};