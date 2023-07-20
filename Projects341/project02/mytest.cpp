// UMBC - CMSC 341 - Fall 2022 - Proj2
// Eric Ekey
// eekey1@gl.umbc.edu
#include "streak.h"
#include <vector>
#include <random>
enum RANDOM {UNIFORMINT, UNIFORMREAL, NORMAL};
enum EDGEERROR {BASE = 0, EDGE = 1, ERROR = 2};
class Random {
public:
    Random(int min, int max, RANDOM type=UNIFORMINT, int mean=50, int stdev=20) : m_min(min), m_max(max), m_type(type)
    {
        if (type == NORMAL){
            //the case of NORMAL to generate integer numbers with normal distribution
            m_generator = std::mt19937(m_device());
            //the data set will have the mean of 50 (default) and standard deviation of 20 (default)
            //the mean and standard deviation can change by passing new values to constructor 
            m_normdist = std::normal_distribution<>(mean,stdev);
        }
        else if (type == UNIFORMINT) {
            //the case of UNIFORMINT to generate integer numbers
            // Using a fixed seed value generates always the same sequence
            // of pseudorandom numbers, e.g. reproducing scientific experiments
            // here it helps us with testing since the same sequence repeats
            m_generator = std::mt19937(10);// 10 is the fixed seed value
            m_unidist = std::uniform_int_distribution<>(min,max);
        }
        else{ //the case of UNIFORMREAL to generate real numbers
            m_generator = std::mt19937(10);// 10 is the fixed seed value
            m_uniReal = std::uniform_real_distribution<double>((double)min,(double)max);
        }
    }
    void setSeed(int seedNum){
        // we have set a default value for seed in constructor
        // we can change the seed by calling this function after constructor call
        // this gives us more randomness
        m_generator = std::mt19937(seedNum);
    }

    int getRandNum(){
        // this function returns integer numbers
        // the object must have been initialized to generate integers
        int result = 0;
        if(m_type == NORMAL){
            //returns a random number in a set with normal distribution
            //we limit random numbers by the min and max values
            result = m_min - 1;
            while(result < m_min || result > m_max)
                result = m_normdist(m_generator);
        }
        else if (m_type == UNIFORMINT){
            //this will generate a random number between min and max values
            result = m_unidist(m_generator);
        }
        return result;
    }

    double getRealRandNum(){
        // this function returns real numbers
        // the object must have been initialized to generate real numbers
        double result = m_uniReal(m_generator);
        // a trick to return numbers only with two deciaml points
        // for example if result is 15.0378, function returns 15.03
        // to round up we can use ceil function instead of floor
        result = std::floor(result*100.0)/100.0;
        return result;
    }
    
    private:
    int m_min;
    int m_max;
    RANDOM m_type;
    std::random_device m_device;
    std::mt19937 m_generator;
    std::normal_distribution<> m_normdist;//normal distribution
    std::uniform_int_distribution<> m_unidist;//integer uniform distribution
    std::uniform_real_distribution<double> m_uniReal;//real uniform distribution

};

class Tester{
    public:
        bool testInsertRuntime(Streak aStreak);
        bool testRemoveRuntime(Streak aStreak);
        bool testRemove(Streak aStreak, int aEdgeError = BASE);
        bool testInsert(Streak aStreak, int aEdgeError = BASE);
        bool testClear(Streak aStreak, int aEdgeError = BASE);
        bool testRemoveDead(Streak aStreak, int aEdgeError = BASE);
        bool testSetState(Streak aStreak, int aEdgeError = BASE);
        bool testCountCubs(Streak aStreak, int aEdgeError = BASE);
        bool testFindTiger(Streak aStreak, int aEdgeError = BASE);
        bool testRebalance(Streak aStreak);
        bool testBSTProperty(Streak aStreak, int aEdgeError = BASE);
        bool testBalanceProperty(Streak aStreak, int aEdgeError = BASE);
};

