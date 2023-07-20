// UMBC - CMSC 341 - Fall 2022 - Proj0
// Eric Ekey
// eekey1@gl.umbc.edu

#include "art.h"

class Tester{
public:
    // the following is implemented as an example of measurement
    void measureInsertionTime(int numTrials, int inputSize);
    // the following tests the normal case of create() function
    bool testCreateNormal(Art & art);

    /******************************************
    * Test function declarations go here! *
    ******************************************/
    int gridSize(Art &aArt);

    bool testDefaultConstructor(Art &aArt);

    bool testOverConstructor(Art &aArt);

    bool testOverConstructor2(Art &aArt);

    bool testOverConstructor3(Art &aArt);

    bool testCopyConstructor(Art &aArt, Art &aArt2);

    bool testCopyConstructor2(Art &aArt, Art &aArt2);

    bool testAssignment(Art &aArt, Art &aArt2);

    bool testAssignment2(Art &aArt, Art &aArt2);

    bool testRight(Art &aArt, Art &aArt2);

    bool testRight2(Art &aArt, Art &aArt2);

    bool testRight3(Art &aArt, Art &aArt2, Art &aArt3);

    bool testBottom(Art &aArt, Art &aArt2);

    bool testBottom2(Art &aArt, Art &aArt2);

    bool testBottom3(Art &aArt, Art &aArt2, Art &aArt3);

    bool testClear(Art &aArt);

    bool testCreate(Art &aArt);

};

