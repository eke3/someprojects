/*****************************************************************************
 ** File: Trivia.cpp
 ** Project: CMSC 202 Project 5, Spring 2022
 ** Author:  Eric Ekey, Kush Shah and CMSC202
 ** Section: 52
 ** Date:    05/01/2022
 ** Email:   eekey1@gl.umbc.edu
 **
 Description: CPP file for Trivia class. Includes both class definition and
 class function definitions. Loads a file of trivia questions
*****************************************************************************/

#ifndef TRIVIA_CPP
#define TRIVIA_CPP
#include "Lqueue.cpp"
#include "Question.cpp"
#include <fstream>
#include <vector>
using namespace std;

const string DEFAULT_FILE = "proj5_string.txt";
const char DELIMITER = '|';

template <class T>
class Trivia {
public:
  // Name: Default Constructor
  // Desc: Displays the title, Loads Questions and calls menu
  // Indicates if the file was not loaded.
  // Precondition: None
  // Postcondition: User is prompted with assignment menus
  Trivia(string filename= DEFAULT_FILE);
  // Name: Destructor
  // Desc: Deallocates memory allocated for the Questions and
  // resets all variables.
  // Precondition: A Trivia exists.
  // Postcondition: All dynamically allocated memory in Trivia is deleted.
  ~Trivia();
  // Name: LoadQuestions
  // Desc: Each input file will be for a specific type of question (int, double, string)
  //       Reads in Questions from a file and stores them in anLqueue.
  //       An input file will be for exactly one type of question (int, double, string)
  // Precondition: None.
  // Postcondition: Returns true if file was read. Otherwise, it returns false.
  bool LoadQuestions(string filename);
  // Name: MainMenu
  // Desc: Presents user with menu options for showing subjects and allowing
  // user to work on a subject.
  // Precondition: None.
  // Postcondition: The main menu is presented.
  void MainMenu();
  // Name: DisplaySubjects
  // Desc: Presents all Subjects with corresponding numerical identifiers.
  // Precondition: Subjects have been added.
  // Postcondition: All assignments are printed to the screen.
  void DisplaySubjects();
  // Name: StartSubject
  // Desc: Starts working on a selected Subject.
  // Displays the number of questions in subject.
  // Starts at beginning and goes through each question.
  // After all questions have been answered:
  //       displays total correct, incorrect, and percentage correct
  // Precondition: m_questions has been populated
  // Postcondition: Returns to main menu
  void StartSubject();
  // Name: AddSubject
  // Desc: Checks to see if a subject exists in m_subjects.
  //       If not, inserts subject into m_subjects.
  // Precondition: A Subject exists.
  // Postcondition: Add subject to m_subjects if new subject.
  void AddSubject(string subject);
  // Name: ChooseSubject
  // Desc: Allows a user to choose one of the subjects to work on. Lists all subjects
  // in m_subjects and allows use to choose one. Returns value - 1 (location in vector)
  // Precondition: A Subject exists.
  // Postcondition: Returns value entered minus one
  int ChooseSubject();
  // Name: QuestionsPerSubject
  // Desc: Iterates over m_questions and counts how many questions match the subject
  // passed into function
  // Precondition: A Subject exists.
  // Postcondition: Returns number of questions of a particular subject
  int QuestionsPerSubject(string subject);
  // Name: DisplayTitle
  // Desc: Displays opening Welcome message
  // Precondition: None.
  // Postcondition: Title is displayed.
  void DisplayTitle();
private:
  Lqueue<Question<T>* >* m_questions; // Holds questions using a specific data type
  vector<string> m_subjects; //Populated as file is loaded
};

//**********Implement Trivia Class Here***********


// Name: Default Constructor
// Desc: Displays the title, Loads Questions and calls menu
// Indicates if the file was not loaded.
template <class T>
Trivia<T>::Trivia(string aFilename) {
    // try to start the game
    DisplayTitle();
    if (LoadQuestions(aFilename)) {
        MainMenu();
    } else {
        cout << "\nThe file could not be loaded-\n";
    }
}


// Name: Destructor
// Desc: Deallocates memory allocated for the Questions
template <class T>
Trivia<T>::~Trivia() {
    // delete dynamically allocated questions and lqueue
    for (int i = 0; i < m_questions->GetSize(); i++) {
        delete m_questions->At(i);
    }
    delete m_questions;
    m_questions = nullptr;
}


// Name: LoadQuestions
// Desc: Reads in Questions from a file and stores them in an Lqueue.
template <class T>
bool Trivia<T>::LoadQuestions(string aFilename) {
    Question<T>* newQuestion = nullptr; // question pointer to dynamically allocated question
    string subject, question, datatype, line;   // question subject
                                                // question
                                                // answer datatype
                                                // helper for counting lines
    T answer;   // question answer
    int difficulty = 0, lineCount = 0, i = 0;   // question difficulty
                                                // datafile linecount
                                                // counter
    bool readSuccess = false;   // whether file was successfully read
    ifstream dataFile(aFilename);   // open datafile

    if (dataFile.is_open()) {
        // count lines in datafile
        while (getline(dataFile, line, '\n')) {
            lineCount++;
        }
        dataFile.close();

        // reopen datafile
        dataFile.open(aFilename);
        // point m_questions to an lqueue
        m_questions = new Lqueue<Question<T>*>;
        // populate m_questions and m_subjects
        while (i < lineCount) {
            getline(dataFile, subject, DELIMITER);
            getline(dataFile, question, DELIMITER);
            getline(dataFile, datatype, DELIMITER);
            dataFile >> difficulty;
            dataFile.ignore();
            dataFile.clear();
            dataFile >> answer; // needs to take spaces
            dataFile.ignore();
            dataFile.clear();
            newQuestion = new Question<T>(subject, question, datatype, difficulty, answer);
            m_questions->Push(newQuestion);  // causing seg fault
            AddSubject(subject);
            i++;
        }
        readSuccess = true;
        dataFile.close();
    }
    return readSuccess;
}


