//Title: Chemist.cpp
//Author: Eric Ekey
//Email: eekey1@gl.umbc.edu
//Section: 52
//Date: 3/11/2022
//Description: Function definitions for Chemist class

#include "Chemist.h"


// Chemist
// Default constructor for chemist class
Chemist::Chemist() {
    m_myName = "Beaker";
    m_numSubstances = 0;
}

// Chemist
// Overloaded constructor for Chemist class, when passed a chemist name
Chemist::Chemist(string aName) {
    m_myName = aName;
    m_numSubstances = 0;
}

// GetName
// Returns the name of a chemist
string Chemist::GetName() {
    return m_myName;
}

// SetName
// Given a string, sets a chemist's name
void Chemist::SetName(string aName) {
    m_myName = aName;
}

// CheckSubstance
// Given a Substance object, returns the index in chemist's backpack where it exists, or returns -1 if it does not
int Chemist::CheckSubstance(Substance aSearchSubstance) {
    for (int i = 0; i < PROJ2_SIZE; i++) {
        if (m_mySubstances[i].m_name == aSearchSubstance.m_name) {
            return (i);
        }
    }
    return (-1);
}

// AddSubstance
// Given a Substance object, appends the substance to the end of chemist's backpack, unless they already have it
void Chemist::AddSubstance(Substance aSubstance) {
    int substanceIndex = CheckSubstance(aSubstance);  // index of the substance passed

    if (substanceIndex == -1) {
        m_mySubstances[m_numSubstances] = aSubstance;
        m_mySubstances[m_numSubstances].m_quantity = 0;
        m_numSubstances++;
    }
}

// IncrementQuantity
// Given a Substance Object increments the quantity of that substance in the chemist's backpack
void Chemist::IncrementQuantity(Substance aSubstance) {
    int substanceIndex = CheckSubstance(aSubstance);  // index of the substance passed

    m_mySubstances[substanceIndex].m_quantity++;
}

// DecrementQuantity
// Given a Substance object, decrements the quantity in the backpack and returns true,
// or just returns false if the substance is not in the backpack
bool Chemist::DecrementQuantity(Substance aSubstance) {
    int substanceIndex = CheckSubstance(aSubstance);  // index of the substance passed

    if (substanceIndex == -1) {
        return false;
    } else {
        m_mySubstances[substanceIndex].m_quantity--;
        return true;
    }
}

// CheckQuantity
// Given 2 substances, checks if the chemist's backpack holds more than 1 of both and returns true or false
bool Chemist::CheckQuantity(Substance aSubstance1, Substance aSubstance2) {
    bool greaterThanOne = ((aSubstance1.m_quantity > 1) && (aSubstance2.m_quantity > 1));  // whether the quantity of both substances passed is greater than one in the chemist's backpack

    if (greaterThanOne) {
        return true;
    } else {
        return false;
    }
}

// GetSubstance
// Given an index, returns the Substance at that index in the chemist's backpack
Substance Chemist::GetSubstance(int aIndex) {
    return m_mySubstances[aIndex];
}

// GetTotalSubstances
// counts the total number of unique substances in the chemist's backpack and returns the count
int Chemist::GetTotalSubstances() {
    int numSubstances = 0;  // total number of unique substances in chemist's backpack

    for (int i = 0; i < PROJ2_SIZE; i++) {
        if (m_mySubstances[i].m_quantity > 0) {
            numSubstances++;
        }
    }
    return numSubstances;
}


