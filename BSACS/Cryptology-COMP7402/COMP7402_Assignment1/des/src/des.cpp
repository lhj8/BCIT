/*---------------------------------------------------------------------------------------------
--	SOURCE FILE:	des.cpp -   Process DES encryption
--
--	DATE:			Jan 08, 2024
--				    Added personal function for assignment
--
--	DESIGNERS:		Based on the code by Educative
--					des.h
--                  des.cpp
--
--	STUDENT:		HyungJoon LEE
-------------------------------------------------------------------------------------------------*/

#include "des.h"

string round_keys[16];
string pt;


bool isValidHex(const string& str) {
    for (char c : str) {
        if (!isxdigit(c)) {
            return false;
        }
    }
    return true;
}


string getHexInput(const string& prompt) {
    string input;
    do {
        cout << prompt;
        cin >> input;
        if (!isValidHex(input)) {
            cout << "Invalid hexadecimal input. Please try again." << endl;
        }
    } while (!isValidHex(input));
    return input;
}


int getRoundsInput(const string& prompt) {
    int rounds;
    while (true) {
        cout << prompt;
        cin >> rounds;

        if (cin.fail() || rounds < 1) {
            cout << "Invalid input. Please enter a positive integer.\n";
            cin.clear(); // Clear error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore remaining input
        } 
        else {
            break;
        }
    }
    return rounds;
}


string hexCharToBin(char hexChar) {
    switch(hexChar) {
        case '0': return "0000";
        case '1': return "0001";
        case '2': return "0010";
        case '3': return "0011";
        case '4': return "0100";
        case '5': return "0101";
        case '6': return "0110";
        case '7': return "0111";
        case '8': return "1000";
        case '9': return "1001";
        case 'A': case 'a': return "1010";
        case 'B': case 'b': return "1011";
        case 'C': case 'c': return "1100";
        case 'D': case 'd': return "1101";
        case 'E': case 'e': return "1110";
        case 'F': case 'f': return "1111";
        default: return ""; // invalid input
    }
}


string hexToBin(const string& hexStr) {
    string binStr = "";
    for (char hexChar : hexStr) {
        binStr += hexCharToBin(hexChar);
    }
    return binStr;
}


string binToHex(const string& binary) {
    string hex;
    int len = binary.length();
    int padding = (4 - len % 4) % 4; // Padding to make length a multiple of 4

    string paddedBinary = string(padding, '0') + binary;

    for (int i = 0; i < paddedBinary.length(); i += 4) {
        string fourBits = paddedBinary.substr(i, 4);
        int value = 0;

        if (fourBits[0] == '1') value += 8;
        if (fourBits[1] == '1') value += 4;
        if (fourBits[2] == '1') value += 2;
        if (fourBits[3] == '1') value += 1;

        if (value < 10) {
            hex += (char)('0' + value);
        } else {
            hex += (char)('A' + (value - 10));
        }
    }

    return hex;
}


string decToBin(int decimal) {
    string binary;
    while(decimal != 0) {
        binary = (decimal % 2 == 0 ? "0" : "1") + binary;
        decimal = decimal/2;
    }
    while(binary.length() < 4){
        binary = "0" + binary;
    }
    return binary;
}


int binToDec(string binary)
{
    int decimal = 0;
    int counter = 0;
    int size = binary.length();
    for(int i = size-1; i >= 0; i--)
    {
        if(binary[i] == '1'){
            decimal += pow(2, counter);
        }
        counter++;
    }
    return decimal;
}


string shift_left_once(string key_chunk){
    string shifted="";
    for(int i = 1; i < 28; i++){
        shifted += key_chunk[i];
    }
    shifted += key_chunk[0];
    return shifted;
}


string shift_left_twice(string key_chunk) {
    string shifted="";
    for(int i = 0; i < 2; i++){
        for(int j = 1; j < 28; j++){
            shifted += key_chunk[j];
        }
        shifted += key_chunk[0];
        key_chunk= shifted;
        shifted ="";
    }
    return key_chunk;
}


string Xor(string a, string b){
    string result = "";
    int size = b.size();
    for(int i = 0; i < size; i++){
        if(a[i] != b[i]){
            result += "1";
        }
        else{
            result += "0";
        }
    }
    return result;
}


