// UMBC - CMSC 341 - Fall 2022 - Proj3
// Eric Ekey
// eekey1@gl.umbc.edu
#include "iqueue.h"
#include <random>

enum RANDOM {UNIFORMINT, UNIFORMREAL, NORMAL};
enum CASE {BASE, EDGE, ERROR};

int priorityFn1(const Crop &crop); // works with a MAXHEAP
int priorityFn2(const Crop &crop); // works with a MINHEAP


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
        bool testHeapProperty(IQueue &aQueue); // helper function for verifying valid heaps
        bool testHeapPropertyMAX(Node* aParent); // maxheap helper for testHeapProperty()
        bool testHeapPropertyMIN(Node* aParent); // minheap helper for testHeapProperty()

        bool testInsertMAX(CASE aCase); // maxheap insertion test
        bool testInsertMIN(CASE aCase); // minheap insertion test

        bool testRemoveMAX(CASE aCase); // maxheap removal test
        bool testRemoveMIN(CASE aCase); // minheap removal test
        bool testDequeueEmpty(); // dequeue empty heap test

        bool testChangePriFn(CASE aCase); // change heap type test

        bool testMerge(prifn_t aPriFn, HEAPTYPE aHeapType, CASE aCase); // merge test
        bool testMergeConflict(); // incompatible merge test

        bool testCopy(prifn_t aPriFn, HEAPTYPE aHeapType, CASE aCase); // copy constructor test
        bool testAssignment(prifn_t aPriFn, HEAPTYPE aHeapType, CASE aCase); // assignment operator test
};


