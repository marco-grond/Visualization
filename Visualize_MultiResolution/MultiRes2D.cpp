#include "headers/MultiRes2D.h"

using namespace std;

// Default constructor
MultiRes2D::MultiRes2D(bool debug) {
    // Set debugging flag
    if (debug) {
        cout << "Initialized empty object." << endl;
        this->debug = true;
    } else {
        this->debug = false;
    }

    // Initialize decomposition trackers
    rowDecomp = 0;
    colDecomp = 0;
}

// Constructor with vector data
MultiRes2D::MultiRes2D(vector< vector<double> > new_data, bool debug) {
    // Copy values from supplied vector into new vector
    for (int i = 0; i < new_data.size(); i++) {
        vector<double> col;
        for (int j = 0; j < new_data[i].size(); j++) {
            col.push_back(new_data[i][j]);
        }
        currentData.push_back(col);
        previousData.push_back(col);
    }

    // Set debugging flag
    if (debug) {
        cout << "Initialized object with 2D vector." << endl;
        this->debug = true;
    } else {
        this->debug = false;
    }

    // Initialize decomposition trackers
    rowDecomp = 0;
    colDecomp = 0;
}

// Constructor with width and height
MultiRes2D::MultiRes2D(int width, int height, bool debug) {
    // Create empty vector with the specified dimensions
    for (int i = 0; i < width; i++) {
        vector<double> col;
        for (int j = 0; j < height; j++) {
            col.push_back(0.0);
        }
        currentData.push_back(col);
        previousData.push_back(col);
    }
        
    // Setting debugging flag
    if (debug) {
        cout << "Initialized object with empty 2D vector" << endl;
        this->debug = true;
    } else {
        this->debug = false;
    }

    // Initialize decomposition trackers
    rowDecomp = 0;
    colDecomp = 0;
}
    

// Returns the number of columns in the data
int MultiRes2D::getWidth() {
    return currentData.size();
}

// Return the number of rows in the data
int MultiRes2D::getHeight() {
    if (currentData.size() == 0) {
        return 0;
    } else {
        return currentData[0].size();
    }
}

/*
* Overwrites the value at the specified location in the current vector. If the location does not exist, nothing is done
*/
void MultiRes2D::setCurrentValue(int col, int row, double val) {
    // Check to see if the specified location exists
    if (col >= currentData.size()) {
        if (debug) {
            cout << "Specified column outside of vector." << endl;
        }
        return;
    } else if (row >= currentData[col].size()) {
        if (debug) {
            cout << "Specified row outside of vector." << endl;
        }
        return;
    }

    // Set the value of the specified location
    currentData[col][row] = val;
    if (rowDecomp == 0 && colDecomp == 0) {
        previousData[col][row] = val;
    }
    if (debug) {
        cout << "Set (" << col << ", " << row << ") to " << val << endl;
    }
}

/*
* Overwrites the value at the specified location in the current vector. If the location does not exist, nothing is done
*/
void MultiRes2D::setPreviousValue(int col, int row, double val) {
    // Check to see if the specified location exists
    if (col >= previousData.size()) {
        if (debug) {
            cout << "Specified column outside of vector." << endl;
        }
        return;
    } else if (row >= previousData[col].size()) {
        if (debug) {
            cout << "Specified row outside of vector." << endl;
        }
        return;
    }

    // Set the value of the specified location
    previousData[col][row] = val;
    if (rowDecomp == 0 && colDecomp == 0) {
        currentData[col][row] = val;
    }
    if (debug) {
        cout << "Set (" << col << ", " << row << ") to " << val << endl;
    }
}

/**
* Adds an empty row onto the bottom of the vector
*/
void MultiRes2D::addRow() {
    // Check to see if the vector can be altered
    if (rowDecomp != 0 || colDecomp != 0) {
        return;
    }

    // Check if the vector is empty
    if (currentData.size() <= 0) {
        vector<double> hold;
        hold.push_back(0);
        currentData.push_back(hold);
        previousData = currentData;
        return;
    }

    // Add a zero onto every column
    for (int i = 0; i < currentData.size(); i++) {
        currentData[i].push_back(0);
    }
    previousData = currentData;
}

/**
* Adds an empty column onto the end of the vector
*/
void MultiRes2D::addColumn() {
    // Check to see if the vector can be altered
    if (rowDecomp != 0 || colDecomp != 0) {
        return;
    }

    // Check if the vector is empty
    if (currentData.size() <= 0) {
        vector<double> hold;
        hold.push_back(0);
        currentData.push_back(hold);
        previousData = currentData;
        return;
    }

    // Create a vector with the same length as the other columns to add
    vector<double> hold;
    for (int i = 0; i < currentData[0].size(); i++) {
        hold.push_back(0);
    }
    currentData.push_back(hold);
    previousData = currentData;
}

