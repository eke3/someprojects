//Title: CipherTool.cpp
//Author: Eric Ekey
//Email: eekey1@gl.umbc.edu
//Section: 52
//Date: 4/19/2022
//Description: Function definitions for CipherTool class

#include "CipherTool.h"

const char RAILFENCE = 'r';
const char ONG = 'o';
const char CAESAR = 'c';


// Name: CipherTool Constructor
// Desc - Creates a new CipherTool and sets m_filename based on string passed
CipherTool::CipherTool(string aFileName) {
    m_filename = aFileName;
}


// Name: CipherTool Destructor
// Desc - Calls destructor for all ciphers in m_ciphers
CipherTool::~CipherTool() {
    if (!m_ciphers.empty()) {
        for (Cipher *cipher: m_ciphers) {
            delete cipher;
            cipher = nullptr;
        }

        for (unsigned int i = 0; i < m_ciphers.size(); i++) {
            m_ciphers.pop_back();
        }
    }
}


// Name: LoadFile
// Desc - Opens file and reads in each Cipher. Each Cipher dynamically allocated
// and put into m_ciphers (c is Caesar, r is RailFence, and o is Ong)
void CipherTool::LoadFile() {
    ifstream dataFile(m_filename);
    string line;    // helper for counting lines in datafile
    int lineCount = 0;  // number of lines in datafile
    Cipher* newCipher = nullptr;    // new cipher pointer
    int i = 0;  // counter for while loop

    // count lines in datafile
    if (dataFile.is_open()) {
        while (getline(dataFile, line, '\n')) {
            lineCount++;
        }
        dataFile.close();
    }

    // read info from datafile
    dataFile.open(m_filename);
    if (dataFile.is_open()) {
        while (i < lineCount) {
            string message;
            char method;
            int shiftrails = 0;
            int encrypted = 0;
            dataFile >> method;
            dataFile.ignore();
            dataFile.clear();
            dataFile >> encrypted;
            dataFile.ignore();
            dataFile.clear();
            getline(dataFile, message, DELIMITER);
            dataFile >> shiftrails;
            dataFile.ignore();
            dataFile.clear();

            // check what kind of cipher, and point newCipher at a dynamically allocated cipher of that type
            if (method == CAESAR) {
                newCipher = new Caesar(message, encrypted, shiftrails);
            } else if (method == ONG) {
                newCipher = new Ong(message, encrypted);
            } else if (method == RAILFENCE) {
                newCipher = new RailFence(message, encrypted, shiftrails);
            }
            m_ciphers.push_back(newCipher);
            i++;
        }
        dataFile.close();
    }
}


// Name: StringToBoolean
// Desc - Helper function that converts a string to a boolean for reading in file
bool CipherTool::StringToBoolean(string aNumber) {
    // unused function
    if (aNumber == "0") {
        return true;
    } else {
        return false;
    }
}


// Name: DisplayCiphers
// Desc - Displays each of the ciphers in the m_ciphers
void CipherTool::DisplayCiphers() {
    int listNum = 1;    // numbers for labeling list
    if (!m_ciphers.empty()) {
        cout << "\n***CIPHERS***\n";
        for (Cipher *cipher: m_ciphers) {
            cout << listNum << ". " << *cipher << cipher->ToString() << "\n\n";
            listNum++;
        }
    }
}


// Name: EncryptDecrypt
// Desc - Encrypts or decrypts each of the ciphers in the m_ciphers
void CipherTool::EncryptDecrypt(bool aEncryptIt) {
    if (!m_ciphers.empty()) {
        if (!aEncryptIt) {
            int numDecrypted = 0;   // counter for decrypted ciphers
            for (Cipher *cipher: m_ciphers) {
                if (cipher->GetIsEncrypted()) {
                    cipher->Decrypt();
                    cipher->ToggleEncrypted();
                    numDecrypted++;
                }
            }
            cout << "\n*" << numDecrypted << " ciphers decrypted*\n";
        } else {
            int numEncrypted = 0;   // counter for encrypted ciphers
            for (Cipher *cipher: m_ciphers) {
                if (!cipher->GetIsEncrypted()) {
                    cipher->Encrypt();
                    cipher->ToggleEncrypted();
                    numEncrypted++;
                }
            }
            cout << "\n*" << numEncrypted << " ciphers encrypted*\n";
        }
    }
}


// Name: Export
// Desc - Exports each of the ciphers in the m_ciphers (so they can be reused)
void CipherTool::Export() {
    string filename;    // export file name
    int numCiphers = 0; // number of ciphers exported

    cout << "\nWhat would you like to call the export file?\n";
    getline(cin, filename);
    //filename += ".txt";

    ofstream exportFile(filename);  // outfile for cipher export

    for (Cipher* cipher : m_ciphers) {
        string formattedOut = cipher->FormatOutput();   // formatted output for export
        exportFile << formattedOut;
        numCiphers++;
    }
    cout << "\n*" << numCiphers << " ciphers exported to " << filename << "*\n";

    exportFile.close();
}


// Name: Menu
// Desc - Displays menu and returns choice
int CipherTool::Menu() {
    int menuChoice = 0; // user menu choice

    cout << "\nWhat would you like to do?\n"
         << "1. Display All Ciphers\n"
         << "2. Encrypt All Ciphers\n"
         << "3. Decrypt All Ciphers\n"
         << "4. Export All Ciphers\n"
         << "5. Quit\n";

    cin >> menuChoice;
    while (cin.fail() || menuChoice > 5 || menuChoice < 1) {
        cin.ignore(100, '\n');
        cin.clear();
        cout << "\nWhat would you like to do?\n"
             << "1. Display All Ciphers\n"
             << "2. Encrypt All Ciphers\n"
             << "3. Decrypt All Ciphers\n"
             << "4. Export All Ciphers\n"
             << "5. Quit\n";
        cin >> menuChoice;
    }
    cin.ignore();
    cin.clear();

    return menuChoice;
}


// Name: Start
// Desc - Loads input file, allows user to choose what to do
void CipherTool::Start() {
    enum menuChoices {
        displayC = 1,
        encryptC,
        decryptC,
        exportC,
        quit
    };  // menu choices

    LoadFile();
    if (!m_ciphers.empty()) {
        int menuChoice = 0; // user menu choice
        do {
            menuChoice = Menu();
            switch (menuChoice) {
                case displayC:
                    DisplayCiphers();
                    break;
                case encryptC:
                    EncryptDecrypt(true);
                    break;
                case decryptC:
                    EncryptDecrypt(false);
                    break;
                case exportC:
                    Export();
                    break;
                default:
                    // covers quit because only 5 can get to this point
                    break;
            }
        } while (menuChoice != quit);

        cout << "\nThanks for using UMBC Encryption!\n";
    }
}
