#include <iostream>
#include <string>
#include <cctype>
using namespace std;

// Create the Playfair matrix
void createMatrix(const string &key, char matrix[5][5]) {
    bool used[26] = {false};
    int k = 0;

    // Fill matrix with key
    for (int i = 0; i < key.length(); i++) {
        char c = tolower(key[i]);
        if (c == 'j') c = 'i';
        if (isalpha(c)) {
            int idx = c - 'a';
            if (!used[idx]) {
                used[idx] = true;
                matrix[k / 5][k % 5] = c;
                k++;
            }
        }
    }

    // Fill with remaining alphabet
    for (char c = 'a'; c <= 'z'; c++) {
        if (c == 'j') continue;
        int idx = c - 'a';
        if (!used[idx]) {
            used[idx] = true;
            matrix[k / 5][k % 5] = c;
            k++;
        }
    }
}

// Prepare plaintext
string preprocess(const string &text) {
    string clean = "";
    // Step 1 & 2: lowercase, replace j->i, remove non-letters
    for (int i = 0; i < text.length(); i++) {
        char c = tolower(text[i]);
        if (!isalpha(c)) continue;
        if (c == 'j') c = 'i';
        clean += c;
    }

    // Step 3: handle digraphs with same letters
    string out = "";
    for (int i = 0; i < clean.length(); i++) {
        out += clean[i];
        if (i + 1 < clean.length() && clean[i] == clean[i + 1]) {
            out += 'x';  // insert x between same letters
        }
    }

    // Step 4: append x if length is odd
    if (out.length() % 2 != 0) out += 'x';

    return out;
}


// Find character position in matrix
void findPos(char matrix[5][5], char c, int &r, int &col) {
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            if (matrix[i][j] == c) { r = i; col = j; return; }
}

// Encrypt text
string encrypt(const string &plain, const string &key) {
    char matrix[5][5];
    createMatrix(key, matrix);
    string text = preprocess(plain), cipher = "";

    for (int i = 0; i < text.size(); i += 2) {
        int r1, c1, r2, c2;
        findPos(matrix, text[i], r1, c1);
        findPos(matrix, text[i+1], r2, c2);

        if (r1 == r2) { // same row
            cipher += matrix[r1][(c1+1)%5];
            cipher += matrix[r2][(c2+1)%5];
        }
        else if (c1 == c2) { // same column
            cipher += matrix[(r1+1)%5][c1];
            cipher += matrix[(r2+1)%5][c2];
        }
        else { // rectangle
            cipher += matrix[r1][c2];
            cipher += matrix[r2][c1];
        }
    }
    return cipher;
}

int main() {
    string key, plain;
    cout << "Enter key: ";
    getline(cin, key);
    cout << "Enter plaintext: ";
    getline(cin, plain);

    cout << "Ciphertext: " << encrypt(plain, key) << endl;
}
