#include <iostream>
#include <string>
#include "cipher.h"

using namespace std;

int main() {
    string operation;
    string filein, fileout, password;

    cout << "Введите режим (encrypt/decrypt): ";
    cin >> operation;

    cout << "Введите пароль: ";
    cin >> password;

    cout << "Введите путь к файлу для обработки (вводный): ";
    cin >> filein;

    cout << "Введите путь к файлу для записи (выводной): ";
    cin >> fileout;

    mod_AES aes(filein, fileout, password);

    if (operation == "encrypt") {
        if (aes.encrypt()) {
            cout << "Шифрование завершено успешно!" << endl;
        } else {
            cerr << "Ошибка при шифровании!" << endl;
        }
    } else if (operation == "decrypt") {
        if (aes.decrypt()) {
            cout << "Дешифрование завершено успешно!" << endl;
        } else {
            cerr << "Ошибка при дешифровании!" << endl;
        }
    } else {
        cerr << "Неверный режим. Используйте 'encrypt' или 'decrypt'." << endl;
        return 1;
    }

    return 0;
}
