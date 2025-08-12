#include <iostream>
#include <cstring>
using namespace std;

char exor(char a, char b) {
    if (a == b) {
        return '0';  
    } else {
        return '1';  
    }
}

void encode(char data[], char key[]) {
    int datalen = strlen(data);
    int keylen = strlen(key);
    
    // Append zeros to the dataword for CRC calculation
    for (int i = 0; i < keylen - 1; i++)
        data[datalen + i] = '0';
    data[datalen + keylen - 1] = '\0';

    int codelen = datalen + keylen - 1;
    char temp[20], rem[20];

    // Initialize the remainder (dividend) with the dataword
    for (int i = 0; i < keylen; i++)
        rem[i] = data[i];

    // Perform the division (XOR) process
    for (int j = keylen; j <= codelen; j++) {
        for (int i = 0; i < keylen; i++)
            temp[i] = rem[i];

        if (rem[0] == '0') {
            for (int i = 0; i < keylen - 1; i++)
                rem[i] = temp[i + 1];
        } else {
            for (int i = 0; i < keylen - 1; i++)
                rem[i] = exor(temp[i + 1], key[i + 1]);
        }

        // Bring in the next bit from the data (if any)
        if (j != codelen)
            rem[keylen - 1] = data[j];
        else
            rem[keylen - 1] = '\0';
    }

    // Append the remainder (CRC) to the original data to create the codeword
    for (int i = 0; i < keylen - 1; i++)
        data[datalen + i] = rem[i];
    data[codelen] = '\0';

    cout << "Codeword = " << data << endl;
}

void decode(char codeword[], char key[]) {
    int datalen = strlen(codeword);
    int keylen = strlen(key);
    char rem[20], temp[20];

    // Initialize the remainder (dividend) with the codeword
    for (int i = 0; i < keylen; i++) {
        rem[i] = codeword[i];
    }

    // Perform the division (XOR) process
    for (int j = keylen; j < datalen; j++) {
        for (int i = 0; i < keylen; i++)
            temp[i] = rem[i];

        if (rem[0] == '0') {
            // Shift the remainder if it starts with '0'
            for (int i = 0; i < keylen - 1; i++) {
                rem[i] = rem[i + 1];
            }
        } else { // XOR with the key if the remainder starts with '1'
            for (int i = 0; i < keylen - 1; i++) {
                rem[i] = exor(rem[i + 1], key[i + 1]);
            }
        }

        // Bring in the next bit from the codeword
        rem[keylen - 1] = codeword[j];
    }

    // Null-terminate the remainder string to check for errors
    rem[keylen - 1] = '\0';

    cout << "Syndrome = " << rem << endl;

    // Check if the remainder is all zeros (no error)
    bool error = false;
    for (int i = 0; i < keylen - 1; i++) {
        if (rem[i] != '0') {
            error = true;
            break;
        }
    }

    if (error)
        cout << "Error detected in the codeword!" << endl;
    else
        cout << "No error detected." << endl;
}

int main() {
    char key[20], data[20];
    int choice;

    while (true) {
        cout << "Select operation:" << endl;
        cout << "1. Encoding (CRC Encoding)" << endl;
        cout << "2. Decoding (CRC Decoding)" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice (1/2/3): ";
        cin >> choice;

        if (choice == 3) {
            cout << "Exiting the program." << endl;
            break;
        }

        cout << "Enter the divisor (key): ";
        cin >> key;

        switch (choice) {
            case 1:
                cout << "Enter the dataword: ";
                cin >> data;
                encode(data, key); 
                break;
            case 2:
                cout << "Enter the codeword: ";
                cin >> data;
                decode(data, key); 
                break;
            default:
                cout << "Invalid choice!" << endl;
                break;
        }
    }

    return 0;
}