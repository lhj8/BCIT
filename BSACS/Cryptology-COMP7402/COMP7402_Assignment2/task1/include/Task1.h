#ifndef COMP7402_ASSIGNMENT2_TASK1_H
#define COMP7402_ASSIGNMENT2_TASK1_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <cctype>
#include <iomanip>


using namespace std;

class Task1 {
private:
    unordered_map<char, int> _LMap;     // Map for letter counts
    unordered_map<char, double> _PMap;  // Map for probilities
public:
    string getFileNameInput(const string& prompt);
    bool isValidExtension(const string& fileName);
    int process(const string& txtFile);
    int saveToCSV(const string& csvFile);
    double sumOfProb();
    void showSumOfProb();
};


#endif //COMP7402_ASSIGNMENT2_TASK1_H
