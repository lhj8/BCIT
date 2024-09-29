#include "aes.h"

int main() {
//    string plains = "0123456789abcdeffedcba9876543210";
//    string keys   = "0f1571c947d9e8590cb7add6af7f6798";
    vector<unsigned char> plain;
    vector<unsigned char> key;
    string txt;

    AES aes(AESKeyLength::AES_128); //// 128 - key length, can be 128, 192 or 256
    string plains = aes.getHexInput("Enter hexadecimal plain text: ");
    string keys = aes.getHexInput("Enter 64-bit hexadecimal key: ");
    int round = aes.getRoundsInput("Enter the number of rounds: ");


    plain = aes.hexStringToVector(plains);
    key = aes.hexStringToVector(keys);

    string ct = aes.vectorToString(aes.EncryptECB(plain, key, round));
    cout << "Cipher Text(Hex): " << ct << endl;
    cout << "Cipher Text(Bin): " << aes.hexToBin(ct) << endl;

    txt += "Cipher Text(Hex): " + ct + "\nCipher Text(Bin): " + aes.hexToBin(ct) + "\n\n";
    aes.appendToFile("aes.txt", txt);
}