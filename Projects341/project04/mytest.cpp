// CMSC 341 - Fall 2022 - Project 4
// Eric Ekey
// eekey1@gl.umbc.edu
#include "cache.h"
#include <vector>
enum CASE {BASE, EDGE, ERROR, LOAD, DELETE}; // cases for tests
unsigned int hashCode(const string); // hashes key

// class Tester
// contains functions for testing Cache class
class Tester{
    public:
        bool testInsert(CASE); // tests insert function
        bool testGetPerson(CASE); // tests getPerson function
        bool testRemove(CASE); // tests remove function
        bool testRehash(CASE); // tests rehashing functionality
};


int main() {
    Tester tester;

    // insert()
    cout << "\nTesting insert()\n";
    {
        bool base = tester.testInsert(BASE),
            edge = tester.testInsert(EDGE),
            error = tester.testInsert(ERROR);
        
        if (base) {
            cout << "\ttestInsert() base case PASS\n";
        } else {
            cout << "\ttestInsert() base case FAIL\n";
        }
        if (edge) {
            cout << "\ttestInsert() edge case PASS\n";
        } else {
            cout << "\ttestInsert() edge case FAIL\n";
        }
        if (error) {
            cout << "\ttestInsert() error case PASS\n";
        
        } else {
            cout << "\ttestInsert() error case FAIL\n";
        }
    }

    // getPerson()
    cout << "\nTesting getPerson()\n";
    {
        bool base = tester.testGetPerson(BASE),
            edge = tester.testGetPerson(EDGE),
            error = tester.testGetPerson(ERROR);
        
        if (base) {
            cout << "\ttestGetPerson() base case PASS\n";
        } else {
            cout << "\ttestGetPerson() base case FAIL\n";
        }
        if (edge) {
            cout << "\ttestGetPerson() edge case PASS\n";
        } else {
            cout << "\ttestGetPerson() edge case FAIL\n";
        }
        if (error) {
            cout << "\ttestGetPerson() error case PASS\n";
        
        } else {
            cout << "\ttestGetPerson() error case FAIL\n";
        }
    }

    // remove()
    cout << "\nTesting remove()\n";
    {
        bool base = tester.testRemove(BASE),
            edge = tester.testRemove(EDGE),
            error = tester.testRemove(ERROR);
        
        if (base) {
            cout << "\ttestRemove() base case PASS\n";
        } else {
            cout << "\ttestRemove() base case FAIL\n";
        }
        if (edge) {
            cout << "\ttestRemove() edge case PASS\n";
        } else {
            cout << "\ttestRemove() edge case FAIL\n";
        }
        if (error) {
            cout << "\ttestRemove() error case PASS\n";
        
        } else {
            cout << "\ttestRemove() error case FAIL\n";
        }
    }

    // rehash()
    cout << "\nTesting rehash()\n";
    {
        bool load = tester.testRehash(LOAD),
            del = tester.testRehash(DELETE);

        if (load) {
            cout << "\ttestRehash() load factor case PASS\n";
        } else {
            cout << "\ttestRehash() load factor case FAIL\n";
        }
        if (del) {
            cout << "\ttestRehash() delete ratio case PASS\n";
        } else {
            cout << "\ttestRehash() delete ratio case FAIL\n";
        }
    }

    return 0;
}


