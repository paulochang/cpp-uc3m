
#include <string>
#include <iostream>
#include <fstream>

#include <regex>
#include <sstream>
#include <locale>

#include "ticker.h"
#include "ticker_storage.h"
#include "simplified_ticker.h"

using namespace std;
class file_manager {

    public:
    ticker_storage file_reader(const string input_path);

    void file_writer(const string output_path, const string file_name,
                     const std::vector<simplified_ticker> printing_vector) const;
};

