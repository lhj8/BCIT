#ifndef COMP7402_ASSIGNMENT1_AVALANCHE_H
#define COMP7402_ASSIGNMENT1_AVALANCHE_H

#include <iostream>
#include <string>


using namespace std;

class Avalanche {
private:
    string hexStr1;
    string hexStr2;
    int difference;

public:
    string getBinInput(const string &prompt);
    bool isValidBin(const string &str);
    int compareString(string &s1, string &s2);

};
#endif //COMP7402_ASSIGNMENT1_AVALANCHE_H
