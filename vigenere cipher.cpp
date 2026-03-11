#include <iostream>
#include <string>
using namespace std;

int main() {
    string text, key, result = "";
    int choice;

    cout << "Vigenere Cipher\n";
    cout << "1. Encrypt\n2. Decrypt\nChoose option (1 or 2): ";
    cin >> choice;
    cin.ignore();

    cout << "Enter text: ";
    getline(cin, text);
    cout << "Enter key: ";
    getline(cin, key);

    int keyIndex = 0; // track key position

    for (int i = 0; i < text.size(); i++) {
        char ch = text[i];

        if (isalpha(ch)) {
            char k = toupper(key[keyIndex % key.size()]);
            keyIndex++;

            char c;
            if (choice == 1) { // encryption
                c = toupper(ch) + (k - 'A');
                if (c > 'Z') c -= 26;
            } else { // decryption
                c = toupper(ch) - (k - 'A');
                if (c < 'A') c += 26;
            }
            result += c;
        } else {
            result += ch; // keep symbols and spaces
        }
    }

    if (choice == 1)
        cout << "Ciphertext: " << result << endl;
    else
        cout << "Decrypted text: " << result << endl;

    return 0;
}