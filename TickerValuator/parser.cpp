
#include "parser.h"

using namespace std;


void parser::parse_input(bool input, bool output, string input_path, string output_path){

    string line;

    if (input){
    ifstream myfile (input_path);
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            // TEST
            cout << "line:" << line << '\n';

            int date = stoi(line.substr(0,2) + line.substr(3,2) + line.substr(6,4));
            int time = stoi(line.substr(11,2) + line.substr(14,2));
            double seconds = stod(line.substr(17, 9));
            string symbol = line.substr(line.find('"')+1, line.find('"', line.find('"')+1) - line.find('"')-1);
            double price = stod(line.substr(line.find('"', line.find('"')+1)+2));


            ticker(date, time, seconds, symbol, price);

        }
        myfile.close();
    }

    else cout << "Unable to open file" << endl; 
    }

    if (output){
        output_path = "";
    }
}
