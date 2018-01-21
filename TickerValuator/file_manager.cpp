
#include "file_manager.h"
#include "fmt/format.h"

using namespace std;


ticker_storage file_manager::file_reader(string input_path){

    string line;
    ticker_storage ts = ticker_storage();

    ifstream myfile (input_path);

    // Open file
    if (myfile.is_open()) {

        cin.exceptions(cin.exceptions() | ios_base::failbit);

        ticker tk;

        while ( myfile >> tk){
            // DEBUG
            // cout << "Ticker cout: " << tk << endl;
            ts.add_ticker(tk);
        }
        myfile.close();

    }

    else cout << "Unable to open file " << input_path << endl;
    
    return ts;

}

void file_manager::file_writer(const string output_path, const string file_name,
                               const std::vector<simplified_ticker> printing_vector) const {

    stringstream result;

    std::string my_string(file_name);

    // Uses STL to transform string and apply STL toupper function
    transform(my_string.begin(), my_string.end(), my_string.begin(), ::toupper);
    my_string.erase(std::remove_if(my_string.begin(), my_string.end(), [](char c) { return !std::isalnum(c); }),
                    my_string.end());

    ofstream myfile (output_path+my_string+".txt");

    fmt::MemoryWriter writer;

    if (myfile.is_open()) {

        for (auto stk : printing_vector) {

            stk.write(writer);
        
        }
        myfile << writer.c_str();
        myfile.close();
    }

    else cout << "Unable to create file " << output_path << endl;    

}