/*---------------------------------------------------------------------------------------------
--	SOURCE FILE:	aes.cpp -   Process AES encryption and decryption
--
--	DATE:			Jan 08, 2024
--				    Added personal function for assignment
--
--	DESIGNERS:		Based on the code by SergeyBel
--					aes.h
--                  aes.cpp
--
--	STUDENT:		HyungJoon LEE
-------------------------------------------------------------------------------------------------*/

#include "aes.h"

AES::AES(const AESKeyLength keyLength) {
    switch (keyLength) {
        case AESKeyLength::AES_128:
            this->Nk = 4;
            this->Nr = 10;
            break;
        case AESKeyLength::AES_192:
            this->Nk = 6;
            this->Nr = 12;
            break;
        case AESKeyLength::AES_256:
            this->Nk = 8;
            this->Nr = 14;
            break;
    }
}

unsigned char *AES::EncryptECB(const unsigned char in[], unsigned int inLen,
                               const unsigned char key[], int rounds) {
    CheckLength(inLen);
    unsigned char *out = new unsigned char[inLen];
    unsigned char *roundKeys = new unsigned char[4 * Nb * (rounds + 1)];
    getRoundKeys(key, roundKeys, rounds);
    for (unsigned int i = 0; i < inLen; i += blockBytesLen) {
        EncryptBlock(in + i, out + i, roundKeys);
    }

    delete[] roundKeys;

    return out;
}

unsigned char *AES::DecryptECB(const unsigned char in[], unsigned int inLen,
                               const unsigned char key[]) {
    CheckLength(inLen);
    unsigned char *out = new unsigned char[inLen];
    unsigned char *roundKeys = new unsigned char[4 * Nb * (Nr + 1)];
    KeyExpansion(key, roundKeys);
    for (unsigned int i = 0; i < inLen; i += blockBytesLen) {
        DecryptBlock(in + i, out + i, roundKeys);
    }

    delete[] roundKeys;

    return out;
}

unsigned char *AES::EncryptCBC(const unsigned char in[], unsigned int inLen,
                               const unsigned char key[],
                               const unsigned char *iv) {
    CheckLength(inLen);
    unsigned char *out = new unsigned char[inLen];
    unsigned char block[blockBytesLen];
    unsigned char *roundKeys = new unsigned char[4 * Nb * (Nr + 1)];
    KeyExpansion(key, roundKeys);
    memcpy(block, iv, blockBytesLen);
    for (unsigned int i = 0; i < inLen; i += blockBytesLen) {
        XorBlocks(block, in + i, block, blockBytesLen);
        EncryptBlock(block, out + i, roundKeys);
        memcpy(block, out + i, blockBytesLen);
    }

    delete[] roundKeys;

    return out;
}

unsigned char *AES::DecryptCBC(const unsigned char in[], unsigned int inLen,
                               const unsigned char key[],
                               const unsigned char *iv) {
    CheckLength(inLen);
    unsigned char *out = new unsigned char[inLen];
    unsigned char block[blockBytesLen];
    unsigned char *roundKeys = new unsigned char[4 * Nb * (Nr + 1)];
    KeyExpansion(key, roundKeys);
    memcpy(block, iv, blockBytesLen);
    for (unsigned int i = 0; i < inLen; i += blockBytesLen) {
        DecryptBlock(in + i, out + i, roundKeys);
        XorBlocks(block, out + i, out + i, blockBytesLen);
        memcpy(block, in + i, blockBytesLen);
    }

    delete[] roundKeys;

    return out;
}