int main() {
    Tester tester;
    
    // insertCrop() maxqueue
    cout << "\nTesting insertCrop() with MAXHEAP\n";
    {
        IQueue queue(priorityFn1, MAXHEAP);
        bool base = tester.testInsertMAX(BASE),
        error = tester.testInsertMAX(ERROR);

        if (base) {
            cout << "insertCrop() with MAXHEAP base case PASS\n";
        } else {
            cout << "insertCrop() with MAXHEAP base case FAIL\n";
        }
        if (error) {
            cout << "insertCrop() with MAXHEAP error case PASS\n";
        } else {
            cout << "insertCrop() with MAXHEAP error case FAIL\n";
        }
    }


    // insertCrop() minqueue
    cout << "\nTesting insertCrop() with MINHEAP\n";
    {
        IQueue queue(priorityFn2, MINHEAP);
        bool base = tester.testInsertMIN(BASE),
        error = tester.testInsertMIN(ERROR);

        if (base) {
            cout << "insertCrop() with MINHEAP base case PASS\n";
        } else {
            cout << "insertCrop() with MINHEAP base case FAIL\n";
        }
        if (error) {
            cout << "insertCrop() with MINHEAP error case PASS\n";
        } else {
            cout << "insertCrop() with MINHEAP error case FAIL\n";
        }
    }
    

    // mergeWithQueue()
    cout << "\nTesting mergeWithQueue() with MAXHEAP\n";
    {
        IQueue queue(priorityFn1, MAXHEAP);
        bool base = tester.testMerge(priorityFn1, MAXHEAP, BASE),
        edge = tester.testMerge(priorityFn1, MAXHEAP, EDGE),
        error = tester.testMerge(priorityFn1, MAXHEAP, ERROR);

        if (base) {
            cout << "mergeWithQueue() with MAXHEAP base case PASS\n";
        } else {
            cout << "mergeWithQueue() with MAXHEAP base case FAIL\n";
        }
        if (edge) {
            cout << "mergeWithQueue() with MAXHEAP edge case PASS\n";
        } else {
            cout << "mergeWithQueue() with MAXHEAP edge case FAIL\n";
        }
        if (error) {
            cout << "mergeWithQueue() with MAXHEAP error case PASS\n";
        } else {
            cout << "mergeWithQueue() with MAXHEAP error case FAIL\n";
        }
    }


    // mergeWithQueue() mismatched queues
    cout << "\nTesting mergeWithQueue() with mismatched queues\n";
    {
        bool base = tester.testMergeConflict();

        if (base) {
            cout << "mergeWithQueue() with mismatched queues PASS\n";
        } else {
            cout << "mergeWithQueue() with mismatched queues FAIL\n";
        }
    }


    // insertCrop() maxqueue
    cout << "\nTesting getNextCrop() with MAXHEAP\n";
    {
        IQueue queue(priorityFn1, MAXHEAP);
        bool base = tester.testRemoveMAX(BASE),
        edge = tester.testRemoveMAX(EDGE),
        error = tester.testDequeueEmpty();

        if (base) {
            cout << "getNextCrop() with MAXHEAP base case PASS\n";
        } else {
            cout << "getNextCrop() with MAXHEAP base case FAIL\n";
        }
        if (edge) {
            cout << "getNextCrop() with MAXHEAP edge case PASS\n";
        } else {
            cout << "getNextCrop() with MAXHEAP edge case FAIL\n";
        }
        if (error) {
            cout << "getNextCrop() with MAXHEAP error case PASS\n";
        } else {
            cout << "getNextCrop() with MAXHEAP error case FAIL\n";
        }
    }


    // insertCrop() minqueue
    cout << "\nTesting getNextCrop() with MINHEAP\n";
    {
        IQueue queue(priorityFn2, MINHEAP);
        bool base = tester.testRemoveMIN(BASE),
        error = tester.testRemoveMIN(ERROR);

        if (base) {
            cout << "getNextCrop() with MINHEAP base case PASS\n";
        } else {
            cout << "getNextCrop() with MINHEAP base case FAIL\n";
        }
        if (error) {
            cout << "getNextCrop() with MINHEAP error case PASS\n";
        } else {
            cout << "getNextCrop() with MINHEAP error case FAIL\n";
        }
    }


    // copy constructor maxqueue
    cout << "\nTesting copy constructor with MAXHEAP\n";
    {
        bool base = tester.testCopy(priorityFn1, MAXHEAP, BASE),
        edge = tester.testCopy(priorityFn1, MAXHEAP, EDGE),
        error = tester.testCopy(priorityFn1, MAXHEAP, ERROR);

        if (base) {
            cout << "copy constructor with MAXHEAP base case PASS\n";
        } else {
            cout << "copy constructor with MAXHEAP base case FAIL\n";
        }
        if (edge) {
            cout << "copy constructor with MAXHEAP edge case PASS\n";
        } else {
            cout << "copy constructor with MAXHEAP edge case FAIL\n";
        }
        if (error) {
            cout << "copy constructor with MAXHEAP error case PASS\n";
        } else {
            cout << "copy constructor with MAXHEAP error case FAIL\n";
        }
    }

    
    // copy constructor minqueue
    cout << "\nTesting copy constructor with MINHEAP\n";
    {
        bool base = tester.testCopy(priorityFn2, MINHEAP, BASE),
        edge = tester.testCopy(priorityFn2, MINHEAP, EDGE),
        error = tester.testCopy(priorityFn2, MINHEAP, ERROR);

        if (base) {
            cout << "copy constructor with MINHEAP base case PASS\n";
        } else {
            cout << "copy constructor with MINHEAP base case FAIL\n";
        }
        if (edge) {
            cout << "copy constructor with MINHEAP edge case PASS\n";
        } else {
            cout << "copy constructor with MINHEAP edge case FAIL\n";
        }
        if (error) {
            cout << "copy constructor with MINHEAP error case PASS\n";
        } else {
            cout << "copy constructor with MINHEAP error case FAIL\n";
        }
    }


    // operator= maxqueue
    cout << "\nTesting operator= with MAXHEAP\n";
    {
        bool base = tester.testAssignment(priorityFn1, MAXHEAP, BASE),
        edge = tester.testAssignment(priorityFn1, MAXHEAP, EDGE),
        error = tester.testAssignment(priorityFn1, MAXHEAP, ERROR);

        if (base) {
            cout << "operator= with MAXHEAP base case PASS\n";
        } else {
            cout << "operator= with MAXHEAP base case FAIL\n";
        }
        if (edge) {
            cout << "operator= with MAXHEAP edge case PASS\n";
        } else {
            cout << "operator= with MAXHEAP edge case FAIL\n";
        }
        if (error) {
            cout << "operator= with MAXHEAP error case PASS\n";
        } else {
            cout << "operator= with MAXHEAP error case FAIL\n";
        }
    }

    
    // operator= minqueue
    cout << "\nTesting operator= with MINHEAP\n";
    {
        bool base = tester.testAssignment(priorityFn2, MINHEAP, BASE),
        edge = tester.testAssignment(priorityFn2, MINHEAP, EDGE),
        error = tester.testAssignment(priorityFn2, MINHEAP, ERROR);

        if (base) {
            cout << "operator= with MINHEAP base case PASS\n";
        } else {
            cout << "operator= with MINHEAP base case FAIL\n";
        }
        if (edge) {
            cout << "operator= with MINHEAP edge case PASS\n";
        } else {
            cout << "operator= with MINHEAP edge case FAIL\n";
        }
        if (error) {
            cout << "operator= with MINHEAP error case PASS\n";
        } else {
            cout << "operator= with MINHEAP error case FAIL\n";
        }
    }


    // setPriorityFn()
    cout << "\nTesting setPriorityFn()\n";
    {
        bool base = tester.testChangePriFn(BASE),
        edge = tester.testChangePriFn(EDGE),
        error = tester.testChangePriFn(ERROR);

        if (base) {
            cout << "setPriorityFn() base case PASS\n";
        } else {
            cout << "setPriorityFn() base case FAIL\n";
        }
        if (edge) {
            cout << "setPriorityFn() edge case PASS\n";
        } else {
            cout << "setPriorityFn() edge case FAIL\n";
        }
        if (error) {
            cout << "setPriorityFn() error case PASS\n";
        } else {
            cout << "setPriorityFn() error case FAIL\n";
        }
    }
    
    return 0;
}