/**
* Removes the last row from the vector
*/
void MultiRes2D::deleteRow() {
    // Check to see if the vector can be altered
    if (rowDecomp != 0 || colDecomp != 0) {
        return;
    }

    // Check if the vector is empty
    if (currentData.size() <= 0) {
        return;
    }

    // Delete the last row from the vector
    for (int i = 0; i < currentData.size(); i++) {
        if (currentData[i].size() > 0) {
            currentData[i].pop_back();
        }
    }

    if (currentData[0].size() <= 0) {
        currentData.clear();
    }
    previousData = currentData;
}

/**
* Removes the last column from the current vector
*/
void MultiRes2D::deleteColumn() {
    // Check to see if the vector can be altered
    if (rowDecomp != 0 || colDecomp != 0) {
        return;
    }

    // Check if the vector is empty
    if (currentData.size() <= 0) {
        return;
    }

    // Delete the last column from the vector
    currentData.pop_back();
    previousData = currentData;
}


/**
* Return whether or not any decompositions currently exist
*/
bool MultiRes2D::noDecomp() {
    return (rowDecomp == 0 && colDecomp == 0);
}

/**
* Returns the current data
*/
vector< vector<double> > MultiRes2D::getCurrent() {
    return currentData;
}

/**
* Returns the previous data
*/
vector< vector<double> > MultiRes2D::getPrevious() {
    return previousData;
}

/**
* Returns the current row decomposition level
*/
int MultiRes2D::getRowDecomp() {
    return rowDecomp;
}

/**
* Returns the current column decomposition level
*/
int MultiRes2D::getColDecomp() {
    return colDecomp;
}

int MultiRes2D::mod(int value1, int value2) {
    int hold = value1 % value2;
    if (hold < 0) {
        hold += value2;
    }
    return hold;
}

bool MultiRes2D::increaseRows(int numRows) {
    // Check to see if the vector size should be increased
    if (numRows % 2 == 1) {
        if (debug) {
            cout << "Adding additional row..." << endl;
            this->printCurrent();
            cout << endl;
        }
        for (int i = 0; i < currentData.size(); i++) {
            currentData[i].insert(currentData[i].begin()+numRows, currentData[i][numRows-1]);
        }
        if (debug) {
            cout << "Row added:" << endl;
            this->printCurrent();
            cout << "New number of rows to be used: " << (numRows+1) << endl << endl;
        }
        return true;
    }
    return false;
}

bool MultiRes2D::increaseCols(int numCols) {
    // Check to see if the vector size should be increased
    if (numCols % 2 == 1) {
        if (debug) {
            cout << "Adding additional column..." << endl;
            this->printCurrent();
            cout << endl;
        }
        currentData.insert(currentData.begin()+numCols, currentData[numCols-1]);
        if (debug) {
            cout << "Column added:" << endl;
            this->printCurrent();
            cout << "New number of columns to be used: " << numCols+1 << endl << endl;
        }
        return true;
    }
    return false;
}

// Prints the current vector data to console
void MultiRes2D::printCurrent() {
    if (currentData.size() >= 1) {
        for (int j = 0; j < currentData[0].size(); j++) {
            for (int i = 0; i < currentData.size(); i++) {
                cout << currentData[i][j] << "\t";
            }
            cout << endl;
        }
    }
}

// Prints the previous vector data to console
void MultiRes2D::printPrevious() {
    if (previousData.size() >= 1) {
        for (int j = 0; j < previousData[0].size(); j++) {
            for (int i = 0; i < previousData.size(); i++) {
                cout << previousData[i][j] << "\t";
            }
            cout << endl;
        }
    }
}

/**
* Function to apply the filters to the rows of only the data (no details)
*/
bool MultiRes2D::decompRowsHaar(bool partial) {
    // Set up struct to define decompostition
    decomp newDecomp;
    newDecomp.partial = partial;
    newDecomp.added = false;
    newDecomp.degree = 0;
    newDecomp.rowCol = 'R';
        
    //Determine the number of rows and columns that should be decomposed
    if (currentData.size() <= 0) {
        return false;
    }
    int numCols = currentData.size();
    int numRows = currentData[0].size();
    if (partial) {
        numCols = ceil(currentData.size() / (pow(2.0, colDecomp)));
        numRows = ceil(currentData[0].size() / (pow(2.0, rowDecomp)));
    }
    if (numRows < 2) {
        return false;
    }
    if (debug) {
        cout << numCols << " columns and " << numRows << " rows will be decomposed." << endl;
    }

    // Check to see if the vector size should be increased
    newDecomp.added = increaseRows(numRows);
    if (newDecomp.added) {
        numRows++;
    }

    // Copy data from current vector to previous vector
    previousData.clear();
    for (int i = 0; i < currentData.size(); i++) {
        previousData.push_back(currentData[i]);
    }

    // Compute coarse approximation for rows
    int pos;
    for (int i = 0; i < numCols; i++) {
        pos = 0;
        for (int j = 0; j <= numRows-2; j+=2) {
            currentData[i][pos] = 0.5*previousData[i][j] + 0.5*previousData[i][j+1];
            pos += 1;
        }
    }

    if (debug) {
        cout << "Computed coarse approximation" << endl << endl;
        this->printCurrent();
        cout << endl;
    }

    // Compute details for rows
    for (int i = 0; i < numCols; i++) {
        pos = numRows/2;
        for (int j = 0; j <= numRows-2; j+=2) {
            currentData[i][pos] = 0.5*previousData[i][j] - 0.5*previousData[i][j+1];
            pos+=1;
        }
    }

    if (debug) {
        cout << "Computed details" << endl << endl;
        this->printCurrent();
        cout << endl;
    }

    // Update variables to keep track of decompositions
    this->rowDecomp += 1;
    this->decompList.push(newDecomp);
    return true;
}