unsigned char *AES::EncryptCFB(const unsigned char in[], unsigned int inLen,
                               const unsigned char key[],
                               const unsigned char *iv) {
    CheckLength(inLen);
    unsigned char *out = new unsigned char[inLen];
    unsigned char block[blockBytesLen];
    unsigned char encryptedBlock[blockBytesLen];
    unsigned char *roundKeys = new unsigned char[4 * Nb * (Nr + 1)];
    KeyExpansion(key, roundKeys);
    memcpy(block, iv, blockBytesLen);
    for (unsigned int i = 0; i < inLen; i += blockBytesLen) {
        EncryptBlock(block, encryptedBlock, roundKeys);
        XorBlocks(in + i, encryptedBlock, out + i, blockBytesLen);
        memcpy(block, out + i, blockBytesLen);
    }

    delete[] roundKeys;

    return out;
}

unsigned char *AES::DecryptCFB(const unsigned char in[], unsigned int inLen,
                               const unsigned char key[],
                               const unsigned char *iv) {
    CheckLength(inLen);
    unsigned char *out = new unsigned char[inLen];
    unsigned char block[blockBytesLen];
    unsigned char encryptedBlock[blockBytesLen];
    unsigned char *roundKeys = new unsigned char[4 * Nb * (Nr + 1)];
    KeyExpansion(key, roundKeys);
    memcpy(block, iv, blockBytesLen);
    for (unsigned int i = 0; i < inLen; i += blockBytesLen) {
        EncryptBlock(block, encryptedBlock, roundKeys);
        XorBlocks(in + i, encryptedBlock, out + i, blockBytesLen);
        memcpy(block, in + i, blockBytesLen);
    }

    delete[] roundKeys;

    return out;
}

void AES::CheckLength(unsigned int len) {
    if (len % blockBytesLen != 0) {
        throw std::length_error("Plaintext length must be divisible by " +
                                std::to_string(blockBytesLen));
    }
}

void AES::EncryptBlock(const unsigned char in[], unsigned char out[],
                       unsigned char *roundKeys) {
    unsigned char state[4][Nb];
    unsigned int i, j, round;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < Nb; j++) {
            state[i][j] = in[i + 4 * j];
        }
    }

    AddRoundKey(state, roundKeys);

    for (round = 1; round <= Nr - 1; round++) {
        SubBytes(state);
        ShiftRows(state);
        MixColumns(state);
        AddRoundKey(state, roundKeys + round * 4 * Nb);
    }

    SubBytes(state);
    ShiftRows(state);
    AddRoundKey(state, roundKeys + Nr * 4 * Nb);

    for (i = 0; i < 4; i++) {
        for (j = 0; j < Nb; j++) {
            out[i + 4 * j] = state[i][j];
        }
    }
}

void AES::DecryptBlock(const unsigned char in[], unsigned char out[],
                       unsigned char *roundKeys) {
    unsigned char state[4][Nb];
    unsigned int i, j, round;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < Nb; j++) {
            state[i][j] = in[i + 4 * j];
        }
    }

    AddRoundKey(state, roundKeys + Nr * 4 * Nb);

    for (round = Nr - 1; round >= 1; round--) {
        InvSubBytes(state);
        InvShiftRows(state);
        AddRoundKey(state, roundKeys + round * 4 * Nb);
        InvMixColumns(state);
    }

    InvSubBytes(state);
    InvShiftRows(state);
    AddRoundKey(state, roundKeys);

    for (i = 0; i < 4; i++) {
        for (j = 0; j < Nb; j++) {
            out[i + 4 * j] = state[i][j];
        }
    }
}

void AES::SubBytes(unsigned char state[4][Nb]) {
    unsigned int i, j;
    unsigned char t;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < Nb; j++) {
            t = state[i][j];
            state[i][j] = sbox[t / 16][t % 16];
        }
    }
}

void AES::ShiftRow(unsigned char state[4][Nb], unsigned int i,
                   unsigned int n)  // shift row i on n positions
{
    unsigned char tmp[Nb];
    for (unsigned int j = 0; j < Nb; j++) {
        tmp[j] = state[i][(j + n) % Nb];
    }
    memcpy(state[i], tmp, Nb * sizeof(unsigned char));
}