// priorityFn1(const Crop&)
// computes priority for a crop in a MAXHEAP
int priorityFn1(const Crop &crop) {
    //needs MAXHEAP
    //priority value is determined based on some criteria
    //priority value falls in the range [30-116]
    //the highest priority would be 110+6 = 116
    //the lowest priority would be 30+0 = 30
    //the larger value means the higher priority
    int priority = crop.getTemperature() + crop.getType();
    return priority;
}


// priorityFn2(const Crop&)
// computes priority for a crop in a MINHEAP
int priorityFn2(const Crop &crop) {
    //needs MINHEAP
    //priority value is determined based on some criteria
    //priority value falls in the range [0-103]
    //the highest priority would be 0+0 = 0
    //the lowest priority would be 100+3 = 103
    //the smaller value means the higher priority
    int priority = crop.getMoisture() + crop.getTime();
    return priority;
}


// testHeapProperty(IQueue)
// tests heap property in a given queue
bool Tester::testHeapProperty(IQueue &aQueue) {
    int valid = true;

    // check which heap property to test
    if (aQueue.getHeapType() == MAXHEAP) {
        valid = testHeapPropertyMAX(aQueue.m_heap);
    } else {
        valid = testHeapPropertyMIN(aQueue.m_heap);
    }

    return valid;
}


// testHeapPropertyMAX(Node*)
// tests heap property in a max queue
bool Tester::testHeapPropertyMAX(Node* aParent) {
    int valid = true, valid2 = true;

    // verify that parent priority is always a higher number than children
    if (aParent != nullptr) {
        if (aParent->m_left != nullptr) {
            if (priorityFn1(aParent->m_left->getCrop()) > priorityFn1(aParent->getCrop())) {
                return false;
            }
        }
        if (aParent->m_right != nullptr) {
            if (priorityFn1(aParent->m_right->getCrop()) > priorityFn1(aParent->getCrop())) {
                return false;
            }
        }
        valid = testHeapPropertyMAX(aParent->m_left);
        valid2 = testHeapPropertyMAX(aParent->m_right);
    }
    
    if (!valid2) { valid = false; }
    return valid;
}