int main() {
    Tester tester;

    // insert()
    cout << "Testing insert()\n";
    {
        Streak theStreak, theStreak2, theStreak3, theStreak4;
        bool base = tester.testInsert(theStreak),
        edge = tester.testInsert(theStreak2, EDGE),
        error = tester.testInsert(theStreak3, ERROR),
        runtime = tester.testInsertRuntime(theStreak4);

        if (base) {
            cout << "insert() base case PASS\n";
        } else {
            cout << "insert() base case FAIL\n";
        }

        if (edge) {
            cout << "insert() edge case PASS\n";
        } else {
            cout << "insert() edge case FAIL\n";
        }

        if (error) {
            cout << "insert() error case PASS\n";
        } else {
            cout << "insert() error case FAIL\n";
        }

        if (runtime) {
            cout << "insert() runtime test PASS\n";
        } else {
            cout << "insert() runtime test FAIL\n";
        }
    }
    

    // clear()
    cout << "\nTesting clear()\n";
    {
        Streak theStreak, theStreak2, theStreak3;
        bool base = tester.testClear(theStreak),
        edge = tester.testClear(theStreak2, EDGE),
        error = tester.testClear(theStreak3, ERROR);

        if (base) {
            cout << "testClear() base case PASS\n";
        } else {
            cout << "testClear() base case FAIL\n";
        }

        if (edge) {
            cout << "testClear() edge case PASS\n";
        } else {
            cout << "testClear() edge case FAIL\n";
        }

        if (error) {
            cout << "testClear() error case PASS\n";
        } else {
            cout << "testClear() error case FAIL\n";
        }
    }


    // remove()
    cout << "\nTesting remove()\n";
    {
        Streak theStreak, theStreak2, theStreak3, theStreak4;
        bool base = tester.testRemove(theStreak),
        edge = tester.testRemove(theStreak2, EDGE),
        error = tester.testRemove(theStreak3, ERROR),
        runtime = tester.testRemoveRuntime(theStreak4);

        if (base) {
            cout << "remove() base case PASS\n";
        } else {
            cout << "remove() base case FAIL\n";
        }

        if (edge) {
            cout << "remove() edge case PASS\n";
        } else {
            cout << "remove() edge case FAIL\n";
        }

        if (error) {
            cout << "remove() error case PASS\n";
        } else {
            cout << "remove() error case FAIL\n";
        }

        if (runtime) {
            cout << "remove() runtime test PASS\n";
        } else {
            cout << "remove() runtime test FAIL\n";
        }
    }


    // setState()
    cout << "\nTesting setState()\n";
    {
        Streak theStreak, theStreak2, theStreak3;
        bool base = tester.testSetState(theStreak),
        edge = tester.testSetState(theStreak2, EDGE),
        error = tester.testSetState(theStreak3, ERROR);

        if (base) {
            cout << "testSetState() base case PASS\n";
        } else {
            cout << "testSetState() base case FAIL\n";
        }

        if (edge) {
            cout << "testSetState() edge case PASS\n";
        } else {
            cout << "testSetState() edge case FAIL\n";
        }

        if (error) {
            cout << "testSetState() error case PASS\n";
        } else {
            cout << "testSetState() error case FAIL\n";
        }
    }


    // findTiger()
    cout << "\nTesting findTiger()\n";
    {
        Streak theStreak, theStreak2, theStreak3;
        bool base = tester.testFindTiger(theStreak),
        edge = tester.testFindTiger(theStreak2, EDGE),
        error = tester.testFindTiger(theStreak3, ERROR);

        if (base) {
            cout << "findTiger() base case PASS\n";
        } else {
            cout << "findTiger() base case FAIL\n";
        }

        if (edge) {
            cout << "findTiger() edge case PASS\n";
        } else {
            cout << "findTiger() edge case FAIL\n";
        }

        if (error) {
            cout << "findTiger() error case PASS\n";
        } else {
            cout << "findTiger() error case FAIL\n";
        }
    }


    // countTigerCubs()
    cout << "\nTesting countTigerCubs()\n";
    {
        Streak theStreak, theStreak2, theStreak3;
        bool base = tester.testCountCubs(theStreak),
        edge = tester.testCountCubs(theStreak2, EDGE),
        error = tester.testCountCubs(theStreak3, ERROR);

        if (base) {
            cout << "countTigerCubs() base case PASS\n";
        } else {
            cout << "countTigerCubs() base case FAIL\n";
        }

        if (edge) {
            cout << "countTigerCubs() edge case PASS\n";
        } else {
            cout << "countTigerCubs() edge case FAIL\n";
        }

        if (error) {
            cout << "countTigerCubs() error case PASS\n";
        } else {
            cout << "countTigerCubs() error case FAIL\n";
        }
    }


    // rebalance()
    cout << "\nTesting rebalance()\n";
    {
        Streak theStreak;
        bool base = tester.testRebalance(theStreak);

        if (base) {
            cout << "rebalance() PASS\n";
        } else {
            cout << "rebalance() FAIL\n";
        }
    }


    // BST property
    cout << "\nTesting preservation of BST property\n";
    {
        Streak theStreak;
        bool base = tester.testBSTProperty(theStreak);

        if (base) {
            cout << "BST property preservation PASS\n";
        } else {
            cout << "BST property preservation FAIL\n";
        }
    }
    

    // Balance property
    cout << "\nTesting preservation of balance property\n";
    {
        Streak theStreak;
        bool base = tester.testBalanceProperty(theStreak);

        if (base) {
            cout << "Balance property preservation PASS\n";
        } else {
            cout << "Balance property preservation FAIL\n";
        }
    }


    // removeDead()
    cout << "\nTesting removeDead()\n";
    {
        Streak theStreak, theStreak2, theStreak3;
        bool base = tester.testRemoveDead(theStreak),
        edge = tester.testRemoveDead(theStreak2, EDGE),
        error = tester.testRemoveDead(theStreak3, ERROR);

        if (base) {
            cout << "removeDead() base case PASS\n";
        } else {
            cout << "removeDead() base case FAIL\n";
        }

        if (edge) {
            cout << "removeDead() edge case PASS\n";
        } else {
            cout << "removeDead() edge case FAIL\n";
        }

        if (error) {
            cout << "removeDead() error case PASS\n";
        } else {
            cout << "removeDead() error case FAIL\n";
        }
    }
    return 0;
}


