#include "Feistel.h"
#include "Key.h"


Feistel::Feistel() {
    data_.reserve(3000000);
    hexdata_.reserve(6000000);
    bindata_.reserve(12000000);
}


void Feistel::ECBencrypt(User& u) {
    Key mkey;
    int padding;

    // Input data plain text or file
    initializeData(u);

    padding = addPadding(hexdata_);
    bindata_ = hexToBin(hexdata_);

    // Round Key generation
    if (u.getKeyFlag() == USER_DEFINED) {
        mkey.setRK(u.getRoundKeys());
    }
    else
        initializeRoundKeys(u, mkey);

    // Feistel process
    for (int i = 0; i < bindata_.length(); i += 64) {
        string bin = bindata_.substr(i, 64);
        string cipherBin = feistel(u.getRoundNum(), bin, mkey.getRK());
        if (i + 64 >= bindata_.length() && !isTxt(u.getOutFile())) {
            cutLastPadding(cipherBin, padding * 4);
        }
        appendToFile(u.getOutFile(), binToHex(cipherBin));
        bin.clear();
        cipherBin.clear();
    }

    // Process DD
    if (!u.getInFile().empty() && !isTxt(u.getInFile())) {
        runDD(u.getInFile(), u.getOutFile());
    }
}


void Feistel::ECBdecrypt(User &u) {
    Key mkey;
    int padding;

    if (u.getKeyFlag() == USER_DEFINED) {
        mkey.setRK(u.getRoundKeys());
        mkey.generateReverseRoundKeys(mkey.getRK(), u.getRoundNum());
    }
    else
        initializeRoundKeys(u, mkey);

    hexdata_ = readFile(u.getInFile());
    if (!isTxt(u.getInFile())) {
        padding = addPadding(hexdata_);
    }
    bindata_ = hexToBin(hexdata_);

    for (int i = 0; i < bindata_.length(); i += 64) {
        string bin = bindata_.substr(i, 64);
        string decryptBin = feistel(u.getRoundNum(), bin, mkey.getRRK());

        // If data was from .txt file
        if (bin.size() <= 64 && isTxt(u.getInFile())) {
            decryptBin =  removeTrailingZeros(decryptBin);
        }

        // If data was from other file
        if (i + 64 >= bindata_.length() && !isTxt(u.getInFile())) {
            cutLastPadding(decryptBin, padding * 4);
        }

        if (isTxt(u.getInFile())) {
            appendToFile(u.getOutFile(), hexToASCII(binToHex(decryptBin)));
        }
        else {
            appendToFile(u.getOutFile(), binToHex(decryptBin));
        }
    }
    if (!isTxt(u.getInFile())) {
        runDD(u.getInFile(), u.getOutFile());
    }
}


void Feistel::CBCencrypt(User& u) {
    Key mkey;
    int padding;
    string iv;

    // Input data plain text or file
    initializeData(u);

    padding = addPadding(hexdata_);
    bindata_ = hexToBin(hexdata_);

    // Key gen
    if (u.getKeyFlag() == USER_DEFINED) {
        mkey.setRK(u.getRoundKeys());
    }
    else
        initializeRoundKeys(u, mkey);

    // Feistel process
    iv = u.getIV();
    for (int i = 0; i < bindata_.length(); i += 64) {
        string bin = bindata_.substr(i, 64);
        string newbin = XOR_binary(bin, iv);
        string cipherBin = feistel(u.getRoundNum(), newbin, mkey.getRK());
        if (i + 64 >= bindata_.length() && !isTxt(u.getOutFile())) {
            cutLastPadding(cipherBin, padding * 4);
        }
        iv = cipherBin;
        appendToFile(u.getOutFile(), binToHex(cipherBin));
    }

    // Process DD
    if (!u.getInFile().empty() && !isTxt(u.getInFile())) {
        runDD(u.getInFile(), u.getOutFile());
    }
}


