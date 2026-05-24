#pragma once
#include <cstdint>

/*!
 *   \brief Класс восстановления сжатых данных
 */
class Decompressor
{
public:

    /*!
     * \brief Конструктор
     */
    Decompressor ();

    /*!
     * \brief Метод восстановления данных
     *
     * \param inputBufferUint16  - Указатель на входной буффер
     * \param outputBufferFloat  - Указатель на выходной буффер
     * \param size               - Количество чисел для восстановления
     */
    void decompress (uint16_t* inputBufferUint16, float* outputBufferFloat, int size);

private:

    int bitAlign_; //!< Количество бит для обратного сдвига
};