// testInsert()
// tests Streak::insert()
bool Tester::testInsert(Streak aStreak, int aEdgeError) {
    Random idGen(MINID, MAXID);
    Random ageGen(0, 2);
    Random genderGen(0, 2);
    int ID;
    bool valid = true;

    if (aEdgeError == BASE) {
    // insert tigers and check to see if they exist in the streak
        for (int i = 0; i < 300 && valid; i++) {
            ID = idGen.getRandNum();
            Tiger theTiger(ID, static_cast<AGE>(ageGen.getRandNum()), static_cast<GENDER>(genderGen.getRandNum()));
            aStreak.insert(theTiger);

            if (!aStreak.findTiger(ID)) {
                valid = false;
            }
        }
    } else if (aEdgeError == EDGE) {
        // leaf insert
        for (int i = 0; i < 300 && valid; i++) {
            ID = idGen.getRandNum();
            Tiger theTiger(ID, static_cast<AGE>(ageGen.getRandNum()), static_cast<GENDER>(genderGen.getRandNum()));
            aStreak.insert(theTiger);

            if (!aStreak.findTiger(ID)) {
                valid = false;
            }
        }
        Tiger theTiger2(DEFAULT_ID);
        aStreak.insert(theTiger2);

        if (!aStreak.findTiger(DEFAULT_ID)) {
            valid = false;
        }
    } else if (aEdgeError == ERROR) {
        // dupe insert
        for (int i = 1; i <= 300 && valid; i++) {
            Tiger theTiger(i, CUB, static_cast<GENDER>(genderGen.getRandNum()));
            aStreak.insert(theTiger);

            if (!aStreak.findTiger(i)) {
                valid = false;
            }
        }

        int numCubs = aStreak.countTigerCubs();
        Tiger theTiger2(1, CUB);
        aStreak.insert(theTiger2);
        
        if (aStreak.countTigerCubs() != numCubs) {
            valid = false;
        }
    }

    return valid;
}


