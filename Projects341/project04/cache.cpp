// CMSC 341 - Fall 2022 - Project 4
// Eric Ekey
// eekey1@gl.umbc.edu
#include "cache.h"
#define EMPTYKEY ""
#define MAXLOAD 0.5
#define MAXDELETE 0.8

// Cache(int, hash_fn)
// default constructor for Cache object
Cache::Cache(int aSize, hash_fn aHash) {
    m_currentCap = findNextPrime(aSize);
    m_currentTable = new Person[m_currentCap];
    
    for (int i = 0; i < m_currentCap; i++) {
        m_currentTable[i] = EMPTY;
    }
    m_currentSize = 0;
    m_currNumDeleted = 0;
    m_hash = aHash;

    m_oldTable = nullptr;
    m_oldCap = 0;
    m_oldNumDeleted = 0;
}


// ~Cache()
// destructor for Cache object
Cache::~Cache() {
    if (m_oldTable != m_currentTable) {
        delete [] m_oldTable;
        m_oldTable = nullptr;
    }
    m_oldCap = 0;
    m_oldSize = 0;
    m_oldNumDeleted = 0;

    m_currentCap = 0;
    m_currentSize = 0;
    m_currNumDeleted = 0;
    delete [] m_currentTable;
    m_currentTable = nullptr;
}


// insert(Person)
// inserts a Person object into Cache
// returns whether the insertion was successful
bool Cache::insert(Person aPerson) {
    bool inserted = false;
    int j = 0;

    // validate Person object for insertion
    if (isValidPerson(aPerson) && !personExists(aPerson)) {
        int insertIndex = m_hash(aPerson.getKey()) % m_currentCap;

        // keep trying to put it in until it goes in
        while (!inserted) {
            if (!isCollision(insertIndex)) {
                // insert and change insert flag
                m_currentTable[insertIndex] = aPerson;
                m_currentSize++;
                inserted = true;
                j=0;
                rehash();
            } else {
                // quadratic probing for free index
                insertIndex = probe(j, aPerson.getKey());
                j++;
            }
        }
    }
    return inserted;
}


// remove(Person)
// removes a Person object from Cache
// returns whether the removal was successful
bool Cache::remove(Person aPerson) {
    bool removed = false;
    
    if (isValidPerson(aPerson) && personExists(aPerson)) {
        // try to remove from current table
        for (int i = 0; i < m_currentCap && !removed; i++) {
            if (m_currentTable[i] == aPerson) {
                m_currentTable[i] = DELETED;
                m_currNumDeleted++;
                removed = true;
            }
        }

        // try to remove from old table if old table exists
        if (m_oldTable != nullptr) {
            for (int i = 0; i < m_oldCap && !removed; i++) {
                if (m_oldTable[i] == aPerson) {
                    m_oldTable[i] = DELETED;
                    m_oldNumDeleted++;
                    removed = true;
                }
            }
        }
        rehash();
    }
    return removed;
}


// rehash()
// rehashes Cache to a larger array when load factor or ratio of deleted items grows too large
void Cache::rehash() {
    // rehash if load factor > 0.5 or deletedratio > 0.8
    if (lambda() > MAXLOAD || deletedRatio() > MAXDELETE) {
        // make the current table the old table
        m_oldTable = m_currentTable;
        m_oldCap = m_currentCap;
        m_oldSize = m_currentSize;
        m_oldNumDeleted = m_currNumDeleted;
        
        // create an empty current table
        m_currentCap = findNextPrime((m_currentSize - m_currNumDeleted) * 4);
        m_currentTable = new Person[m_currentCap];

        // fill current with empty objects
        for (int i = 0; i < m_currentCap; i++) {
            m_currentTable[i] = EMPTY;
        }
        m_currentSize = 0;
        m_currNumDeleted = 0;
        //dump();
    }

    // if there are things in the old table, move 25% of them to the current table
    if (keepMoving()) {
        int quarter = floor(m_oldCap / 4), startIndex = 0;
        bool foundStart = false;


        // find first valid index
        // do 25% starting from there
        for (int i = 0; i < m_oldCap && !foundStart; i++) {
            if (m_oldTable[i].getKey() != DELETEDKEY && m_oldTable[i].getKey() != EMPTYKEY) {
                startIndex = i;
                foundStart = true;
            }
        }
        
        for (int i = startIndex, count = 0; count < quarter && i < m_oldCap; i++) {
            if (m_oldTable[i].getKey() != DELETEDKEY && m_oldTable[i].getKey() != EMPTYKEY) {
                // delete 25% of contents from old table and reinsert to current table
                reinsert(m_oldTable[i]);
                m_oldTable[i] = DELETED;
                m_oldNumDeleted++;
                count++;
            }
        }
        // delete old table if it is empty
        tryDeleteOld();
    }
}


// reinsert(Person)
// helper object for rehash(), inserts Person object to current table
void Cache::reinsert(Person aPerson) {
    int insertIndex = m_hash(aPerson.getKey()) % m_currentCap, j = 0;
    bool inserted = false;

    // keep trying to insert until it goes in
    while (!inserted) {
        if (!isCollision(insertIndex)) {
            // insert and change insert flag
            m_currentTable[insertIndex] = aPerson;
            m_currentSize++;
            inserted = true;
            j=0;            
        } else {
            // quadratic probing for new insertion index
            insertIndex = probe(j, aPerson.getKey());
            j++;
        }
    }
}


