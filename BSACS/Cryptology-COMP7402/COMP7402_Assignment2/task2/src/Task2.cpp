/*---------------------------------------------------------------------------------------------
--	SOURCE FILE:	ceasar.py - the code for the Caesar cipher for a simple substitution
--
--	DATE:			Jan 14, 2024
--				    Added personal function for assignment
--
--	REVISIONS:		(Date and nic_description)
--
--	DESIGNERS:		Based on the code by Aman Abdulla
--					Modified & redesigned: HyungJoon LEE: Jan 14, 2024
--
--	STUDENT:		HyungJoon LEE
-------------------------------------------------------------------------------------------------*/

#include "Task2.h"


string Task2::getFileNameInput(const string& prompt) {
    string input;
    do {
        cout << prompt;
        cin >> input;
        if (!isValidExtension(input)) {
            cout << "Invalid extension. Please try again." << endl;
        }
    } while (!isValidExtension(input));
    return input;
}


int Task2::getOffsetInput(const string &prompt) {
    int offset;
    while (true) {
        cout << prompt;
        cin >> offset;

        if (cin.fail() || offset < 1 || offset > 26) {
            cout << "Invalid input. Please enter a positive integer.\n";
            cin.clear(); // Clear error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore remaining input
        }
        else {
            break;
        }
    }
    return offset;
}


bool Task2::isValidExtension(const string& fileName) {
    size_t dotPosition = fileName.find_last_of('.');
    if (dotPosition != string::npos) {
        string extension = fileName.substr(dotPosition + 1);
        if (extension == "txt") return true;
    }
    return false;
}


void Task2::encode(const string &inFile, const string &outFile, int shift) {
    char ch;
    ifstream fp1(inFile);
    ofstream fp2(outFile);

    if (!fp1) {
        cerr << "Input file is wrong" << endl;
        exit(1);
    }

    if (!fp2) {
        cerr << "Output file is wrong" << endl;
        exit(1);
    }

    while (fp1.get(ch)) {
        if (isalpha(ch)) {
            char base = islower(ch) ? 'a' : 'A';
            ch = (ch - base + shift) % 26 + base;
        }

        fp2.put(ch);
    }
}


void Task2::calculateFrequency(ifstream &fp) {
    char ch;
    totalCharacters = 0;
    while (fp.get(ch)) {
        ch = tolower(ch);
        if (isalpha(ch)) {
            frequencyMap[ch]++;
            totalCharacters++;
        }
    }
}


void Task2::calculateProbability() {
    for (auto& pair : frequencyMap) {
        probabilityMap[pair.first] = static_cast<double>(pair.second) / totalCharacters;
    }
}


void Task2::calculateDistributions(const string &fileName, bool flag) {
    ifstream fp(fileName);
    if (!fp) {
        cerr << "Cannot open file for distribution calculation: " << fileName << endl;
        exit(1);
    }

    // Clear previous data
    frequencyMap.clear();
    probabilityMap.clear();
    totalCharacters = 0;

    // Calculate frequency of each character
    calculateFrequency(fp);

    // Calculate probability of each character
    calculateProbability();
    if (flag == INPUT)
        appendToCSV("plain.csv", "Plain txt result");
    else
        appendToCSV("encode.csv", "Encoded txt result");

    fp.close();
}


void Task2::setConditionalProbabilities(const string& fileName1, const string& fileName2) {
    ifstream file1(fileName1);
    if (!file1.is_open()) {
        cerr << "Error opening file1" << endl;
        return;
    }

    ifstream file2(fileName2);
    if (!file1.is_open()) {
        cerr << "Error opening file2" << endl;
        return;
    }

    string line1 ,line2;
    getline(file1, line1);
    getline(file2, line2);

    while (getline(file1, line1)) {
        stringstream ss(line1);
        char ch;
        double prob;
        if (ss >> ch && ss.ignore(64, ',') && ss >> prob) {
            plainTxtProb[ch] = prob;
        }
    }

    while (getline(file2, line2)) {
        stringstream ss(line2);
        char ch;
        double prob;
        if (ss >> ch && ss.ignore(64, ',') && ss >> prob) {
            cipherTxtProb[ch] = prob;
        }
    }
}


void Task2::printProbabilities() const {
    for (const auto &entry : probabilityMap) {
        cout << "P(" << entry.first << ") = " << entry.second << endl;
    }
}


void Task2::appendToCSV(const string &fileName, const string &instruction) {
    ofstream file(fileName);

    if (!file) {
        cerr << "Cannot open file for appending: " << fileName << endl;
        exit(1);
    }

    file << instruction << endl;
    for (const auto &entry : probabilityMap) {
        file << entry.first << "," << entry.second << endl;
    }
    file << endl;
    file.close();
}


void Task2::printConditionalProbabilities(int key, const string &fileName) {
    ofstream file(fileName, ios::app);
    if (!file) {
        cerr << "Cannot open file for appending: " << fileName << endl;
        exit(1);
    }

    file << "Offset(Key): " << key << endl;
    cout << "Offset(Key): " << key << endl;
    for (char plainChar : {'e', 't', 'a', 'i', 'o', 'n'}) {
        char cipherChar = (plainChar  - 'a' + key) % 26 + 'a';
        std::cout << "P(M=" << plainChar << "|" << cipherChar << ") = "
            << plainTxtProb[plainChar] / cipherTxtProb[cipherChar] << std::endl;
        file << "P(M=" << plainChar << "|" << cipherChar << ") = "
             << plainTxtProb[plainChar] / cipherTxtProb[cipherChar] << endl;
    }
    cout << endl;
    file << endl;
    file.close();
}