// testHeapPropertyMIN(Node*)
// tests heap property in a min queue
bool Tester::testHeapPropertyMIN(Node* aParent) {
    int valid = true, valid2 = true;

    // verify that parent priority is always a lower number than children
    if (aParent != nullptr) {
        if (aParent->m_left != nullptr) {
            if (priorityFn2(aParent->m_left->getCrop()) < priorityFn2(aParent->getCrop())) {
                return false;
            }
        }
        if (aParent->m_right != nullptr) {
            if (priorityFn2(aParent->m_right->getCrop()) < priorityFn2(aParent->getCrop())) {
                return false;
            }
        }
        valid = testHeapPropertyMIN(aParent->m_left);
        valid2 = testHeapPropertyMIN(aParent->m_right);
    }
    
    if (!valid2) { valid = false; }
    return valid;
}


// testInsertMAX(IQueue, CASE)
// tests inserting a crop to a max queue
bool Tester::testInsertMAX(CASE aCase) {
    Random idGen(MINCROPID,MAXCROPID), temperatureGen(MINTEMP,MAXTEMP), moistureGen(MINMOISTURE,MAXMOISTURE), timeGen(MINTIME,MAXTIME), typeGen(MINTYPE,MAXTYPE);
    int temperature = temperatureGen.getRandNum(), time = timeGen.getRandNum();
    IQueue aQueue(priorityFn1, MAXHEAP);
    bool valid = true;

    if (aCase == BASE) {
        // valid crop id
        // 500 crop queue
        for (int i = 0; i < 500 && valid; i++) {
            int numcrops = aQueue.numCrops();
            Crop aCrop(idGen.getRandNum(),
                    temperature,// it is the same in the region
                    moistureGen.getRandNum(),
                    time,       // it is the same in the region
                    typeGen.getRandNum());
            aQueue.insertCrop(aCrop);

            // verify heap property and size at every insertion
            if (!testHeapProperty(aQueue) || aQueue.numCrops() != (numcrops + 1)) {
                valid = false;
            }
        }
    } else if (aCase == ERROR) {
        // try to insert invalid crop id
        Crop aCrop(DEFAULTCROPID,
                temperature,// it is the same in the region
                moistureGen.getRandNum(),
                time,       // it is the same in the region
                typeGen.getRandNum());
        aQueue.insertCrop(aCrop);

        // verify invalid crop not added
        if (aQueue.numCrops()) {
            valid = false;
        }
    }
    return valid;
}


// testInsertMIN(IQueue, CASE)
// tests inserting a crop to a min queue
bool Tester::testInsertMIN(CASE aCase) {
    Random idGen(MINCROPID,MAXCROPID), temperatureGen(MINTEMP,MAXTEMP), moistureGen(MINMOISTURE,MAXMOISTURE), timeGen(MINTIME,MAXTIME), typeGen(MINTYPE,MAXTYPE);
    int temperature = temperatureGen.getRandNum(), time = timeGen.getRandNum();
    IQueue aQueue(priorityFn2, MINHEAP);
    bool valid = true;

    if (aCase == BASE) {
        // valid crop id
        // 500 crop queue
        for (int i = 0; i < 500 && valid; i++) {
            int numcrops = aQueue.numCrops();
            Crop aCrop(idGen.getRandNum(),
                    temperature,// it is the same in the region
                    moistureGen.getRandNum(),
                    time,       // it is the same in the region
                    typeGen.getRandNum());
            aQueue.insertCrop(aCrop);

            // verify heap property and size at every insertion
            if (!testHeapProperty(aQueue) || aQueue.numCrops() != (numcrops + 1)) {
                valid = false;
            }
        }
    } else if (aCase == ERROR) {
        // try to insert invalid crop id
        Crop aCrop(DEFAULTCROPID,
                temperature,// it is the same in the region
                moistureGen.getRandNum(),
                time,       // it is the same in the region
                typeGen.getRandNum());
        aQueue.insertCrop(aCrop);

        // verify invalid crop not added
        if (aQueue.numCrops()) {
            valid = false;
        }
    }
    return valid;
}


