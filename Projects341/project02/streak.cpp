// UMBC - CMSC 341 - Fall 2022 - Proj2
// Eric Ekey
// eekey1@gl.umbc.edu
#include "streak.h"

// Streak()
// Default constructor
Streak::Streak() {
    m_root = nullptr;
    m_numDead = 0;
}


//~Streak()
// Destructor
Streak::~Streak() {
    clear();
}


// insert(const Tiger& aTiger)
// Takes a Tiger object and inserts it in the Streak
void Streak::insert(const Tiger& aTiger) {
    // make a tiger to insert
    Tiger theTiger(aTiger.getID(), aTiger.getAge(), aTiger.getGender(), aTiger.getState());
    Tiger* saveRoot = m_root;

    // insert and update m_numDead if needed
    m_root = insert(theTiger, m_root);
    if (saveRoot == nullptr) {
        if (saveRoot != m_root) {
            if (theTiger.getState() == DEAD) {
                m_numDead++;
            }
        }
    }
}


// insert(Tiger t, Tiger* aParent)
// recursive helper for insert
Tiger* Streak::insert(Tiger t, Tiger* aParent) {
    if (aParent == nullptr) {
        // insert tiger
        Tiger* theTiger = new Tiger(t.getID(), t.getAge(), t.getGender(), t.getState());
        if (theTiger->getState() == DEAD) {
            m_numDead++;
        }
        return theTiger;
    } else if (t.getID() < aParent->getID()) {
        // look left
        aParent->setLeft(insert(t, aParent->getLeft()));
        updateHeight(aParent);
        return rebalance(aParent);
    } else if (t.getID() > aParent->getID()) {
        // look right
        aParent->setRight(insert(t, aParent->getRight()));
        updateHeight(aParent);
        return rebalance(aParent);
    } else {
        return aParent;
    }
}


// clear()
// clears the Streak object
void Streak::clear() {
    clear(m_root);
    m_root = nullptr;
    m_numDead = 0;
}


// clear(Tiger* aTiger)
// recursive helper for clear
void Streak::clear(Tiger* aTiger) {
    // post order deletion
    if (aTiger != nullptr) {
        clear(aTiger->m_left);
        clear(aTiger->m_right);
        delete aTiger;
        aTiger = nullptr;
    }
}


// remove(int aId)
// removes the Tiger with the given ID from the Streak
void Streak::remove(int aId) {
    if (!findTiger(aId)) {
        // tiger doesnt exist
        return;
    }

    if (m_root != nullptr) {
        // tiger exists
        Tiger* theTiger = getTiger(aId, m_root);

        if (theTiger->getState() == DEAD) {
            m_numDead--;
        }
        m_root = remove(*theTiger, m_root);
    }
}

// remove(Tiger& element, Tiger* aParent)
// recursive helper for remove
Tiger* Streak::remove(Tiger& element, Tiger* aParent) {
    Tiger *tmp;

    if (aParent == nullptr) {
        return aParent;
    } else if (element.getID() < aParent->getID()) {
        aParent->setLeft(remove(element, aParent->getLeft()));
    } else if (element.getID() > aParent->getID()) {
        aParent->setRight(remove(element, aParent->getRight()));
    } else if (aParent->getLeft() && aParent->getRight()) {
        // 2 children
        tmp = getMin(aParent->m_right);
        aParent->setID(tmp->getID());
        aParent->setRight(remove(*aParent, aParent->getRight()));
    } else {
        // 1 or no children
        tmp = aParent;
        if (aParent->getLeft() == nullptr) {
            aParent = aParent->getRight();
        } else if (aParent->getRight() == nullptr) {
            aParent = aParent->getLeft();
        }
        delete tmp;
        //tmp = nullptr;
    }

    // update height and rebalance if needed
    updateHeight(aParent);
    aParent = rebalance(aParent);
    return aParent;
}


// getMin(Tiger* aTiger)
// returns Tiger with lowest ID, helper for remove
Tiger* Streak::getMin(Tiger* aTiger){
    Tiger* curr = aTiger;

    // find and return tiger with lowest id
    while (curr->getLeft() != nullptr) {
        curr = curr->getLeft();
    }
    return curr;
}


// updateHeight(Tiger* aParent)
// update height of passed tiger after editing Streak
void Streak::updateHeight(Tiger* aParent) {
    int leftHeight = -1, rightHeight = -1;

    if (aParent != nullptr) {
        if (aParent->getLeft() != nullptr) {
            // get left height
            leftHeight = aParent->getLeft()->getHeight();
        }

        if (aParent->getRight() != nullptr) {
            // get right height
            rightHeight = aParent->getRight()->getHeight();
        }
        // update tiger height
        aParent->setHeight(1 + max(leftHeight, rightHeight));
    }
}