/**
* Function to apply the filters to the columns of only the datapoints, excluding the details
*/
bool MultiRes2D::decompColsHaar(bool partial) {
    // Set up struct to define decompostition
    decomp newDecomp;
    newDecomp.partial = partial;
    newDecomp.added = false;
    newDecomp.degree = 0;
    newDecomp.rowCol = 'C';

    //Determine the number of rows and columns that should be decomposed
    if ((currentData.size() <= 1) || (currentData[0].size() <= 0)){
        return false;
    }
    int numCols = currentData.size();
    int numRows = currentData[0].size();
    if (partial) {
        numCols = ceil(currentData.size() / (pow(2.0, colDecomp)));
        numRows = ceil(currentData[0].size() / (pow(2.0, rowDecomp)));
    }
    if (numCols < 2) {
        return false;
    }
    if (debug) {
        cout << numCols << " columns and " << numRows << " rows will be decomposed." << endl;
    }

    // Check to see if the vector size should be increased
    newDecomp.added = increaseCols(numCols);
    if (newDecomp.added) {
        numCols++;
    }

    // Copy data from current vector to previous vector
    previousData.clear();
    for (int i = 0; i < currentData.size(); i++) {
        previousData.push_back(currentData[i]);
    }

    // Compute coarse approximation for columns
    int pos;
    for (int j = 0; j < numRows; j++) {
        pos = 0;
        for (int i = 0; i <= numCols-2; i+=2) {
            currentData[pos][j] = 0.5*previousData[i][j] + 0.5*previousData[i+1][j];
            pos += 1;
        }
    }

    if (debug) {
        cout << "Computed coarse approximation" << endl << endl;
        this->printCurrent();
        cout << endl;
    }

    // Compute details for columns
    for (int j = 0; j < numRows; j++) {
        pos = numCols/2;
        for (int i = 0; i <= numCols-2; i+=2) {
            currentData[pos][j] = 0.5*previousData[i][j] - 0.5*previousData[i+1][j];
            pos+=1;
        }
    }

    if (debug) {
        cout << "Computed details" << endl << endl;
        this->printCurrent();
        cout << endl;
    }

    this->colDecomp += 1;
    decompList.push(newDecomp);
    return true;
}

bool MultiRes2D::decompRowsChaikin(bool partial) {
    // Set up struct to define decompostition
    decomp newDecomp;
    newDecomp.partial = partial;
    newDecomp.added = false;
    newDecomp.degree = 2;
    newDecomp.rowCol = 'R';

    //Determine the number of rows and columns that should be decomposed
    if ((currentData.size() <= 0) || (currentData[0].size() < 3)){
        return false;
    }
    int numCols = currentData.size();
    int numRows = currentData[0].size();
    if (partial) {
        numCols = ceil(currentData.size() / (pow(2.0, colDecomp)));
        numRows = ceil(currentData[0].size() / (pow(2.0, rowDecomp)));
    }
    if (numRows < 3) {
        return false;
    }
    if (debug) {
        cout << numCols << " columns and " << numRows << " rows will be decomposed." << endl;
    }

    // Check to see if a new row should be added to the 2D vector
    newDecomp.added = increaseRows(numRows);
    if (newDecomp.added) {
        numRows++;
    }

    // Copy data from current vector to previous vector
    previousData.clear();
    for (int i = 0; i < currentData.size(); i++) {
        previousData.push_back(currentData[i]);
    }

    // Compute coarse approximation for rows
    int pos;
    for (int i = 0; i < numCols; i++) {
        currentData[i][0] = -0.25*previousData[i][numRows-2] + 0.75*previousData[i][numRows-1] + 0.75 *previousData[i][0] -0.25*previousData[i][1];
        pos = 1;
        for (int j = 2; j <= numRows-2; j+=2) {
            currentData[i][pos] = -0.25*previousData[i][j-2] + 0.75*previousData[i][j-1] + 0.75 *previousData[i][j] -0.25*previousData[i][j+1];
            pos += 1;
        }
    }
    if (debug) {
        cout << "Computed coarse approximation" << endl << endl;
        this->printCurrent();
        cout << endl;
    }

    // Compute details for rows
    for (int i = 0; i < numCols; i++) {
        currentData[i][numRows/2] = 0.25*previousData[i][numRows-2] - 0.75*previousData[i][numRows-1] + 0.75*previousData[i][0] - 0.25*previousData[i][1];
        pos = numRows/2+1;
        for (int j = 2; j <= numRows-2; j+=2) {
            currentData[i][pos] = 0.25*previousData[i][j-2] - 0.75*previousData[i][j-1] + 0.75*previousData[i][j] - 0.25*previousData[i][j+1];
            pos+=1;
        }
    }
    if (debug) {
        cout << "Computed details" << endl << endl;
        this->printCurrent();
        cout << endl;
    }

    // Update variables to keep track of decompositions
    this->rowDecomp += 1;
    this->decompList.push(newDecomp);
    return true;
}