// testMerge(IQueue, CASE)
// tests merging 2 compatible queues
bool Tester::testMerge(prifn_t aPriFn, HEAPTYPE aHeapType, CASE aCase) {
    Random idGen(MINCROPID,MAXCROPID), temperatureGen(MINTEMP,MAXTEMP), moistureGen(MINMOISTURE,MAXMOISTURE), timeGen(MINTIME,MAXTIME), typeGen(MINTYPE,MAXTYPE);
    int temperature = temperatureGen.getRandNum(), time = timeGen.getRandNum();
    IQueue aQueue(aPriFn, aHeapType);
    bool valid = true;

    if (aCase == BASE) {
        // 500 with 300
        // 500 crop queue
        for (int i = 0; i < 500; i++) {
            Crop aCrop(idGen.getRandNum(),
                    temperature,// it is the same in the region
                    moistureGen.getRandNum(),
                    time,       // it is the same in the region
                    typeGen.getRandNum());
            aQueue.insertCrop(aCrop);
        }

        // 300 crop queue
        IQueue aQueue2(aQueue.getPriorityFn(), aQueue.getHeapType());
        for (int i = 0; i < 300; i++) {
            Crop aCrop2(idGen.getRandNum(),
                    temperature,// it is the same in the region
                    moistureGen.getRandNum(),
                    time,       // it is the same in the region
                    typeGen.getRandNum());
            aQueue2.insertCrop(aCrop2);
        }

        // merge and verify numcrops and heap property
        aQueue.mergeWithQueue(aQueue2);
        if (aQueue.numCrops() != 800 || !testHeapProperty(aQueue)) {
            valid = false;
        }
    } else if (aCase == EDGE) {
        // 500 with 1 or 0, 0 with 501
        // 500 crop queue
        for (int i = 0; i < 500; i++) {
            Crop aCrop(idGen.getRandNum(),
                    temperature,// it is the same in the region
                    moistureGen.getRandNum(),
                    time,       // it is the same in the region
                    typeGen.getRandNum());
            aQueue.insertCrop(aCrop);
        }
        
        // 1 crop queue
        IQueue aQueue2(aQueue.getPriorityFn(), aQueue.getHeapType());
        Crop aCrop2(idGen.getRandNum(),
                temperature,// it is the same in the region
                moistureGen.getRandNum(),
                time,       // it is the same in the region
                typeGen.getRandNum());
        aQueue2.insertCrop(aCrop2);

        // merge 500 and 1, verify properties
        aQueue.mergeWithQueue(aQueue2);
        if (aQueue.numCrops() != 501 || !testHeapProperty(aQueue)) {
            return false;
        }
        
        // empty queue
        IQueue aQueue3(aQueue.getPriorityFn(), aQueue.getHeapType());

        // merge 0 into 501, verify properties
        aQueue.mergeWithQueue(aQueue3);
        if (aQueue.numCrops() != 501 || !testHeapProperty(aQueue)) {
            return false;
        }

        // 0 crop queue
        IQueue aQueue4(aQueue.getPriorityFn(), aQueue.getHeapType());

        // merge 501 into 0, verify properties
        aQueue4.mergeWithQueue(aQueue);
        if (aQueue4.numCrops() != 501 || !testHeapProperty(aQueue4)) {
            valid = false;
        }
    } else if (aCase == ERROR) {
        // 0 with 0
        // error case of merging incompatible queues covered in other function
        // 0 crop queue
        IQueue aQueue2(aQueue.getPriorityFn(), aQueue.getHeapType());

        // merge 0 into 0, verify empty queue
        aQueue.mergeWithQueue(aQueue2);
        if (aQueue.numCrops() != 0) {
            valid = false;
        }
    }
    return valid;
}


