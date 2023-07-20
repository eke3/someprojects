/*****************************************************************************
 ** File: Question.cpp
 ** Project: CMSC 202 Project 5, Spring 2022
 ** Author:  Eric Ekey, Kush Shah and CMSC202
 ** Section: 52
 ** Date:    05/01/2022
 ** Email:   eekey1@gl.umbc.edu
 **
 Description: CPP file for Question class. Includes both class definition and
 class function definitions.
*****************************************************************************/

#ifndef QUESTION_CPP
#define QUESTION_CPP
#include <iostream>
#include <string>
using namespace std;

// Global constants for number of types
const int NUM_TYPES = 6;
const string KNOWN_TYPES[NUM_TYPES] = { "int", "double", "bool", "char", "string"};

template <class T>
struct Question {
public:
  // Name: Overloaded Constructor
  // Desc: Constructs a question object given all fields.
  // Precondition: Question must be templated by the data type passed in as an argument.
  // Postcondition: A new Question object is created for use.
  Question(string subject, string question, string datatype, int difficulty, T answer);
  // Name: Copy Constructor
  // Desc: Makes a copy of an existing Question object
  // Precondition: A Question object exists.
  // Postcondtion: A new populated Question exists
  Question(const Question&);
  // Name: Destructor
  // Desc: Resets variables and deallocates dynamically allocated memory
  // Precondition: A Question object exists.
  // Postcondtion: All dynamically allocated memory is destroyed.
  ~Question();
  // Name: CheckAnswer
  // Desc: Compares passed value with m_answer
  // Precondition: A Question object exists.
  // Postcondtion: Returns true if value passed matches m_answer else false.
  bool CheckAnswer(T submission);
  // Name: Overloaded insertion operator
  // Desc: Returns ostream object for the question prompt. Presents
  // question and answer data type.
  // Precondition: Question object exists
  // Postcondition: Returns ostream of question prompt.
  template<class Y> //As friend function, has to use different templated variable
  friend ostream& operator<< (ostream& output, Question<Y>&);

  //Member variables (all public)
  string m_subject; //Subject for question
  string m_question; // Question
  string m_datatype; // What type of data used for answer
  int m_difficulty; // Difficulty Rating (1 - 5)
  T m_answer; // Answer to question
  bool m_isAnswered; // True once question is answered. Otherwise, false.
};

//**********Implement Question Class Here***********


// Name: Overloaded Constructor
// Desc: Constructs a question object given all fields.
template <class T>
Question<T>::Question(string subject, string question, string datatype, int difficulty, T answer) {
    m_subject = subject;
    m_question = question;
    m_datatype = datatype;
    m_difficulty = difficulty;
    m_answer = answer;
    m_isAnswered = false;
}


// Name: Copy Constructor
// Desc: Makes a copy of an existing Question object
template <class T>
Question<T>::Question(const Question& aQuestion) {
    // copy values from passes question to new question
    m_subject = aQuestion.m_subject;
    m_question = aQuestion.m_question;
    m_datatype = aQuestion.m_datatype;
    m_difficulty = aQuestion.m_difficulty;
    m_answer = aQuestion.m_answer;
    m_isAnswered = aQuestion.m_isAnswered;

}


// Name: Destructor
// Desc: Resets variables and deallocates dynamically allocated memory
template <class T>
Question<T>::~Question() {
    // no dynamically allocated memory
}


// Name: CheckAnswer
// Desc: Compares passed value with m_answer
template <class T>
bool Question<T>::CheckAnswer(T aSubmission) {
    bool rightAnswer = false;   // whether the submission matches the correct answer

    // compare submission and right answer
    if (aSubmission == m_answer) {
        rightAnswer = true;
    }
    m_isAnswered = true;
    return rightAnswer;
}


// Name: Overloaded insertion operator
// Desc: Returns ostream object for the question prompt
template<class Y>
ostream& operator<< (ostream& aOutput, Question<Y>& aQuestion) {
    string message; // message to return

    // construct message and insert into ostream
    message = ("Question: " + aQuestion.m_question
            + "\nPlease answer with a(n) " + aQuestion.m_datatype + "\n");
    aOutput << message;
    return aOutput;
}


#endif
