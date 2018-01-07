#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

int main() {
    using namespace std;
    cout << __cplusplus << endl;
    cout << "Ingrese un nombre: " << endl;
    string name;
    cin >> name;
    cout << "Hola " << name << " !" << endl;

    vector<string> v(2);
    v.push_back("hola");
    v.push_back("paulo");

    for (auto cade : v) {
        cout << cade << endl;
    }

    cout << "Ingrese una cantidad finita de notas: " << endl;

    double grade;
    vector<double> scoreboard;
    while (cin >> grade) {
        scoreboard.push_back(grade);
    }

    if (scoreboard.size()>0){
        double min = scoreboard[0];
        double max = scoreboard[0];
        double average = 0;

        for (auto currentGrade: scoreboard) {
            if (currentGrade > max) {
                max = currentGrade;
            }
            if (currentGrade < min) {
                min = currentGrade;
            }
            average += currentGrade;
        }

        average /= scoreboard.size();

        cout << "El promedio es : " << average << endl;
        cout << "El máximo es : " << max << endl;
        cout << "El mínimo es : " << min << endl;
    } else {
        cout << "No existen suficientes datos" << endl;
    }

    return 0;
}