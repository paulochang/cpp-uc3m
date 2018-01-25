
#include <iostream>
#include <fstream>
#include <stdio.h>

#include <regex>
#include <sstream>
#include "file_manager.h"
#include "fmt/format.h"

using namespace std;


ticker_storage file_manager::file_reader(const string input_path) {

    string line;
    ticker_storage ts = ticker_storage();

    ifstream myfile(input_path);


    //long counter = 0;

    // Open file
    /*if (myfile.is_open()) {

        cin.exceptions(cin.exceptions() | ios_base::failbit);

        ticker tk;
        //unsigned int d;
        //unsigned int m;
        //unsigned int y;
        //unsigned int h;
        //unsigned int min;
        //double secs;
        //char symbol[32];
        //double price;
        //13-02-2002 18:58:19.594486 "BBVA" 184.18
        // while(int ret = fscanf(fp, "%u-%u-%u %u:%u:%lf \"%[^\"]\" %lf",
        //                      &d, &m, &y, &h, &min, &secs, symbol, &price) == 8) {

        while (myfile >> tk) {
            // DEBUG
            // cout << "counter: " << counter++;
            // unsigned int date = d + m * 100u + y * 10000u;
            //unsigned short time_ = static_cast<unsigned short>(h * 100u + min);
            //tk = ticker{date, time_, secs, symbol, price};

            ts.add_ticker(tk);

            //cout << "Ticker cout: " << tk << endl;
        }
        myfile.close();

    }

        //fclose(fp);

    else cout << "Unable to open file " << input_path << endl;
*/
    //////


    FILE *fp;

    fp = fopen(input_path.c_str(), "r");
    ticker tk;
    unsigned int d;
    unsigned int m;
    unsigned int y;
    unsigned int h;
    unsigned int min;
    double secs;
    char symbol[32];
    double price;
    //13-02-2002 18:58:19.594486 "BBVA" 184.18
    while (int ret = fscanf(fp, "%u-%u-%u %u:%u:%lf \"%[^\"]\" %lf",
                            &d, &m, &y, &h, &min, &secs, symbol, &price) == 8) {

        unsigned int date = d + m * 100u + y * 10000u;
        unsigned short time_ = static_cast<unsigned short>(h * 100u + min);
        tk = ticker{date, time_, secs, symbol, price};
        ts.add_ticker(tk);
    }

    fclose(fp);

    /////
    return ts;

}

void file_manager::file_writer(const string output_path, const string file_name,
                               const std::vector<simplified_ticker> &printing_vector) const {

    std::string my_string(file_name);

    // Uses STL to transform string and apply STL toupper function
    transform(my_string.begin(), my_string.end(), my_string.begin(), ::toupper);
    my_string.erase(std::remove_if(my_string.begin(), my_string.end(), [](char c) { return !std::isalnum(c); }),
                    my_string.end());

    auto myfile = std::fstream(output_path + my_string + ".txt", std::ios::out | std::ios::binary);

    fmt::MemoryWriter writer;

    if (myfile.is_open()) {

        for (auto stk : printing_vector) {

            stk.write(writer);
        
        }
        //myfile << writer.c_str();
        myfile.write(writer.c_str(), writer.size());
        myfile.close();
    }

    else cout << "Unable to create file " << output_path << endl;    

}