void AES::ShiftRows(unsigned char state[4][Nb]) {
    ShiftRow(state, 1, 1);
    ShiftRow(state, 2, 2);
    ShiftRow(state, 3, 3);
}

unsigned char AES::xtime(unsigned char b)  // multiply on x
{
    return (b << 1) ^ (((b >> 7) & 1) * 0x1b);
}

void AES::MixColumns(unsigned char state[4][Nb]) {
    unsigned char temp_state[4][Nb];

    for (size_t i = 0; i < 4; ++i) {
        memset(temp_state[i], 0, 4);
    }

    for (size_t i = 0; i < 4; ++i) {
        for (size_t k = 0; k < 4; ++k) {
            for (size_t j = 0; j < 4; ++j) {
                if (CMDS[i][k] == 1)
                    temp_state[i][j] ^= state[k][j];
                else
                    temp_state[i][j] ^= GF_MUL_TABLE[CMDS[i][k]][state[k][j]];
            }
        }
    }

    for (size_t i = 0; i < 4; ++i) {
        memcpy(state[i], temp_state[i], 4);
    }
}

void AES::AddRoundKey(unsigned char state[4][Nb], unsigned char *key) {
    unsigned int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < Nb; j++) {
            state[i][j] = state[i][j] ^ key[i + 4 * j];
        }
    }
}

void AES::SubWord(unsigned char *a) {
    int i;
    for (i = 0; i < 4; i++) {
        a[i] = sbox[a[i] / 16][a[i] % 16];
    }
}

void AES::RotWord(unsigned char *a) {
    unsigned char c = a[0];
    a[0] = a[1];
    a[1] = a[2];
    a[2] = a[3];
    a[3] = c;
}

void AES::XorWords(unsigned char *a, unsigned char *b, unsigned char *c) {
    int i;
    for (i = 0; i < 4; i++) {
        c[i] = a[i] ^ b[i];
    }
}

void AES::Rcon(unsigned char *a, unsigned int n) {
    unsigned int i;
    unsigned char c = 1;
    for (i = 0; i < n - 1; i++) {
        c = xtime(c);
    }

    a[0] = c;
    a[1] = a[2] = a[3] = 0;
}

void AES::KeyExpansion(const unsigned char key[], unsigned char w[]) {
    unsigned char temp[4];
    unsigned char rcon[4];
    size_t len = 4 * Nb * (Nr + 1);
    unsigned int i = 0;
    while (i < 4 * Nk) {
        w[i] = key[i];
        i++;
    }

    i = 4 * Nk;
    while (i < len) {
        temp[0] = w[i - 4 + 0];
        temp[1] = w[i - 4 + 1];
        temp[2] = w[i - 4 + 2];
        temp[3] = w[i - 4 + 3];

        if (i / 4 % Nk == 0) {
            RotWord(temp);
            SubWord(temp);
            Rcon(rcon, i / (Nk * 4));
            XorWords(temp, rcon, temp);
        } else if (Nk > 6 && i / 4 % Nk == 4) {
            SubWord(temp);
        }

        w[i + 0] = w[i - 4 * Nk] ^ temp[0];
        w[i + 1] = w[i + 1 - 4 * Nk] ^ temp[1];
        w[i + 2] = w[i + 2 - 4 * Nk] ^ temp[2];
        w[i + 3] = w[i + 3 - 4 * Nk] ^ temp[3];
        i += 4;
    }
}

void AES::InvSubBytes(unsigned char state[4][Nb]) {
    unsigned int i, j;
    unsigned char t;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < Nb; j++) {
            t = state[i][j];
            state[i][j] = inv_sbox[t / 16][t % 16];
        }
    }
}