// testClear()
// tests Streak::clear()
bool Tester::testClear(Streak aStreak, int aEdgeError) {
    Random idGen(MINID, MAXID);
    Random ageGen(0, 2);
    Random genderGen(0, 2);
    int ID;
    bool valid = true;

    if (aEdgeError == BASE) {
        // random ~300 tigers
        for (int i = 0; i < 300; i++) {
            ID = idGen.getRandNum();
            Tiger theTiger(ID, static_cast<AGE>(ageGen.getRandNum()), static_cast<GENDER>(genderGen.getRandNum()));
            aStreak.insert(theTiger);
        }
        aStreak.clear();

        if (aStreak.m_root) {
            valid = false;
        }
    } else if (aEdgeError == EDGE) {
        // single tiger
        ID = idGen.getRandNum();
        Tiger theTiger(ID, static_cast<AGE>(ageGen.getRandNum()), static_cast<GENDER>(genderGen.getRandNum()));
        aStreak.insert(theTiger);

        aStreak.clear();

        if (aStreak.m_root) {
            valid = false;
        }
    } else if (aEdgeError == ERROR) {
        // empty
        aStreak.clear();

        if (aStreak.m_root) {
            valid = false;
        }
    }

    return valid;
}


// testRemove()
// tests Streak::remove()
bool Tester::testRemove(Streak aStreak, int aEdgeError) {
    Random idGen(MINID, MAXID);
    Random ageGen(0, 2);
    Random genderGen(0, 2);
    int ID = 0;
    bool valid = true;

    if (aEdgeError == BASE) {
        // remove one by one from full streak
        vector<int> ids;
        for (int i = 0; i < 300; i++) {
            Tiger theTiger(i, static_cast<AGE>(ageGen.getRandNum()), static_cast<GENDER>(genderGen.getRandNum()));
            aStreak.insert(theTiger);
            ids.push_back(i);
        }

        // remove & verify
        for (int id : ids) {
            aStreak.remove(id);
            if (aStreak.findTiger(id)) {
                valid = false;
            }
        }
    } else if (aEdgeError == EDGE) {
        // 1 tiger
        ID = idGen.getRandNum();
        Tiger theTiger(ID, static_cast<AGE>(ageGen.getRandNum()), static_cast<GENDER>(genderGen.getRandNum()));
        aStreak.insert(theTiger);
        aStreak.remove(ID);

        if (aStreak.findTiger(ID)) {
            valid = false;
        }

    } else if (aEdgeError == ERROR) {
        // empty streak
        aStreak.remove(MINID);

        if (aStreak.findTiger(MINID)) {
            valid = false;
        }

        // nonexistent tiger
        for (int i = 0; i < 300; i++) {
            Tiger theTiger(ID, CUB, static_cast<GENDER>(genderGen.getRandNum()));
            aStreak.insert(theTiger);
        }
        int numCubs = aStreak.countTigerCubs();
        aStreak.remove(1);  // doesnt exist

        if (aStreak.countTigerCubs() != numCubs) {
            valid = false;
        }
    }

    return valid;
}