int main(){
    Tester tester;// test object

    cout << "\nTesting constructors\n";

    // default constructor
    {
        Art theArt;
        if (tester.testDefaultConstructor(theArt)) {
            cout << "\tDefault constructor PASS\n";
        } else {
            cout << "\tDefault constructor FAIL\n";
        }
    }

    // overloaded constructor error cases
    {
        Art theArt1(-2,3);
        if (tester.testOverConstructor(theArt1)) {
            cout << "\tOverloaded constructor error case 1 PASS\n";
        } else {
            cout << "\tOverloaded constructor error case 1 FAIL\n";
        }
        Art theArt2(-2,-2);
        if (tester.testOverConstructor(theArt2)) {
            cout << "\tOverloaded constructor error case 2 PASS\n";
        } else {
            cout << "\tOverloaded constructor error case 2 FAIL\n";
        }
        Art theArt3(0,0);
        if (tester.testOverConstructor(theArt3)) {
            cout << "\tOverloaded constructor error case 3 PASS\n";
        } else {
            cout << "\tOverloaded constructor error case 3 FAIL\n";
        }
        Art theArt4(0,3);
        if (tester.testOverConstructor(theArt4)) {
            cout << "\tOverloaded constructor error case 4 PASS\n";
        } else {
            cout << "\tOverloaded constructor error case 4 FAIL\n";
        }
        Art theArt5(-2,0);
        if (tester.testOverConstructor(theArt5)) {
            cout << "\tOverloaded constructor error case 5 PASS\n";
        } else {
            cout << "\tOverloaded constructor error case 5 FAIL\n";
        }
    }

    // overloaded constructor edge case
    {
        Art theArt(1,1);
        if (tester.testOverConstructor2(theArt)) {
            cout << "\tOverloaded constructor edge case PASS\n";
        } else {
            cout << "\tOverloaded constructor edge case FAIL\n";
        }
    }

    // overloaded constructor normal case
    {
        Art theArt(2,3);
        if (tester.testOverConstructor3(theArt)) {
            cout << "\tOverloaded constructor normal case PASS\n";
        } else {
            cout << "\tOverloaded constructor normal case FAIL\n";
        }
    }

    // copy constructor edge cases
    {
        Art theArt(1,1);
        theArt.create(6);
        Art theArt2(theArt);

        if (tester.testCopyConstructor(theArt, theArt2)) {
            cout << "\tCopy Constructor edge case 1 PASS\n";
        } else {
            cout << "\tCopy constructor edge case 1 FAIL\n";
        }

        Art theArt3;
        theArt3.create(6);
        Art theArt4(theArt3);
        if (tester.testCopyConstructor(theArt3, theArt4)) {
            cout << "\tCopy Constructor edge case 2 PASS\n";
        } else {
            cout << "\tCopy constructor edge case 2 FAIL\n";
        }
    }

    // copy constructor normal case
    {
        Art theArt(2,3);
        theArt.create(6);
        Art theArt2(theArt);

        if (tester.testCopyConstructor2(theArt, theArt2)) {
            cout << "\tCopy constructor normal case PASS\n";
        } else {
            cout << "\tCopy constructor normal case FAIL\n";
        }
    }

    cout << "\nTesting assignment operator\n";

    // assignment operator edge cases
    {
        Art theArt, theArt2;
        theArt.create(6);
        theArt2 = theArt;
        if (tester.testAssignment(theArt, theArt2)) {
            cout << "\tAssignment operator edge case 1 PASS\n";
        } else {
            cout << "\tAssignment operator edge case 1 FAIL\n";
        }

        theArt2 = theArt2;
        if (tester.testAssignment(theArt2, theArt2)) {
            cout << "\tAssignment operator edge case 2 PASS\n";
        } else {
            cout << "\tAssignment operator edge case 2 FAIL\n";
        }

        Art theArt3(2,2), theArt4(1,1);
        theArt4.create(6);
        theArt3 = theArt4;
        if (tester.testAssignment(theArt4, theArt3)) {
            cout << "\tAssignment operator edge case 3 PASS\n";
        } else {
            cout << "\tAssignment operator edge case 3 FAIL\n";
        }

        Art theArt5(2,2), theArt6(1,1);
        theArt5.create(6);
        theArt6 = theArt5;
        if (tester.testAssignment(theArt5, theArt6)) {
            cout << "\tAssignment operator edge case 4 PASS\n";
        } else {
            cout << "\tAssignment operator edge case 4 FAIL\n";
        }

        Art theArt7, theArt8(2,2);
        theArt8.create(6);
        theArt7 = theArt8;
        if (tester.testAssignment(theArt8, theArt7)) {
            cout << "\tAssignment operator edge case 5 PASS\n";
        } else {
            cout << "\tAssignment operator edge case 5 FAIL\n";
        }

        Art theArt9, theArt10(2,2);
        theArt9.create(6);
        theArt10 = theArt9;
        if (tester.testAssignment(theArt9, theArt10)) {
            cout << "\tAssignment operator edge case 6 PASS\n";
        } else {
            cout << "\tAssignment operator edge case 6 FAIL\n";
        }

        Art theArt11, theArt12(1,1);
        theArt12.create(6);
        theArt11 = theArt12;
        if (tester.testAssignment(theArt12, theArt11)) {
            cout << "\tAssignment operator edge case 7 PASS\n";
        } else {
            cout << "\tAssignment operator edge case 7 FAIL\n";
        }

        Art theArt13, theArt14(1,1);
        theArt13.create(6);
        theArt14 = theArt13;
        if (tester.testAssignment(theArt13, theArt14)) {
            cout << "\tAssignment operator edge case 8 PASS\n";
        } else {
            cout << "\tAssignment operator edge case 8 FAIL\n";
        }

        Art theArt15(2,2);
        theArt15.create(6);
        theArt15 = theArt15;
        if (tester.testAssignment(theArt15, theArt15)) {
            cout << "\tAssignment operator edge case 9 FAIL\n";
        } else {
            cout << "\tAssignment operator edge case 9 PASS\n";
        }

        Art theArt16(1,1);
        theArt16.create(6);
        theArt16 = theArt16;
        if (tester.testAssignment(theArt16, theArt16)) {
            cout << "\tAssignment operator edge case 10 FAIL\n";
        } else {
            cout << "\tAssignment operator edge case 10 PASS\n";
        }
    }

    // assignment operator normal case
    {
        Art theArt(2,2), theArt2(3,3);
        theArt.create(6);
        theArt2 = theArt;
        if (tester.testAssignment2(theArt, theArt2)) {
            cout << "\tAssignment operator normal case PASS\n";
        } else {
            cout << "\tAssignment operator normal case FAIL\n";
        }
    }

    cout << "\nTesting create\n";

    // create error case
    {
        Art theArt;
        theArt.create(6);
        if (tester.testCreate(theArt)) {
            cout << "\tCreate error case PASS\n";
        } else {
            cout << "\tCreate error case FAIL\n";
        }
    }

    // create normal case
    {
        Art theArt(2,3);
        theArt.create(6);
        if (tester.testCreate(theArt)) {
            cout << "\tCreate normal case PASS\n";
        } else {
            cout << "\tCreate normal case FAIL\n";
        }
    }

    cout << "\nTesting append\n";

    // append right error case
    {
        Art newArt(3,3), rightArt(2,3);
        newArt.create(4);
        rightArt.create(6);
        Art saveOrg = newArt;
        newArt.appendToRight(rightArt);
        if (tester.testRight(saveOrg, newArt)) {
            cout << "\tAppend right error case PASS\n";
        } else {
            cout << "\tAppend right error case FAIL\n";
        }
    }

    // append right edge cases
    {
        Art newArt(3,3), emptyArt;
        newArt.create(5);
        Art saveArt = newArt;

        newArt.appendToRight(emptyArt);
        if (tester.testRight2(newArt, saveArt)) {
            cout << "\tAppend right edge case 1 PASS\n";
        } else {
            cout << "\tAppend right edge case 1 FAIL\n";
        }

        Art newArt2(1,1), emptyArt2;
        newArt2.create(5);
        Art saveArt2 = newArt2;

        emptyArt2.appendToRight(newArt2);
        if (tester.testRight2(newArt2, saveArt2)) {
            cout << "\tAppend right edge case 2 PASS\n";
        } else {
            cout << "\tAppend right edge case 2 FAIL\n";
        }

        Art newArt3(3,3);
        newArt3.create(5);
        Art saveArt3 = newArt3, addArt3 = newArt3;

        newArt3.appendToRight(addArt3);
        if (tester.testRight3(saveArt3, addArt3, newArt3)) {
            cout << "\tAppend right edge case 3 PASS\n";
        } else {
            cout << "\tAppend right edge case 3 FAIL\n";
        }

        Art newArt4;
        Art saveArt4 = newArt4, addArt4 = newArt4;

        newArt4.appendToRight(addArt4);
        if (tester.testRight3(saveArt4, addArt4, newArt4)) {
            cout << "\tAppend right edge case 4 PASS\n";
        } else {
            cout << "\tAppend right edge case 4 FAIL\n";
        }
    }

    // append right normal case
    {
        Art newArt(4,4), addArt(4, 6);
        newArt.create(5);
        addArt.create(6);
        Art saveArt = newArt;
        newArt.appendToRight(addArt);

        if (tester.testRight3(saveArt, addArt, newArt)) {
            cout << "\tAppend right normal case PASS\n";
        } else {
            cout << "\tAppend right normal case FAIL\n";
        }
    }

    // append down error case
    {
        Art newArt(3,3), rightArt(3,2);
        newArt.create(4);
        rightArt.create(6);
        Art saveOrg = newArt;
        newArt.appendToBottom(rightArt);
        if (tester.testBottom(saveOrg, newArt)) {
            cout << "\tAppend bottom error case PASS\n";
        } else {
            cout << "\tAppend bottom error case FAIL\n";
        }
    }

    // append down edge cases
    {
        Art newArt(3,3), emptyArt;
        newArt.create(5);
        Art saveArt = newArt;

        newArt.appendToBottom(emptyArt);
        if (tester.testBottom2(newArt, saveArt)) {
            cout << "\tAppend bottom edge case 1 PASS\n";
        } else {
            cout << "\tAppend bottom edge case 1 FAIL\n";
        }

        Art newArt2(1,1), emptyArt2;
        newArt2.create(5);
        Art saveArt2 = newArt2;

        emptyArt2.appendToBottom(newArt2);
        if (tester.testBottom2(newArt2, saveArt2)) {
            cout << "\tAppend bottom edge case 2 PASS\n";
        } else {
            cout << "\tAppend bottom edge case 2 FAIL\n";
        }

        Art newArt3(3,3);
        newArt3.create(5);
        Art saveArt3 = newArt3, addArt3 = newArt3;

        newArt3.appendToBottom(addArt3);
        if (tester.testBottom3(saveArt3, addArt3, newArt3)) {
            cout << "\tAppend bottom edge case 3 PASS\n";
        } else {
            cout << "\tAppend bottom edge case 3 FAIL\n";
        }

        Art newArt4;
        Art saveArt4 = newArt4, addArt4 = newArt4;

        newArt4.appendToBottom(addArt4);
        if (tester.testBottom3(saveArt4, addArt4, newArt4)) {
            cout << "\tAppend bottom edge case 4 PASS\n";
        } else {
            cout << "\tAppend bottom edge case 4 FAIL\n";
        }
    }

    // append down normal case
    {
        Art newArt(4,4), addArt(6, 4);
        newArt.create(5);
        addArt.create(6);
        Art saveArt = newArt;
        newArt.appendToBottom(addArt);

        if (tester.testBottom3(saveArt, addArt, newArt)) {
            cout << "\tAppend bottom normal case PASS\n";
        } else {
            cout << "\tAppend bottom normal case FAIL\n";
        }
    }

    cout << "\nTesting clear\n";

    // clear edge case
    {
        Art theArt;
        theArt.clear();
        if (tester.testClear(theArt)) {
            cout << "\tClear edge case PASS\n";
        } else {
            cout << "\tClear edge case FAIL\n";
        }
    }

    // clear normal case
    {
        Art theArt(2,3);
        theArt.clear();
        if (tester.testClear(theArt)) {
            cout << "\tClear normal case PASS\n";
        } else {
            cout << "\tClear normal case FAIL\n";
        }
    }

    cout << endl;

    return 0;
}