// testInsert(CASE)
// tests cache insert function
bool Tester::testInsert(CASE aCase = BASE)  {
    Cache theCache(MINPRIME, hashCode);
    bool valid = true;

    if (aCase == BASE) {
        // insert non colliding keys
        string insertKeys[10] = {"c++","python","java","scheme","prolog","c#","c","js","something","unprofessional"};
        int insertID[10] = {1000, 1001, 1002, 1003, 1004, 1005, 1006, 1007, 1008, 1009};

        // insert keys 
        for (int i = 1; i <= 9 && valid; i++) {
            Person thePerson(insertKeys[i], insertID[i]);
            int expectedIndex = hashCode(thePerson.getKey()) % theCache.m_currentCap;
            theCache.insert(thePerson);

            // check if person is where they should be
            if (theCache.m_currentTable[expectedIndex] == thePerson) {
                // do nothing
            } else {
                valid = false;
            }

            // check if size is incrementing correctly
            if (theCache.m_currentSize != i) {
                valid = false;
            }
        }
    } else if (aCase == EDGE) {
        // colliding data points
        for (int i = 1; i <= 20 && valid; i++) {
            Person thePerson("thekey", MINID + i);
            theCache.insert(thePerson);
            if (theCache.m_currentSize != i) {
                valid = false;
            }
        }
    } else if (aCase == ERROR) {
        // nonexistent person objects, invalid ids, and Person objects already in hash table
        Person thePerson("thekey", MAXID + 1);
        Person thePerson2("validkey", MAXID);
        Person thePerson3(thePerson2);

        // insert keys
        theCache.insert(thePerson);
        theCache.insert(thePerson2);
        theCache.insert(thePerson3);
        
        // check if invalid id inserted
        if (theCache.getPerson(thePerson.getKey(), thePerson.getID()) == EMPTY) {
            // do nothing
        } else {
            valid = false;
        }

        // check if nonexistent person returns EMPTY
        if (theCache.getPerson("non-key", MINID) == EMPTY) {
            // do nothing
        } else {
            valid = false;
        }

        // check if duplicate person inserted
        if (theCache.m_currentSize > 1) {
            valid = false;
        }
    }
    return valid;
}


// testRemove(CASE)
// tests cache remove function
bool Tester::testRemove(CASE aCase = BASE) {
    Cache theCache(1381, hashCode);
    bool valid = true;

    if (aCase == BASE) {
        // non colliding keys
        string insertKeys[26] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};
        vector<Person> people;

        // populate cache
        for (int i = 0; i < 26; i++) {
            Person thePerson(insertKeys[i], MINID + i);
            theCache.insert(thePerson);
            people.push_back(thePerson);
        }

        // depopulate cache
        for (int i = 0; i < 26 && valid; i++) {
            pair<string,int> person = make_pair(people.at(i).getKey(), people.at(i).getID());
            theCache.remove(people.at(i));

            // check if object successfully removed
            if (theCache.getPerson(person.first, person.second) == EMPTY) {
                // do nothing
            } else {
                valid = false;
            }
        }
    } else if (aCase == EDGE) {
        // colliding keys WITHOUT TRIGGERING REHASH
        string insertKeys[26] = {"a", "b", "b", "d", "e", "f", "a", "g", "c", "c", "k", "g", "m", "c", "c", "a", "q", "f", "s", "t", "u", "b", "w", "x", "y", "z"};
        vector <Person> people;

        // populate cache
        for (int i = 0; i < 26; i++) {
            Person thePerson(insertKeys[i], MINID + i);
            theCache.insert(thePerson);
            people.push_back(thePerson);
        }

        // remove some objects
        for (int i = 0; i < 13 && valid; i++) {
            pair<string,int> person = make_pair(people.at(i).getKey(), people.at(i).getID());
            theCache.remove(people.at(i));

            // check if object successfully removed
            if (theCache.getPerson(person.first, person.second) == EMPTY) {
                // do nothing
            } else {
                valid = false;
            }
        }
    } else if (aCase == ERROR) {
        // nonexistent key
        Person thePerson("keyvalue", MINID);
        
        // remove person that doesnt exist in cache
        theCache.remove(thePerson);
        if (theCache.getPerson(thePerson.getKey(), thePerson.getID()) == EMPTY) {
            // do nothing
        } else {
            valid = false;
        }
    }
    return valid;
}