void AES::InvMixColumns(unsigned char state[4][Nb]) {
    unsigned char temp_state[4][Nb];

    for (size_t i = 0; i < 4; ++i) {
        memset(temp_state[i], 0, 4);
    }

    for (size_t i = 0; i < 4; ++i) {
        for (size_t k = 0; k < 4; ++k) {
            for (size_t j = 0; j < 4; ++j) {
                temp_state[i][j] ^= GF_MUL_TABLE[INV_CMDS[i][k]][state[k][j]];
            }
        }
    }

    for (size_t i = 0; i < 4; ++i) {
        memcpy(state[i], temp_state[i], 4);
    }
}

void AES::InvShiftRows(unsigned char state[4][Nb]) {
    ShiftRow(state, 1, Nb - 1);
    ShiftRow(state, 2, Nb - 2);
    ShiftRow(state, 3, Nb - 3);
}

void AES::XorBlocks(const unsigned char *a, const unsigned char *b,
                    unsigned char *c, unsigned int len) {
    for (unsigned int i = 0; i < len; i++) {
        c[i] = a[i] ^ b[i];
    }
}

void AES::printHexArray(unsigned char a[], unsigned int n) {
    for (unsigned int i = 0; i < n; i++) {
        printf("%02x ", a[i]);
    }
}

void AES::printHexVector(std::vector<unsigned char> a) {
    for (unsigned int i = 0; i < a.size(); i++) {
        printf("%02x ", a[i]);
    }
}

std::vector<unsigned char> AES::ArrayToVector(unsigned char *a,
                                              unsigned int len) {
    std::vector<unsigned char> v(a, a + len * sizeof(unsigned char));
    return v;
}

unsigned char *AES::VectorToArray(std::vector<unsigned char> &a) {
    return a.data();
}

std::vector<unsigned char> AES::EncryptECB(std::vector<unsigned char>& in,
                                           std::vector<unsigned char>& key,
                                           int rounds) {
    unsigned char *out = EncryptECB(VectorToArray(in), (unsigned int)in.size(),
                                    VectorToArray(key), rounds);
    std::vector<unsigned char> v = ArrayToVector(out, in.size());
    delete[] out;
    return v;
}

std::vector<unsigned char> AES::DecryptECB(std::vector<unsigned char> in,
                                           std::vector<unsigned char> key) {
    unsigned char *out = DecryptECB(VectorToArray(in), (unsigned int)in.size(),
                                    VectorToArray(key));
    std::vector<unsigned char> v = ArrayToVector(out, (unsigned int)in.size());
    delete[] out;
    return v;
}

std::vector<unsigned char> AES::EncryptCBC(std::vector<unsigned char> in,
                                           std::vector<unsigned char> key,
                                           std::vector<unsigned char> iv) {
    unsigned char *out = EncryptCBC(VectorToArray(in), (unsigned int)in.size(),
                                    VectorToArray(key), VectorToArray(iv));
    std::vector<unsigned char> v = ArrayToVector(out, in.size());
    delete[] out;
    return v;
}

std::vector<unsigned char> AES::DecryptCBC(std::vector<unsigned char> in,
                                           std::vector<unsigned char> key,
                                           std::vector<unsigned char> iv) {
    unsigned char *out = DecryptCBC(VectorToArray(in), (unsigned int)in.size(),
                                    VectorToArray(key), VectorToArray(iv));
    std::vector<unsigned char> v = ArrayToVector(out, (unsigned int)in.size());
    delete[] out;
    return v;
}

std::vector<unsigned char> AES::EncryptCFB(std::vector<unsigned char> in,
                                           std::vector<unsigned char> key,
                                           std::vector<unsigned char> iv) {
    unsigned char *out = EncryptCFB(VectorToArray(in), (unsigned int)in.size(),
                                    VectorToArray(key), VectorToArray(iv));
    std::vector<unsigned char> v = ArrayToVector(out, in.size());
    delete[] out;
    return v;
}