void Feistel::CBCdecrypt(User &u) {
    Key mkey;
    int padding;
    string iv;

    if (u.getKeyFlag() == USER_DEFINED) {
        mkey.setRK(u.getRoundKeys());
        mkey.generateReverseRoundKeys(mkey.getRK(), u.getRoundNum());
    }
    else
        initializeRoundKeys(u, mkey);

    hexdata_ = readFile(u.getInFile());
    if (!isTxt(u.getInFile())) {
        padding = addPadding(hexdata_);
    }
    bindata_ = hexToBin(hexdata_);

    iv = u.getIV();

    for (int i = 0; i < bindata_.length(); i += 64) {
        string bin = bindata_.substr(i, 64);
        string beforeIv = feistel(u.getRoundNum(), bin, mkey.getRRK());
        string decryptBin = XOR_binary(beforeIv, iv);
        iv = bin;

        // If data was from .txt file
        if (bin.size() <= 64 && isTxt(u.getInFile())) {
            decryptBin =  removeTrailingZeros(decryptBin);
        }

        // If data was from other file
        if (i + 64 >= bindata_.length() && !isTxt(u.getInFile())) {
            cutLastPadding(decryptBin, padding * 4);
        }

        if (isTxt(u.getInFile())) {
            appendToFile(u.getOutFile(), hexToASCII(binToHex(decryptBin)));
        }
        else {
            appendToFile(u.getOutFile(), binToHex(decryptBin));
        }
    }
    if (!isTxt(u.getInFile())) {
        runDD(u.getInFile(), u.getOutFile());
    }
}


string Feistel::feistel(unsigned int round, const string& bin, const vector<string>& rk) {

    string perm;
    string txt;

    // Permutation1 applied
    for (int i : initial_permutation)
    {
        perm += bin[i - 1];
    }

    // Dividing the result into two equal halves
    string binL = perm.substr(0, 32);
    string binR = perm.substr(32, 32);

    // The plain text is encrypted # of round times
    for (int i = 0; i < round; i++)
    {
        string right_expand;

        // The right half of the plain text expand
        for (int j : expansion_table)
        {
            right_expand += binR[j - 1];
        }

        // right_expand XOR round key[i]
        string xored = XOR_binary(rk[i], right_expand);

        // The result is divided into 8 equal parts
        // Pass parts through 8 substitution boxes
        // After process, each parts is reduces from 6 to 4 bits
        string res;
        for (int j = 0; j < 8; j++)
        {
            // Finding row and column index to look up the substitution box
            string row1 = xored.substr(j * 6,1) + xored.substr(j * 6 + 5,1);
            string col1 = xored.substr(j * 6 + 1,1) + xored.substr(j * 6 + 2,1)
                          + xored.substr(j * 6 + 3,1) + xored.substr(j * 6 + 4,1);

            int row = binToDec(row1);
            int col = binToDec(col1);
            int val = substitution_boxes[j][row][col];
            res += decToBin(val);
        }

        // Permutation2 is applied
        string perm2;
        for (int j : permutation_tab) {
            perm2 += res[j - 1];
        }

        // perm2 XOR with the left
        xored = XOR_binary(perm2, binL);

        // The left and the right swapped
        binL = xored;
        if (i < round - 1)
        {
            string temp = binR;
            binR = xored;
            binL = temp;
        }

//        cout << "Round " << i + 1 << ": "
//             << "L" << i + 1 << ": " << binToHex(binL) << "  "
//             << "R" << i + 1 << ": " << binToHex(binR) << "  "
//             << "Round Key: " << binToHex(rk[i]) << endl;
    }

    // The halves of the plain text are applied
    string combined = binL + binR;

    // Inverse of the initial permutation is applied
    string ciphertext;
    for (int i : inverse_permutation){
        ciphertext += combined[i - 1];
    }

    return ciphertext;
}


void Feistel::initializeData(User &u) {
    if (u.isPlainTextMode()) {
        data_ = readPlainText("Enter plain text: ");
        hexdata_ = strToHex(data_);
    }
    else {
        if (isTxt(u.getInFile())) {
            data_ = readFile(u.getInFile());
            hexdata_ = strToHex(data_);
        }
        else {
            hexdata_ = readFile(u.getInFile());
        }
    }
}


void Feistel::initializeRoundKeys(User &u, Key &k) {
    bool isPreDefined = (u.getKeyFlag() == PRE_DEFINED);
    k.generateRoundKeys(u.getMainKey(), u.getRoundNum(), isPreDefined);
    if (!u.isEncryption())
        k.generateReverseRoundKeys(k.getRK(), u.getRoundNum());
}

