#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>

#include "file_manager.h"
#include "ticker.h"
#include "ticker_storage.h"

int main(int argc, char ** argv) {
  using namespace std;

  
  string input_path;
  string output_path;
  file_manager fm = file_manager();

  // Default arguments
  if (argc == 1 ) {

    cout << "Ingrese cotizaciones de valores: " << endl;
    
    cin.exceptions(cin.exceptions() | ios_base::failbit);
    ticker tk;
    ticker_storage ts = ticker_storage();
    
    while (cin >> tk){
      ts.add_ticker(tk);
    }

    ts.sort_ticker();

  // One argument, input or output path
  } else if (argc == 3){

    string argv1 = argv[1];
    if (argv1 == "-i"){

      input_path = argv[2];
      fm.file_reader(input_path);

    } else if (argv1 == "-o"){

      output_path = argv[2];

    } else{

      cerr << "Wrong arguments" << endl;
      return -1;

    }

  // Both arguments, input and output path
  } else if (argc == 5){

    string argv1 = argv[1];
    string argv3 = argv[3];

    // Set input and output paths
    if (argv1 == "-i"){

      input_path = argv[2];

    } else if (argv1 == "-o"){

      output_path = argv[2];

    } else{

      cerr << "Wrong arguments" << endl;
      return -1;

    }

    if (argv3 == "-i"){

      input_path = argv[4];

    } else if (argv3 == "-o"){

      output_path = argv[4];

    } else{

      cerr << "Wrong arguments" << endl;
      return -1;

    }

  // Error
  } else{

      cerr << "Wrong arguments" << endl;
      cerr << "Valid formats: " << endl;
      cerr << "-i <filename>" << endl;
      cerr << "-o <path>" << endl;
      cerr << "-i <filename> -o <path>" << endl;
      return -1;
  }


}