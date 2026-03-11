#include <iostream>
#include <string>
#include <cctype>
using namespace std;

string cleanPlaintext(string text)
{
    string result = "";
    for (char c : text)
    {
        if (isalpha(c))
            result += (char)toupper(c); // keep J as J
    }
    return result;
}

string cleanKeyText(string text)
{
    string result = "";
    for (char c : text)
    {
        if (isalpha(c))
        {
            char up = (char)toupper(c);
            if (up == 'J') up = 'I'; // ONLY key merges J->I
            result += up;
        }
    }
    return result;
}

string buildKey(string keyword)
{
    keyword = cleanKeyText(keyword);

    bool used[26] = {false};
    used['J' - 'A'] = true; // J alada bebohar nei tai agei use kore nissi

    string key = "";

    for (char c : keyword)
    {
        if (!used[c - 'A'])
        {
            used[c - 'A'] = true;
            key += c;
        }
    }

    for (char c = 'A'; c <= 'Z'; c++)
    {
        if (!used[c - 'A'])
        {
            used[c - 'A'] = true;
            key += c;
        }
    }

    return key; // 25 chars
}

void buildMatrix(const string &key, char matrix[5][5], int pos[26][2])
{
    int idx = 0;
    for (int r = 0; r < 5; r++)
    {
        for (int c = 0; c < 5; c++)
        {
            char ch = key[idx++];
            matrix[r][c] = ch;
            pos[ch - 'A'][0] = r;
            pos[ch - 'A'][1] = c;
        }
    }
    // J maps to I position (same cell I/J)
    pos['J' - 'A'][0] = pos['I' - 'A'][0];
    pos['J' - 'A'][1] = pos['I' - 'A'][1];
}

// ✅ EXACT preparation rules you described
string preparePlaintext(string text)
{
    text = cleanPlaintext(text);
    string prepared = "";

    int i = 0;
    while (i < (int)text.size())
    {
        char a = text[i];
        char b = (i + 1 < (int)text.size()) ? text[i + 1] : '\0';

        // last single letter -> padding rule
        if (b == '\0')
        {
            prepared += a;

            if (a == 'Z') prepared += 'X';
            else if (a == 'X') prepared += 'Z';
            else prepared += 'Z';

            break;
        }

        // same pair -> split using filler
        if (a == b)
        {
            prepared += a;

            // if XX -> XZ, otherwise AX (including ZZ -> ZX)
            if (a == 'X') prepared += 'Z';
            else prepared += 'X';

            i += 1; // only move one step
        }
        else
        {
            prepared += a;
            prepared += b;
            i += 2;
        }
    }

    return prepared;
}

string encryptPair(char a, char b, char matrix[5][5], int pos[26][2])
{
    int r1 = pos[a - 'A'][0], c1 = pos[a - 'A'][1];
    int r2 = pos[b - 'A'][0], c2 = pos[b - 'A'][1];

    string out = "";

    if (r1 == r2) // same row
    {
        out += matrix[r1][(c1 + 1) % 5];
        out += matrix[r2][(c2 + 1) % 5];
    }
    else if (c1 == c2) // same column
    {
        out += matrix[(r1 + 1) % 5][c1];
        out += matrix[(r2 + 1) % 5][c2];
    }
    else // rectangle
    {
        out += matrix[r1][c2];
        out += matrix[r2][c1];
    }

    return out;
}

string decryptPair(char a, char b, char matrix[5][5], int pos[26][2])
{
    int r1 = pos[a - 'A'][0], c1 = pos[a - 'A'][1];
    int r2 = pos[b - 'A'][0], c2 = pos[b - 'A'][1];

    string out = "";

    if (r1 == r2) // same row
    {
        out += matrix[r1][(c1 + 4) % 5];
        out += matrix[r2][(c2 + 4) % 5];
    }
    else if (c1 == c2) // same column
    {
        out += matrix[(r1 + 4) % 5][c1];
        out += matrix[(r2 + 4) % 5][c2];
    }
    else // rectangle
    {
        out += matrix[r1][c2];
        out += matrix[r2][c1];
    }

    return out;
}

void encryptPlayfair(string plaintext, string keyword)
{
    string key = buildKey(keyword);

    char matrix[5][5];
    int pos[26][2];
    buildMatrix(key, matrix, pos);

    string prepared = preparePlaintext(plaintext);
    string ciphertext = "";

    for (int i = 0; i < (int)prepared.size(); i += 2)
        ciphertext += encryptPair(prepared[i], prepared[i + 1], matrix, pos);

    cout << "Prepared   : " << prepared << endl;
    cout << "Ciphertext : " << ciphertext << endl;
}

void decryptPlayfair(string ciphertext, string keyword)
{
    ciphertext = cleanPlaintext(ciphertext);

    if (ciphertext.size() % 2 != 0)
    {
        cout << "Error: Ciphertext length must be even for Playfair.\n";
        return;
    }

    string key = buildKey(keyword);

    char matrix[5][5];
    int pos[26][2];
    buildMatrix(key, matrix, pos);

    string plaintext = "";
    for (int i = 0; i < (int)ciphertext.size(); i += 2)
        plaintext += decryptPair(ciphertext[i], ciphertext[i + 1], matrix, pos);

    cout << "Plaintext  : " << plaintext << endl;
}

int main()
{
    int choice;
    string text, keyword;

    while (true)
    {
        cout << "\n=== Playfair Cipher ===\n";
        cout << "1. Encryption\n";
        cout << "2. Decryption\n";
        cout << "3. Exit\n";
        cout << "Choice: ";

        cin >> choice;
        cin.ignore();

        if (choice == 1)
        {
            cout << "Enter plaintext: ";
            getline(cin, text);

            cout << "Enter keyword: ";
            getline(cin, keyword);

            encryptPlayfair(text, keyword);
        }
        else if (choice == 2)
        {
            cout << "Enter ciphertext: ";
            getline(cin, text);

            cout << "Enter keyword: ";
            getline(cin, keyword);

            decryptPlayfair(text, keyword);
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