bool MultiRes2D::decompColsChaikin(bool partial) {
    // Set up struct to define decompostition
    decomp newDecomp;
    newDecomp.partial = partial;
    newDecomp.added = false;
    newDecomp.degree = 2;
    newDecomp.rowCol = 'C';

    //Determine the number of rows and columns that should be decomposed
    if ((currentData.size() <= 3) || (currentData[0].size() <= 0)){
        return false;
    }
    int numCols = currentData.size();
    int numRows = currentData[0].size();
    if (partial) {
        numCols = ceil(currentData.size() / (pow(2.0, colDecomp)));
        numRows = ceil(currentData[0].size() / (pow(2.0, rowDecomp)));
    }
    if (numCols < 3) {
        return false;
    }
    if (debug) {
        cout << numCols << " columns and " << numRows << " rows will be decomposed." << endl;
    }

    // Check to see if the vector size should be increased
    newDecomp.added = increaseCols(numCols);
    if (newDecomp.added) {
        numCols++;
    }

    // Copy data from current vector to previous vector
    previousData.clear();
    for (int i = 0; i < currentData.size(); i++) {
        previousData.push_back(currentData[i]);
    }

    // Compute coarse approximation for columns
    int pos;
    for (int j = 0; j < numRows; j++) {
        currentData[0][j] = -0.25*previousData[numCols-2][j] + 0.75*previousData[numCols-1][j] + 0.75 *previousData[0][j] -0.25*previousData[1][j];
        pos = 1;
        for (int i = 2; i <= numCols-2; i+=2) {
            currentData[pos][j] = -0.25*previousData[i-2][j] + 0.75*previousData[i-1][j] + 0.75 *previousData[i][j] -0.25*previousData[i+1][j];
            pos += 1;
        }
    }
    if (debug) {
        cout << "Computed coarse approximation" << endl << endl;
        this->printCurrent();
        cout << endl;
    }

    // Compute details for columns
    for (int j = 0; j < numRows; j++) {
        currentData[numCols/2][j] = 0.25*previousData[numCols-2][j] - 0.75*previousData[numCols-1][j] + 0.75*previousData[0][j] - 0.25*previousData[1][j];
        pos = numCols/2+1;
        for (int i = 2; i <= numCols-2; i+=2) {
            currentData[pos][j] = 0.25*previousData[i-2][j] - 0.75*previousData[i-1][j] + 0.75*previousData[i][j] - 0.25*previousData[i+1][j];
            pos+=1;
        }
    }
    if (debug) {
        cout << "Computed details" << endl << endl;
        this->printCurrent();
        cout << endl;
    }

    this->colDecomp += 1;
    decompList.push(newDecomp);
    return true;
}