// testMergeConflict()
// tests trying to merge incompatible queues
bool Tester::testMergeConflict() {
    Random idGen(MINCROPID,MAXCROPID), temperatureGen(MINTEMP,MAXTEMP), moistureGen(MINMOISTURE,MAXMOISTURE), timeGen(MINTIME,MAXTIME), typeGen(MINTYPE,MAXTYPE);
    int temperature = temperatureGen.getRandNum(), time = timeGen.getRandNum();
    IQueue queue(priorityFn1, MAXHEAP), queue2(priorityFn2, MINHEAP);
    bool valid = false;

    // 1 crop maxqueue, 1 crop minqueue
    Crop aCrop(idGen.getRandNum(),
                temperature,// it is the same in the region
                moistureGen.getRandNum(),
                time,       // it is the same in the region
                typeGen.getRandNum());
    Crop aCrop2(idGen.getRandNum(),
                temperature,// it is the same in the region
                moistureGen.getRandNum(),
                time,       // it is the same in the region
                typeGen.getRandNum());
    queue.insertCrop(aCrop);
    queue2.insertCrop(aCrop2);

    // verify that domain error is thrown
    try {
        queue.mergeWithQueue(queue2);
    } catch (std::domain_error&) {
        valid = true;
    }
    return valid;
}


// testRemoveMax(IQueue, CASE)
// tests removing from a maxheap
bool Tester::testRemoveMAX(CASE aCase) {
    Random idGen(MINCROPID,MAXCROPID), temperatureGen(MINTEMP,MAXTEMP), moistureGen(MINMOISTURE,MAXMOISTURE), timeGen(MINTIME,MAXTIME), typeGen(MINTYPE,MAXTYPE);
    int temperature = temperatureGen.getRandNum(), time = timeGen.getRandNum();
    IQueue aQueue(priorityFn1, MAXHEAP);
    bool valid = true;

    if (aCase == BASE) {
        // 500 minus 1
        // 500 crop queue
        for (int i = 0; i < 500; i++) {
            Crop aCrop(idGen.getRandNum(),
                    temperature,// it is the same in the region
                    moistureGen.getRandNum(),
                    time,       // it is the same in the region
                    typeGen.getRandNum());
            aQueue.insertCrop(aCrop);
        }

        // remove all crops and verify heap property after each removal
        while (aQueue.m_heap != nullptr && valid) {
            aQueue.getNextCrop();
            if (!testHeapProperty(aQueue)) {
                valid = false;
            }
        }
    } else if (aCase == EDGE) {
        // 1 minus 1
        // dequeueing from empty is covered in other function
        // 1 crop queue
        Crop aCrop(idGen.getRandNum(),
                temperature,// it is the same in the region
                moistureGen.getRandNum(),
                time,       // it is the same in the region
                typeGen.getRandNum());
        aQueue.insertCrop(aCrop);

        // verify empty queue
        aQueue.getNextCrop();
        if (aQueue.m_heap != nullptr) {
            valid = false;
        }
    }
    return valid;
}


// testRemoveMIN(IQueue, CASE)
// tests removing from a minheap
bool Tester::testRemoveMIN(CASE aCase) {
    Random idGen(MINCROPID,MAXCROPID), temperatureGen(MINTEMP,MAXTEMP), moistureGen(MINMOISTURE,MAXMOISTURE), timeGen(MINTIME,MAXTIME), typeGen(MINTYPE,MAXTYPE);
    int temperature = temperatureGen.getRandNum(), time = timeGen.getRandNum();
    IQueue aQueue(priorityFn2, MINHEAP);
    bool valid = true;

    if (aCase == BASE) {
        // 500 minus 1
        // 500 crop queue
        for (int i = 0; i < 500; i++) {
            Crop aCrop(idGen.getRandNum(),
                    temperature,// it is the same in the region
                    moistureGen.getRandNum(),
                    time,       // it is the same in the region
                    typeGen.getRandNum());
            aQueue.insertCrop(aCrop);
        }

        // remove each crop and verify heap propert after each removal
        while (aQueue.m_heap != nullptr && valid) {
            aQueue.getNextCrop();
            if (!testHeapProperty(aQueue)) {
                valid = false;
            }
        }
    } else if (aCase == EDGE) {
        // 1 minus 1
        // dequeueing from empty is covered in other function
        // 1 crop queue
        Crop aCrop(idGen.getRandNum(),
                temperature,// it is the same in the region
                moistureGen.getRandNum(),
                time,       // it is the same in the region
                typeGen.getRandNum());
        aQueue.insertCrop(aCrop);

        // verify empty queue
        aQueue.getNextCrop();
        if (aQueue.m_heap != nullptr) {
            valid = false;
        }
    }
    return valid;
}