// checkImbalance(Tiger* aParent)
// return balance factor of apssed Tiger, helper for rebalance
int Streak::checkImbalance(Tiger* aParent) {
    int balanceFactor = -1, leftHeight = -1, rightHeight = -1;

    if (aParent != nullptr) {
        if (aParent->getLeft() != nullptr) {
            // get left height
            leftHeight = aParent->getLeft()->getHeight();
        }

        if (aParent->getRight() != nullptr) {
            // get right height
            rightHeight = aParent->getRight()->getHeight();
        }
        // calculate balance factor
        balanceFactor = leftHeight - rightHeight;
    }
    return balanceFactor;
}


// rebalance(Tiger* aParent)
// check passed Tiger to see if a rotation is needed, rebalance if needed
Tiger* Streak::rebalance(Tiger* aParent) {
    // check which type of rotation is needed, if any, and perform it
    if (checkImbalance(aParent) < -1 && checkImbalance(aParent->getRight()) <= 0){
        // left rotation needeed
        return leftRotation(aParent);
    } else if (checkImbalance(aParent) > 1 && checkImbalance(aParent->getLeft()) >= 0) {
        // right rotation needed
        return rightRotation(aParent);
    } else if (checkImbalance(aParent) < -1 && checkImbalance(aParent->getRight()) >= 0) {
        // double rotation RL needed
        aParent->setRight(rightRotation(aParent->getRight()));
        return leftRotation(aParent);
    } else if (checkImbalance(aParent) > 1 && checkImbalance(aParent->getLeft()) <= 0) {
        // double rotation LR needed
        aParent->setLeft(leftRotation(aParent->getLeft()));
        return rightRotation(aParent);
    } else {
        // no rotation needed
        return aParent;
    }
}


// dumpTree()
// print out Streak contents in order
void Streak::dumpTree() const{
    dump(m_root);
}


// dump(Tiger* aTiger)
// recursive helper for dumpTree
void Streak::dump(Tiger* aTiger) const{
    if (aTiger != nullptr){
        cout << "(";
        dump(aTiger->m_left);//first visit the left child
        cout << aTiger->m_id << ":" << aTiger->m_height;//second visit the node itself
        dump(aTiger->m_right);//third visit the right child
        cout << ")";
    }
}


// listTigers()
// print Tigers in Streak in order
void Streak::listTigers() const{
    inOrder(m_root);
}


// inOrder(Tiger* aParent)
// recursive helper for listTigers
void Streak::inOrder(Tiger* aParent) const{
    // inOrder traveral to display
    if (aParent != nullptr) {
        inOrder(aParent->getLeft());
        printf("%d:%s:%s:%s\n",
            aParent->getID(), aParent->getAgeStr().c_str(), aParent->getGenderStr().c_str(),
            aParent->getStateStr().c_str());
        inOrder(aParent->getRight());
    }
}


// setState(int aId, STATE aState)
// change state of Tiger in Streak with passed ID to the passed STATE
bool Streak::setState(int aId, STATE aState) {
    if (m_root == nullptr) {
        // empty streak
        return false;
    }

    Tiger* theTiger = getTiger(aId, m_root);
    STATE orgState = theTiger->getState();

    if (theTiger != nullptr) {
        // tiger exists
        theTiger->setState(aState);
        // update m_numDead if needed
        if (orgState == DEAD && theTiger->getState() != DEAD) {
            m_numDead--;
        } else if (orgState != DEAD && theTiger->getState() == DEAD) {
            m_numDead++;
        }
        return true;
    } else {
        // tiger with aId does not exist
        return false;
    }
}


// removeDead()
// remove all Tigers with state DEAD from Streak
void Streak::removeDead() {
    if (m_numDead != 0) {
        int dead[countTigers(m_root)];

        // populate an array with all Tigers
        TreetoArray(dead, m_root);
        
        // remove the ones that are dead
        for (int id : dead) {
            if (getTiger(id, m_root)->getState() == DEAD) {
                remove(id);
            }
        }
        m_numDead = 0;
    }

}


// TreetoArray(int dead[], Tiger* aParent)
// recursive helper for removeDead
void Streak::TreetoArray(int dead[], Tiger* aParent) {
    // put contents of tree into array
    if (aParent != nullptr) {
        shiftArray(dead, countTigers(m_root));
        dead[0] = aParent->getID();
        TreetoArray(dead, aParent->getLeft());
        TreetoArray(dead, aParent->getRight());
    }
}


// shiftArray(int array[], int size)
// helper for TreetoArray
void Streak::shiftArray(int array[], int size) {
    // shift array elements one to right
    for (int i = size; i > 0; i--) {
        array[i] = array[i-1];
    }
}

// findTiger(int aId)
// returns whether a Tiger with passed ID exists in Streak
bool Streak::findTiger(int aId) const{
    return bool(getTiger(aId, m_root));
}


