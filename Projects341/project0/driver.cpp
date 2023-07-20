// UMBC - CMSC 341 - Fall 2022 - Proj0
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

};

int main(){
    
    Tester tester;// test object
    
    {
        // the following is a sample usage of the Art class
        // we create two objects and append them
        cout << "\nSample usage of the Art class:\n\n";
        Art art1(5,10);
        art1.create(10);
        cout << endl << "Dump of a 5x10 object:\n\n";
        art1.dumpColors("\u2588");// prints a box
        Art art2(5,15);
        art2.create(5);
        cout << endl << "Dump of a 5x15 object:\n\n";
        art2.dumpColors("\u2588");
        art1.appendToRight(art2);
        cout << endl << "Dump of the append result (5x25):\n\n";
        art1.dumpColors("\u2588");
        cout << endl << "Dump of the append result (5x25) values:\n\n";
        art1.dumpValues();
    }
    
    {
        // testing create function for normal case
        Art art(10,10);
        cout << "\nTesting the normal case of create function:\n\n";
        if (tester.testCreateNormal(art) == true)
            cout << "\tNormal case of create passed!\n";
        else
            cout << "\tNormal case of create failed!\n";
    }

    {
        // measuring the running time of insertion
        cout << "\nMeasuring the performance of insertion function:\n\n";
        // measuring the insertion of 100x100 colors, and 200x200 colors
        tester.measureInsertionTime(2,100);
    }

    cout << endl;

    return 0;
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