bool MultiRes2D::decompRowsCubic(bool partial) {
    // Set up struct to define decompostition
    decomp newDecomp;
    newDecomp.partial = partial;
    newDecomp.added = false;
    newDecomp.degree = 3;
    newDecomp.rowCol = 'R';

    //Determine the number of rows and columns that should be decomposed
    if ((currentData.size() <= 0) || (currentData[0].size() < 7)){
        return false;
    }
    int numCols = currentData.size();
    int numRows = currentData[0].size();
    if (partial) {
        numCols = ceil(currentData.size() / (pow(2.0, colDecomp)));
        numRows = ceil(currentData[0].size() / (pow(2.0, rowDecomp)));
    }
    if (numRows < 7) {
        return false;
    }
    if (debug) {
        cout << numCols << " columns and " << numRows << " rows will be decomposed." << endl;
    }

    // Check to see if a new row should be added to the 2D vector
    newDecomp.added = increaseRows(numRows);
    if (newDecomp.added) {
        numRows++;
    }

    // Copy data from current vector to previous vector
    previousData.clear();
    for (int i = 0; i < currentData.size(); i++) {
        previousData.push_back(currentData[i]);
    }

    // Compute coarse approximation for rows
    int pos;
    for (int i = 0; i < numCols; i++) {
        currentData[i][0] = 0.125*previousData[i][numRows-4] - 0.5*previousData[i][numRows-3] + 0.375*previousData[i][numRows-2] + previousData[i][numRows-1] + \
                            0.375*previousData[i][0] -0.5*previousData[i][1] + 0.125*previousData[i][2];
        currentData[i][1] = 0.125*previousData[i][numRows-2] - 0.5*previousData[i][numRows-1] + 0.375*previousData[i][0] + previousData[i][1] + \
                            0.375*previousData[i][2] -0.5*previousData[i][3] + 0.125*previousData[i][4];
        pos = 2;
        for (int j = 3; j <= numRows-5; j+=2) {
            currentData[i][pos] = 0.125*previousData[i][j-3] - 0.5*previousData[i][j-2] + 0.375*previousData[i][j-1] + previousData[i][j] + \
                                  0.375*previousData[i][j+1] -0.5*previousData[i][j+2] + 0.125*previousData[i][j+3];
            pos += 1;
        }
        currentData[i][pos] = 0.125*previousData[i][numRows-6] - 0.5*previousData[i][numRows-5] + 0.375*previousData[i][numRows-4] + previousData[i][numRows-3] + \
                              0.375*previousData[i][numRows-2] -0.5*previousData[i][numRows-1] + 0.125*previousData[i][0];
    }
    if (debug) {
        cout << "Computed coarse approximation" << endl << endl;
        this->printCurrent();
        cout << endl;
    }

    // Compute details for rows
    for (int i = 0; i < numCols; i++) {
        currentData[i][numRows/2] = -0.125*previousData[i][numRows-2] + 0.5*previousData[i][numRows-1] - 0.75*previousData[i][0] + 0.5*previousData[i][1] - 0.125*previousData[i][2];
        pos = numRows/2+1;
        for (int j = 2; j <= numRows-4; j+=2) {
            currentData[i][pos] = -0.125*previousData[i][j-2] + 0.5*previousData[i][j-1] - 0.75*previousData[i][j] + 0.5*previousData[i][j+1] - 0.125*previousData[i][j+2];
            pos+=1;
        }
        currentData[i][pos] = -0.125*previousData[i][numRows-4] + 0.5*previousData[i][numRows-3] - 0.75*previousData[i][numRows-2] + 0.5*previousData[i][numRows-1] - 0.125*previousData[i][0];
    }
    if (debug) {
        cout << "Computed details" << endl << endl;
        this->printCurrent();
        cout << endl;
    }

    // Update variables to keep track of decompositions
    this->rowDecomp += 1;
    this->decompList.push(newDecomp);
    return true;
}

