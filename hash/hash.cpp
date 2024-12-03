#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cryptopp/cryptlib.h>
#include <cryptopp/hex.h>
#include <cryptopp/files.h>
#include <cryptopp/sha.h>

using namespace std;
using namespace CryptoPP;

int main () {
    SHA224 hash;  
    cout << "Name: " << hash.AlgorithmName() << endl;
    cout << "Digest size: " << hash.DigestSize() << " bytes" << endl;
    cout << "Block size: " << hash.BlockSize() << " bytes" << endl;

    string msg = "";
    string str;
    ifstream f("/home/stud/pract4_timp/SLS");
    while (getline(f, str)) {
        msg += str;
    }

    vector<byte> digest(hash.DigestSize());
    hash.Update((const byte*)msg.data(), msg.size());
    hash.Final(digest.data());

    cout << "Message: " << msg << endl;
    cout << "Digest: ";
    StringSource(digest.data(), digest.size(), true, new HexEncoder(new FileSink(cout)));
    cout << endl;

    return 0;
}
