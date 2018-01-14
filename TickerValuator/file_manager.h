
#include <string>
#include <iostream>
#include <fstream>

#include "ticker.h"
#include "ticker_storage.h"

using namespace std;
class file_manager {

    public:
    void file_reader(string input_path);
    void file_writer(string output_path);
};