bool MultiRes2D::decompColsCubic(bool partial) {
    // Set up struct to define decompostition
    decomp newDecomp;
    newDecomp.partial = partial;
    newDecomp.added = false;
    newDecomp.degree = 3;
    newDecomp.rowCol = 'C';

    //Determine the number of rows and columns that should be decomposed
    if ((currentData.size() < 7) || (currentData[0].size() < 1)){
        return false;
    }
    int numCols = currentData.size();
    int numRows = currentData[0].size();
    if (partial) {
        numCols = ceil(currentData.size() / (pow(2.0, colDecomp)));
        numRows = ceil(currentData[0].size() / (pow(2.0, rowDecomp)));
    }
    if (numCols < 7) {
        return false;
    }
    if (debug) {
        cout << numCols << " columns and " << numRows << " rows will be decomposed." << endl;
    }

    // Check to see if a new column should be added to the 2D vector
    newDecomp.added = increaseCols(numCols);
    if (newDecomp.added) {
        numCols++;
    }

    // Copy data from current vector to previous vector
    previousData.clear();
    for (int i = 0; i < currentData.size(); i++) {
        previousData.push_back(currentData[i]);
    }

    // Compute coarse approximation for columns
    int pos;
    for (int j = 0; j < numRows; j++) {
        currentData[0][j] = 0.125*previousData[numCols-4][j] - 0.5*previousData[numCols-3][j] + 0.375*previousData[numCols-2][j] + previousData[numCols-1][j] + \
                            0.375*previousData[0][j] - 0.5*previousData[1][j] + 0.125*previousData[2][j];
        currentData[1][j] = 0.125*previousData[numCols-2][j] - 0.5*previousData[numCols-1][j] + 0.375*previousData[0][j] + previousData[1][j] + \
                            0.375*previousData[2][j] - 0.5*previousData[3][j] + 0.125*previousData[4][j];
        pos = 2;
        for (int i = 3; i <= numCols-5; i+=2) {
            currentData[pos][j] = 0.125*previousData[i-3][j] - 0.5*previousData[i-2][j] + 0.375*previousData[i-1][j] + previousData[i][j] + \
                                  0.375*previousData[i+1][j] - 0.5*previousData[i+2][j] + 0.125*previousData[i+3][j];
            pos += 1;
        }
        currentData[pos][j] = 0.125*previousData[numCols-6][j] - 0.5*previousData[numCols-5][j] + 0.375*previousData[numCols-4][j] + previousData[numCols-3][j] + \
                              0.375*previousData[numCols-2][j] - 0.5*previousData[numCols-1][j] + 0.125*previousData[0][j];
    }
    if (debug) {
        cout << "Computed coarse approximation" << endl << endl;
        this->printCurrent();
        cout << endl;
    }

    // Compute details for columns
    for (int j = 0; j < numRows; j++) {
        currentData[numCols/2][j] = -0.125*previousData[numCols-2][j] + 0.5*previousData[numCols-1][j] - 0.75*previousData[0][j] + 0.5*previousData[1][j] - 0.125*previousData[2][j];
        pos = numCols/2+1;
        for (int i = 2; i <= numCols-4; i+=2) {
            currentData[pos][j] = -0.125*previousData[i-2][j] + 0.5*previousData[i-1][j] - 0.75*previousData[i][j] + 0.5*previousData[i+1][j] - 0.125*previousData[i+2][j];
            pos+=1;
        }
        currentData[pos][j] = -0.125*previousData[numCols-4][j] + 0.5*previousData[numCols-3][j] - 0.75*previousData[numCols-2][j] + 0.5*previousData[numCols-1][j] - 0.125*previousData[0][j];
    }
    if (debug) {
        cout << "Computed details" << endl << endl;
        this->printCurrent();
        cout << endl;
    }

    // Update variables to keep track of decomposition
    this->colDecomp += 1;
    decompList.push(newDecomp);
    return true;
}

int MultiRes2D::reconstruct() {
    // Check if the stack is empty
    if (decompList.size() <= 0) {
        return -1;
    }

    // Get the last decomposition performed
    decomp top = decompList.top();
    decompList.pop();
    if (debug) {
        cout << "Reconstructing with the following variables:" << endl;
        cout << "\tRow/Col: " << top.rowCol << endl;
        cout << "\tDegree : " << top.degree << endl;
        cout << "\tPartial: " << top.partial << endl;
        cout << "\tAdded  : " << top.added << endl << endl;
    }

    int retVal = 0;
    if (top.rowCol == 'R') {
        // Choose the correct row function corresponding to the degree
        if (top.degree == 0) {
            reconstRowsHaar(top.partial);
        } else if (top.degree == 2) {
            reconstRowsChaikin(top.partial);
        } else if (top.degree == 3) {
            reconstRowsCubic(top.partial);
        } else {
            cout << "Unable to reconstruct: Unknown degree for reconstruction" << endl;
            return -1;
        }

        // Check if a row should be removed
        if (top.added) {
            int location = ceil(currentData[0].size()/pow(2.0, (rowDecomp-1))) - 1;
            for (int i = 0; i < currentData.size(); i++) {
                currentData[i].erase(currentData[i].begin() + location);
            }
        }
        rowDecomp--;
        if (debug) {
            cout << "Reconstructed fine data for rows" << endl << endl;
            this->printCurrent();
            cout << endl;
        }
    } else if (top.rowCol == 'C') {
        retVal += 10;
        // Choose the correct column function corresponding to the degree
        if (top.degree == 0) {
            reconstColsHaar(top.partial);
        } else if (top.degree == 2) {
            reconstColsChaikin(top.partial);
        } else if (top.degree == 3) {
            reconstColsCubic(top.partial);
        } else {
            cout << "Unable to reconstruct: Unknown degree for reconstruction" << endl;
            return -1;
        }

        // Check if a column should be removed
        if (top.added) {
            int location = ceil(currentData.size()/pow(2.0, (colDecomp-1))) - 1;
            currentData.erase(currentData.begin() + location);
        }
        colDecomp--;
        if (debug) {
            cout << "Reconstructed fine data for columns" << endl << endl;
            this->printCurrent();
            cout << endl;
        }
    } else {
        cout << "Unable to reconstruct: Unknown row/column identifier" << endl;
        return false;
    }
    return (retVal + top.degree);
}