// testRemoveDead()
// tests Streak::removeDead()
bool Tester::testRemoveDead(Streak aStreak, int aEdgeError) {
    Random idGen(MINID,MAXID);
    Random ageGen(0,2);
    Random genderGen(0,2);
    int ID = 0;
    bool valid = true;

    if (aEdgeError == BASE) {
        // 150 dead 150 alive
        for (int i = 0; i < 150; i++) {
            // all OLD are also ALIVE
            Tiger theTiger(i, OLD, static_cast<GENDER>(genderGen.getRandNum()), ALIVE);
            aStreak.insert(theTiger);
        }

        for (int i = 150; i < 300; i++) {
            // all CUB are also DEAD
            Tiger theTiger(i, CUB, static_cast<GENDER>(genderGen.getRandNum()), DEAD);
            aStreak.insert(theTiger);
        }  
        aStreak.removeDead();

        // CUB matches with DEAD
        if (aStreak.countTigerCubs() != 0) {
            valid = false;
        }
    } else if (aEdgeError == EDGE) {
        // 1 dead tiger
        ID = idGen.getRandNum();
        Tiger theTiger(ID, CUB, static_cast<GENDER>(genderGen.getRandNum()), DEAD);
        aStreak.insert(theTiger);
        aStreak.removeDead();

        // CUB matches with DEAD
        if (aStreak.countTigerCubs() != 0) {
            valid = false;
        }
    } else if (aEdgeError == ERROR) {
        // nothing there at all
        aStreak.removeDead();
        if (aStreak.m_root) {
            valid = false;
        }

        // no dead ones
        for (int i = 0; i < 300; i++) {
            ID = idGen.getRandNum();
            Tiger theTiger(ID, CUB, static_cast<GENDER>(genderGen.getRandNum()), ALIVE);
            aStreak.insert(theTiger);
        }
        int numCubs = aStreak.countTigerCubs();
        aStreak.removeDead();

        // CUB matches with DEAD
        if (aStreak.countTigerCubs() != numCubs) {
            valid = false;
        }
    }

    return valid;
}


// testSetState()
// tests Streak::setState()
bool Tester::testSetState(Streak aStreak, int aEdgeError) {
    Random idGen(MINID, MAXID);
    Random ageGen(0, 2);
    Random genderGen(0, 2);
    int ID;
    bool valid = true;

    if (aEdgeError == BASE) {
        // kill 1 of 300 living tigers
        vector<int> ids;
        for (int i = 0; i < 300; i++) {
            ID = idGen.getRandNum();
            Tiger theTiger(ID,CUB, static_cast<GENDER>(genderGen.getRandNum()), ALIVE);
            aStreak.insert(theTiger);
            ids.push_back(ID);
        }
        
        // kill one tiger and verify that one is now dead
        aStreak.setState(ids.at(5), DEAD);
        if (aStreak.m_numDead != 1) {
            valid = false;
        }
    } else if (aEdgeError == EDGE) {
        // kill 1 of 1 living tigers
        ID = idGen.getRandNum();
        Tiger theTiger(ID,CUB, static_cast<GENDER>(genderGen.getRandNum()), ALIVE);
        aStreak.insert(theTiger);
        aStreak.setState(ID, DEAD);
        aStreak.removeDead();

        if (aStreak.countTigerCubs()) {
            valid = false;
        }
    } else if (aEdgeError== ERROR) {
        // empty streak
        aStreak.setState(MAXID, ALIVE);
        if (aStreak.m_root) {
            valid = false;
        }
        
    }

    return valid;
}


// testFindTiger()
// tests Streak::findTiger()
bool Tester::testFindTiger(Streak aStreak, int aEdgeError) {
    Random idGen(MINID, MAXID);
    Random ageGen(0, 2);
    Random genderGen(0, 2);
    int ID;
    bool valid = true;
    vector<int> ids;

    if (aEdgeError == BASE) {
        // insert ~300 tigers
        for (int i = 0; i < 300; i++) {
            ID = idGen.getRandNum();
            Tiger theTiger(ID, static_cast<AGE>(ageGen.getRandNum()), static_cast<GENDER>(genderGen.getRandNum()));
            aStreak.insert(theTiger);
            ids.push_back(ID);
        }

        // find each of the inserted tigers
        for (int id : ids) {
            if (!aStreak.findTiger(id)) {
                valid = false;
            }
        }
    } else if (aEdgeError == EDGE) {
        // insert 1 tiger
        ID = idGen.getRandNum();
        Tiger theTiger(ID, static_cast<AGE>(ageGen.getRandNum()), static_cast<GENDER>(genderGen.getRandNum()));
        aStreak.insert(theTiger);

        // find inserted tiger
        if (!aStreak.findTiger(ID)) {
            valid = false;
        }
    } else if (aEdgeError == ERROR) {
        // empty streak
        ID = idGen.getRandNum();
        if (aStreak.findTiger(ID)) {
            valid = false;
        }
    }

    return valid;
}


