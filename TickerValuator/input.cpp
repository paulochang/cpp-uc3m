#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>

#include "parser.h"
#include "ticker.h"

int main(int argc, char ** argv) {
  using namespace std;

  
  string input_path;
  string output_path;
  parser ps = parser();

  if (argc == 1 ) {
    // Default
    ps.parse_input(false, false, "", "");
  } else if (argc == 3){
    // input or output
    string argv1 = argv[1];
    if (argv1 == "-i"){
      // set input path
      input_path = argv[2];
      ps.parse_input(true, false, input_path, "");
    } else if (argv1 == "-o"){
      // set output path
      output_path = argv[2];
    } else{
      cerr << "Wrong arguments" << endl;
      return -1;
    }
  } else if (argc == 5){
    // input and output
    string argv1 = argv[1];
    string argv3 = argv[3];

    if (argv1 == "-i"){
      // set input path
      input_path = argv[2];
    } else if (argv1 == "-o"){
      // set output path
      output_path = argv[2];
    } else{
      cerr << "Wrong arguments" << endl;
      return -1;
    }

    if (argv3 == "-i"){
      // set input path
      input_path = argv[4];
    } else if (argv3 == "-o"){
      // set output path
      output_path = argv[4];
    } else{
      cerr << "Wrong arguments" << endl;
      return -1;
    }

  } else{
      cerr << "Wrong arguments" << endl;
      cerr << "Valid formats: " << endl;
      cerr << "-i <filename>" << endl;
      cerr << "-o <path>" << endl;
      cerr << "-i <filename> -o <path>" << endl;
      return -1;
  }


}