void MultiRes2D::reconstRowsHaar(bool partial) {
    // Check to see if the rows can be reconstructed
    if (rowDecomp <= 0) {
        return;
    }

    // Determine the number of rows and columns that should be reconstructed
    if (currentData.size() <= 0 || currentData[0].size() <= 0) {
        return;
    }
    int numCols = currentData.size();
    int numRows = currentData[0].size()/2;
    if (partial) {
        numCols = ceil(currentData.size() / (pow(2.0, colDecomp)));
        numRows = ceil(currentData[0].size() / (pow(2.0, rowDecomp)));
    }
    if (debug) {
        cout << numCols << " columns and " << numRows << " rows will be reconstructed." << endl;
    }

    // Copy data from current vector to previous vector
    previousData.clear();
    for (int i = 0; i < currentData.size(); i++) {
        previousData.push_back(currentData[i]);
    }

    // Reconstruct the rows of the current vector
    for (int i = 0; i < numCols; i++) {
        for (int j = 0; j < numRows; j++) {
            currentData[i][j*2] = previousData[i][j] + previousData[i][j+numRows];
            currentData[i][j*2+1] = previousData[i][j] - previousData[i][j+numRows];
        }
    }
}

void MultiRes2D::reconstColsHaar(bool partial) {
    // Check to see if the columns can be reconstructed
    if (colDecomp <= 0) {
        return;
    }

    // Determine the number of rows and columns that should be reconstructed
    if (currentData.size() <= 0 || currentData[0].size() <= 0) {
        return;
    }
    int numCols = currentData.size()/2;
    int numRows = currentData[0].size();
    if (partial) {
        numCols = ceil(currentData.size() / (pow(2.0, colDecomp)));
        numRows = ceil(currentData[0].size() / (pow(2.0, rowDecomp)));
    }
    if (debug) {
        cout << numCols << " columns and " << numRows << " rows will be reconstructed." << endl;
    }

    // Copy data from current vector to previous vector
    previousData.clear();
    for (int i = 0; i < currentData.size(); i++) {
        previousData.push_back(currentData[i]);
    }

    // Reconstruct the col of the current vector
    for (int j = 0; j < numRows; j++) {
        for (int i = 0; i < numCols; i++) {
            currentData[i*2][j] = previousData[i][j] + previousData[i+numCols][j];
            currentData[i*2+1][j] = previousData[i][j] - previousData[i+numCols][j];
        }
    }
}

void MultiRes2D::reconstRowsChaikin(bool partial) {
    // Check to see if the rows can be reconstructed
    if (rowDecomp <= 0) {
        return;
    }

    // Determine the number of rows and columns that should be reconstructed
    if (currentData.size() <= 0 || currentData[0].size() <= 0) {
        return;
    }
    int numCols = currentData.size();
    int numRows = currentData[0].size()/2;
    if (partial) {
        numCols = ceil(currentData.size() / (pow(2.0, colDecomp)));
        numRows = ceil(currentData[0].size() / (pow(2.0, rowDecomp)));
    }
    if (debug) {
        cout << numCols << " columns and " << numRows << " rows will be reconstructed." << endl;
    }

    // Copy data from current vector to previous vector
    previousData.clear();
    for (int i = 0; i < currentData.size(); i++) {
        previousData.push_back(currentData[i]);
    }

    // Reconstruct the rows of the current vector
    for (int i = 0; i < numCols; i++) {
        for (int j = 0; j < numRows-1; j++) {
            currentData[i][j*2] = 0.75*previousData[i][j] + 0.25*previousData[i][j+1] + 0.75*previousData[i][j+numRows] - 0.25*previousData[i][j+numRows+1];
            currentData[i][j*2+1] = 0.25*previousData[i][j] + 0.75*previousData[i][j+1] + 0.25*previousData[i][j+numRows] - 0.75*previousData[i][j+numRows+1];
        }
        currentData[i][(numRows-1)*2] = 0.75*previousData[i][numRows-1] + 0.25*previousData[i][0] + 0.75*previousData[i][numRows*2-1] - 0.25*previousData[i][numRows];
        currentData[i][(numRows-1)*2+1] = 0.25*previousData[i][numRows-1] + 0.75*previousData[i][0] + 0.25*previousData[i][numRows*2-1] - 0.75*previousData[i][numRows];
    }
}

