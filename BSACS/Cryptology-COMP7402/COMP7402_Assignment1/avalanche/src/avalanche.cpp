#include "avalanche.h"

string Avalanche::getBinInput(const string &prompt) {
    string input;
    do {
        cout << prompt;
        cin >> input;
        if (!isValidBin(input)) {
            cout << "Invalid hexadecimal input. Please try again." << endl;
        }
    } while (!isValidBin(input));
    return input;
}


bool Avalanche::isValidBin(const string &str) {
    for (char c : str) {
        if (c != '0' && c != '1') {
            return false;
        }
    }
    return true;
}


int Avalanche::compareString(string &s1, string &s2) {
    int diff = 0;
    if (s1.size() != s2.size()) {
        cerr << "Error length is different" << endl;
        return -1;
    }
    for (int i = 0; i < s1.size(); i++) {
        if (s1[i] != s2[i]) diff++;
    }
    return diff;
}

