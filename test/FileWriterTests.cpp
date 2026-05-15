#include <gtest/gtest.h>
#include "FileWriter.h"

TEST(FileWriterTest, BasicWorkTest)
{

    const int MAX_SIZE_READING = 356;
    FileWriter fw {"/home/mikhail/Documents/tmp/file1234"};

    char * buffer = new char [MAX_SIZE_READING];
    int bufferSize;
    buffer[0] = '0';
    buffer[1] = '1';
    buffer[2] = '2';
    buffer[3] = '3';
    fw.writeNextBuffer (buffer, 4);

    EXPECT_EQ(26, 26);
}