void MultiRes2D::reconstColsChaikin(bool partial) {
    // Check to see if the columns can be reconstructed
    if (colDecomp <= 0) {
        return;
    }

    // Determine the number of rows and columns that should be reconstructed
    if (currentData.size() <= 0 || currentData[0].size() <= 0) {
        return;
    }
    int numCols = currentData.size()/2;
    int numRows = currentData[0].size();
    if (partial) {
        numCols = ceil(currentData.size() / (pow(2.0, colDecomp)));
        numRows = ceil(currentData[0].size() / (pow(2.0, rowDecomp)));
    }
    if (debug) {
        cout << numCols << " columns and " << numRows << " rows will be reconstructed." << endl;
    }

    // Copy data from current vector to previous vector
    previousData.clear();
    for (int i = 0; i < currentData.size(); i++) {
        previousData.push_back(currentData[i]);
    }

    // Reconstruct the col of the current vector
    for (int j = 0; j < numRows; j++) {
        for (int i = 0; i < numCols-1; i++) {
            currentData[i*2][j] = 0.75*previousData[i][j] + 0.25*previousData[i+1][j] + 0.75*previousData[i+numCols][j] - 0.25*previousData[i+numCols+1][j];
            currentData[i*2+1][j] = 0.25*previousData[i][j] + 0.75*previousData[i+1][j] + 0.25*previousData[i+numCols][j] - 0.75*previousData[i+numCols+1][j];
        }
        currentData[(numCols-1)*2][j] = 0.75*previousData[numCols-1][j] + 0.25*previousData[0][j] + 0.75*previousData[numCols*2-1][j] - 0.25*previousData[numCols][j];
        currentData[(numCols-1)*2+1][j] = 0.25*previousData[numCols-1][j] + 0.75*previousData[0][j] + 0.25*previousData[numCols*2-1][j] - 0.75*previousData[numCols][j];
    }
}

void MultiRes2D::reconstRowsCubic(bool partial) {
    // Check to see if the rows can be reconstructed
    if (rowDecomp <= 0) {
        return;
    }

    // Determine the number of rows and columns that should be reconstructed
    if (currentData.size() <= 0 || currentData[0].size() <= 0) {
        return;
    }
    int numCols = currentData.size();
    int numRows = currentData[0].size()/2;
    if (partial) {
        numCols = ceil(currentData.size() / (pow(2.0, colDecomp)));
        numRows = ceil(currentData[0].size() / (pow(2.0, rowDecomp)));
    }
    if (debug) {
        cout << numCols << " columns and " << numRows << " rows will be reconstructed." << endl;
    }

    // Copy data from current vector to previous vector
    previousData.clear();
    for (int i = 0; i < currentData.size(); i++) {
        previousData.push_back(currentData[i]);
    }

    // Reconstruct the rows of the current vector
    for (int i = 0; i < numCols; i++) {
        for (int j = 0; j < numRows; j++) {
            currentData[i][j*2] = 0.5*previousData[i][mod(j, numRows)] + 0.5*previousData[i][mod(j+1, numRows)] + 
                                  0.5*previousData[i][mod(j-1, numRows)+numRows] - previousData[i][mod(j, numRows)+numRows] + 0.5*previousData[i][mod(j+1, numRows)+numRows];
            currentData[i][j*2+1] = 0.125*previousData[i][mod(j, numRows)] + 0.75*previousData[i][mod(j+1, numRows)] + 0.125*previousData[i][mod(j+2, numRows)] + 
                                    0.125*previousData[i][mod(j-1, numRows)+numRows]  + 0.375*previousData[i][mod(j, numRows)+numRows] +
                                    0.375*previousData[i][mod(j+1, numRows)+numRows] + 0.125*previousData[i][mod(j+2, numRows)+numRows];
        }
    }
}

void MultiRes2D::reconstColsCubic(bool partial) {
    // Check to see if the columns can be reconstructed
    if (colDecomp <= 0) {
        return;
    }

    // Determine the number of rows and columns that should be reconstructed
    if (currentData.size() <= 0 || currentData[0].size() <= 0) {
        return;
    }
    int numCols = currentData.size()/2;
    int numRows = currentData[0].size();
    if (partial) {
        numCols = ceil(currentData.size() / (pow(2.0, colDecomp)));
        numRows = ceil(currentData[0].size() / (pow(2.0, rowDecomp)));
    }
    if (debug) {
        cout << numCols << " columns and " << numRows << " rows will be reconstructed." << endl;
    }

    // Copy data from current vector to previous vector
    previousData.clear();
    for (int i = 0; i < currentData.size(); i++) {
        previousData.push_back(currentData[i]);
    }

    // Reconstruct the col of the current vector
    for (int j = 0; j < numRows; j++) {
        for (int i = 0; i < numCols; i++) {
            currentData[i*2][j] = 0.5*previousData[mod(i, numCols)][j] + 0.5*previousData[mod(i+1, numCols)][j] + 
                                  0.5*previousData[mod(i-1, numCols) + numCols][j] -previousData[mod(i, numCols) + numCols][j] +0.5*previousData[mod(i+1, numCols) + numCols][j];
            currentData[i*2+1][j] = 0.125*previousData[mod(i, numCols)][j] + 0.75*previousData[mod(i+1, numCols)][j] +0.125*previousData[mod(i+2, numCols)][j] + 
                                    0.125*previousData[mod(i-1, numCols) + numCols][j] + 0.375*previousData[mod(i, numCols) + numCols][j] + 
                                    0.375*previousData[mod(i+1, numCols) + numCols][j] + 0.125*previousData[mod(i+2, numCols) + numCols][j];
        }
    }
}