// testCountCubs()
// tests Streak::countTigerCubs()
bool Tester::testCountCubs(Streak aStreak, int aEdgeError) {
    Random idGen(MINID,MAXID);
    Random ageGen(0,2);
    Random genderGen(0,2);
    bool valid = true;

    if (aEdgeError == BASE) {
        // 300 cubs
        for (int i = 0; i < 300; i++) {
            Tiger theTiger(i, CUB, static_cast<GENDER>(genderGen.getRandNum()));
            aStreak.insert(theTiger);
        }

        // verify 300 cubs
        if (aStreak.countTigerCubs() != 300) {
            valid = false;
        }
    } else if (aEdgeError == EDGE) {
        // 1 cub
        Tiger theTiger(MINID, CUB, static_cast<GENDER>(genderGen.getRandNum()));
        aStreak.insert(theTiger);

        // verify 1 cub
        if (aStreak.countTigerCubs() != 1) {
            valid = false;
        }
    } else if (aEdgeError == ERROR) {
        // empty streak
        if (aStreak.countTigerCubs()) {
            valid = false;
        }
    }

    return valid;
}


// testBSTProperty()
// tests BST property of Streak
bool Tester::testBSTProperty(Streak aStreak, int aEdgeError) {
    Random idGen(MINID,MAXID);
    Random ageGen(0,2);
    Random genderGen(0,2);
    int ID = 0;
    bool valid = true;
    vector<int> ids;

    if (aEdgeError == BASE) {
        // 300 insertions
        for (int i = 0; i < 300; i++) {
            ID = idGen.getRandNum();
            Tiger theTiger(ID, OLD, static_cast<GENDER>(genderGen.getRandNum()));
            aStreak.insert(theTiger);
            ids.push_back(ID);
        }

        // verify bst property
        if (!aStreak.testProperty(aStreak.m_root)) {
            valid = false;
        }

        // 150 deletions
        for (int i = 0; i < 150; i++) {
            aStreak.remove(ids.at(i));
        }

        // verify property again
        if (!aStreak.testProperty(aStreak.m_root)) {
            valid = false;
        }
    }

    return valid;
}


// testBalanceProperty()
// tests balance property of Streak
bool Tester::testBalanceProperty(Streak aStreak, int aEdgeError) {
    Random idGen(MINID,MAXID);
    Random ageGen(0,2);
    Random genderGen(0,2);
    int ID = 0;
    bool valid = true;
    vector<int> ids;

    if (aEdgeError == BASE) {
        // 300 insertions
        for (int i = 0; i < 300; i++) {
            ID = idGen.getRandNum();
            Tiger theTiger(ID, OLD, static_cast<GENDER>(genderGen.getRandNum()));
            aStreak.insert(theTiger);
            ids.push_back(ID);
        }

        // verify balance property
        if (!aStreak.verifyBalance(aStreak.m_root)) {
            valid = false;
        }

        // 150 deletions
        for (int i = 0; i < 150; i++) {
            aStreak.remove(ids.at(i));
        }

        // verify property again
        if (!aStreak.verifyBalance(aStreak.m_root)) {
            valid = false;
        }
    }

    return valid;
}


