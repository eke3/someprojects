// UMBC - CMSC 341 - Fall 2022 - Proj3
// Eric Ekey
// eekey1@gl.umbc.edu
#include "iqueue.h"

// IQueue(prifn_t, HEAPTYPE)
// default constructor
IQueue::IQueue(prifn_t priFn, HEAPTYPE heapType) { 
    m_priorFunc = priFn;
    m_size = 0;
    m_heapType = heapType;
    m_heap = nullptr;
}


// ~IQueue()
// destructor
IQueue::~IQueue() {
    if (m_heap != nullptr) {
        clear();
    }
}


// clear()
// clears dynamically allocated memory
void IQueue::clear() {
    if (m_heap != nullptr) {
        clear(m_heap);
    }
    m_size = 0;
}


// clear(Node*)
// recursive helper for clear()
void IQueue::clear(Node* aParent) {
    if (aParent != nullptr) {
        clear(aParent->m_left);
        clear(aParent->m_right);
        delete aParent;
        aParent = nullptr;
    }
}


// IQueue(const IQueue&)
// copy constructor
IQueue::IQueue(const IQueue& rhs) {
    if (rhs.m_heap != nullptr) {
        m_heapType = rhs.m_heapType;
        m_priorFunc = rhs.m_priorFunc;
        m_size = rhs.m_size;
        m_heap = copyQueue(rhs.m_heap);
    } else {
        m_heap = nullptr;
        m_size = 0;
        m_heapType = rhs.m_heapType;
        m_priorFunc = rhs.m_priorFunc;
    }
}


// operator=(const IQueue&)
// assignment operator
IQueue& IQueue::operator=(const IQueue& rhs) {
    if (this != &rhs) {
        if (rhs.m_heap != nullptr) {
            clear();
            m_heapType = rhs.m_heapType;
            m_priorFunc = rhs.m_priorFunc;
            m_size = rhs.m_size;
            m_heap = copyQueue(rhs.m_heap);
        } else {
            clear();
            m_heapType = rhs.m_heapType;
            m_priorFunc = rhs.m_priorFunc;
            m_size = rhs.m_size;
        }
    }
    return *this;
}


// copyQueue(Node*)
// recursive helper for assignment operator and copy constructor
Node* IQueue::copyQueue(Node* aParent) {
    Node* newNode = nullptr;

    // preorder copy of tree
    if (aParent != nullptr) {
        newNode = new Node(aParent->getCrop());
        newNode->m_left = copyQueue(aParent->m_left);
        newNode->m_right = copyQueue(aParent->m_right);
    }

    return newNode;
}


// insertCrop(const Crop&)
// inserts a node holding a crop to the queue
void IQueue::insertCrop(const Crop& aCrop) {
    if (aCrop.getCropID() != DEFAULTCROPID) {
        Node* newCrop = new Node(aCrop);
        IQueue newQueue(m_priorFunc, m_heapType);
        
        // make new crop into a heap
        newQueue.m_heap = newCrop;
        newQueue.m_size = 1;

        // merge new heap into current
        mergeWithQueue(newQueue);
        newQueue.m_heap = nullptr;
    }
}


// mergeWithQueue(IQueue&)
// merges given queue with current queue
void IQueue::mergeWithQueue(IQueue& rhs) {
    // throw error for mismatched heaps
    if (m_heapType != rhs.m_heapType) {
        throw std::domain_error("Mismatched heap types"); 
    } else {
        int size = rhs.numCrops();
        if (m_heap != rhs.m_heap) {
            // check if minheap or maxheap and call proper function
            if (m_heapType == MAXHEAP) {
                m_heap = mergeMax(m_heap, rhs.m_heap);
            } else {
                m_heap = mergeMin(m_heap, rhs.m_heap);
            }
            rhs.m_heap = nullptr;
        }
        m_size = m_size + size;
    }
}


// mergeMax(Node*, Node*)
// recursive helper to merge 2 MAXHEAP queues
Node* IQueue::mergeMax(Node* aHeap, Node* aHeap2) const{
    // termination cases
    if (aHeap == nullptr) {
        return aHeap2;
    }
    if (aHeap2 == nullptr) {
        return aHeap;
    }

    // preserve heap property
    if (m_priorFunc(aHeap->getCrop()) <= m_priorFunc(aHeap2->getCrop())) {
        swap(aHeap, aHeap2);
    }
    swap(aHeap->m_left, aHeap->m_right);
    aHeap->m_left = mergeMax(aHeap2, aHeap->m_left);

    return aHeap;
}


