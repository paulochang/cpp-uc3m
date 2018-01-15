
#include "file_manager.h"

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
            cout << "Ticker cout: " << tk << endl;
            ts.add_ticker(tk);
        }
        myfile.close();

    }

    else cout << "Unable to open file " << input_path << endl;
    
    return ts;

}

void file_manager::file_writer(string output_path, string file_name, std::vector<simplified_ticker> printing_vector){

    const regex alphanumeric("[a-z0-9]");
    stringstream result;
    regex_replace(std::ostream_iterator<char>(result), file_name.begin(), file_name.end(), alphanumeric, "");

    ofstream myfile (output_path+result.str());

    if (myfile.is_open()) {

        for (auto stk : printing_vector) {
            cout << stk << endl;
            myfile << stk << endl;
        }
        myfile.close();
    }

    else cout << "Unable to create file " << output_path << endl;    

}