// Name: MainMenu
// Desc: Presents user with menu options
template <class T>
void Trivia<T>::MainMenu() {
    int menuChoice = 0; // user menu choice
    enum menuChoices {displaySubjects = 1, startSubject, quitGame}; // valid menu choices

    // run main menu and evaluate user menu choices
    do {
        cout << "\nChoose an option:\n"
        << "1. Display Subjects\n"
        << "2. Start Subject\n"
        << "3. Quit\n";

        while (!(cin >> menuChoice || menuChoice < 1 || menuChoice > 3)) {
            cout << "-Invalid Selection-\n";
            cin.ignore(10000, '\n');
            cin.clear();
        }

        // react to user menu selections
        switch (menuChoice) {
            case displaySubjects:
                DisplaySubjects();
                break;
            case startSubject:
                StartSubject();
                break;
            default:
                // only covers quit
                break;
        }
    } while (menuChoice != quitGame);
}


// Name: DisplaySubjects
// Desc: Presents all Subjects with corresponding numerical identifiers.
template <class T>
void Trivia<T>::DisplaySubjects() {
    int listNum = 1;    // numbers for labeling list

    // list possible subjects
    if (!m_subjects.empty()) {
        cout << "\n***Possible Subjects***\n";
        for (string subject : m_subjects) {
            cout << listNum << ". " << subject << "\n";
            listNum++;
        }
    }
}


// Name: StartSubject
// Desc: Starts working on a selected Subject.
// Displays the number of questions in subject.
// Starts at beginning and goes through each question.
// After all questions have been answered:
//       displays total correct, incorrect, and percentage correct
template <class T>
void Trivia<T>::StartSubject() {
    int subjectChoice = ChooseSubject();    // user-chosen subject index
    int listNum = 1, totalCorrect = 0, totalIncorrect = 0, numQuestions = 0;    // numbers for labeling list
                                                                                // questions correct
                                                                                // questions incorrect
                                                                                // total questions
    double percentCorrect;  // percent of questions correct
    T answer;   // user answer input
    string subject = m_subjects.at(subjectChoice), lqCurrSubject;   // user chosen subject
                                                                    // moving subject in m_questions

    // find questions of the selected subject, ask them, and tel the user if their answer is correct
    cout << "There are " << QuestionsPerSubject(subject) << " questions in this subject\n";
    for (int i = 0; i < m_questions->GetSize(); i++) {
        lqCurrSubject = m_questions->At(i)->m_subject;
        if (lqCurrSubject == subject) {
            cout << "\n" << listNum << ". " << *m_questions->At(i);
            cin >> answer;
            cin.ignore(10000, '\n');
            cin.clear();
            if (m_questions->At(i)->CheckAnswer(answer)) {
                cout << "*Correct*\n";
                totalCorrect++;
            } else {
                cout << "*Incorrect*\n";
                totalIncorrect++;
            }
            numQuestions++;
            listNum++;
        }
    }
    // calculate percent of correct answers given by user
    percentCorrect = double(totalCorrect)/double(numQuestions) * 100;

    // output stats for user answers
    cout << "\nYou got " << totalCorrect << " answer(s) correct\n"
    << "You got " << totalIncorrect << " answer(s) incorrect\n"
    << "Which is a " << percentCorrect << "%\n";
}


// Name: AddSubject
// Desc: Checks to see if a subject exists in m_subjects.
//       If not, inserts subject into m_subjects.
template <class T>
void Trivia<T>::AddSubject(string aSubject) {
    bool subjectMissing = true; // whether the passed subject is missing from m_subjects

    // determine if the subject is present in m_subjects
    for (string subject : m_subjects) {
        if (subject == aSubject) {
            subjectMissing = false;
        }
    }

    // if the subject is missing, add it to m_subjects
    if (subjectMissing) {
        m_subjects.push_back(aSubject);
    }
}


// Name: ChooseSubject
// Desc: Allows a user to choose one of the subjects to work on. Lists all subjects
// in m_subjects and allows use to choose one. Returns value - 1 (location in vector)
template <class T>
int Trivia<T>::ChooseSubject() {
    int userChoice = -1;    // user choice of subject

    // display list of subjects and have user select one
    DisplaySubjects();
    if (!m_subjects.empty()) {
        cout << "\nWhat subject would you like to attempt?\n";
        while (!(cin >> userChoice) || userChoice < 1 || userChoice > int(m_subjects.size())) {
            cout << "-Invalid Selection-\n";
            cin.ignore(10000, '\n');
            cin.clear();
        }
        userChoice--;
        QuestionsPerSubject(m_subjects.at(userChoice));
    }
    return userChoice;
}


// Name: QuestionsPerSubject
// Desc: Iterates over m_questions and counts how many questions match the subject
template <class T>
int Trivia<T>::QuestionsPerSubject(string aSubject) {
    string subject; // subject of questions in m_questions
    int matchingS = 0;  // number of questions in m_questions with the passed subject

    // search m_questions for subjects matching passed subject
    for (int i = 0; i < m_questions->GetSize(); i++) {
        subject = m_questions->At(i)->m_subject;
        if (subject == aSubject) {
            matchingS++;
        }
    }
    return matchingS;
}


// Name: DisplayTitle
// Desc: Displays opening Welcome message
template <class T>
void Trivia<T>::DisplayTitle() {
    cout << "***Welcome to UMBC Trivia***";
}


#endif