int Tester::gridSize(Art &aArt) {
    return (aArt.m_numColumns * aArt.m_numRows);
}

bool Tester::testCreateNormal(Art & art){
    // this function assumes the art object is not empty
    // all color codes must be within the correct range
    bool result = true;
    art.create(10);
    if (art.m_numRows > 0 && art.m_numColumns > 0 && art.m_masterPiece != nullptr){
        for (int i=0; i < art.m_numRows; i++){
            for (int j=0; j < art.m_numColumns; j++){
                if(art.m_masterPiece[i][j] < 30 ||
                   art.m_masterPiece[i][j] > 37)
                    result = false;
            }
        }
    }
    else{
        result = false;
        cout << "\tA proper object is not passed to testCreateNormal()\n";
    }
    return result;
}

void Tester::measureInsertionTime(int numTrials, int inputSize)
{
    //Measuring the efficiency of insertion algorithm with system clock ticks
    //Clock ticks are units of time of a constant but system-specific length, as those returned by function clock().
    //Dividing a count of clock ticks by CLOCKS_PER_SEC yields the number of seconds.
    const int a = 2;//scaling factor for input size
    double T = 0.0;//to store running times
    clock_t start, stop;//stores the clock ticks while running the program
    for (int k=0;k<numTrials;k++)
    {
        Art testObject(inputSize,inputSize);
        start = clock();
        testObject.create(10);//the algorithm to be analyzed for efficiency
        stop = clock();
        T = stop - start;//number of clock ticks the algorithm took
        cout << "\tInserting " << inputSize * inputSize << " members took " << T << " clock ticks ("<< T/CLOCKS_PER_SEC << " seconds)!" << endl;
        inputSize = inputSize * a;//increase the input size by the scaling factor
    }
}