std::vector<unsigned char> AES::DecryptCFB(std::vector<unsigned char> in,
                                           std::vector<unsigned char> key,
                                           std::vector<unsigned char> iv) {
    unsigned char *out = DecryptCFB(VectorToArray(in), (unsigned int)in.size(),
                                    VectorToArray(key), VectorToArray(iv));
    std::vector<unsigned char> v = ArrayToVector(out, (unsigned int)in.size());
    delete[] out;
    return v;
}


void AES::printRoundKeys(const unsigned char w[], size_t len) {
    ofstream outputFile("aes.txt", ios::app);
    if (!outputFile.is_open()) {
        cerr << "Error: Unable to open the output file." << endl;
        return;
    }
    cout << "\nGenerated Round Keys:" << endl;
    outputFile << "\nGenerated Round Keys:" << endl;
    int j = 0;
    for (int i = 0; i < len; i++) {
        if (i != 0 && i % 16 == 0) {
            printf(" : Round Key %d\n", j);
            outputFile << " : Round Key " << j << endl;
            j++;
        }
        printf("%02X ", w[i]);
        outputFile << hex << setw(2) << setfill('0') << static_cast<int>(w[i]) << " ";
    }
    printf(" : Round Key %d\n\n", j);
    cout << "Ciphertext Message:" << endl;
    outputFile << " : Round Key " << j << "\n" << endl;
    outputFile.close();
}


void AES::getRoundKeys(const unsigned char key[], unsigned char w[], int rounds) {
    unsigned char temp[4];
    unsigned char rcon[4];
    Nr = rounds;
    size_t len = 4 * Nb * (Nr + 1);
    unsigned int i = 0;
    while (i < 4 * Nk) {
        w[i] = key[i];
        i++;
    }

    i = 4 * Nk;
    while (i < len) {
        temp[0] = w[i - 4 + 0];
        temp[1] = w[i - 4 + 1];
        temp[2] = w[i - 4 + 2];
        temp[3] = w[i - 4 + 3];

        if (i / 4 % Nk == 0) {
            RotWord(temp);
            SubWord(temp);
            Rcon(rcon, i / (Nk * 4));
            XorWords(temp, rcon, temp);
        } else if (Nk > 6 && i / 4 % Nk == 4) {
            SubWord(temp);
        }

        w[i + 0] = w[i - 4 * Nk] ^ temp[0];
        w[i + 1] = w[i + 1 - 4 * Nk] ^ temp[1];
        w[i + 2] = w[i + 2 - 4 * Nk] ^ temp[2];
        w[i + 3] = w[i + 3 - 4 * Nk] ^ temp[3];
        i += 4;
    }

    printRoundKeys(w, len);
}


bool AES::isValidHex(const string &str) {
    for (char c : str) {
        if (!isxdigit(c)) {
            return false;
        }
    }
    return true;
}


string AES::getHexInput(const string &prompt) {
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


string AES::hexCharToBin(char hexChar) {
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


string AES::hexToBin(const string &hexStr) {
    string binStr = "";
    for (char hexChar : hexStr) {
        binStr += hexCharToBin(hexChar);
    }
    return binStr;
}


string AES::binToHex(const string &binary) {
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


int AES::getRoundsInput(const string &prompt) {
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


string AES::vectorToString(const std::vector<unsigned char>& vec) {
    std::ostringstream oss;
    for (unsigned int i = 0; i < vec.size(); i++) {
        oss << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(vec[i]) << " ";
    }
    return oss.str();
}


vector<unsigned char> AES::hexStringToVector(const std::string& hexStr) {
    if (hexStr.length() % 2 != 0) {
        throw std::invalid_argument("Hexadecimal string length must be even.");
    }

    std::vector<unsigned char> ucharArray;
    for (size_t i = 0; i < hexStr.length(); i += 2) {
        std::string byteString = hexStr.substr(i, 2);
        auto byte = static_cast<unsigned char>(std::stoul(byteString, nullptr, 16));
        ucharArray.push_back(byte);
    }

    return ucharArray;
}

void AES::appendToFile(const std::string& filename, const std::string& text) {
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
