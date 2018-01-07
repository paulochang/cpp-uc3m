// reading a text file
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main () {
  string line;
  ifstream myfile ("../sample_input.txt");
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
        cout << "date: " << line.substr(0,2) << line.substr(3,2) << line.substr(6,4) << '\n';
        cout << "time: " << line.substr(11,2) << line.substr(14,2) << '\n';
        cout << "seconds: " << line.substr(17, 9) << '\n';
        cout << "symbol: " << line.substr(line.find('"')+1, line.find('"', line.find('"')+1) - line.find('"')-1) << '\n';
        cout << "price: " << line.substr(line.find('"', line.find('"')+1)+2) << '\n';
        cout << "line:" << line << '\n';
    }
    myfile.close();
  }

  else cout << "Unable to open file"; 

  return 0;
}