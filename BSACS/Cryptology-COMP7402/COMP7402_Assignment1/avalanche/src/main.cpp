#include "avalanche.h"

int main() {
    Avalanche av;
    string str1 = av.getBinInput("Enter hex string 1: ");
    string str2 = av.getBinInput("Enter hex string 2: ");
    cout << endl;

    cout << "HexStr1: " << str1 << "\n" << endl;
    cout << "HexStr2: " << str2 << "\n" << endl;

    cout << "size: " << str1.size() << "\n" << endl;

    double result = static_cast<double>(av.compareString(str1, str2)) / str1.size() * 100;
    cout << "Difference: " << to_string(av.compareString(str1, str2)) << " ( " << result << " % )" << endl;
}
