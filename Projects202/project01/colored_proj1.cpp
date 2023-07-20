/**
* File:    proj1.cpp
* Project: CMSC 202 Project 1, Spring 2022
* Author:  Eric Ekey
* Date:    02/21/2022
* Section: 52
* E-mail:  eekey1@gl.umbc.edu
*
* This file loads a list of 5 letter words
* and selects one at random, then prompts
* the user to try and guess the word,
* while the program indicates the accuracy
* of their guesses
**/

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <cstdlib>



using namespace std;

const int LENGTH_WORD_FILE = 2315;
const string BLANK_LINE = "_____";
const char INCORRECT_LETTER = '_';


// FUNCTIONS
string chooseWinningWord(string aWordList[]);
string getGuess(string aWordList[]);
void fillWordList(string aWordList[]);
void fillEmptyArray(string aEmptyArray[], int aNumRows=6);
void compareWords(string aGuess, string aWinningWord, string aIndicators, string aIndicatorArray[], int k);
void winLoseMessage(bool aWonGame, string aWinningWord);
void playGame();

int main() {

    string playAgain;  // whether the user will play playAgain

    cout << "Welcome to UMBC Wordle\n";
    // run the game as many times as the user wants
    do {
        playGame();
        cout << "Another game? [y/n]\n";
        getline(cin, playAgain);
    } while (playAgain == "y");

    return 0;
}


// chooseWinningWord
// given array of words, randomly returns one of them
string chooseWinningWord(string aWordList[]) {
    int winningIndex = 0;  // index of winning word in array

    // choose random word from list
    srand(time(NULL));
    winningIndex = rand() % LENGTH_WORD_FILE;

    return aWordList[winningIndex];
}


// getGuess
// prompts the user for a 5 letter word in the word list and returns a valid input
string getGuess(string aWordList[]) {
    string userInput;  // user's guess
    bool validWord = false;  // whether the guess is in the word list

    while (!validWord) {
        cout << "What word would you like to guess?\n";
        getline(cin, userInput);
        for (int i = 0; (i < LENGTH_WORD_FILE) && (!validWord); i++) {
            if (userInput == aWordList[i]) {
                validWord = true;
            }
        }
        if (!validWord) {
            cout << "That word is not in the word list\n";
        }
    }

    return userInput;
}


// fillWordList
// imports all words from proj1_data.txt into an array
void fillWordList(string aWordList[]) {
    string word;  // word in word file
    int index_tracker = 0;  // index of word array
    ifstream wordFile("proj1_data.txt");  // word file

    // add all the words in the word file to an array
    while (wordFile >> word) {
        aWordList[index_tracker] = word;
        index_tracker++;
    }

    wordFile.close();

    cout << "Your file was imported.\n" << LENGTH_WORD_FILE << " words imported.\n";
}


// fillEmptyArray
// fills empty string array with 6 rows of underscores ( _ )
void fillEmptyArray(string aEmptyArray[], int aNumRows /* =6 */) {
    for (int i = 0; i < aNumRows; i++) {
        aEmptyArray[i] = BLANK_LINE;
    }
}


// compareWords
// compares user guess with winning word and reflects accuracy of the guess in an indicator array
void compareWords(string aGuess, string aWinningWord, string aIndicators, string aIndicatorArray[], int k) {
    if (aGuess == aWinningWord) {

        aIndicatorArray[k] = ("\033[1m\033[32m" + aGuess + "\033[0m");

    } else {
        for (int i = 0; i < 5; i++) {
            bool hit = false;
            for (int j = 0; j < 5; j++) {
                if ((aGuess[i] == aWinningWord[i]) && (!hit)) {
                    // this is a hit ( ! )
                    string temp;
                    temp += aGuess[i];
                    aIndicators += ("\033[1m\033[32m" + temp + "\033[0m");
                    hit = true;
                } else if ((aGuess[i] != aWinningWord[i]) && (aGuess[i] == aWinningWord[j]) && (!hit)) {
                    // the letter is present but not a hit ( & )
                    string temp2;
                    temp2 += aGuess[i];
                    aIndicators += ("\033[1m\033[33m" + temp2 + "\033[0m");
                    hit = true;

                }
            }
            if (!hit) {
                string temp3;
                temp3 += INCORRECT_LETTER;
                aIndicators += ("\033[1m\033[31m" + temp3 + "\033[0m");
            }
        }

        aIndicatorArray[k] = aIndicators;
        k++;
    }
}




// winLoseMessage
// Tells the user whether they won or lost
void winLoseMessage(bool aWonGame, string aWinningWord) {
    if (aWonGame) {
        cout << "Congrats, you won!\n";
    } else {
        cout << "Sorry, you lost\n";
    }
    cout << "The correct word was:\t" << aWinningWord << "\n";
}


// playGame
// runs the Wordle game once
void playGame() {
    string wordList[LENGTH_WORD_FILE], indicatorArray[6];  // list of words
    // array for displaying guess accuracy
    string winningWord, guess;  // winning word
    // user guess
    string indicators = "";  // array of symbols showing guess accuracy
    string emptyIndicators = "_____";
    int numGuesses = 0;  // guess counter
    bool wonGame = false;  // whether the user has won the game

    // fill empty array with placeholders
    fillEmptyArray(indicatorArray);



    // load words from file into array
    fillWordList(wordList);

    // randomly choose a winning word
    winningWord = chooseWinningWord(wordList);

    // FOR TESTING, TELLS THE WINNING WORD
    //cout << "THE WINNING WORD IS:\t" << winningWord << "\n";

    cout << "Ok, I'm thinking of a word with 5 letters\n";
    int k = 0;
    do {
        // get guess and put it on the grid
        guess = getGuess(wordList);

        // check for matching or nonmatching but present letters
        compareWords(guess, winningWord, indicators, indicatorArray, k);
        k++;

        // print arrays of guesses
        cout << "\n";
        for (int i = 0; i < 6; i++) {
            cout << indicatorArray[i] << "\n";
        }
        cout << "\n";

        numGuesses++;
    } while ((guess != winningWord) && (numGuesses < 6));


    if (guess == winningWord) {
        wonGame = true;
    } else {
        wonGame = false;
    }
    winLoseMessage(wonGame, winningWord);

}