bool Tester::testDefaultConstructor(Art &aArt) {
    if (!aArt.m_numRows && !aArt.m_numColumns && aArt.m_masterPiece == nullptr) {
        return true;
    }
    return false;
}

bool Tester::testOverConstructor(Art &aArt) {
    if (!aArt.m_numRows && !aArt.m_numColumns && aArt.m_masterPiece == nullptr) {
        return true;
    }
    return false;
}

bool Tester::testOverConstructor2(Art &aArt) {
    if (gridSize(aArt) == 1 && aArt.m_masterPiece != nullptr) {
        return true;
    } else {
        return false;
    }
}

bool Tester::testOverConstructor3(Art &aArt) {
    // loop the grid, count the squares
    int count = 0;
    for (int i = 0; i < aArt.m_numRows; i++) {
        for (int j = 0; j < aArt.m_numColumns; j++) {
            count++;
        }
    }

    // compare with size
    if (count == gridSize(aArt)) {
        return true;
    } else {
        return false;
    }
}

bool Tester::testCopyConstructor(Art &aArt, Art &aArt2) {
    if (aArt.m_masterPiece == aArt2.m_masterPiece) {
        if (aArt.m_masterPiece != nullptr) {
            return false;
        }
    }

    if (gridSize(aArt) == gridSize(aArt2)) {
        if (!gridSize(aArt) && !gridSize(aArt2)) {
            if (aArt.m_masterPiece == nullptr) {
                return true;
            }
        }
        if (aArt.m_masterPiece[0][0] == aArt2.m_masterPiece[0][0] && aArt2.m_masterPiece != nullptr) {
            return true;
        }
    }
    return false;
}

