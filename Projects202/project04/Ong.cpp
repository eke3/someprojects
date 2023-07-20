//Title: Ong.cpp
//Author: Eric Ekey
//Email: eekey1@gl.umbc.edu
//Section: 52
//Date: 4/19/2022
//Description: Function definitions for Ong class

#include "Ong.h"


const string VOWELS = "aeiouAEIOU";
const string CONSONANTS = "bcdfghjklmnpqrstvwxyzBCDFGHJKLMNPQRSTVWXYZ";


// Name: Ong (Default Constructor)
// Desc: Constructor to build an empty Ong Cipher
Ong::Ong() {}


// Name: Ong (Overloaded Constructor)
// Desc: Constructor to build a populated Ong Cipher
Ong::Ong(string aMessage, bool aIsEncrypted) {
    SetMessage(aMessage);
    if (GetIsEncrypted() != aIsEncrypted) {
        ToggleEncrypted();
    }
}


// Name: Ong (Destructor)
// Desc: Destructor
Ong::~Ong() {}


// Name: IsVowel (Helper function)
// Desc: Returns true if vowel
bool Ong::IsVowel(char aChar) {
    // checks if a character is a vowel aeiou
    for (char vowel : VOWELS) {
        if (aChar == vowel) {
            return true;

        }
    }
    return false;

}


// Name: Encrypt
// Desc: Encrypts ong cipher
void Ong::Encrypt() {
    string oldMessage = GetMessage();   // decrypted message
    string newMessage;  // encrypted message

    // construct encrypted message
    for (unsigned int j = 0; j < oldMessage.size(); j++) {
        char letter = oldMessage[j];    // current letter in decrypted message
        bool isVowel = IsVowel(letter);   // whether letter is a vowel
        bool isConsonant = false;   // whether letter is a consonant

        if (isVowel) {
            if (oldMessage[j+1] == ' ' || oldMessage[j+1] == '\0') {
                string letterString(1, char(letter));
                newMessage += (letterString);
            } else {
                string letterString(1, char(letter));
                newMessage += (letterString + "-");
            }
        } else {
            // check if its a consonant
            for (char cLetter : CONSONANTS) {
                if (letter == cLetter) {
                    isConsonant = true;
                }
            }
            if (isConsonant) {
                if (oldMessage[j+1] == ' ' || oldMessage[j+1] == '\0') {
                    newMessage += (letter + ong);
                } else {
                    newMessage += (letter + ong + '-');
                }
            } else {
                // punctuation or special character
                newMessage += letter;
            }
        }
    }
    SetMessage(newMessage);
}


// Name: Decrypt
// Desc: Decrypts ong cipher
void Ong::Decrypt() {
    string oldMessage = GetMessage();   // encrypted message
    string newMessage;  // decrypted message

    // undo ong encryption
    for (unsigned int i = 0; i < oldMessage.size(); i++) {
        if (IsVowel(oldMessage[i])) {
            if (oldMessage[i] == 'o' || oldMessage[i] == 'O') {
                if (oldMessage[i + 1] == 'n' && oldMessage[i + 2] == 'g' && ((oldMessage[i + 3] == '-') || (oldMessage[i+3] == ' ') || (oldMessage[i+3] == '\0'))) {
                    if (oldMessage[i+3] == ' ') {
                        i += 2;
                    } else {
                        i += 3;
                    }
                } else {
                    if (oldMessage[i+1] == ' ') {
                        newMessage += oldMessage[i];
                        newMessage += oldMessage[i+1];
                        i += 1;
                    } else {
                        newMessage += oldMessage[i];
                        i += 1;
                    }
                }
            } else {
                if (oldMessage[i+1] == ' ') {
                    newMessage += oldMessage[i];
                    newMessage += ' ';
                    i += 1;
                } else {
                    newMessage += oldMessage[i];
                    i += 1;
                }
            }
        } else {
            newMessage += oldMessage[i];
        }
    }

    SetMessage(newMessage);
}


// Name: ToString
// Desc - A function that returns the string of the object type
string Ong::ToString() {
    return " (Ong)";
}


// Name: FormatOutput()
// Desc - A function that returns the formatted output for Output function
string Ong::FormatOutput() {
    stringstream formattedOut;  // formatted output for export

    formattedOut << "o" << DELIMITER << GetIsEncrypted()
    << DELIMITER << GetMessage() << DELIMITER << "" << endl;

    return formattedOut.str();
}