void generate_keys(string key) {
    // 1. Compressing the key using the PC1 table
    string perm_key = "";
    for (int i = 0; i < 56; i++){
        perm_key += key[pc1[i]-1];
    }
    // 2. Dividing the key into two equal halves
    string left = perm_key.substr(0, 28);
    string right = perm_key.substr(28, 28);
    for(int i = 0; i < 16; i++){
        // 3.1. For rounds 1, 2, 9, 16 the key_chunks
        // are shifted by one.
        if(i == 0 || i == 1 || i == 8 || i == 15 ){
            left = shift_left_once(left);
            right = shift_left_once(right);
        }
            // 3.2. For other rounds, the key_chunks
            // are shifted by two
        else{
            left = shift_left_twice(left);
            right = shift_left_twice(right);
        }

        // Combining the two chunks
        string combined_key = left + right;
        string round_key = "";
        // Finally, using the PC2 table to transpose the key bits
        for (int i = 0; i < 48; i++){
            round_key += combined_key[pc2[i]-1];
        }
        round_keys[i] = round_key;
    }
}


string DES(unsigned int round){
    //1. Applying the initial permutation
    string perm = "";
    string txt = "";
    for (int i = 0; i < 64; i++){
        perm += pt[initial_permutation[i]-1];
    }
    // 2. Dividing the result into two equal halves
    string left = perm.substr(0, 32);
    string right = perm.substr(32, 32);

    // The plain text is encrypted 16 times
    for (int i = 0; i < round; i++) {
        string right_expanded = "";
        // 3.1. The right half of the plain text is expanded
        for (int j = 0; j < 48; j++) {
            right_expanded += right[expansion_table[j]-1];
        };  // 3.3. The result is xored with a key
        string xored = Xor(round_keys[i], right_expanded);
        string res = "";
        // 3.4. The result is divided into 8 equal parts and passed
        // through 8 substitution boxes. After passing through a
        // substituion box, each box is reduces from 6 to 4 bits.
        for (int j = 0; j < 8; j++) {
            // Finding row and column indices to lookup the
            // substituition box
            string row1= xored.substr(j * 6,1) + xored.substr(j * 6 + 5,1);
            int row = binToDec(row1);
            string col1 = xored.substr(j * 6 + 1,1) + xored.substr(j * 6 + 2,1)
                    + xored.substr(j * 6 + 3,1) + xored.substr(j * 6 + 4,1);;
            int col = binToDec(col1);
            int val = substition_boxes[j][row][col];
            res += decToBin(val);
        }
        // 3.5. Another permutation is applied
        string perm2 ="";
        for (int i = 0; i < 32; i++) {
            perm2 += res[permutation_tab[i]-1];
        }
        // 3.6. The result is xored with the left half
        xored = Xor(perm2, left);
        // 3.7. The left and the right parts of the plain text are swapped
        left = xored;
        if (i < 15) {
            string temp = right;
            right = xored;
            left = temp;
        }
        cout << "Round " << i + 1 << ": "
             << "L" << i + 1 << ": " << binToHex(left) << "  "
             << "R" << i + 1 << ": " << binToHex(right) << "  "
             << "Round Key: " << binToHex(round_keys[i]) << endl;

        txt += "Round " + to_string(i + 1) + ":  L" + to_string(i + 1) + ": "
                + binToHex(left) + "  R" + to_string(i + 1) + ": "
                + binToHex(right) + "  Round Key: " + binToHex(round_keys[i]);
        appendToFile("des.txt", txt);
        txt = "";
    }
    // 4. The halves of the plain text are applied
    string combined_text = left + right;
    string ciphertext = "";
    // The inverse of the initial permuttaion is applied
    for (int i = 0; i < 64; i++){
        ciphertext += combined_text[inverse_permutation[i] - 1];
    }
    //And we finally get the cipher text
    return ciphertext;
}


void appendToFile(const std::string& filename, const std::string& text) {
    // Open the file in append mode. It will be created if it doesn't exist.
    std::ofstream file(filename, std::ios::app);

    if (!file.is_open()) {
        std::cerr << "Failed to open or create the file: " << filename << std::endl;
        return;
    }

    // Write the text to the file
    file << text << std::endl;

    // Close the file
    file.close();
}

