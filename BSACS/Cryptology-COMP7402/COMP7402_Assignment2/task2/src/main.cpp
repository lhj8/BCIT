#include "Task2.h"

int main() {
    Task2 t2;

    string inFile = t2.getFileNameInput("Please enter the name of the text file to read from (e.g., 'input.txt'): ");
    string outFile = t2.getFileNameInput("Please enter the name of the text file to write to (e.g., 'output.txt'): ");
    int offset = t2.getOffsetInput("Please enter the offset between 1 and 26: ");

    t2.encode(inFile, outFile, offset);

    // Calculate and print the probability distributions for the input file (plaintext)
    cout << "Probability distributions for the input file (plaintext):" << endl;
    t2.calculateDistributions(inFile, INPUT);
    t2.printProbabilities();
    cout << endl;

    // Calculate and print the probability distributions for the output file (ciphertext)
    cout << "Probability distributions for the output file (ciphertext):" << endl;
    t2.calculateDistributions(outFile, OUTPUT);
    t2.printProbabilities();
    cout << endl;

    // Print conditional probabilities
    t2.setConditionalProbabilities("plain.csv", "encode.csv");
    for (int i = 1; i < 27; i++) {
        t2.printConditionalProbabilities(i, "result.csv");
    }
}

