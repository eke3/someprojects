//Title: Caesar.cpp
//Author: Eric Ekey
//Email: eekey1@gl.umbc.edu
//Section: 52
//Date: 4/19/2022
//Description: Function definitions for Caesar class

#include "Caesar.h"

const int LENGTH_ALPHABET = 26;
const int UPPERCASE_START = 65;
const int UPPERCASE_END = 90;
const int LOWERCASE_START = 97;
const int LOWERCASE_END = 122;


// Name: Caesar (Default Constructor)
// Desc: Constructor to build an empty Caesar Cipher (Defaults to shift 3)
Caesar::Caesar() {
    m_shift = 3;
}


// Name: Caesar (Overloaded Constructor)
// Desc: Constructor to build a populated Caesar Cipher (Defaults to shift 3)
Caesar::Caesar(string aMessage, bool aIsEncrypted, int aShift) {
    SetMessage(aMessage);
    if (GetIsEncrypted() != aIsEncrypted) {
        ToggleEncrypted();
    }
    m_shift = (aShift % LENGTH_ALPHABET);
}


// Name: Caesar (Destructor)
// Desc: Destructor
Caesar::~Caesar() {}


// Name: Encrypt
// Desc: Shifts characters right based on shift
void Caesar::Encrypt() {
    // make a copy of the message
    string newMessage = GetMessage();   // decrypted message to be encrypted in place
    int newLetter = 0;  // ASCII value for characters in message

    // encrypt each letter of decrypted message
    for (unsigned int i = 0; i < GetMessage().size(); i++) {
        newLetter = newMessage[i];
        if ((newLetter > LOWERCASE_END) || ((newLetter > UPPERCASE_END) && (newLetter < LOWERCASE_START)) || (newLetter < UPPERCASE_START)) {
            /// do nothing
        } else {
            newLetter = newMessage[i] + m_shift;
            if ((newLetter > LOWERCASE_END) || ((newLetter > UPPERCASE_END) && (newLetter < LOWERCASE_START))) {
                newLetter -= LENGTH_ALPHABET;
            }
            newMessage[i] = char(newLetter);
        }
    }

    SetMessage(newMessage);
}


// Name: Decrypt
// Desc: Shifts characters left based on shift
void Caesar::Decrypt() {
    string newMessage = GetMessage();   // encrypted message, to be decrypted in place

    // undo encryption for each character in encrypted message
    for (unsigned int i = 0; i < GetMessage().size(); i++) {
        int newLetter = newMessage[i];  // letter in newMessage

        if ((newLetter < UPPERCASE_START) || ((newLetter > UPPERCASE_END) && (newLetter < LOWERCASE_START)) || (newLetter > LOWERCASE_END)) {
            // do nothing
        } else {
            newLetter = newMessage[i] - m_shift;
            if ((newLetter < UPPERCASE_START) || ((newLetter > UPPERCASE_END) && (newLetter < LOWERCASE_START))) {
                newLetter += LENGTH_ALPHABET;
            }
            newMessage[i] = char(newLetter);
        }
    }

    SetMessage(newMessage);
}


// Name: ToString
// Desc - A function that returns the string of the object type
string Caesar::ToString() {
    return " (Caesar)";
}


// Name: FormatOutput()
// Desc - A function that returns the formatted output for Output function
string Caesar::FormatOutput() {
    stringstream formattedOut;  // formatted output for export

    formattedOut << "c" << DELIMITER << GetIsEncrypted()
    << DELIMITER << GetMessage() << DELIMITER << m_shift << endl;

    return formattedOut.str();
}