// testDequeueEmpty(IQueue)
// tests dequeueing from empty queue
bool Tester::testDequeueEmpty() {
    IQueue aQueue(priorityFn1, MAXHEAP);
    bool valid = false;

    // verify out of range error thrown for dequeueing from empty queue
    try {
        aQueue.getNextCrop();
    } catch (std::out_of_range&) {
        valid = true;
    }

    return valid;
}


// testChangePriFn(IQueue, CASE)
// tests changing priority function
bool Tester::testChangePriFn(CASE aCase) {
    Random idGen(MINCROPID,MAXCROPID), temperatureGen(MINTEMP,MAXTEMP), moistureGen(MINMOISTURE,MAXMOISTURE), timeGen(MINTIME,MAXTIME), typeGen(MINTYPE,MAXTYPE);
    int temperature = temperatureGen.getRandNum(), time = timeGen.getRandNum();
    IQueue aQueue(priorityFn1, MAXHEAP), aQueue2(priorityFn2, MINHEAP);
    bool valid = true;

    if (aCase == BASE) {
        // 500 nodes
        // 500 crop queue
        for (int i = 0; i < 500; i++) {
            Crop aCrop(idGen.getRandNum(),
                    temperature,// it is the same in the region
                    moistureGen.getRandNum(),
                    time,       // it is the same in the region
                    typeGen.getRandNum());
            aQueue2.insertCrop(aCrop);
        }

        // verify new heap property
        aQueue2.setPriorityFn(priorityFn1, MAXHEAP);
        if (!testHeapPropertyMAX(aQueue2.m_heap) || aQueue2.numCrops() != 500) {
            valid = false;
        }

        // verify going back to old heap property
        aQueue2.setPriorityFn(priorityFn2, MINHEAP);
        if (!testHeapPropertyMIN(aQueue2.m_heap) || aQueue2.numCrops() != 500) {
            valid = false;
        }
    } else if (aCase == EDGE) {
        // 1 node
        // 1 crop queue
        Crop aCrop(idGen.getRandNum(),
                temperature,// it is the same in the region
                moistureGen.getRandNum(),
                time,       // it is the same in the region
                typeGen.getRandNum());
        aQueue.insertCrop(aCrop);

        // verify new heap property
        aQueue.setPriorityFn(priorityFn2, MINHEAP);
        if (!testHeapPropertyMIN(aQueue.m_heap)) {
            valid = false;
        }

        // verify going back to old heap property
        aQueue.setPriorityFn(priorityFn1, MAXHEAP);
        if (!testHeapPropertyMAX(aQueue.m_heap)) {
            valid = false;
        }
    } else if (aCase == ERROR) {
        // 0 nodes
        // 0 node queue
        // verify new heap property
        aQueue.setPriorityFn(priorityFn2, MINHEAP);
        if (!testHeapPropertyMIN(aQueue.m_heap)) {
            valid = false;
        }

        // verify going back to old heap property
        aQueue.setPriorityFn(priorityFn1, MAXHEAP);
        if (!testHeapPropertyMAX(aQueue.m_heap)) {
            valid = false;
        }
    }
    return valid;
}


