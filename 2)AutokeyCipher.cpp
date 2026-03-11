#include <iostream>
#include <string>
#include <cctype>
using namespace std;

string cleanInput(string text)
{
    string result = "";
    for (char c : text)
    {
        if (isalpha(c))
        {
            result += toupper(c);
        }
    }
    return result;
}

string generateKeyStream(string plaintext, string keyword)
{
    string key = keyword;
    int pLen = plaintext.size();

    for (int i = 0; key.size() < pLen; i++)
    {
        key += plaintext[i];
    }
    return key;
}

void encrypt(string plaintext, string keyword)
{
    plaintext = cleanInput(plaintext);
    keyword = cleanInput(keyword);

    string keystream = generateKeyStream(plaintext, keyword);
    string ciphertext = "";

    for (int i = 0; i < plaintext.size(); i++)
    {
        int p = plaintext[i] - 'A';
        int k = keystream[i] - 'A';
        int c = (p + k) % 26;
        ciphertext += char(c + 'A');
    }

    cout << "Keystream  : " << keystream << endl;
    cout << "Ciphertext : " << ciphertext << endl;
}

// Decryption
void decrypt(string ciphertext, string keyword)
{
    ciphertext = cleanInput(ciphertext);
    keyword = cleanInput(keyword);

    string plaintext = "";
    string keystream = keyword;

    for (int i = 0; i < ciphertext.size(); i++)
    {
        int c = ciphertext[i] - 'A';
        int k = keystream[i] - 'A';
        int p = c - k;
        if (p < 0)
            p += 26;

        char plainChar = char(p + 'A');
        plaintext += plainChar;
        keystream += plainChar; // extend keystream dynamically
    }

    keystream = keystream.substr(0, ciphertext.size());// trim to correct length

    cout << "Keystream  : " << keystream << endl;
    cout << "Plaintext  : " << plaintext << endl;
}

int main()
{
    int choice;
    string text, keyword;

    while (true)
    {
        cout << "\n=== Autokey Cipher ===\n";
        cout << "1. Encryption\n";
        cout << "2. Decryption\n";
        cout << "3. Exit\n";
        cout << "Enter your choice (1/2/3): ";

        cin >> choice;
        cin.ignore();

        if (choice == 1)
        {
            cout << "Enter plaintext: ";
            getline(cin, text);
            cout << "Enter keyword: ";
            getline(cin, keyword);
            encrypt(text, keyword);
        }
        else if (choice == 2)
        {
            cout << "Enter ciphertext: ";
            getline(cin, text);
            cout << "Enter keyword: ";
            getline(cin, keyword);
            decrypt(text, keyword);
        }
        else if (choice == 3)
        {
            cout << "Program Exit.\n";
            break;
        }
        else
        {
            cout << "Invalid choice! Please try again.\n";
        }
    }

    return 0;
}