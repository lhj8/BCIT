#include <iostream>
#include "Task1.h"


int main() {
    Task1 t1;
    string txtFile = t1.getFileNameInput
            ("Please enter the name of the text file to read from (e.g., 'input.txt'): ");
    string csvFile = t1.getFileNameInput
            ("Please enter the name of the CSV file to write to (e.g., 'output.csv'): ");
    if (t1.process(txtFile)) {
        t1.saveToCSV(csvFile);
        t1.showSumOfProb();
    }
    return 0;
}