bool Tester::testCopyConstructor2(Art &aArt, Art &aArt2) {
    if (aArt.m_masterPiece == aArt2.m_masterPiece) {
        return false;
    }

    int count = 0;
    int count2 = 0;

    for (int i = 0; i < aArt.m_numRows; i++) {
        for (int j = 0; j < aArt.m_numColumns; j++) {
            if (aArt.m_masterPiece[i][j] != aArt2.m_masterPiece[i][j]) {
                return false;
            }
            count++;
        }
    }

    for (int i = 0; i < aArt2.m_numRows; i++) {
        for (int j = 0; j < aArt2.m_numColumns; j++) {
            if (aArt2.m_masterPiece[i][j] != aArt.m_masterPiece[i][j]) {
                return false;
            }
            count2++;
        }
    }

    if (gridSize(aArt2) != count2) {
        return false;
    }

    if (count != count2) {
        return false;
    }

    return true;
}

bool Tester::testAssignment(Art &aArt, Art &aArt2) {
    if (aArt.m_masterPiece == aArt2.m_masterPiece) {
        if (aArt.m_masterPiece != nullptr) {
            return false;
        }
    }

    if (gridSize(aArt) == gridSize(aArt2)) {
        if (!gridSize(aArt) && aArt2.m_masterPiece == nullptr) {
            return true;
        } else if (aArt.m_masterPiece[0][0] == aArt2.m_masterPiece[0][0] && aArt2.m_masterPiece != nullptr) {
            return true;
        }
    }
    return false;
}

bool Tester::testAssignment2(Art &aArt, Art &aArt2) {
    if (aArt.m_masterPiece == aArt2.m_masterPiece) {
        return false;
    }

    int count = 0;
    int count2 = 0;

    for (int i = 0; i < aArt.m_numRows; i++) {
        for (int j = 0; j < aArt.m_numColumns; j++) {
            if (aArt.m_masterPiece[i][j] != aArt2.m_masterPiece[i][j]) {
                return false;
            }
            count++;
        }
    }

    for (int i = 0; i < aArt2.m_numRows; i++) {
        for (int j = 0; j < aArt2.m_numColumns; j++) {
            if (aArt2.m_masterPiece[i][j] != aArt.m_masterPiece[i][j]) {
                return false;
            }
            count2++;
        }
    }

    if (gridSize(aArt2) != count2) {
        return false;
    }

    if (count != count2) {
        return false;
    }

    return true;
}

bool Tester::testRight(Art &aArt, Art &aArt2) {
    int count = 0;
    int count2 = 0;

    for (int i = 0; i < aArt.m_numRows; i++) {
        for (int j = 0; j < aArt.m_numColumns; j++) {
            if (aArt.m_masterPiece[i][j] != aArt2.m_masterPiece[i][j]) {
                return false;
            }
            count++;
        }
    }

    for (int i = 0; i < aArt2.m_numRows; i++) {
        for (int j = 0; j < aArt2.m_numColumns; j++) {
            if (aArt2.m_masterPiece[i][j] != aArt.m_masterPiece[i][j]) {
                return false;
            }
            count2++;
        }
    }

    if (gridSize(aArt2) != count2) {
        return false;
    }

    if (count != count2) {
        return false;
    }

    return true;
}

bool Tester::testRight2(Art &aArt, Art &aArt2) {
    int count = 0;
    int count2 = 0;

    for (int i = 0; i < aArt.m_numRows; i++) {
        for (int j = 0; j < aArt.m_numColumns; j++) {
            if (aArt.m_masterPiece[i][j] != aArt2.m_masterPiece[i][j]) {
                return false;
            }
            count++;
        }
    }

    for (int i = 0; i < aArt2.m_numRows; i++) {
        for (int j = 0; j < aArt2.m_numColumns; j++) {
            if (aArt2.m_masterPiece[i][j] != aArt.m_masterPiece[i][j]) {
                return false;
            }
            count2++;
        }
    }

    if (gridSize(aArt2) != count2) {
        return false;
    }

    if (count != count2) {
        return false;
    }

    return true;
}

