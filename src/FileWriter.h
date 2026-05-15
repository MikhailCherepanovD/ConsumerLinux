#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class FileWriter
{
public:
    FileWriter (string filePath);
    ~FileWriter ();

    void writeNextBuffer (char* buffer, int size);

private:
    fstream file_;
};