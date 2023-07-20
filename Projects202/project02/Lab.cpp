//Title: Lab.cpp
//Author: Eric Ekey
//Email: eekey1@gl.umbc.edu
//Section: 52
//Date: 3/11/2022
//Description: Function definitions for Lab class

#include "Lab.h"


// Lab
// Default constructor for Lab objects
Lab::Lab() {}


// LoadSubstances
// Populates m_substances[] with all the substances and their qualities from the data file
void Lab::LoadSubstances() {
    ifstream dataFile(PROJ2_DATA);  // data file
    string name, type, formula, sub1, sub2;  // qualities of each substance
    int i = 0;  // line number in datafile

    while (i < PROJ2_SIZE) {
        getline(dataFile, name, ',');
        getline(dataFile, type, ',');
        getline(dataFile, formula, ',');
        getline(dataFile, sub1, ',');
        getline(dataFile, sub2, '\n');
        Substance theSubstance(name, type, formula, sub1, sub2, 0); // Substance on the line of the datafile
        m_substances[i] = theSubstance;
        i++;
    }

    dataFile.close();
}


// StartLab
// 1. Displays Lab Title (as implemented below)
// 2. Loads all substances and their recipes into m_substances (Load Substances)
// 3. Asks user for their chemist's name (store in m_myChemist as m_myName)
// 4. Copies all substances from m_substances into the chemist's substance array
// 5. Manages the game itself including win conditions continually calling the main menu
void Lab::StartLab() {
    string chemistName;  // chemist neme
    bool quitGame = false, wonGame = false;  // booleans for whether the user has won the game or quit the game

    // display the lab title and laod all the substances from the datafile into an array
    LabTitle();
    LoadSubstances();

    cout << "What is the chemist name?\n";
    getline(cin,chemistName);
    m_myChemist.SetName(chemistName);

    // populates the chemist's inventory with all the substances, with quantities of 0
    for (int i = 0; i < PROJ2_SIZE; i++) {
        m_myChemist.AddSubstance(m_substances[i]);
    }

    // display the main menu and react accordingly to user choice
    do {
        int menuChoice = MainMenu();  // user's menu choice

        switch (menuChoice) {
            case 1:
                DisplaySubstances();
                break;
            case 2:
                SearchSubstances();
                break;
            case 3:
                CombineSubstances();
                break;
            case 4:
                CalcScore();
                break;
            case 5:
                quitGame = true;
                break;
            default:
                cout << "\nInvalid menu choice\n";
                break;
        }

        // checks if the user has at least 1 of every substance (won the game)
        if (m_myChemist.GetTotalSubstances() == PROJ2_SIZE) {
            wonGame = true;
        }

    } while (!quitGame && !wonGame);

    cout << "\nThank you for practicing chemistry!\n";
}


// DisplaySubstances
// Displays a numbered list of substances
void Lab::DisplaySubstances() {
    cout << "\n" << m_myChemist.GetName() << " has " << m_myChemist.GetTotalSubstances() << " different substances in their inventory\n";

    for (int i = 0; i < PROJ2_SIZE; i++) {
        cout << (i+1) << ". " << m_myChemist.GetSubstance(i).m_name
        << " (" << m_myChemist.GetSubstance(i).m_formula << ") "
        << m_myChemist.GetSubstance(i).m_quantity << "\n";
    }
    cout << "\n";
}


// MainMenu
// Displays a main menu and takes user input for menu choice, returns the menu choice
int Lab::MainMenu() {
    int userChoice = 0;  // user choice

    cout << "\nWhat would you like to do?\n" <<
    "1. Display your Chemist's Substances\n" <<
    "2. Search for Elements\n" <<
    "3. Attempt to Merge Substances\n" <<
    "4. See Score\n" <<
    "5. Quit\n";

    // reprompts the user if they enter something of the wrong datatype
    while (!(cin >> userChoice)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "\nWhat would you like to do?\n" <<
             "1. Display your Chemist's Substances\n" <<
             "2. Search for Elements\n" <<
             "3. Attempt to Merge Substances\n" <<
             "4. See Score\n" <<
             "5. Quit\n";
    }

    return userChoice;
}


// SearchSubstances
// Randomly selects a substance of type element and increments the quantity of it in the chemist's backpack
void Lab::SearchSubstances() {
    int randomIndex = rand() % 29; // randomly chosen positive integer less than 29
    Substance randomSubstance = m_substances[randomIndex];  // randomly chosen substance

    m_myChemist.IncrementQuantity(randomSubstance);
    cout << "\n" << m_myChemist.GetSubstance(randomIndex).m_name << " found!\n";
}


