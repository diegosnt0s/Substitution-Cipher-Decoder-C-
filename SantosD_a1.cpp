#include <iostream>
#include <unordered_map>
#include <fstream>
#include <cctype>
#include <string> 
using namespace std;

int main() {
    string ciphertextFile = "Ciphertext.txt";
    ifstream inputFile(ciphertextFile);
    string PlainTextFile = "PlainText.txt";
    ifstream inputFile2(PlainTextFile);

    if (!inputFile || !inputFile2) {
        cout << "File failed to open." << endl;
        return 1;
    }
    /*
    This is the key for this specific substitution cipher, 
    it was obtained via getting the letter Frequency and mapping it 
    to the corresponding value.  
    */
    unordered_map<char, char> cipherToPlain = {
        {'G', 'A'}, {'D', 'W'}, {'E', 'C'}, {'V', 'L'}, {'S', 'E'},
        {'W', 'U'}, {'X', 'G'}, {'F', 'H'}, {'O', 'I'}, {'N', 'K'},
        {'A', 'V'}, {'K', 'D'}, {'R', 'M'}, {'I', 'N'}, {'T', 'O'},
        {'H', 'Y'}, {'C', 'J'}, {'Y', 'T'}, {'M', 'P'},
        {'J', 'B'}, {'M', 'P'}, {'L', 'Z'}, {'Q', 'S'}, {'Z', 'R'}, {'U', 'F'}
    };

    int letterFrequency[26] = { 0 }; 
    char ch;
    int chCounter = 0;
    string cipherText = "", plainText = "";
    string line;

    while (inputFile.get(ch)) { 
        if (isalpha(ch)) {  // Only store letters (ignore spaces/punctuation)
            ch = toupper(ch);  // Convert to uppercase
            letterFrequency[ch - 'A']++;  // Increment letter count
            chCounter++; // Counter for total Chars
            cipherText += ch;  // Store ciphertext
        }
        else {
            cipherText += ch; // Preserve spaces/punctuation
        }
    }
    inputFile.close();

    cout << "Total Count of Characters: " << chCounter << endl;

    for (int i = 0; i < 26; i++) {
        if (letterFrequency[i] > 0) { 
            cout << "Total Ciphertext Appearances For " << char('A' + i) << ": " << letterFrequency[i] << endl;
            double x = (double)letterFrequency[i] / chCounter * 100;
            cout << "Frequency: " << x << "%" << endl;
        }
    }

    // Print cipher to plain text mapping
    cout << "\nCipher to Plain Text Mapping:\n";
    for (const auto& pair : cipherToPlain) {
        cout << pair.first << " -> " << pair.second << endl;
    }

    // Convert ciphertext to plaintext
    for (char c : cipherText) {
        if (cipherToPlain.find(c) != cipherToPlain.end()) {
            plainText += cipherToPlain[c];  // Replace with mapped letter
        }
        else {
            plainText += c;  // Preserve spaces and unknown characters
        }
    }
    
    // Printout For Cipher/Plain Text 
    cout << "\n";
    cout << "Ciphertext: " << cipherText << endl;
    cout << "\n";
    cout << "Plaintext:  " << plainText << endl;
    cout << "\n";
    cout << "Plaintext with spaces and punctuation: ";
    getline(inputFile2, line);
    cout << line << endl; 
    

    inputFile2.close();

    return 0;
}