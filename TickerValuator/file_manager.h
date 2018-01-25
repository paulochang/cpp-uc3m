
#include <string>

#include "ticker.h"
#include "ticker_storage.h"
#include "simplified_ticker.h"

using namespace std;
class file_manager {

    public:
    ticker_storage file_reader(string input_path);

    void file_writer(string output_path, string file_name,
                     const tbb::concurrent_vector<simplified_ticker> &printing_vector) const;
};