// mergeMin(Node*, Node*)
// recursive helper to merge 2 MINHEAP queues
Node* IQueue::mergeMin(Node* aHeap, Node* aHeap2) const{
    // termination cases
    if (aHeap == nullptr) {
        return aHeap2;
    }
    if (aHeap2 == nullptr) {
        return aHeap;
    }

    // preserve heap property
    if (m_priorFunc(aHeap->getCrop()) >= m_priorFunc(aHeap2->getCrop())) {
        swap(aHeap, aHeap2);
    }
    swap(aHeap->m_left, aHeap->m_right);
    aHeap->m_left = mergeMin(aHeap2, aHeap->m_left);

    return aHeap;
}


// getNextCrop()
// dequeues and returns highest priority crop
Crop IQueue::getNextCrop() {
    Node* leftHeap;
    Node* rightHeap;
    Crop theCrop;

    // throw error for empty queue
    if (m_heap == nullptr) {
        throw std::out_of_range("Queue is empty");
    } else {
        // get the highest priority node
        theCrop = m_heap->getCrop();
        leftHeap = m_heap->m_left;
        rightHeap = m_heap->m_right;
        delete m_heap;
        m_heap = leftHeap;

        // merge left and right subqueues of previous top node
        if (m_heapType == MAXHEAP) {
            m_heap = mergeMax(m_heap, rightHeap);
        } else {
            m_heap = mergeMin(m_heap, rightHeap);
        }

        m_size--;
        leftHeap = nullptr;
        rightHeap = nullptr;
    }

    return theCrop;
}


// setPriorityFn(prifn_t HEAPTYPE)
// sets new priority function and heaptype for queue and reorders contents to follow
void IQueue::setPriorityFn(prifn_t aPriFn, HEAPTYPE aHeapType) {
    m_priorFunc = aPriFn;
    m_heapType = aHeapType;

    // make new queue with opposite priFn
    if (m_heap != nullptr) {
        IQueue newQueue(aPriFn, aHeapType);
        int numcrops = numCrops();

        // insert from top of current one by one to new queue
        for (int i = 0; i < numcrops; i++) {
            newQueue.insertCrop(getNextCrop());
        }
        clear();
        m_size = newQueue.numCrops();

        // point current object to updated queue
        m_heap = newQueue.m_heap;
        newQueue.m_heap = nullptr;
    }
}


// printCropsQueue()
// preorder print of crop details at every node in queue
void IQueue::printCropsQueue() const {
    printf("Contents of the crops queue:\n");
    printCropsQueue(m_heap);
}


// printCropsQueue(Node*)
// recursive helper for printCropsQueue()
void IQueue::printCropsQueue(Node* aParent) const {
    // preorder print of queue
    if (aParent != nullptr) {
        cout << *aParent << "\n";
        printCropsQueue(aParent->m_left);
        printCropsQueue(aParent->m_right);
    }
}


// dump()
// dumps queue for viewing in tree viewer tool
void IQueue::dump() const
{
    if (m_size == 0) {
        cout << "Empty skew heap.\n" ;
    } else {
        dump(m_heap);
        cout << endl;
    }
}


// dump(Node*)
// recursive helper for dump()
void IQueue::dump(Node *pos) const {
    if ( pos ) {
        cout << "(";
        dump(pos->m_left);
        cout << m_priorFunc(pos->m_crop) << ":" << pos->m_crop.getCropID();
        dump(pos->m_right);
        cout << ")";
    }
}


// operator<<(ostream&, const Crop&)
// overloaded insertion operator for printing crops
ostream& operator<<(ostream& sout, const Crop& crop) {
    sout << "Crop ID: " << crop.getCropID() 
                << ", current temperature: " << crop.getTemperature()
                << ", current soil moisture: " << crop.getMoisture() << "%"
                << ", current time: " << crop.getTimeString()
                << ", plant type: " << crop.getTypeString();
    return sout;
}


// operator<<(ostream&, const Node&)
// overloaded insertion operator for printing nodes
ostream& operator<<(ostream& sout, const Node& node) {
    sout << node.getCrop();
    return sout;
}


// numCrops()
// returns number of crops in queue
int IQueue::numCrops() const {
    return m_size;
}


// getPriorityFn()
// returns priority function for queue
prifn_t IQueue::getPriorityFn() const {
    return m_priorFunc;
}


// getHeapType()
// returns heap type for queue
HEAPTYPE IQueue::getHeapType() const{
    return m_heapType;
}