#include <iostream>
#include <string>
using namespace std;

// Convert uppercase letter to lowercase
char toLower(char c) {
    if (c >= 'A' && c <= 'Z') return c + 32;
    return c;
}

// Check if character is a letter
bool isLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

// Create 5x5 Playfair matrix
void createMatrix(string key, char m[5][5]) {
    int used[26] = {0};  // Track used letters
    int k = 0;

    // Fill matrix with key
    for (int i = 0; i < key.length(); i++) {
        char c = toLower(key[i]);
        if (c == 'j') c = 'i';
        if (isLetter(c)) {
            int idx = c - 'a';
            if (used[idx] == 0) {
                used[idx] = 1;
                m[k/5][k%5] = c;
                k++;
            }
        }
    }

    // Fill matrix with remaining letters
    for (char c = 'a'; c <= 'z'; c++) {
        if (c == 'j') continue;
        int idx = c - 'a';
        if (used[idx] == 0) {
            used[idx] = 1;
            m[k/5][k%5] = c;
            k++;
        }
    }
}

// Preprocess plaintext: lowercase, replace j->i, remove non-letters, handle repeated letters, even length
string preprocess(string text) {
    string out = "";
    for (int i = 0; i < text.length(); i++) {
        char c = toLower(text[i]);
        if (!isLetter(c)) continue;
        if (c == 'j') c = 'i';
        out += c;
        if (i+1 < text.length() && toLower(text[i+1]) == c) out += 'x';
    }
    if (out.length() % 2 != 0) out += 'x';
    return out;
}

// Find position of character in matrix
void findPos(char m[5][5], char c, int &r, int &col) {
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            if (m[i][j] == c) { r = i; col = j; return; }
}

// Encrypt plaintext using Playfair cipher
string encrypt(string plain, string key) {
    char m[5][5];
    createMatrix(key, m);
    string text = preprocess(plain), cipher = "";

    for (int i = 0; i < text.length(); i += 2) {
        int r1,c1,r2,c2;
        findPos(m, text[i], r1,c1);
        findPos(m, text[i+1], r2,c2);

        if (r1 == r2) { // same row
            cipher += m[r1][(c1+1)%5];
            cipher += m[r2][(c2+1)%5];
        } else if (c1 == c2) { // same column
            cipher += m[(r1+1)%5][c1];
            cipher += m[(r2+1)%5][c2];
        } else { // rectangle
            cipher += m[r1][c2];
            cipher += m[r2][c1];
        }
    }
    return cipher;
}

// Print matrix
void printMatrix(char m[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) cout << m[i][j] << ' ';
        cout << endl;
    }
}

int main() {
    string key, plain;
    cout << "Enter key: "; getline(cin, key);
    cout << "Enter plaintext: "; getline(cin, plain);

    char m[5][5];
    createMatrix(key, m);
    cout << "\nPlayfair Matrix:\n";
    printMatrix(m);

    cout << "\nCiphertext: " << encrypt(plain, key) << endl;
}
