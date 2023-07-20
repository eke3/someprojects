// UMBC - CMSC 341 - Fall 2022 - Proj0
// Eric Ekey
// eekey1@gl.umbc.edu

#include "art.h"

Art::Art(){
    m_numColumns = 0;
    m_numRows = 0;
    m_masterPiece = nullptr;
}

Art::Art(int aRows, int aColumns){
    if (aRows <= 0 || aColumns <= 0) {
        m_numColumns = 0;
        m_numRows = 0;
        m_masterPiece = nullptr;
    } else {
        m_numColumns = aColumns;
        m_numRows = aRows;

        m_masterPiece = new int *[aRows];
        for (int i = 0; i < m_numRows; i++) {
            m_masterPiece[i] = new int[aColumns];
        }
    }
}

Art::~Art(){
    if (m_masterPiece != nullptr) {
        for (int i = 0; i < m_numRows; i++) {
            delete [] m_masterPiece[i];
            m_masterPiece[i] = nullptr;
        }
        delete [] m_masterPiece;
        m_masterPiece = nullptr;
    }

    m_numColumns = 0;
    m_numRows = 0;
}

void Art::clear(){
    if (m_masterPiece != nullptr) {
        for (int i = 0; i < m_numRows; i++) {
            delete [] m_masterPiece[i];
            m_masterPiece[i] = nullptr;
        }
        delete [] m_masterPiece;
        m_masterPiece = nullptr;
    }

    m_numColumns = 0;
    m_numRows = 0;
}

void Art::create(int aSeed){
    if (m_masterPiece != nullptr) {
        Random colorCode(30, 37);
        colorCode.setSeed(aSeed);

        for (int i = 0; i < m_numRows; i++) {
            for (int j = 0; j < m_numColumns; j++) {
                m_masterPiece[i][j] = colorCode.getRandNum();
            }
        }
    }
}

void Art::dumpColors(string pixel){
    if (m_numRows > 0 && m_numColumns > 0 && m_masterPiece != nullptr){
        for (int i=1;i <= m_numRows;i++){
            for (int j=1;j<=m_numColumns;j++){
                cout << "\033[1;" << to_string(m_masterPiece[i-1][j-1]) << "m" << pixel << pixel << "\033[0m";
            }
            cout << endl;
        }
        cout << endl;
    }
}

void Art::dumpValues(){
    if (m_numRows > 0 && m_numColumns > 0 && m_masterPiece != nullptr){
        for (int i=1;i <= m_numRows;i++){
            for (int j=1;j<=m_numColumns;j++){
                cout << m_masterPiece[i-1][j-1] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
}

Art::Art(const Art& rhs){
    m_numRows = rhs.m_numRows;
    m_numColumns = rhs.m_numColumns;

    if (rhs.m_masterPiece != nullptr) {
        m_masterPiece = new int *[m_numRows];
        for (int i = 0; i < m_numRows; i++) {
            m_masterPiece[i] = new int[m_numColumns];
        }

        for (int i = 0; i < m_numRows; i++) {
            for (int j = 0; j < m_numColumns; j++) {
                m_masterPiece[i][j] = rhs.m_masterPiece[i][j];
            }
        }
    } else {
        m_masterPiece = nullptr;
    }
}

const Art& Art::operator=(const Art& rhs){
    if(this != &rhs) {

        // clear this object
        clear();
        m_numRows = rhs.m_numRows;
        m_numColumns = rhs.m_numColumns;

        // allocate new space
        if (rhs.m_masterPiece != nullptr) {
            m_masterPiece = new int *[rhs.m_numRows];
            for (int i = 0; i < rhs.m_numRows; i++) {
                m_masterPiece[i] = new int[rhs.m_numColumns];
            }

            // copy the data from rhs
            for (int i = 0; i < m_numRows; i++) {
                for (int j = 0; j < m_numColumns; j++) {
                    m_masterPiece[i][j] = rhs.m_masterPiece[i][j];
                }
            }
        } else {
            m_masterPiece = nullptr;
        }
    }
    return *this;
}

bool Art::appendToRight(const Art& rhs){
    if ((m_numRows == rhs.m_numRows) || !m_numRows || !rhs.m_numRows) {
        // calculate new size
        int newRows = m_numRows;
        int newColumns = m_numColumns + rhs.m_numColumns;

        // make a giant array to fit everything
        int ** newMasterpiece = new int*[newRows];

        for (int i = 0;i < newRows;i++) {
            newMasterpiece[i] = new int[newColumns];
        }

        if (m_numRows) {
            // populate the giant array with old stuff
            for (int i = 0; i < m_numRows; i++) {
                for (int j = 0; j < m_numColumns; j++) {
                    newMasterpiece[i][j] = m_masterPiece[i][j];
                }
            }
        }

        if (rhs.m_numRows) {
            // then add the new stuff
            for (int i = 0; i < newRows; i++) {
                for (int j = m_numColumns, k = 0; j < newColumns; j++,k++) {
                    newMasterpiece[i][j] = rhs.m_masterPiece[i][k];
                }
            }
        }

        // clear this object
        clear();

        // set member variables to match giant array
        m_numRows = newRows;
        m_numColumns = newColumns;
        m_masterPiece = newMasterpiece;

        // return true/false if operation is/isnt successful
        return true;
    }
    return false;
}

bool Art::appendToBottom(const Art& bottom){
    if ((m_numColumns == bottom.m_numColumns) || !m_numColumns || !bottom.m_numColumns) {
        // calculate new size
        int newRows = m_numRows + bottom.m_numRows;
        int newColumns = m_numColumns;

        // make a giant array to fit everything
        int ** newMasterpiece = new int*[newRows];

        for (int i = 0;i < newRows;i++) {
            newMasterpiece[i] = new int[newColumns];
        }

        if (m_numColumns) {
            // populate the giant array with old stuff
            for (int i = 0;i < m_numRows; i++) {
                for (int j = 0; j < m_numColumns; j++) {
                    newMasterpiece[i][j] = m_masterPiece[i][j];
                }
            }
        }

        if (bottom.m_numColumns) {
            // then add the new stuff
            for (int i = m_numRows, k = 0; i < newRows; i++, k++) {
                for (int j = 0; j < newColumns; j++) {
                    newMasterpiece[i][j] = bottom.m_masterPiece[k][j];
                }
            }
        }

        // clear this object
        clear();

        // set member variables to match giant array
        m_numRows = newRows;
        m_numColumns = newColumns;
        m_masterPiece = newMasterpiece;

        // return true/false if operation is/isnt successful
        return true;
    }
    return false;
}