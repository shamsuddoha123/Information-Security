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

string generateKeyStream(string text, string keyword)
{
    string keystream = "";
    int kLen = keyword.length();

    for (int i = 0; i < text.length(); i++)
    {
        keystream += keyword[i % kLen];
    }

    return keystream;
}

void encrypt(string plaintext, string keyword)
{
    plaintext = cleanInput(plaintext);// Clean the plaintext input
    keyword = cleanInput(keyword);

    string keystream = generateKeyStream(plaintext, keyword);
    string ciphertext = "";

    for (int i = 0; i < plaintext.length(); i++)
    {
        int p = plaintext[i] - 'A';// Convert char to 0-25 range
        int k = keystream[i] - 'A';
        ciphertext += char((p + k) % 26 + 'A');
    }

    cout << "Keystream  : " << keystream << endl;
    cout << "Ciphertext : " << ciphertext << endl;
}

void decrypt(string ciphertext, string keyword)
{
    ciphertext = cleanInput(ciphertext);
    keyword = cleanInput(keyword);

    string keystream = generateKeyStream(ciphertext, keyword);
    string plaintext = "";

    for (int i = 0; i < ciphertext.length(); i++)
    {
        int c = ciphertext[i] - 'A';
        int k = keystream[i] - 'A';
        plaintext += char((c - k + 26) % 26 + 'A');
    }

    cout << "Keystream  : " << keystream << endl;
    cout << "Plaintext  : " << plaintext << endl;
}

int main()
{
    int choice;
    string text, keyword;

    while (true)
    {
        cout << "\n=== Vigenere Cipher ===\n";
        cout << "1. Encryption\n";
        cout << "2. Decryption\n";
        cout << "3. Exit\n";
        cout << "Choice: ";

        cin >> choice;
        cin.ignore();// to ignore the newline character after choice input

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