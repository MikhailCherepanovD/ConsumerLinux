#pragma once
#include "CommonFolder/SharedData.h"
#include "FileWriter.h"
#include "Decompressor.h"
#include "CommonFolder/PMutexLocker.h"
#include <cstring>

#include <sys/shm.h>  // Функции для Shared Memory

/*!
 *  \brief Основной класс потребителя данных
 */
class Consumer 
{

public:
    /*!
     *  \brief Конструктор
     *
     *  \param memoryId - Идентификатор разделяемой памяти
     *  \param outputPath - Путь записи выходного файла
     */
    Consumer ( int memoryId
             , std::string outputPath
             , bool decompressEnable);

    /*!
     *  \brief Деструктор
     */
    ~Consumer ();

    /*!
     *  \brief Основной метод запуска приема данных
     */
    void launch ();

private:

    /*!
     *   \brief Метод чтения буффера из разделенной памяти
     *
     *   Принимает буффер типа float* для несжатых данных. Буффера типа int16_t для сжатых данных
     *   \param buffer - буффер, в который будут прочитаны данные
     *   \param size   - размер прочитанных данных (Количество чисел указанного типа)
     * 
     *   \return bool. True - если все данные прочитаны. False - если еще остались данные для чтения.
    */
    template<typename T> 
    bool readBuffer (T* buffer, int& size)
    {
        PMutexLocker locker {&sharedData_->mutex};

        while (sharedData_->dataReady == false)
        {
            pthread_cond_wait(&sharedData_->condVar, &sharedData_->mutex);
        }

        if (sharedData_->allDataSent == true)
        {
            return true;
        }

        size = sharedData_->writedSize;
        memcpy (buffer, sharedData_->buffer, size * sizeof (T));
        sharedData_->dataReady = false;

        pthread_cond_signal(&sharedData_->condVar);
        return false;
    }

private:

    FileWriter* fileWriter_;        //!< Указатель на объект писателя данных в выходной файд
    SharedData* sharedData_;        //!< Указатель на объект разделенной памяти

    Decompressor* decompressor_;    //!< Указатель на объект Decompressor
    bool decompressEnable_;      //!< Флаг, обозначающий, включена ли декомпрессия данных

};