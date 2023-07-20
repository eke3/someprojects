//Title: Cipher.cpp
//Author: Eric Ekey
//Email: eekey1@gl.umbc.edu
//Section: 52
//Date: 4/19/2022
//Description: Function definitions for Cipher class

#include "Cipher.h"

// Name: Cipher (Default Constructor)
// Desc - Stores a message and if it is encrypted (or not)
Cipher::Cipher() {
    m_message = "";
    m_isEncrypted = false;
}


// Name: Cipher (Overloaded Constructor)
// Desc - Passed a message and if it is encrypted (or not)
Cipher::Cipher(string aMessage, bool aIsEncrypted) {
    m_message = aMessage;
    m_isEncrypted = aIsEncrypted;
}


// Name: ~Cipher (Destructor)
// Desc - Virtual destructor
Cipher::~Cipher() {}


// Name: GetMessage
// Desc - Returns the message
string Cipher::GetMessage() {
    return m_message;
}


// Name: GetIsEncrypted
// Desc - Returns isEncrypted (0 is not encrypted and 1 is encrypted)
bool Cipher::GetIsEncrypted() {
    return m_isEncrypted;
}


// Name: SetMessage
// Desc - Updates a message
void Cipher::SetMessage(string aMessage) {
    m_message = aMessage;
}


// Name: ToggleEncrypted
// Desc - Turns (true to false) or (false to true)
void Cipher::ToggleEncrypted() {
    if (m_isEncrypted) {
        m_isEncrypted = false;
    } else {
        m_isEncrypted = true;
    }
}


// Name: Overloaded << Operator
// Desc - Outputs the message
ostream &operator<< (ostream &rOutput, Cipher &rCipher) {
    rOutput << rCipher.m_message;
    return rOutput;
}