bool Tester::testRight3(Art &aArt, Art &aArt2, Art &aArt3) {
    int newCol = aArt.m_numColumns + aArt2.m_numColumns;

    if (newCol != aArt3.m_numColumns) {
        return false;
    }

    for (int i = 0; i < aArt.m_numRows; i++) {
        for (int j = 0; j < aArt.m_numColumns; j++) {
            if (aArt3.m_masterPiece[i][j] != aArt.m_masterPiece[i][j]) {
                return false;
            }
        }
    }

    for (int i = 0; i < aArt.m_numRows; i++) {
        for (int j = aArt.m_numColumns, k = 0; j < (aArt.m_numColumns + aArt2.m_numColumns); j++,k++) {
            if (aArt2.m_masterPiece[i][k] != aArt3.m_masterPiece[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool Tester::testBottom(Art &aArt, Art &aArt2) {
    int count = 0;
    int count2 = 0;

    for (int i = 0; i < aArt.m_numRows; i++) {
        for (int j = 0; j < aArt.m_numColumns; j++) {
            if (aArt.m_masterPiece[i][j] != aArt2.m_masterPiece[i][j]) {
                return false;
            }
            count++;
        }
    }

    for (int i = 0; i < aArt2.m_numRows; i++) {
        for (int j = 0; j < aArt2.m_numColumns; j++) {
            if (aArt2.m_masterPiece[i][j] != aArt.m_masterPiece[i][j]) {
                return false;
            }
            count2++;
        }
    }

    if (gridSize(aArt2) != count2) {
        return false;
    }

    if (count != count2) {
        return false;
    }

    return true;
}

bool Tester::testBottom2(Art &aArt, Art &aArt2) {
    int count = 0;
    int count2 = 0;

    for (int i = 0; i < aArt.m_numRows; i++) {
        for (int j = 0; j < aArt.m_numColumns; j++) {
            if (aArt.m_masterPiece[i][j] != aArt2.m_masterPiece[i][j]) {
                return false;
            }
            count++;
        }
    }

    for (int i = 0; i < aArt2.m_numRows; i++) {
        for (int j = 0; j < aArt2.m_numColumns; j++) {
            if (aArt2.m_masterPiece[i][j] != aArt.m_masterPiece[i][j]) {
                return false;
            }
            count2++;
        }
    }

    if (gridSize(aArt2) != count2) {
        return false;
    }

    if (count != count2) {
        return false;
    }

    return true;
}

bool Tester::testBottom3(Art &aArt, Art &aArt2, Art &aArt3) {
    int newRow = aArt.m_numRows + aArt2.m_numRows;

    if (newRow != aArt3.m_numRows) {
        return false;
    }

    for (int i = 0; i < aArt.m_numRows; i++) {
        for (int j = 0; j < aArt.m_numColumns; j++) {
            if (aArt3.m_masterPiece[i][j] != aArt.m_masterPiece[i][j]) {
                return false;
            }
        }
    }

    for (int i = aArt.m_numRows, k = 0; i < newRow; i++, k++) {
        for (int j = 0; j < aArt.m_numColumns; j++) {
            if (aArt2.m_masterPiece[k][j] != aArt3.m_masterPiece[i][j]) {
                return false;
            }
        }
    }
    return true;



}

bool Tester::testClear(Art &aArt) {
    if (aArt.m_numColumns || aArt.m_numRows || aArt.m_masterPiece != nullptr) {
        return false;
    } else {
        return true;
    }
}

bool Tester::testCreate(Art &aArt) {
    if (!gridSize(aArt)) {
        if (aArt.m_masterPiece == nullptr) {
            return true;
        } else {
            return false;
        }
    } else {
        for (int i = 0; i < aArt.m_numRows; i++) {
            for (int j = 0; j < aArt.m_numColumns; j++) {
                if (aArt.m_masterPiece[i][j] < 30 || aArt.m_masterPiece[i][j] > 37) {
                    return false;
                }
            }
        }
        return true;
    }
}