// keepMoving()
// helper function for rehash(), flag for whether to continue moving from old table to current table
bool Cache::keepMoving() {
    bool keepMoving = false;

    // check if the old table if empty yet, return false if it is
    if (m_oldTable != nullptr) {
        for (int i = 0; i < m_oldCap && !keepMoving; i++) {
            if (m_oldTable[i].getKey() != DELETEDKEY && m_oldTable[i].getKey() != EMPTYKEY) {
                keepMoving = true;
            }
        }
    }
    return keepMoving;
} 


// tryDeleteOld()
// deletes old table if it is empty 
void Cache::tryDeleteOld() {
    if (m_oldTable != nullptr) {
        bool deleteOld = true;

        // check if old table is empty
        for (int i = 0; i < m_oldCap && deleteOld; i++) {
            if (m_oldTable[i].getKey() != EMPTYKEY && m_oldTable[i].getKey() != DELETEDKEY) {
                deleteOld = false;
            }
        }

        // if empty, delete it and reset member variables
        if (deleteOld) {
            m_oldSize = 0;
            m_oldNumDeleted = 0;
            m_oldCap = 0;
            delete [] m_oldTable;
            m_oldTable = nullptr;
        }
    }
}


// personExists(Person)
// returns whether a person exists already in the current or old table
bool Cache::personExists(Person aPerson) {
    bool exists = false;

    // check if Person exists in current table 
    for (int i = 0; i < m_currentCap && !exists; i++) {
        if (m_currentTable[i] == aPerson) {
            exists = true;
        }
    }

    // check if person exists in old table
    for (int i = 0; i < m_oldCap && !exists; i++) {
        if (m_oldTable[i] == aPerson) {
            exists = true;
        }
    }
    return exists;
}


// isValidPerson(Person)
// returns whether the Person passed has a valid ID
bool Cache::isValidPerson(Person aPerson) {
    int id = aPerson.getID();
    bool valid = false;

    // check if Person's ID is within acceptable range
    if (id >= MINID && id <= MAXID) {
        valid = true;
    }
    return valid;
}


// isCollision(int)
// returns whether there is an element at the passed index in the current table
bool Cache::isCollision(int aIndex) {
    bool collision = false;

    // check if there is a nondeleted nonempty Person at aIndex
    if (m_currentTable[aIndex].getID() >= MINID && m_currentTable[aIndex].getKey() != DELETEDKEY && m_currentTable[aIndex].getKey() != EMPTYKEY) {
        collision = true;
    }
    return collision;
}


// getPerson(string, int)
// returns Person in old or current table with passed Key and ID
// if the person does not exist, returns an empty Person object
Person Cache::getPerson(string aKey, int aId) const{
    Person checkPerson(aKey, aId), returnPerson = EMPTY;

    // search for person with aKey and aId in current table
    for (int i = 0; i < m_currentCap; i++) {
        if (m_currentTable[i] == checkPerson) {
            returnPerson = m_currentTable[i];
        }
    }

    // search for person with aKey and aId in old table
    if (m_oldTable != nullptr) {
        for (int i = 0; i < m_oldCap; i++) {
            if (m_oldTable[i] == checkPerson) {
                returnPerson = m_oldTable[i];
            }
        }
    }
    return returnPerson;
}


// probe(int, string)
// uses quadratic probing to handle collisions
// returns new index to insert at
int Cache::probe(int j, string aKey) {
    // quadratic probing equation
    return (((m_hash(aKey) % m_currentCap) + (j * j)) % m_currentCap);
}


// lambda()
// returns load factor of current table
float Cache::lambda() const{
    // load factor equation
    return (float(m_currentSize) / m_currentCap);
}


// deletedRatio()
// returns ratio of deleted to size in current table
float Cache::deletedRatio() const{
    // deleted to size ratio
    return (float(m_currNumDeleted) / m_currentSize);
}


// dump()
// dumps current and old table to console
void Cache::dump() const{
    cout << "Dump for the current table: " << endl;
    if (m_currentTable != nullptr)
        for (int i = 0; i < m_currentCap; i++) {
            cout << "[" << i << "] : " << m_currentTable[i] << endl;
        }
    cout << "Dump for the old table: " << endl;
    if (m_oldTable != nullptr)
        for (int i = 0; i < m_oldCap; i++) {
            cout << "[" << i << "] : " << m_oldTable[i] << endl;
        }
}


// isPrime(int)
// returns whether passed number is prime
bool Cache::isPrime(int aNumber) {
    bool result = true;

    for (int i = 2; i <= aNumber / 2; ++i) {
        if (aNumber % i == 0) {
            result = false;
            break;
        }
    }
    return result;
}


// findNextPrime(int)
// helper function for constructor
// returns first valid prime starting with number passed
int Cache::findNextPrime(int aCurrent) {
    //we always stay within the range [MINPRIME-MAXPRIME]
    //the smallest prime starts at MINPRIME
    if (aCurrent < MINPRIME) {
        aCurrent = MINPRIME-1;  
    } 
    for (int i=aCurrent; i<MAXPRIME; i++) { 
        for (int j=2; j*j<=i; j++) {
            if (i % j == 0) 
                break;
            else if (j+1 > sqrt(i) && i != aCurrent) {
                return i;
            }
        }
    }
    //if a user tries to go over MAXPRIME
    return MAXPRIME;
}


// operator<<(ostream&, const Person&)
// overloaded operator<< for Person object
ostream& operator<<(ostream& sout, const Person &person ) {
    if (!person.m_key.empty())
        sout << person.m_key << " (ID " << person.m_id << ")";
    else
        sout << "";
  return sout;
}


// operator==(const Person&, const Person&)
// overloaded operator== for 2 Person objects
bool operator==(const Person& lhs, const Person& rhs) {
    return ((lhs.m_key == rhs.m_key) && (lhs.m_id == rhs.m_id));
}