// testCopy(IQueue, CASE)
// tests copy constructor
bool Tester::testCopy(prifn_t aPriFn, HEAPTYPE aHeapType, CASE aCase) {
    Random idGen(MINCROPID,MAXCROPID), temperatureGen(MINTEMP,MAXTEMP), moistureGen(MINMOISTURE,MAXMOISTURE), timeGen(MINTIME,MAXTIME), typeGen(MINTYPE,MAXTYPE);
    int temperature = temperatureGen.getRandNum(), time = timeGen.getRandNum();
    IQueue aQueue(aPriFn, aHeapType);
    bool valid = true;

    if (aCase == BASE) {
        // copy 300
        // 300 crop queue
        for (int i = 0; i < 300; i++){
            Crop aCrop(idGen.getRandNum(),
                        temperature,// it is the same in the region
                        moistureGen.getRandNum(),
                        time,       // it is the same in the region
                        typeGen.getRandNum());
            aQueue.insertCrop(aCrop);
        }

        // copy and verify qualities
        IQueue aQueue2(aQueue);
        if (aQueue.m_heap == aQueue2.m_heap || aQueue.numCrops() != aQueue2.numCrops() || aQueue.m_heap->getCrop().getCropID() != aQueue2.m_heap->getCrop().getCropID()) {
            valid = false;
        }
    } else if (aCase == EDGE) {
        // copy one crop queue
        // 1 crop queue
        Crop aCrop(idGen.getRandNum(),
                    temperature,// it is the same in the region
                    moistureGen.getRandNum(),
                    time,       // it is the same in the region
                    typeGen.getRandNum());
        aQueue.insertCrop(aCrop);

        // copy and verify properties
        IQueue aQueue2(aQueue);
        if (aQueue.m_heap == aQueue2.m_heap || aQueue.numCrops() != aQueue2.numCrops() || aQueue.m_heap->getCrop().getCropID() != aQueue2.m_heap->getCrop().getCropID()) {
            valid = false;
        }
    } else if (aCase == ERROR) {
        // zero crop copy
        // 0 crop queue
        // copy and verify empty queue
        IQueue aQueue2(aQueue);
        if (aQueue2.m_heap != nullptr || aQueue2.numCrops()) {
            valid = false;
        }
    }
    return valid;
}


// testAssignment(IQueue, CASE)
// tests assignment operator
bool Tester::testAssignment(prifn_t aPriFn, HEAPTYPE aHeapType, CASE aCase) {
    Random idGen(MINCROPID,MAXCROPID), temperatureGen(MINTEMP,MAXTEMP), moistureGen(MINMOISTURE,MAXMOISTURE), timeGen(MINTIME,MAXTIME), typeGen(MINTYPE,MAXTYPE);
    int temperature = temperatureGen.getRandNum(), time = timeGen.getRandNum();
    IQueue aQueue(aPriFn, aHeapType);
    bool valid = true;
    
    if (aCase == BASE) {
        // 300 crop queue
        for (int i = 0; i < 300; i++){
            Crop aCrop(idGen.getRandNum(),
                        temperature,// it is the same in the region
                        moistureGen.getRandNum(),
                        time,       // it is the same in the region
                        typeGen.getRandNum());
            aQueue.insertCrop(aCrop);
        }

        // 200 crop queue
        IQueue aQueue2(aQueue.getPriorityFn(), aQueue.getHeapType());
        for (int i = 0; i < 200; i++){
            Crop aCrop(idGen.getRandNum(),
                        temperature,// it is the same in the region
                        moistureGen.getRandNum(),
                        time,       // it is the same in the region
                        typeGen.getRandNum());
            aQueue2.insertCrop(aCrop);
        }

        // 200 = 300 and verify properties
        aQueue2 = aQueue;
        if (aQueue.m_heap == aQueue2.m_heap || aQueue.numCrops() != aQueue2.numCrops() || aQueue.m_heap->getCrop().getCropID() != aQueue2.m_heap->getCrop().getCropID()) {
            valid = false;
        }
    } else if (aCase == EDGE) {
        // set full equal to empty
        // 300 crop queue
        for (int i = 0; i < 300; i++){
            Crop aCrop(idGen.getRandNum(),
                        temperature,// it is the same in the region
                        moistureGen.getRandNum(),
                        time,       // it is the same in the region
                        typeGen.getRandNum());
            aQueue.insertCrop(aCrop);
        }

        // 0 crop queue
        IQueue aQueue2(aQueue.getPriorityFn(), aQueue.getHeapType());

        // 0 = 300 and verify properties
        aQueue2 = aQueue;
        if (aQueue.m_heap == aQueue2.m_heap || aQueue.numCrops() != aQueue2.numCrops() || aQueue.m_heap->getCrop().getCropID() != aQueue2.m_heap->getCrop().getCropID()) {
            valid = false;
        }
    } else if (aCase == ERROR) {
        // self assignment check
        IQueue* addy = &aQueue;
        aQueue = aQueue;
        if (addy != &aQueue) {
            valid = false;
        }
    }
    return valid;
}