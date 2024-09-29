#include "Task1.h"

string Task1::getFileNameInput(const string& prompt) {
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


bool Task1::isValidExtension(const string& fileName) {
    size_t dotPosition = fileName.find_last_of('.');
    if (dotPosition != std::string::npos) {
        std::string extension = fileName.substr(dotPosition + 1);
        if (extension == "txt" || extension == "csv") return true;
    }
    return false;
}


int Task1::process(const string& txtFile) {
    ifstream inputFile(txtFile);

    if (!inputFile.is_open()) {
        std::cerr << "Error opening files!" << std::endl;
        return -1;
    }

    char ch;

    // Count letter frequencies
    while (inputFile >> ch) {
        ch = tolower(ch);
        if (isalpha(ch)) {
            _LMap[ch]++;
        }
    }

    inputFile.close();
    return 1;
}


int Task1::saveToCSV(const string &csvFile) {
    ofstream outputFile(csvFile);

    if (!outputFile.is_open()) {
        cerr << "Error opening output file!" << endl;
        return 0;
    }
    outputFile << "letter,count\n";
    for (const auto& pair : _LMap) {
        outputFile << pair.first << "," << pair.second << "\n";
    }

    outputFile.close();
    return 1;
}


double Task1::sumOfProb() {
    unsigned int count = 0;
    double sum = 0;

    // Calculate the total count
    for (const auto& pair : _LMap) {
        count += pair.second;
    }

    // Calculate probability and update the sum
    for (const auto& pair : _LMap) {
        double prob = static_cast<double>(pair.second) / count;
        _PMap[pair.first] = prob;
        sum += prob;
    }

    return sum;
}


void Task1::showSumOfProb() {
    double sum = sumOfProb();

    cout << "\nSum of the probabilities of each distribution =\n";
    for (const auto& pair : _PMap) {
        std::cout << std::fixed << std::setprecision(7) << pair.second << " + ";
    }

    cout << "\b\b\b"; // Remove the last " + "
    cout << "\nTotal Sum = " << std::fixed << setprecision(7) << sum << endl;
}