// CombineSubstances
// Attempts to combine known substances. If combined, quantity of substance decreased
// 1. Requests user to choose two substances (RequestSubstance)
// 2. Checks to see if formula exists for combining two chosen substances
//     (checks sub1, sub2 and sub2, sub1) using SearchFormula
// 3. If there is an available formula for two chosen substances, checks
//     quantity for two chosen substance.
// If no quantity for two substances, tells user that there is no available quantity
// If quantity is available, decreases quantity for two chosen substances
//     from the chemist then increases new substance
// 4. If there is no available formula, tells user that nothing happens when you try and merge two chosen substances
void Lab::CombineSubstances() {
    int materialIndex1 = 0, materialIndex2 = 0;  // indexes of components for combining
    bool hasMaterials = false;  // whether the user has the required materials to combine

    // passes material index by reference and changes them to the index where the material is
    RequestSubstance(materialIndex1);
    RequestSubstance(materialIndex2);
    // sets to properly align with indexes
    materialIndex1--;
    materialIndex2--;

    Substance material1 = m_myChemist.GetSubstance(materialIndex1);  // substance matching index #1
    Substance material2 = m_myChemist.GetSubstance(materialIndex2);  // substance matching index #2

    // checks to see if formula exists for combining two chosen substances
    int compoundIndex = SearchFormulas(m_substances[materialIndex1].m_formula, m_substances[materialIndex2].m_formula);  // index of compound you can make

    //   If there is an available formula for two chosen substances, checks quantity for two chosen substance
    if (compoundIndex == -1) {
        cout << "\nNothing happens when you try to merge these two substances...\n";
    } else {
        hasMaterials = m_myChemist.CheckQuantity(material, material2);
    }


    // If quantity is available, decreases quantity for two chosen substances from the chemist then increases new substance
    if (hasMaterials) {
        Substance compound = m_myChemist.GetSubstance(compoundIndex);

        m_myChemist.DecrementQuantity(material);
        m_myChemist.DecrementQuantity(material2);

        m_myChemist.IncrementQuantity(compound);

        cout << "\nYour chemist has built " << m_myChemist.GetSubstance(compoundIndex).m_name << "!\n";
    } else {
        if (compoundIndex != -1) {
            cout << "\nYou do not have enough of these elements to combine\n";
        }
    }
}


// RequestSubstance
// Given an integer passed by reference, alter it to the user's choice of substance to merge
void Lab::RequestSubstance(int &choice) {

    cout << "Which substances would you like to merge?\n" <<
         "To list known substances enter -1\n" <<
         "Enter substance: ";

    while (!(cin >> choice) || choice <= 0 || choice > PROJ2_SIZE) {
        cin.clear();
        cin.ignore(10000, '\n');

        if (choice == -1) {
            DisplaySubstances();
        }

        cout << "Which substances would you like to merge?\n" <<
             "To list known substances enter -1\n" <<
             "Enter substance: ";
    }
}


// SearchFormula
// Given 2 formulas, checks for a compound whose formula is those 2 components and returns its index
int Lab::SearchFormulas(string aComponent1, string aComponent2) {
    int compoundIndex = -1;  // index of compound to create

    for (int i = 0; i < PROJ2_SIZE; i++) {
        bool foundIt = ((m_substances[i].m_substance1 == aComponent1) && (m_substances[i].m_substance2 == aComponent2));  // found the formula
        bool foundItBackwards = ((m_substances[i].m_substance1 == aComponent2) && (m_substances[i].m_substance2 == aComponent1));  // found the formula in the reverse order

        if (foundIt || foundItBackwards) {
            compoundIndex = i;
        }
    }

    return compoundIndex;
}


// CalcScore
// Displays current score for Chemist
void Lab::CalcScore() {
    int numFound = m_myChemist.GetTotalSubstances();  // number of substances the chemist has 1 or more of
    const int decimalToPercent = 100;  // conversion factor of decimal to percent
    double percentFound = (decimalToPercent * (double(numFound) / PROJ2_SIZE));  // percent of total substances the chemist has found

    cout << "\n***The Chemist***\n" << "The Great Chemist " << m_myChemist.GetName()
    << "\nThere are " << PROJ2_SIZE << " substances to find\n"
    << "You have found " << numFound << " so far\n"
    << "This is " << percentFound << "%\n";
}