// testGetPerson(CASE)
// tests cache getPerson function
bool Tester::testGetPerson(CASE aCase = BASE) {
    Cache theCache(MINPRIME, hashCode);
    bool valid = true;

    if (aCase == BASE) {
        // non colliding keys
        string insertKeys[10] = {"a","b","c","d","e","f","g","h","i","j"};

        // insert keys
        for (int i = 0; i < 10 && valid; i++) {
            Person thePerson(insertKeys[i], MINID + i);
            if (theCache.getPerson(insertKeys[i], MINID + i) == EMPTY) {
                // do nothing
            } else {
                valid = false;
            }
        }
    } else if (aCase == EDGE) {
        // colliding keys
        string insertKeys[10] = {"c","a","a","b","a","b","b","a","c","c"};

        // insert keys
        for (int i = 0; i < 10 && valid; i++) {
            Person thePerson(insertKeys[i], MINID + i);
            if (theCache.getPerson(insertKeys[i], MINID + i) == EMPTY) {
                // do nothing
            } else {
                valid = false;
            }
        }
    } else if (aCase == ERROR) {
        // person does not exist
        // populate cache
        for (int i = 0; i < 10; i++) {
            Person thePerson("validkey", MINID + 1);
            theCache.insert(thePerson);
        }
        
        // get nonexistent person
        if (theCache.getPerson("invalidkey", MAXID) == EMPTY) {
            // do nothing
        } else {
            valid = false;
        }
    }
    return valid;
}


// testRehash(CASE)
//tests cache rehash functionality
bool Tester::testRehash(CASE aCase = LOAD) {
    Cache theCache(MINPRIME, hashCode);
    bool valid = true;

    if (aCase == LOAD) {
        // insertion-triggered rehash
        string insertKeys[8]={"c++","python","java","scheme","prolog","c#","c","js"};
        vector<Person> people;

        // populate cache
        for (int i = 0, j = 0; j < 52 && valid; i++, j++) {
            i = i % 8;
            Person thePerson(insertKeys[i], MINID + j);
            theCache.insert(thePerson);
            people.push_back(thePerson);

            // check if load factor goes out of control
            if (theCache.lambda() > 0.5) {
                valid = false;
            }
        }

        // check if rehash started
        if (theCache.m_oldTable == nullptr) {
            valid = false;
        }

        // finish rehashing
        for (int i = 0; i < 4; i++) {
            Person thePerson(insertKeys[i], MINID + i + 52);
            theCache.insert(thePerson);
            people.push_back(thePerson);
        }

        // check if rehash finished and old table removed
        if (theCache.m_oldTable != nullptr) {
            valid = false;
        }

        // check if any objects have gone missing
        for (unsigned int i = 0; i < people.size() && valid; i++) {
            pair<string,int> person = make_pair(people.at(i).getKey(), people.at(i).getID());

            if (theCache.getPerson(person.first, person.second) == EMPTY) {
                valid = false;
            }
        }
    } else if (aCase == DELETE) {
        // deletion-triggered rehash
        string insertKeys[8]={"c++","python","java","scheme","prolog","c#","c","js"};
        vector<Person> people;

        // populate cache
        for (int i = 0, j = 0; j < 51; i++, j++) {
            i = i % 8;
            Person thePerson(insertKeys[i], MINID + j);
            theCache.insert(thePerson);
            people.push_back(thePerson);
        }

        // trigger rehash through by deletion
        for (int i = 0, j = 0; j < 41; i++, j++) {
            i = i % 8;
            Person thePerson(insertKeys[i], MINID + j);
            
            theCache.remove(thePerson);
            people.erase(people.begin());
        }

        // check for rehashing
        if (theCache.deletedRatio()) {
            valid = false;
        }

        // check if any objects went missing
        for (unsigned int i = 0; i < people.size() && valid; i++) {
            pair<string,int> person = make_pair(people.at(i).getKey(), people.at(i).getID());
            
            if (theCache.getPerson(person.first, person.second) == EMPTY) {
                valid = false;
            }
        }

        // check if old table removed
        if (theCache.m_oldTable != nullptr) {
            valid = false;
        }
    }
    return valid;
}


// hashCode(const string)
// returns hash code for a key
unsigned int hashCode(const string str) {
   unsigned int val = 0;
   const unsigned int thirtyThree = 33;  // magic number from textbook
   for (unsigned int i = 0; i < str.length(); i++)
      val = val * thirtyThree + str[i];
   return val;
}