// testRebalance()
// tests Streak::rebalance()
bool Tester::testRebalance(Streak aStreak) {
    Random idGen(MINID,MAXID);
    Random ageGen(0,2);
    Random genderGen(0,2);
    int ID = 0;
    bool valid = true;
    vector<int> ids;

    for (int i = 0; i < 1000; i++) {
        // 1000 insertions
        ID = idGen.getRandNum();
        Tiger theTiger(ID, static_cast<AGE>(ageGen.getRandNum()), static_cast<GENDER>(genderGen.getRandNum()));
        aStreak.insert(theTiger);
        ids.push_back(ID);

        // verify balance of every node
        if (!aStreak.fullCheckBalance(aStreak.m_root)) {
            valid = false;
        }
    }

    // 150 deletions
    for (int i = 0; i < 150; i++) {
        aStreak.remove(ids.at(i));
    }

    // verify balance again
    if (!aStreak.fullCheckBalance(aStreak.m_root)) {
        valid = false;
    }
    
    return valid;
}


// testInsertRuntime()
// verifies Streak::insert() runtime is O(nlogn)
bool Tester::testInsertRuntime(Streak aStreak) {
    Random ageGen(0, 2);
    Random genderGen(0, 2);
    bool valid = true;

    // get time to do 1000 insertions (T1)
    // get time to do 2000 insertions (T2)
    // T2 / (2 * T1) must be in range T3 = (0.7, 1.5)

    clock_t start1k, stop1k, start2k, stop2k;
    double T1 = 0.0, T2 = 0.0, goldenRatio = 0.0;

    // 1000 insertions
    start1k = clock();
    for (int i = 0; i < 1000; i++) {
        Tiger theTiger(i, static_cast<AGE>(ageGen.getRandNum()), static_cast<GENDER>(genderGen.getRandNum()));
        aStreak.insert(theTiger);
    }
    stop1k = clock();
    T1 = stop1k - start1k;

    // 200 insertions
    start2k = clock();
    for (int i = 0; i < 2000; i++) {
        Tiger theTiger(i, static_cast<AGE>(ageGen.getRandNum()), static_cast<GENDER>(genderGen.getRandNum()));
        aStreak.insert(theTiger);
    }
    stop2k = clock();
    T2 = stop2k - start2k;

    // calculate tick ratio and verify within acceptable range
    goldenRatio = T2 / (2 * T1);
    if (goldenRatio <= 0.7 && goldenRatio >= 1.5) {
        valid = false;
    }
    
    return valid;
}


// testRemoveRuntime()
// verifies Streak::remove() runtime is O(nlogn)
bool Tester::testRemoveRuntime(Streak aStreak) {
    Random ageGen(0, 2);
    Random genderGen(0, 2);
    bool valid = true;

    // get time to do 1000 deletions (T1)
    // get time to do 2000 deletions (T2)
    // T2 / (2 * T1) must be in range T3 = (0.7, 1.5)

    clock_t start1k, stop1k, start2k, stop2k;
    double T1 = 0.0, T2 = 0.0, goldenRatio = 0.0;

    // 3000 insertions
    for (int i = 0; i < 3000; i++) {
        Tiger theTiger(i, static_cast<AGE>(ageGen.getRandNum()), static_cast<GENDER>(genderGen.getRandNum()));
        aStreak.insert(theTiger);
    }

    // 1000 deletions
    start1k = clock();
    for (int i = 0; i < 1000; i++) {
        aStreak.remove(i);
    }
    stop1k = clock();
    T1 = stop1k - start1k;

    // 2000 deletions
    start2k = clock();
    for (int i = 1000; i < 3000; i++) {
        aStreak.remove(i);
    }
    stop2k = clock();
    T2 = stop2k - start2k;

    // calculate tick ratio and verify within acceptable range
    goldenRatio = T2 / (2 * T1);
    if (goldenRatio <= 0.7 && goldenRatio >= 1.5) {
        valid = false;
    }
    
    return valid;
}