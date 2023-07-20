//Title: RailFence.cpp
//Author: Eric Ekey
//Email: eekey1@gl.umbc.edu
//Section: 52
//Date: 4/19/2022
//Description: Function definitions for RailFence class

#include "RailFence.h"
#include <vector>

const char LETTER = 27;
const char RAIL = 26;


// Name: RailFence (Default Constructor)
// Desc: Constructor to build an empty RailFence Cipher (Defaults to 3 rails)
RailFence::RailFence() {
    m_rails = 3;
}


// Name: RailFence (Overloaded Constructor)
// Desc: Constructor to build a populated RailFence Cipher (Defaults to 3 rails)
RailFence::RailFence(string aMessage, bool aIsEncrypted, int aNumRails) {
    SetMessage(aMessage);
    if (aIsEncrypted != GetIsEncrypted()) {
        ToggleEncrypted();
    }
    m_rails = aNumRails;
}


// Name: RailFence (Destructor)
// Desc: Destructor
RailFence::~RailFence() {}


// Name: Encrypt
// Desc: Letters are placed on a fence rail based on the number of rails
//       Letters are read from one rail at a time into a single string
void RailFence::Encrypt() {
    string oldMessage = GetMessage();   // encrypted message
    string newMessage;  // encrypted message
    int whichRail = 0;  // tracker for rails
    vector<string> rails (m_rails); // vector of rails

    // populate vector with rails
    for (int i = 0; i < m_rails; i++) {
        rails.push_back("");
    }

    // put letters on rails
    for (unsigned int j = 0; j < oldMessage.size(); j++) {
        if (whichRail == m_rails) {
            whichRail -= 2;
            while (whichRail > 0) {
                rails.at(whichRail) = rails.at(whichRail) + oldMessage[j];
                whichRail--;
                j++;
            }
            whichRail = 0;
        }
        rails.at(whichRail) = rails.at(whichRail) + oldMessage[j];
        whichRail++;
    }

    // build new message by concatenating rails
    for (string rail : rails) {
        newMessage += rail;
    }

    SetMessage(newMessage);
}


// Name: Decrypt
// Desc: Single encrypted string is pushed back on the rails and reversed
void RailFence::Decrypt() {
    string oldMessage = GetMessage();   // encrypted message
    string newMessage = oldMessage; // decrypted message
    int lenMessage = GetMessage().size();   // length of message
    char railMatrix[m_rails][lenMessage];   // 2d array for message on rails

    // fill 2d array
    for (int rail = 0; rail < m_rails; rail++) {
        for (int col = 0; col < lenMessage; col++) {
            railMatrix[rail][col] = RAIL;
        }
    }

    // place letters on rails
    for (int col = 0, row = 0, flip = -1; col < lenMessage; col++){
        railMatrix[row][col] = LETTER;
        if (!row || row == m_rails - 1) {
            flip *= (-1);
        }
        row += flip;
    }

    for (int rail = 0, numLetters = 0; rail < m_rails; rail++) {
        for (int col = 0; col < lenMessage; col++) {
            if (railMatrix[rail][col] == LETTER) {
                railMatrix[rail][col] = oldMessage[numLetters];
                numLetters++;
            }
        }
    }

    // get letters off rails and build decrypted message
    for (int col = 0, row = 0, flip = -1; col < lenMessage; col++){
        char letter = railMatrix[row][col];
        newMessage[col] = letter;

        if (!row || row == m_rails - 1) {
            flip *= (-1);
        }
        row += flip;

    }

    SetMessage(newMessage);
}


// Name: ToString
// Desc - A function that returns the string of the object type
string RailFence::ToString() {
    return " (RailFence)";
}


// Name: FormatOutput
// Desc - A function that returns the formatted output for Output function
string RailFence::FormatOutput() {
    stringstream formattedOut; // formatted output for export

    formattedOut << "r" << DELIMITER << GetIsEncrypted()
    << DELIMITER << GetMessage() << DELIMITER << m_rails << endl;

    return formattedOut.str();
}
