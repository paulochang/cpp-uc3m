
#include "file_manager.h"

using namespace std;


void file_manager::file_reader(string input_path){

    string line;
    ifstream myfile (input_path);

    // Open file
    if (myfile.is_open()) {

        cin.exceptions(cin.exceptions() | ios_base::failbit);

        ticker tk;
        ticker_storage ts = ticker_storage();

        while ( myfile >> tk){
            cout << "Ticker cout: " << tk << endl;
            ts.add_ticker(tk);
        }
        myfile.close();
    }

    else cout << "Unable to open file" << endl; 

}

void file_manager::file_writer(string input_path){

}
