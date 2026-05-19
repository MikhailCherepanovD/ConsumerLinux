#include "SharedData.h"
#include "FileWriter.h"

#include <sys/ipc.h>  // Структура ipc_perm
#include <sys/sem.h>  // Семафор
#include <sys/shm.h>  // Функции для Shared Memory
#include <sys/wait.h> // Функции ожидания изменения состояния дочерних процессов



class Consumer 
{

public:

    Consumer ();
    ~Consumer ();
    void work ();
private:

    /*
        returns: True - если все данные прочитаны. False - если еще остались данные для чтения.
    */
    bool readBuffer (char* buffer, int& size);

private:
    FileWriter* fileWriter_;
    SharedData* sharedData_;

    size_t nextByteIndex_;
};