// countTigerCubs()
// returns number of Tigers in Streak with state CUB
int Streak::countTigerCubs() const{
    return countTigerCubs(m_root);
}


// countTigerCubs(Tiger* aParent)
// recursive helper for countTigerCubs
int Streak::countTigerCubs(Tiger* aParent) const {
    if (aParent == nullptr) {
        // base case
        return 0;
    } else if (aParent->getAge() == CUB) {
        // cub found
        return (1 + countTigerCubs(aParent->getLeft())
        + countTigerCubs(aParent->getRight()));
    } else if (aParent->getAge() != CUB) {
        // cub not found
        return (countTigerCubs(aParent->getLeft())
                + countTigerCubs(aParent->getRight()));
    } else {
        // precautionary
        return 0;
    }
}


// countTigers(Tiger* aParent)
// returns number of Tigers in Streak
int Streak::countTigers(Tiger* aParent) {
    if (aParent == nullptr) {
        // base case
        return 0;
    } else {
        // cub found
        return (1 + countTigers(aParent->getLeft())
        + countTigers(aParent->getRight()));
    }
}


// getTiger(int aId, Tiger* aParent)
// recursively returns Tiger with passed ID
Tiger* Streak::getTiger(int aId, Tiger* aParent) const{
    if (aParent == nullptr) {
        return aParent;
    } else if (aId < aParent->getID()) {
        // look to the left
        return getTiger(aId, aParent->getLeft());
    } else if (aId > aParent->getID()) {
        // look to the right
        return getTiger(aId, aParent->getRight());
    } else {
        // found the id
        return aParent;
    }
}


// leftRotation(Tiger* aParent)
// performs a left rotation on the Streak
Tiger* Streak::leftRotation(Tiger* aParent) {
    Tiger* tmp = aParent;
    Tiger* tmpRight = tmp->getRight();

    tmp->setRight(tmpRight->getLeft());
    tmpRight->setLeft(tmp);
    updateHeight(tmp);
    updateHeight(tmpRight);

    return tmpRight;
}


// rightRotation(Tiger* aParent)
// performs a right rotation on the Streak
Tiger* Streak::rightRotation(Tiger* aParent) {
    Tiger* tmp = aParent;
    Tiger* tmpLeft = tmp->getLeft();

    tmp->setLeft(tmpLeft->getRight());
    tmpLeft->setRight(tmp);
    updateHeight(tmp);
    updateHeight(tmpLeft);

    return tmpLeft;
}


// testProperty(Tiger* aParent)
// helper for testing, checks if bst property preserved
bool Streak::testProperty(Tiger* aParent) {
    if (aParent != nullptr) {
        // look left
        if (aParent->getLeft() != nullptr) {
            if (aParent->getLeft()->getID() > aParent->getID()) {
                // m_left id greater than parent
                return false;
            } else {
                // m_left less than parent
                return testProperty(aParent->getLeft());            
            }
        }

        // look right
        if (aParent->getRight() != nullptr) {
            if (aParent->getRight()->getID() < aParent->getID()) {
                // m_right id less than parent
                return false;
            } else {
                // m_right greater than parent
                return testProperty(aParent->getRight());                
            }
        }
    }
    return true;
}


// verifyBalance(Tiger* aParent)
// helper for testing, checks if balance property preserved
bool Streak::verifyBalance(Tiger* aParent) {
    if (aParent != nullptr) {
        // look left
        if (aParent->getLeft() != nullptr) {
            if (aParent->getLeft()->getHeight() > aParent->getHeight()-1) {
                // heights differ too much, imbalanced
                return false;
            } else {
                // heights balanced
                return testProperty(aParent->getLeft());
            }
        }

        // look right
        if (aParent->getRight() != nullptr) {
            if (aParent->getRight()->getHeight() > aParent->getHeight()-1) {
                // heights differ too much, imbalanced
                return false;
            } else {
                // heights balanced
                return testProperty(aParent->getRight());
            }
        }
    }
    return true;
}


// fullCheckBalance(Tiger* aParent)
// helper for testing, verifies balance factor of all nodes
bool Streak::fullCheckBalance(Tiger* aParent) {
    if (aParent != nullptr) {
        // look left
        if (aParent->getLeft() != nullptr) {
            if (abs(checkImbalance(aParent->getLeft())) > 1) {
                // absolute value of balance factor too big
                return false;
            } else {
                // absolute value of balance factor within acceptable range
                return fullCheckBalance(aParent->getLeft());
            }
        }

        // look right
        if (aParent->getRight() != nullptr) {
            if (abs(checkImbalance(aParent->getRight())) > 1) {
                // absolute value of balance factor too big
                return false;
            } else {
                // absolute value of balance factor within acceptable range
                return fullCheckBalance(aParent->getRight());
            }
        }
    }
    return true;
}