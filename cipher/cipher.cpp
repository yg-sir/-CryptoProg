#include "cipher.h"

bool mod_AES::encrypt() {
    // Генерация ключа с использованием пароля и соли
    SecByteBlock key(AES::DEFAULT_KEYLENGTH);
    PKCS12_PBKDF<SHA1> pbkdf;

    // Используем CryptoPP::byte, чтобы избежать конфликтов типов
    pbkdf.DeriveKey(key.data(), key.size(), 0, (CryptoPP::byte*)psw.data(), psw.size(), 
                    (CryptoPP::byte*)salt.data(), salt.size(), 1024, 0.0f);
    
    cout << "Ключ: ";
    StringSource(key.data(), key.size(), true, new HexEncoder(new FileSink(cout)));
    cout << endl;

    // Генерация IV (инициализирующего вектора)
    AutoSeededRandomPool prng;
    CryptoPP::byte iv[AES::BLOCKSIZE];  // Используем CryptoPP::byte
    prng.GenerateBlock(iv, sizeof(iv));

    // Запись IV в файл
    ofstream file_iv(fileout + ".iv", ios::out | ios::binary);
    if (!file_iv) {
        cerr << "Ошибка при открытии файла для записи IV!" << endl;
        return false;
    }
    file_iv.write((char*)iv, AES::BLOCKSIZE);
    file_iv.close();
    cout << "IV записано в: " << fileout << ".iv" << endl;

    // Шифрование файла
    try {
        CBC_Mode<AES>::Encryption encr;
        encr.SetKeyWithIV(key, key.size(), iv);
        FileSource fs(filein.c_str(), true, new StreamTransformationFilter(encr, new FileSink(fileout.c_str())));
    } catch (const Exception& e) {
        cerr << e.what() << endl;
        return false;
    }

    return true;
}

bool mod_AES::decrypt() {
    // Генерация ключа с использованием пароля и соли
    SecByteBlock key(AES::DEFAULT_KEYLENGTH);
    PKCS12_PBKDF<SHA1> pbkdf;
    
    // Используем CryptoPP::byte, чтобы избежать конфликтов типов
    pbkdf.DeriveKey(key.data(), key.size(), 0, (CryptoPP::byte*)psw.data(), psw.size(), 
                    (CryptoPP::byte*)salt.data(), salt.size(), 1024, 0.0f);
    
    cout << "Ключ: ";
    StringSource(key.data(), key.size(), true, new HexEncoder(new FileSink(cout)));
    cout << endl;

    // Чтение IV из файла
    CryptoPP::byte iv[AES::BLOCKSIZE];  // Используем CryptoPP::byte
    ifstream file_iv(filein + ".iv", ios::in | ios::binary);
    if (!file_iv) {
        cerr << "Ошибка при открытии файла IV!" << endl;
        return false;
    }
    file_iv.read((char*)&iv, AES::BLOCKSIZE);
    if (!file_iv) {
        cerr << "Ошибка при чтении IV из файла!" << endl;
        return false;
    }
    file_iv.close();

    // Дешифрование файла
    try {
        CBC_Mode<AES>::Decryption decr;
        decr.SetKeyWithIV(key, key.size(), iv);
        FileSource fs(filein.c_str(), true, new StreamTransformationFilter(decr, new FileSink(fileout.c_str())));
    } catch (const Exception& e) {
        cerr << e.what() << endl;
        return false;
    }

    return true;
}
