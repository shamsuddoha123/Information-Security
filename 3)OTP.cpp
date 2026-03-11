#include <iostream>
#include <string>
#include <cctype>
using namespace std;

string cleanInput(string text)
{
    string result = "";
    for (char c : text)
    {
        if (isalpha((unsigned char)c))
        {
            result += (char)toupper((unsigned char)c);
        }
    }
    return result;
}

void encrypt(string plaintext, string key)
{
    plaintext = cleanInput(plaintext);
    key = cleanInput(key);

    if (plaintext.length() == 0)
    {
        cout << "Error: Plaintext has no valid letters.\n";
        return;
    }

    if (key.length() != plaintext.length())
    {
        cout << "Error: For One-Time Pad, key length must be equal to plaintext length.\n";
        return;
    }

    string ciphertext = "";
    for (int i = 0; i < (int)plaintext.length(); i++)
    {
        int p = plaintext[i] - 'A';
        int k = key[i] - 'A';
        int c = (p + k) % 26;
        ciphertext += char(c + 'A');
    }

    cout << "Keystream  : " << key << endl;
    cout << "Ciphertext : " << ciphertext << endl;
}

void decrypt(string ciphertext, string key)
{
    ciphertext = cleanInput(ciphertext);
    key = cleanInput(key);

    if (ciphertext.length() == 0)
    {
        cout << "Error: Ciphertext has no valid letters.\n";
        return;
    }

    if (key.length() != ciphertext.length())
    {
        cout << "Error: For One-Time Pad, key length must be equal to ciphertext length.\n";
        return;
    }

    string plaintext = "";
    for (int i = 0; i < (int)ciphertext.length(); i++)
    {
        int c = ciphertext[i] - 'A';
        int k = key[i] - 'A';
        int p = (c - k + 26) % 26;
        plaintext += char(p + 'A');
    }

    cout << "Plaintext  : " << plaintext << endl;
}

int main()
{
    int choice;
    string text, key;

    while (true)
    {
        cout << "\n=== One-Time Pad Cipher ===\n";
        cout << "1. Encrypt\n";
        cout << "2. Decrypt\n";
        cout << "3. Exit\n";
        cout << "Choice: ";

        cin >> choice;
        cin.ignore();

        if (choice == 1)
        {
            cout << "Enter plaintext: ";
            getline(cin, text);

            cout << "Enter key (same length as plaintext letters): ";
            getline(cin, key);

            encrypt(text, key);
        }
        else if (choice == 2)
        {
            cout << "Enter ciphertext: ";
            getline(cin, text);

            cout << "Enter key (same length as ciphertext letters): ";
            getline(cin, key);

            decrypt(text, key);
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