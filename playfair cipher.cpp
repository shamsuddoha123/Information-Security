#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

// 5x5 key matrix for Playfair cipher
char keyMatrix[5][5];


// ---------------------------------------------------
// Function: buildMatrix
// Builds the Playfair matrix from a given keyword
// Steps:
// 1. Add keyword letters (J = I, remove duplicates).
// 2. Fill remaining alphabet letters (skip J).
// ---------------------------------------------------
void buildMatrix(char key[]) {
    int seen[26] = {0}; // keeps track of used letters
    int k = 0;

    // Insert keyword characters
    for (int i = 0; key[i]; i++) {
        char c = toupper(key[i]);
        if (c == 'J') c = 'I';           // replace J with I
        if (c < 'A' || c > 'Z') continue; // ignore non-letters
        if (!seen[c - 'A']) {
            keyMatrix[k / 5][k % 5] = c;
            seen[c - 'A'] = 1;
            k++;
        }
    }

    // Insert remaining unused letters
    for (char c = 'A'; c <= 'Z'; c++) {
        if (c == 'J') continue;          // skip J
        if (!seen[c - 'A']) {
            keyMatrix[k / 5][k % 5] = c;
            seen[c - 'A'] = 1;
            k++;
        }
    }
}


// ---------------------------------------------------
// Function: findPos
// Finds the row and column of a character in matrix
// ---------------------------------------------------
void findPos(char c, int &r, int &cpos) {
    if (c == 'J') c = 'I';
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            if (keyMatrix[i][j] == c) {
                r = i; cpos = j; return;
            }
}


// ---------------------------------------------------
// Function: prepareText
// Cleans plaintext and splits into digraphs:
// Rules:
// 1. Convert to uppercase, replace J with I.
// 2. If two same letters in a pair, insert 'X'.
// 3. If last letter has no pair, append 'X'.
// ---------------------------------------------------
void prepareText(char text[], char prepared[]) {
    int n = strlen(text), m = 0, k = 0;
    char clean[200];

    // Step 1: clean text
    for (int i = 0; i < n; i++) {
        char c = toupper(text[i]);
        if (c < 'A' || c > 'Z') continue;
        if (c == 'J') c = 'I';
        clean[m++] = c;
    }
    clean[m] = '\0';

    // Step 2: create digraphs
    for (int i = 0; i < m;) {
        char a = clean[i];
        char b = (i + 1 < m) ? clean[i+1] : 'X';

        if (a == b) { // same letters in a pair
            prepared[k++] = a;
            prepared[k++] = 'X';
            i++;
        } else {      // normal case
            prepared[k++] = a;
            prepared[k++] = b;
            i += 2;
        }
    }
    prepared[k] = '\0';
}


// ---------------------------------------------------
// Function: encryptPair
// Encrypts a digraph according to Playfair rules
// ---------------------------------------------------
void encryptPair(char a, char b, char &x, char &y) {
    int r1,c1,r2,c2;
    findPos(a,r1,c1);
    findPos(b,r2,c2);

    if (r1 == r2) { // same row → shift right
        x = keyMatrix[r1][(c1+1)%5];
        y = keyMatrix[r2][(c2+1)%5];
    }
    else if (c1 == c2) { // same column → shift down
        x = keyMatrix[(r1+1)%5][c1];
        y = keyMatrix[(r2+1)%5][c2];
    }
    else { // rectangle swap
        x = keyMatrix[r1][c2];
        y = keyMatrix[r2][c1];
    }
}


// ---------------------------------------------------
// Function: decryptPair
// Decrypts a digraph according to Playfair rules
// ---------------------------------------------------
void decryptPair(char a, char b, char &x, char &y) {
    int r1,c1,r2,c2;
    findPos(a,r1,c1);
    findPos(b,r2,c2);

    if (r1 == r2) { // same row → shift left
        x = keyMatrix[r1][(c1+4)%5];
        y = keyMatrix[r2][(c2+4)%5];
    }
    else if (c1 == c2) { // same column → shift up
        x = keyMatrix[(r1+4)%5][c1];
        y = keyMatrix[(r2+4)%5][c2];
    }
    else { // rectangle swap
        x = keyMatrix[r1][c2];
        y = keyMatrix[r2][c1];
    }
}


// ---------------------------------------------------
// MAIN FUNCTION
// ---------------------------------------------------
int main() {
    char key[100], text[200], prepared[200];
    
    cout << "Enter keyword: ";
    cin.getline(key, 100);
    buildMatrix(key);

    cout << "\nKey Matrix:\n";
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) cout << keyMatrix[i][j] << " ";
        cout << endl;
    }

    cout << "\nEnter plaintext: ";
    cin.getline(text, 200);
    prepareText(text, prepared);

    cout << "Prepared Text: ";
    for (int i = 0; prepared[i]; i+=2)
        cout << prepared[i] << prepared[i+1] << " ";
    cout << endl;

    // Encrypt
    char cipher[200]; int k = 0;
    for (int i = 0; prepared[i]; i+=2) {
        char x,y; encryptPair(prepared[i], prepared[i+1], x, y);
        cipher[k++] = x; cipher[k++] = y;
    }
    cipher[k] = '\0';
    cout << "Ciphertext: ";
    for (int i = 0; cipher[i]; i+=2)
        cout << cipher[i] << cipher[i+1] << " ";
    cout << endl;

    // Decrypt
    char plain[200]; k = 0;
    for (int i = 0; cipher[i]; i+=2) {
        char x,y; decryptPair(cipher[i], cipher[i+1], x, y);
        plain[k++] = x; plain[k++] = y;
    }
    plain[k] = '\0';
    cout << "Decrypted: ";
    for (int i = 0; plain[i]; i+=2)
        cout << plain[i] << plain[i+1] << " ";
    cout << endl;

    return 0;
}