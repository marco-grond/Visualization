#include "headers/MultiRes1D.h"

using namespace std;

/**
* Default constructor
*/
MultiRes1D::MultiRes1D(bool debug) {
    // Set debugging flag
    if (debug) {
        cout << "Initialized empty object." << endl;
        this->debug = true;
    } else {
        this->debug = false;
    }

    // Initialize decomposition trackers
    this->decompLevel = 0;
}

/**
* Constructor specifying the datapoints to be used
*/
MultiRes1D::MultiRes1D(vector<double> xData, vector<double> yData, bool debug) {
    // Set debugging flag
    if (debug) {
        cout << "Initialized object with given vector." << endl;
        this->debug = true;
    } else {
        this->debug = false;
    }

    // Initialize class variables
    for (int i = 0; i < max(xData.size(), yData.size()); i++) {
        this->currentX.push_back(xData[i]);
        this->currentY.push_back(yData[i]);
        this->previousX.push_back(xData[i]);
        this->previousY.push_back(yData[i]);
    }
    this->decompLevel = 0;
}

/**
* Constructor creating vectors of the specified size filled with zeros
*/
MultiRes1D::MultiRes1D(int size, bool debug) {
    // Set debugging flag
    if (debug) {
        cout << "Initialized object with base vector (All zeros)." << endl;
        this->debug = true;
    } else {
        this->debug = false;
    }

    // Initialize class variables
    for (int i = 0; i < size; i++) {
        this->currentX.push_back(0);
        this->currentY.push_back(0);
        this->previousX.push_back(0);
        this->previousY.push_back(0);
    }
    this->decompLevel = 0;
}

/**
* Adds a single point to the vectors
*/
void MultiRes1D::addPoint(double x, double y) {
    currentX.push_back(x);
    currentY.push_back(y);
    if (this->debug) {
        cout << "Added point: (" << x << ", " << y << ")" << endl;
        this->printX();
        this->printY();
        cout << endl;
    }
}

/**
* Deletes the point with the specified coordinates from the vectors
*/
void MultiRes1D::deletePoint(double x, double y) {
    for (int i = 0; i < this->currentX.size(); i++) {
        if (this->currentX[i] == x && this->currentY[i] == y) {
            this->currentX.erase(this->currentX.begin() + i);
            this->currentY.erase(this->currentY.begin() + i);
            if (this->debug) {
                cout << "Removed point: (" << x << ", " << y << ")" << endl;
                this->printX();
                this->printY();
                cout << endl;
            }
            return;
        }
    }
    if (this->debug) {
        cout << "Point (" << x << ", " << y << ") not found." << endl;
    }
}

/**
* Deletes the point at the specified index
*/
void MultiRes1D::deletePoint(int index) {
    if (0 <= index < currentX.size()) {
        this->currentX.erase(this->currentX.begin() + index);
        this->currentY.erase(this->currentY.begin() + index);
        if (this->debug) {
            cout << "Removed index " << index << endl;
            this->printX();
            this->printY();
            cout << endl;
        }
    } else {
        if (this->debug) {
            cout << "Index " << index << " out of range." << endl;
        }
    }
}

/**
* Change the values of the specified point to the new values
*/
void MultiRes1D::movePoint(double initialX, double initialY, double newX, double newY) {
    for (int i = 0; i < this->currentX.size(); i++) {
        if (this->currentX[i] == initialX && this->currentY[i] == initialY) {
            this->currentX[i] = newX;
            this->currentY[i] = newY;
            if (this->debug) {
                cout << "Moved point (" << initialX << ", " << initialY << ") -> (" << newX << ", " << newY << ")" << endl;
                this->printX();
                this->printY();
                cout << endl;
                return;
            }
        }
    }
    if (this->debug) {
        cout << "Point (" << initialX << ", " << initialY << ") not found." << endl;
    }
}

/**
* Changes the values at the specified index to the provided values
*/
void MultiRes1D::movePoint(double x, double y, int index) {
    if (index < 0 || index > currentX.size()) {
        if (debug) {
            cout << "Invalid index." << endl;
        }
        return;
    }
    if (debug) {
        cout << "Moved point (" << currentX[index] << ", " << currentY[index] << ") -> (" << x << ", " << y << ")" << endl;
    }
    currentX[index] = x;
    currentY[index] = y;
}

/**
* Returns the index of the point that is within the specified distance from the given coordinates
*/
int MultiRes1D::getPointIndex(double x, double y, double distance) {
    for (int i = 0; i < currentX.size(); i++) {
        if (sqrt(pow(currentX[i] - x, 2) + pow(currentY[i] - y, 2)) <= distance) {
            if (debug) {
                cout << "Point (" << currentX[i] << ", " << currentY[i] << ") at index " << i << " lies within " << distance << " from (" << x << ", " << y << ")" << endl;
                return i;
            }
        }
    }
    if (debug) {
        cout << "No point lies within " << distance << " from (" << x << ", " << y << ")" << endl;
    }
    return -1;
}

/**
* Returns the current x-points
*/
vector<double> MultiRes1D::getCoarseX() {
    vector<double> hold;
    if (decompListOpen.size() <= 0) {
        for (int i = 0; i < ceil(currentX.size()/pow(2.0, decompLevel)); i++) {
            hold.push_back(currentX[i]);
        }
    } else {
        decompOpen top = decompListOpen.top();
        for (int i = 0; i < top.coarse; i++) {
            hold.push_back(currentX[i]);
        }
    }
    return hold;
}

/**
* Returns the current y-points
*/
vector<double> MultiRes1D::getCoarseY() {
    vector<double> hold;
    if (decompListOpen.size() <= 0) {
        for (int i = 0; i < ceil(currentY.size()/pow(2.0, decompLevel)); i++) {
            hold.push_back(currentY[i]);
        }
    } else {
        decompOpen top = decompListOpen.top();
        for (int i = 0; i < top.coarse; i++) {
            hold.push_back(currentY[i]);
        }
    }
    return hold;
}

/**
* Returns the current x details
*/
vector<double> MultiRes1D::getDetailX() {
    vector<double> hold;
    if (decompListOpen.size() <= 0) {
        int finalPoint = min(2*((int)ceil(currentX.size()/pow(2.0, decompLevel))), (int)currentX.size());
        for (int i = ceil(currentX.size()/pow(2.0, decompLevel)); i < finalPoint; i++) {
            hold.push_back(currentX[i]);
        }
    } else {
        decompOpen top = decompListOpen.top();
        for (int i = top.coarse; i < top.coarse + top.detail; i++) {
            hold.push_back(currentX[i]);
        }
    }
    return hold;
}

/**
* Returns the current y details
*/
vector<double> MultiRes1D::getDetailY() {
    vector<double> hold;
    if (decompListOpen.size() <= 0) {
        int finalPoint = min(2*((int)ceil(currentY.size()/pow(2.0, decompLevel))), (int)currentY.size());
        for (int i = ceil(currentY.size()/pow(2.0, decompLevel)); i < finalPoint; i++) {
            hold.push_back(currentY[i]);
        }
    } else {
        decompOpen top = decompListOpen.top();
        for (int i = top.coarse; i < top.coarse + top.detail; i++) {
            hold.push_back(currentY[i]);
        }
    }
    return hold;
}

/**
* Computes the modulus between value1 and value2, such that it is always positive and between 0 and value2-1 inclusive
*/
int MultiRes1D::mod(int value1, int value2) {
    int hold = value1 % value2;
    if (hold < 0) {
        hold += value2;
    }
    return hold;
}

/**
* Checks whether or not the number of points are even, and if not duplicates the last point that has to be decomposed
*/
bool MultiRes1D::increasePoints(int numPoints) {
    // Check to see if the vector size needs to be increased in order to perform decomposition
    if (numPoints % 2 == 1) {
        if (this->debug) {
            cout << "Adding additional point..." << endl;
            this->printX();
            this->printY();
            cout << endl;
        }
        currentX.insert(currentX.begin()+numPoints, currentX[numPoints-1]);
        currentY.insert(currentY.begin()+numPoints, currentY[numPoints-1]);
        if (debug) {
            cout << "Point added:" << endl;
            this->printX();
            this->printY();
            cout << "New number of points to be used: " << (numPoints+1) << endl << endl;
        }
        return true;
    }
    return false;
}

/**
* Prints the x-values of the points
*/
void MultiRes1D::printX() {
    cout << "X: ";
    for (int i = 0; i < this->currentX.size(); i++) {
        cout << this->currentX[i] << "\t";
    }
    cout << endl;
}

/**
* Prints the y-values of the points
*/
void MultiRes1D::printY() {
    cout << "Y: ";
    for (int i = 0; i < this->currentY.size(); i++) {
        cout << this->currentY[i] << "\t";
    }
    cout << endl;
}

/**
* Prints the points in order
*/
void MultiRes1D::printPoints() {
    for (int i = 0; i < this->currentY.size(); i++) {
        cout << "(" << this->currentX[i] << ", " << this->currentY[i] << ")\t";
    }
    cout << endl;
}

/**
* Copy the values from the current vectors to the previous vectors
*/
void MultiRes1D::copyToPrevious() {
    this->previousX.clear();
    this->previousY.clear();
    for (int i = 0; i < this->currentX.size(); i++) {
        this->previousX.push_back(this->currentX[i]);
        this->previousY.push_back(this->currentY[i]);
    }
}

/**
*  Decompose the x and y vectors using Haar filters
*/
void MultiRes1D::decompHaarClosed(bool partial) {
    // Set up struct to define decomposition
    decomp newDecomp;
    newDecomp.added = false;
    newDecomp.partial = partial;
    newDecomp.degree = 0;

    // Determine the number of points that should be decomposed
    if (currentX.size() <= 0) {
        return;
    }
    int numPoints = currentX.size();
    if (partial) {
        numPoints = ceil(currentX.size()/pow(2.0, decompLevel));
    }
    if (numPoints < 2) {
        return;
    }
    if (debug) {
        cout << numPoints << " points will be decomposed" << endl;
    }

    // Check to see if the vector size should be increased
    newDecomp.added = increasePoints(numPoints);
    if (newDecomp.added) {
        numPoints++;
    }

    // Copy current vector points to previous vectors
    copyToPrevious();

    // Compute coarse approximation
    int pos = 0;
    for (int i = 0; i <= numPoints-2; i+=2) {
        currentX[pos] = 0.5*previousX[i] + 0.5*previousX[i+1];
        currentY[pos] = 0.5*previousY[i] + 0.5*previousY[i+1];
        pos++;
    }
    if (debug) {
        cout << "Computed coarse approximation" << endl;
        printX();
        printY();
        cout << endl;
    }

    // Compute details
    pos = numPoints/2;
    for (int i = 0; i <= numPoints-2; i+=2) {
        currentX[pos] = 0.5*previousX[i] - 0.5*previousX[i+1];
        currentY[pos] = 0.5*previousY[i] - 0.5*previousY[i+1];
        pos++;
    }
    if (debug) {
        cout << "Computed details:" << endl;
        printX();
        printY();
        cout << endl;
    }

    // Update variables to keep track of decompositions
    decompLevel++;
    decompList.push(newDecomp);
}

/**
* Decompose the x and y vectors using Chaikin filters
*/
void MultiRes1D::decompChaikinClosed(bool partial) {
    // Set up struct to define decomposition
    decomp newDecomp;
    newDecomp.added = false;
    newDecomp.partial = partial;
    newDecomp.degree = 2;

    // Determine the number of points that should be decomposed
    if (currentX.size() < 3) {
        return;
    }
    int numPoints = currentX.size();
    if (partial) {
        numPoints = ceil(currentX.size()/pow(2.0, decompLevel));
    }
    if (numPoints < 3) {
        return;
    }
    if (debug) {
        cout << numPoints << " points will be decomposed" << endl;
    }

    // Check to see if the vector size should be increased
    newDecomp.added = increasePoints(numPoints);
    if (newDecomp.added) {
        numPoints++;
    }

    // Copy current vector points to previous vectors
    copyToPrevious();

    // Compute coarse approximation
    int pos = 0;
    for (int i = 0; i <= numPoints-2; i+=2) {
        currentX[pos] = -0.25*previousX[mod(i-2, numPoints)] + 0.75*previousX[mod(i-1, numPoints)] + 0.75*previousX[mod(i, numPoints)] - 0.25*previousX[mod(i+1, numPoints)];
        currentY[pos] = -0.25*previousY[mod(i-2, numPoints)] + 0.75*previousY[mod(i-1, numPoints)] + 0.75*previousY[mod(i, numPoints)] - 0.25*previousY[mod(i+1, numPoints)];
        pos++;
    }
    if (debug) {
        cout << "Computed coarse approximation" << endl;
        printX();
        printY();
        cout << endl;
    }

    // Compute details
    pos = numPoints/2;
    for (int i = 0; i <= numPoints-2; i+=2) {
        currentX[pos] = 0.25*previousX[mod(i-2, numPoints)] - 0.75*previousX[mod(i-1, numPoints)] + 0.75*previousX[mod(i, numPoints)] - 0.25*previousX[mod(i+1, numPoints)];
        currentY[pos] = 0.25*previousY[mod(i-2, numPoints)] - 0.75*previousY[mod(i-1, numPoints)] + 0.75*previousY[mod(i, numPoints)] - 0.25*previousY[mod(i+1, numPoints)];
        pos++;
    }
    if (debug) {
        cout << "Computed details:" << endl;
        printX();
        printY();
        cout << endl;
    }

    // Update variables to keep track of decompostions
    decompLevel++;
    decompList.push(newDecomp);
}

/**
* Decompose the x and y vectors using Cubic filters
*/
void MultiRes1D::decompCubicClosed(bool partial) {
    // Set up struct to define decomposition
    decomp newDecomp;
    newDecomp.added = false;
    newDecomp.partial = partial;
    newDecomp.degree = 3;

    // Determine the number of points that should be decomposed
    if (currentX.size() < 7) {
        return;
    }
    int numPoints = currentX.size();
    if (partial) {
        numPoints = ceil(currentX.size()/pow(2.0, decompLevel));
    }
    if (numPoints < 7) {
        return;
    }
    if (debug) {
        cout << numPoints << " points will be decomposed" << endl;
    }

    // Check to see if the vector size should be increased
    newDecomp.added = increasePoints(numPoints);
    if (newDecomp.added) {
        numPoints++;
    }

    // Copy current vector points to previous vectors
    copyToPrevious();

    // Compute coarse approximation
    int pos = 0;
    for (int i = 0; i <= numPoints-2; i+=2) {
        currentX[pos] = 0.125*previousX[mod(i-4, numPoints)] - 0.5*previousX[mod(i-3, numPoints)] + 0.375*previousX[mod(i-2, numPoints)] + previousX[mod(i-1, numPoints)] + 
                        0.375*previousX[mod(i, numPoints)] - 0.5*previousX[mod(i+1, numPoints)] + 0.125*previousX[mod(i+2, numPoints)];
        currentY[pos] = 0.125*previousY[mod(i-4, numPoints)] - 0.5*previousY[mod(i-3, numPoints)] + 0.375*previousY[mod(i-2, numPoints)] + previousY[mod(i-1, numPoints)] + 
                        0.375*previousY[mod(i, numPoints)] - 0.5*previousY[mod(i+1, numPoints)] + 0.125*previousY[mod(i+2, numPoints)];
        pos++;
    }
    if (debug) {
        cout << "Computed coarse approximation" << endl;
        printX();
        printY();
        cout << endl;
    }

    // Compute details
    pos = numPoints/2;
    for (int i = 0; i <= numPoints-2; i+=2) {
        currentX[pos] = -0.125*previousX[mod(i-2, numPoints)] + 0.5*previousX[mod(i-1, numPoints)] - 0.75*previousX[mod(i, numPoints)] + 0.5*previousX[mod(i+1, numPoints)] - 
                         0.125*previousX[mod(i+2, numPoints)];
        currentY[pos] = -0.125*previousY[mod(i-2, numPoints)] + 0.5*previousY[mod(i-1, numPoints)] - 0.75*previousY[mod(i, numPoints)] + 0.5*previousY[mod(i+1, numPoints)] - 
                         0.125*previousY[mod(i+2, numPoints)];
        pos++;
    }
    if (debug) {
        cout << "Computed details:" << endl;
        printX();
        printY();
        cout << endl;
    }

    // Update variables to keep track of decompostions
    decompLevel++;
    decompList.push(newDecomp);
}

/**
* Perform one level of closed reconstruction
*/
int MultiRes1D::reconstructClosed() {
    // Check if the stack is empty
    if (decompList.size() <= 0) {
        return -1;
    }

    // Get the last decomposition performed
    decomp top = decompList.top();
    decompList.pop();
    if (debug) {
        cout << "Reconstructing with the following variables:" << endl;
        cout << "\tDegree : " << top.degree << endl;
        cout << "\tPartial: " << top.partial << endl;
        cout << "\tAdded  : " << top.added << endl << endl;
    }

    // Choose the correct function corresponding with the degree
    if (top.degree == 0) {
        reconstHaarClosed(top.partial);
    } else if (top.degree == 2) {
        reconstChaikinClosed(top.partial);
    } else if (top.degree == 3) {
        reconstCubicClosed(top.partial);
    } else {
        cout << "Unable to reconstruct: Unknown degree for reconstruction" << endl;
        return -1;
    }

    // Check if a point should be removed
    if (top.added) {
        int location = ceil(currentX.size()/pow(2.0, (decompLevel-1))) - 1;
        currentX.erase(currentX.begin() + location);
        currentY.erase(currentY.begin() + location);
    }
    decompLevel--;
    if (debug) {
            cout << "Reconstructed fine data:" << endl;
            this->printX();
            this->printY();
            cout << endl;
    }

    return top.degree;
}

/**
* Reconstruct the x and y vectors using the closed Haar filters
*/
void MultiRes1D::reconstHaarClosed(bool partial) {
    // Check to see if the vector has been deconstructed
    if (decompLevel <= 0) {
        return;
    }

    // Determine the number of points that should be reconstructed
    if (currentX.size() <= 0) {
        return;
    }
    int numPoints = currentX.size()/2;
    if (partial) {
        numPoints = ceil(currentX.size()/pow(2.0, decompLevel));
    }
    if (debug) {
        cout << numPoints << " points will be reconstructed" << endl;
    }

    // Copy current vector points to previous vectors
    copyToPrevious();

    // Reconstruct the points of the current vector
    for (int i = 0; i < numPoints; i++) {
        currentX[2*i] = previousX[i] + previousX[i + numPoints];
        currentY[2*i] = previousY[i] + previousY[i + numPoints];
        currentX[2*i+1] = previousX[i] - previousX[i + numPoints];
        currentY[2*i+1] = previousY[i] - previousY[i + numPoints];
    }
}

/**
* Reconstruct the x and y vectors using the closed Chaikin filters
*/
void MultiRes1D::reconstChaikinClosed(bool partial) {
    // Check to see if the vector has been deconstructed
    if (decompLevel <= 0) {
        return;
    }

    // Determine the number of points that should be reconstructed
    if (currentX.size() <= 0) {
        return;
    }
    int numPoints = currentX.size()/2;
    if (partial) {
        numPoints = ceil(currentX.size()/pow(2.0, decompLevel));
    }
    if (debug) {
        cout << numPoints << " points will be reconstructed" << endl;
    }

    // Copy current vector points to previous vectors
    copyToPrevious();

    // Reconstruct the points of the current vectors
    for (int i = 0; i < numPoints; i++) {
        currentX[i*2] = 0.75*previousX[mod(i, numPoints)] + 0.25*previousX[mod(i+1, numPoints)] + 
                        0.75*previousX[mod(i, numPoints) + numPoints] - 0.25*previousX[mod(i+1, numPoints) + numPoints];
        currentY[i*2] = 0.75*previousY[mod(i, numPoints)] + 0.25*previousY[mod(i+1, numPoints)] + 
                        0.75*previousY[mod(i, numPoints) + numPoints] - 0.25*previousY[mod(i+1, numPoints) + numPoints];
        currentX[i*2+1] = 0.25*previousX[mod(i, numPoints)] + 0.75*previousX[mod(i+1, numPoints)] + 
                          0.25*previousX[mod(i, numPoints) + numPoints] - 0.75*previousX[mod(i+1, numPoints) + numPoints];
        currentY[i*2+1] = 0.25*previousY[mod(i, numPoints)] + 0.75*previousY[mod(i+1, numPoints)] + 
                          0.25*previousY[mod(i, numPoints) + numPoints] - 0.75*previousY[mod(i+1, numPoints) + numPoints];
    }
}

/**
* Reconstruct the x and y vectors using the closed Cubic filters
*/
void MultiRes1D::reconstCubicClosed(bool partial) {
    // Check to see if the vector has been deconstructed
    if (decompLevel <= 0) {
        return;
    }

    // Determine the number of points that should be reconstructed
    if (currentX.size() <= 0) {
        return;
    }
    int numPoints = currentX.size()/2;
    if (partial) {
        numPoints = ceil(currentX.size()/pow(2.0, decompLevel));
    }
    if (debug) {
        cout << numPoints << " points will be reconstructed" << endl;
    }

    // Copy current vector points to previous vectors
    copyToPrevious();

    // Reconstruct the points of the current vectors
    for (int i = 0; i < numPoints; i++) {
        currentX[i*2] = 0.5*previousX[mod(i, numPoints)] + 0.5*previousX[mod(i+1, numPoints)] + 
                        0.5*previousX[mod(i-1, numPoints)+numPoints] - previousX[mod(i, numPoints) + numPoints] + 0.5*previousX[mod(i+1, numPoints) + numPoints];
        currentY[i*2] = 0.5*previousY[mod(i, numPoints)] + 0.5*previousY[mod(i+1, numPoints)] + 
                        0.5*previousY[mod(i-1, numPoints)+numPoints] - previousY[mod(i, numPoints) + numPoints] + 0.5*previousY[mod(i+1, numPoints) + numPoints];
        currentX[i*2+1] = 0.125*previousX[mod(i, numPoints)] + 0.75*previousX[mod(i+1, numPoints)] + 0.125*previousX[mod(i+2, numPoints)] +
                          0.125*previousX[mod(i-1, numPoints)+numPoints] + 0.375*previousX[mod(i, numPoints)+numPoints] + 
                          0.375*previousX[mod(i+1, numPoints)+numPoints] + 0.125*previousX[mod(i+2, numPoints)+numPoints];
        currentY[i*2+1] = 0.125*previousY[mod(i, numPoints)] + 0.75*previousY[mod(i+1, numPoints)] + 0.125*previousY[mod(i+2, numPoints)] +
                          0.125*previousY[mod(i-1, numPoints)+numPoints] + 0.375*previousY[mod(i, numPoints)+numPoints] + 
                          0.375*previousY[mod(i+1, numPoints)+numPoints] + 0.125*previousY[mod(i+2, numPoints)+numPoints];
    }
}

/**
*
*/
void MultiRes1D::decompHaarOpen(bool partial) {
    // Set up struct to define decomposition
    decompOpen newDecomp;
    newDecomp.partial = partial;
    newDecomp.degree = 0;
    newDecomp.coarse = 0;
    newDecomp.detail = 0;

    // Determine the number of points that should be decomposed
    if (currentX.size() < 4) {
        return;
    }
    int numPoints = currentX.size();
    if (decompListOpen.size() > 0) {
        decompOpen top;
        top = decompListOpen.top();
        numPoints = top.coarse;
    }
    if (numPoints < 4) {
        return;
    }
    if (debug) {
        cout << numPoints << " points will be decomposed" << endl;
    }

    // Check to see if the vector size should be increased
    newDecomp.added = increasePoints(numPoints);
    if (newDecomp.added) {
        numPoints++;
    }

    // Copy current vector points to previous vectors
    copyToPrevious();
    currentX.clear();
    currentY.clear();

    // Compute coarse approximation
    currentX.push_back(previousX[0]);
    currentY.push_back(previousY[0]);
    for (int i = 1; i <= numPoints-3; i+=2) {
        currentX.push_back(0.5*previousX[i] + 0.5*previousX[i+1]);
        currentY.push_back(0.5*previousY[i] + 0.5*previousY[i+1]);
    }
    currentX.push_back(previousX[numPoints-1]);
    currentY.push_back(previousY[numPoints-1]);
    newDecomp.coarse = currentX.size();
    if (debug) {
        cout << "Computed coarse approximation (#" << newDecomp.coarse << " points)" << endl << "X: ";
        printX();
        printY();
        cout << endl<< endl;
    }

    // Compute details
    currentX.push_back(0);
    currentY.push_back(0);
    for (int i = 1; i <= numPoints-3; i+=2) {
        currentX.push_back(0.5*previousX[i] - 0.5*previousX[i+1]);
        currentY.push_back(0.5*previousY[i] - 0.5*previousY[i+1]);
    }
    currentX.push_back(0);
    currentY.push_back(0);
    newDecomp.detail = currentX.size() - newDecomp.coarse;
    
    if (debug) {
        cout << "Computed details (#" << newDecomp.detail << " points):" << endl << "X: ";
        printX();
        printY();
        cout << endl<< endl;
    }

    // Add detail from previous decomps
    for (int i = numPoints; i < previousX.size(); i++) {
        currentX.push_back(previousX[i]);
        currentY.push_back(previousY[i]);
    }

    // Update variables to keep track of decompostions
    decompLevel++;
    decompListOpen.push(newDecomp);
}

/**
* Decompose the x and y vectors using the closed Chaikin filters
*/
void MultiRes1D::decompChaikinOpen(bool partial) {
    // Set up struct to define decomposition
    decompOpen newDecomp;
    newDecomp.partial = partial;
    newDecomp.degree = 2;
    newDecomp.coarse = 0;
    newDecomp.detail = 0;

    // Determine the number of points that should be decomposed
    if (currentX.size() < 7) {
        return;
    }
    int numPoints = currentX.size();
    if (decompListOpen.size() > 0) {
        decompOpen top;
        top = decompListOpen.top();
        numPoints = top.coarse;
    }
    if (numPoints < 7) {
        return;
    }
    if (debug) {
        cout << numPoints << " points will be decomposed" << endl;
    }

    // Check to see if the vector size should be increased
    newDecomp.added = increasePoints(numPoints);
    if (newDecomp.added) {
        numPoints++;
    }

    // Copy current vector points to previous vectors
    copyToPrevious();
    currentX.clear();
    currentY.clear();

    // Compute coarse approximation
    currentX.push_back(previousX[0]);
    currentY.push_back(previousY[0]);
    currentX.push_back(-0.5*previousX[0] + previousX[1] + 0.75*previousX[2] - 0.25*previousX[3]);
    currentY.push_back(-0.5*previousY[0] + previousY[1] + 0.75*previousY[2] - 0.25*previousY[3]);
    for (int i = 2; i <= numPoints-6; i+=2) {
        currentX.push_back(-0.25*previousX[mod(i, numPoints)] + 0.75*previousX[mod(i+1, numPoints)] + 0.75*previousX[mod(i+2, numPoints)] - 0.25*previousX[mod(i+3, numPoints)]);
        currentY.push_back(-0.25*previousY[mod(i, numPoints)] + 0.75*previousY[mod(i+1, numPoints)] + 0.75*previousY[mod(i+2, numPoints)] - 0.25*previousY[mod(i+3, numPoints)]);
    }
    currentX.push_back(-0.25*previousX[numPoints-4] + 0.75*previousX[numPoints-3] + previousX[numPoints-2] - 0.5*previousX[numPoints-1]);
    currentY.push_back(-0.25*previousY[numPoints-4] + 0.75*previousY[numPoints-3] + previousY[numPoints-2] - 0.5*previousY[numPoints-1]);
    currentX.push_back(previousX[numPoints-1]);
    currentY.push_back(previousY[numPoints-1]);
    newDecomp.coarse = currentX.size();
    if (debug) {
        cout << "Computed coarse approximation (#" << newDecomp.coarse << " points)" << endl << "X: ";
        printX();
        printY();
        cout << endl<< endl;
    }

    // Compute details
    currentX.push_back(-0.5*previousX[0] + previousX[1] - 0.75*previousX[2] + 0.25*previousX[3]);
    currentY.push_back(-0.5*previousY[0] + previousY[1] - 0.75*previousY[2] + 0.25*previousY[3]);
    currentX.push_back(-0.25*previousX[2] + 0.75*previousX[3] - 0.75*previousX[4] + 0.25*previousX[5]);
    currentY.push_back(-0.25*previousY[2] + 0.75*previousY[3] - 0.75*previousY[4] + 0.25*previousY[5]);
    for (int i = 4; i <= numPoints-6; i+=2) {
        currentX.push_back(0.25*previousX[mod(i, numPoints)] - 0.75*previousX[mod(i+1, numPoints)] + 0.75*previousX[mod(i+2, numPoints)] - 0.25*previousX[mod(i+3, numPoints)]);
        currentY.push_back(0.25*previousY[mod(i, numPoints)] - 0.75*previousY[mod(i+1, numPoints)] + 0.75*previousY[mod(i+2, numPoints)] - 0.25*previousY[mod(i+3, numPoints)]);
    }
    currentX.push_back(0.25*previousX[numPoints-4] - 0.75*previousX[numPoints-3] + previousX[numPoints-2] - 0.5*previousX[numPoints-1]);
    currentY.push_back(0.25*previousY[numPoints-4] - 0.75*previousY[numPoints-3] + previousY[numPoints-2] - 0.5*previousY[numPoints-1]);
    newDecomp.detail = currentX.size() - newDecomp.coarse;
    
    if (debug) {
        cout << "Computed details (#" << newDecomp.detail << " points):" << endl << "X: ";
        printX();
        printY();
        cout << endl<< endl;
    }

    // Add detail from previous decomps
    for (int i = numPoints; i < previousX.size(); i++) {
        currentX.push_back(previousX[i]);
        currentY.push_back(previousY[i]);
    }

    // Update variables to keep track of decompostions
    decompLevel++;
    decompListOpen.push(newDecomp);
}

/**
*
*/
void MultiRes1D::decompCubicOpen(bool partial) {
    // Set up struct to define decomposition
    decompOpen newDecomp;
    newDecomp.partial = partial;
    newDecomp.degree = 3;
    newDecomp.coarse = 0;
    newDecomp.detail = 0;

    // Determine the number of points that should be decomposed
    if (currentX.size() < 7) {
        return;
    }
    int numPoints = currentX.size();
    if (decompListOpen.size() > 0) {
        decompOpen top;
        top = decompListOpen.top();
        numPoints = top.coarse;
    }
    if (numPoints < 7) {
        return;
    }
    if (debug) {
        cout << numPoints << " points will be decomposed" << endl;
    }

    // Check to see if the vector size should be increased
    newDecomp.added = increasePoints(numPoints);
    if (newDecomp.added) {
        numPoints++;
    }

    // Copy current vector points to previous vectors
    copyToPrevious();
    currentX.clear();
    currentY.clear();

    // Compute coarse approximation
    currentX.push_back(previousX[0]);
    currentY.push_back(previousY[0]);
    currentX.push_back((-49.0/139)*previousX[0] + (98.0/139)*previousX[1] + (135.0/139)*previousX[2] + (-60.0/139)*previousX[3] + (15.0/139)*previousX[4]);
    currentY.push_back((-49.0/139)*previousY[0] + (98.0/139)*previousY[1] + (135.0/139)*previousY[2] + (-60.0/139)*previousY[3] + (15.0/139)*previousY[4]);
    currentX.push_back((9.0/50)*previousX[0] + (-9.0/25)*previousX[1] + (-2.0/25)*previousX[2] + (32.0/25)*previousX[3] + (43.0/100)*previousX[4] + (-3.0/5)*previousX[5] + (3.0/20)*previousX[6]);
    currentY.push_back((9.0/50)*previousY[0] + (-9.0/25)*previousY[1] + (-2.0/25)*previousY[2] + (32.0/25)*previousY[3] + (43.0/100)*previousY[4] + (-3.0/5)*previousY[5] + (3.0/20)*previousY[6]);
    for (int i = 2; i < numPoints-9; i+=2) {
        currentX.push_back((23.0/196)*previousX[i] + (-23.0/49)*previousX[i+1] + (9.0/28)*previousX[i+2] + (52.0/49)*previousX[i+3] + (9.0/28)*previousX[i+4] + 
                           (-23.0/49)*previousX[i+5] + (23.0/196)*previousX[i+6]);
        currentY.push_back((23.0/196)*previousY[i] + (-23.0/49)*previousY[i+1] + (9.0/28)*previousY[i+2] + (52.0/49)*previousY[i+3] + (9.0/28)*previousY[i+4] + 
                           (-23.0/49)*previousY[i+5] + (23.0/196)*previousY[i+6]);
    }
    currentX.push_back((3.0/20)*previousX[numPoints-7] + (-3.0/5)*previousX[numPoints-6] + (43.0/100)*previousX[numPoints-5] + (32.0/25)*previousX[numPoints-4] + 
                       (-2.0/25)*previousX[numPoints-3] + (-9.0/25)*previousX[numPoints-2] + (9.0/50)*previousX[numPoints-1]);
    currentY.push_back((3.0/20)*previousY[numPoints-7] + (-3.0/5)*previousY[numPoints-6] + (43.0/100)*previousY[numPoints-5] + (32.0/25)*previousY[numPoints-4] + 
                       (-2.0/25)*previousY[numPoints-3] + (-9.0/25)*previousY[numPoints-2] + (9.0/50)*previousY[numPoints-1]);
    currentX.push_back((15.0/139)*previousX[numPoints-5] + (-60.0/139)*previousX[numPoints-4] + (135.0/139)*previousX[numPoints-3] + (98.0/139)*previousX[numPoints-2] + 
                       (-49.0/139)*previousX[numPoints-1]);
    currentY.push_back((15.0/139)*previousY[numPoints-5] + (-60.0/139)*previousY[numPoints-4] + (135.0/139)*previousY[numPoints-3] + (98.0/139)*previousY[numPoints-2] + 
                       (-49.0/139)*previousY[numPoints-1]);
    currentX.push_back(previousX[numPoints-1]);
    currentY.push_back(previousY[numPoints-1]);
    newDecomp.coarse = currentX.size();
    if (debug) {
        cout << "Computed coarse approximation (#" << newDecomp.coarse << " points)" << endl;
        printX();
        printY();
        cout << endl<< endl;
    }

    // Compute details
    currentX.push_back((-45.0/139)*previousX[0] + (90.0/139)*previousX[1] + (-135.0/278)*previousX[2] + (30.0/139)*previousX[3] + (-15.0/278)*previousX[4]);
    currentY.push_back((-45.0/139)*previousY[0] + (90.0/139)*previousY[1] + (-135.0/278)*previousY[2] + (30.0/139)*previousY[3] + (-15.0/278)*previousY[4]);
    currentX.push_back((57.0/490)*previousX[2] + (-114.0/245)*previousX[3] + (171.0/245)*previousX[4] + (-114.0/245)*previousX[5] + (57.0/490)*previousX[6]);
    currentY.push_back((57.0/490)*previousY[2] + (-114.0/245)*previousY[3] + (171.0/245)*previousY[4] + (-114.0/245)*previousY[5] + (57.0/490)*previousY[6]);
    for (int i = 4; i < numPoints-9; i+=2) {
        currentX.push_back((13.0/98)*previousX[i] + (-26.0/49)*previousX[i+1] + (39.0/49)*previousX[i+2] + (-26.0/49)*previousX[i+3] + (13.0/98)*previousX[i+4]);
        currentY.push_back((13.0/98)*previousY[i] + (-26.0/49)*previousY[i+1] + (39.0/49)*previousY[i+2] + (-26.0/49)*previousY[i+3] + (13.0/98)*previousY[i+4]);
    }
    currentX.push_back((57.0/490)*previousX[numPoints-7] + (-114.0/245)*previousX[numPoints-6] + (171.0/245)*previousX[numPoints-5] + (-114.0/245)*previousX[numPoints-4] + 
                       (57.0/490)*previousX[numPoints-3]);
    currentY.push_back((57.0/490)*previousY[numPoints-7] + (-114.0/245)*previousY[numPoints-6] + (171.0/245)*previousY[numPoints-5] + (-114.0/245)*previousY[numPoints-4] + 
                       (57.0/490)*previousY[numPoints-3]);
    currentX.push_back((-15.0/278)*previousX[numPoints-5] + (30.0/139)*previousX[numPoints-4] + (-135.0/278)*previousX[numPoints-3] + (90.0/139)*previousX[numPoints-2] + 
                       (-45.0/139)*previousX[numPoints-1]);
    currentY.push_back((-15.0/278)*previousY[numPoints-5] + (30.0/139)*previousY[numPoints-4] + (-135.0/278)*previousY[numPoints-3] + (90.0/139)*previousY[numPoints-2] + 
                       (-45.0/139)*previousY[numPoints-1]);

    newDecomp.detail = currentX.size() - newDecomp.coarse;
    
    if (debug) {
        cout << "Computed details (#" << newDecomp.detail << " points):" << endl;
        printX();
        printY();
        cout << endl<< endl;
    }

    // Add detail from previous decomps
    for (int i = numPoints; i < previousX.size(); i++) {
        currentX.push_back(previousX[i]);
        currentY.push_back(previousY[i]);
    }

    // Update variables to keep track of decompostions
    decompLevel++;
    decompListOpen.push(newDecomp);
}

/**
*
*/
void MultiRes1D::decompCubicShort(bool partial) {
    // Set up struct to define decomposition
    decompOpen newDecomp;
    newDecomp.partial = partial;
    newDecomp.degree = 3;
    newDecomp.coarse = 0;
    newDecomp.detail = 0;

    // Determine the number of points that should be decomposed
    if (currentX.size() < 7) {
        return;
    }
    int numPoints = currentX.size();
    if (decompListOpen.size() > 0) {
        decompOpen top;
        top = decompListOpen.top();
        numPoints = top.coarse;
    }
    if (numPoints < 7) {
        return;
    }
    if (debug) {
        cout << numPoints << " points will be decomposed" << endl;
    }

    // Check to see if the vector size should be increased
    newDecomp.added = increasePoints(numPoints);
    if (newDecomp.added) {
        numPoints++;
    }

    // Copy current vector points to previous vectors
    copyToPrevious();
    currentX.clear();
    currentY.clear();

    // Compute coarse approximation
    currentX.push_back(previousX[0]);
    currentY.push_back(previousY[0]);
    currentX.push_back(-1*previousX[0] + 2*previousX[1]);
    currentY.push_back(-1*previousY[0] + 2*previousY[1]);

    for (int i = 2; i <= numPoints-4; i+=2) {
        currentX.push_back(-0.5*previousX[i] + 2*previousX[i+1] - 0.5*previousX[i+2]);
        currentY.push_back(-0.5*previousY[i] + 2*previousY[i+1] - 0.5*previousY[i+2]);
    }

    currentX.push_back(2*previousX[numPoints-2] - previousX[numPoints-1]);
    currentY.push_back(2*previousY[numPoints-2] - previousY[numPoints-1]);
    currentX.push_back(previousX[numPoints-1]);
    currentY.push_back(previousY[numPoints-1]);
    newDecomp.coarse = currentX.size();
    if (debug) {
        cout << "Computed coarse approximation (#" << newDecomp.coarse << " points)" << endl;
        printX();
        printY();
        cout << endl<< endl;
    }

    // Compute details
    currentX.push_back(0.75*previousX[0] - 1.5*previousX[1] + 1.125*previousX[2] - 0.5*previousX[3] + 0.125*previousX[4]);
    currentY.push_back(0.75*previousY[0] - 1.5*previousY[1] + 1.125*previousY[2] - 0.5*previousY[3] + 0.125*previousY[4]);

    for (int i = 2; i <= numPoints-6; i+=2) {
        currentX.push_back(0.25*previousX[i] - previousX[i+1] + 1.5*previousX[i+2] - previousX[i+3] + 0.25*previousX[i+4]);
        currentY.push_back(0.25*previousY[i] - previousY[i+1] + 1.5*previousY[i+2] - previousY[i+3] + 0.25*previousY[i+4]);
    }

    currentX.push_back(0.125*previousX[numPoints-5] - 0.5*previousX[numPoints-4] + 1.125*previousX[numPoints-3] - 1.5*previousX[numPoints-2] + 0.75*previousX[numPoints-1]);
    currentY.push_back(0.125*previousY[numPoints-5] - 0.5*previousY[numPoints-4] + 1.125*previousY[numPoints-3] - 1.5*previousY[numPoints-2] + 0.75*previousY[numPoints-1]);

    newDecomp.detail = currentX.size() - newDecomp.coarse;
    
    if (debug) {
        cout << "Computed details (#" << newDecomp.detail << " points):" << endl;
        printX();
        printY();
        cout << endl<< endl;
    }

    // Add detail from previous decomps
    for (int i = numPoints; i < previousX.size(); i++) {
        currentX.push_back(previousX[i]);
        currentY.push_back(previousY[i]);
    }

    // Update variables to keep track of decompostions
    decompLevel++;
    decompListOpen.push(newDecomp);
}

/**
*
*/
int MultiRes1D::reconstructOpen() {
    // Check if the stack is empty
    if (decompListOpen.size() <= 0) {
        return -1;
    }

    // Get the last decomposition performed
    decompOpen top = decompListOpen.top();
    decompListOpen.pop();
    if (debug) {
        cout << "Reconstructing with the following variables:" << endl;
        cout << "\tDegree : " << top.degree << endl;
        cout << "\tPartial: " << top.partial << endl;
        cout << "\tAdded: " << top.added << endl;
        cout << "\tCoarse : " << top.coarse << endl;
        cout << "\tDetail : " << top.detail << endl << endl;
    }

    // Choose the correct function corresponding with the degree
    if (top.degree == 0) {
        reconstHaarOpen(top.coarse, top.detail, top.partial);
    } else if (top.degree == 2) {
        reconstChaikinOpen(top.coarse, top.detail, top.partial);
    } else if (top.degree == 3) {
        reconstCubicOpen(top.coarse, top.detail, top.partial);
    } else {
        cout << "Unable to reconstruct: Unknown degree for reconstruction" << endl;
        return -1;
    }

    // Check if a point should be removed
    if (top.added) {
        int location;
        if (decompListOpen.size() <= 0) {
            location = currentX.size()-1;
        } else {
            decompOpen hold = decompListOpen.top();
            location = hold.coarse;
        }
        cout << location << endl;
        printX();
        printY();
        currentX.erase(currentX.begin() + location);
        currentY.erase(currentY.begin() + location);
    }
    decompLevel--;
    if (debug) {
            cout << "Reconstructed fine data:" << endl;
            this->printX();
            this->printY();
            cout << endl;
    }

    return top.degree;
}

/**
*
*/
void MultiRes1D::reconstHaarOpen(int coarse, int detail, bool partial) {
    // Check to see if the vector has been deconstructed
    if (decompLevel <= 0) {
        return;
    }

    // Copy current vector points to previous vectors
    copyToPrevious();
    currentX.clear();
    currentY.clear();

    // Reconstruct the fine points
    currentX.push_back(previousX[0]);
    currentY.push_back(previousY[0]);
    int pos = 2;
    for (int i = 1; i < coarse-1; i++) {
        currentX.push_back(previousX[i] + previousX[coarse+i]);
        currentX.push_back(previousX[i] - previousX[coarse+i]);
        currentY.push_back(previousY[i] + previousY[coarse+i]);
        currentY.push_back(previousY[i] - previousY[coarse+i]);
        pos += 2;
    }
    currentX.push_back(previousX[coarse-1]);
    currentY.push_back(previousY[coarse-1]);

    // Copy old detail back into vector
    for (int i = (coarse + detail); i < previousX.size(); i++) {
        currentX.push_back(previousX[i]);
        currentY.push_back(previousY[i]);
    }

    if (debug) {
        cout << pos << " fine points reconstructed." << endl;
    }
}

/**
*
*/
void MultiRes1D::reconstChaikinOpen(int coarse, int detail, bool partial) {
    // Check to see if the vector has been deconstructed
    if (decompLevel <= 0) {
        return;
    }

    // Copy current vector points to previous vectors
    copyToPrevious();
    currentX.clear();
    currentY.clear();

    // Construct the E vector
    vector<double> eX, eY;
    eX.push_back(0);
    eX.push_back(0.5*previousX[coarse]);
    eX.push_back(-0.75*previousX[coarse] + 0.25*previousX[coarse+1]);
    eX.push_back(-0.25*previousX[coarse] + 0.75*previousX[coarse+1]);
    eX.push_back(-0.75*previousX[coarse+1] - 0.25*previousX[coarse+2]);
    eX.push_back(-0.25*previousX[coarse+1] - 0.75*previousX[coarse+2]);
    eY.push_back(0);
    eY.push_back(0.5*previousY[coarse]);
    eY.push_back(-0.75*previousY[coarse] + 0.25*previousY[coarse+1]);
    eY.push_back(-0.25*previousY[coarse] + 0.75*previousY[coarse+1]);
    eY.push_back(-0.75*previousY[coarse+1] - 0.25*previousY[coarse+2]);
    eY.push_back(-0.25*previousY[coarse+1] - 0.75*previousY[coarse+2]);
    for (int i = 2; i < detail - 1; i++) {
        eX.push_back(0.75*previousX[coarse+i] - 0.25*previousX[coarse+i+1]);
        eX.push_back(0.25*previousX[coarse+i] - 0.75*previousX[coarse+i+1]);
        eY.push_back(0.75*previousY[coarse+i] - 0.25*previousY[coarse+i+1]);
        eY.push_back(0.25*previousY[coarse+i] - 0.75*previousY[coarse+i+1]);
    }
    eX.push_back(0.5*previousX[coarse + detail - 1]);
    eX.push_back(0);
    eY.push_back(0.5*previousY[coarse + detail - 1]);
    eY.push_back(0);

    // Reconstruct the fine points
    currentX.push_back(previousX[0] + eX[0]);
    currentX.push_back((0.5*previousX[0] + 0.5*previousX[1]) + eX[1]);
    currentY.push_back(previousY[0] + eY[0]);
    currentY.push_back((0.5*previousY[0] + 0.5*previousY[1]) + eY[1]);
    int pos = 2;
    for (int i = 1; i < coarse-2; i++) {
        currentX.push_back((0.75*previousX[i] + 0.25*previousX[i+1]) + eX[pos]);
        currentX.push_back((0.25*previousX[i] + 0.75*previousX[i+1]) + eX[pos+1]);
        currentY.push_back((0.75*previousY[i] + 0.25*previousY[i+1]) + eY[pos]);
        currentY.push_back((0.25*previousY[i] + 0.75*previousY[i+1]) + eY[pos+1]);
        pos += 2;
    }
    currentX.push_back((0.5*previousX[coarse-2] + 0.5*previousX[coarse-1]) + eX[pos]);
    currentY.push_back((0.5*previousY[coarse-2] + 0.5*previousY[coarse-1]) + eY[pos]);
    currentX.push_back(previousX[coarse-1] + eX[pos+1]);
    currentY.push_back(previousY[coarse-1] + eY[pos+1]);

    // Copy old detail back into vector
    for (int i = (coarse + detail); i < previousX.size(); i++) {
        currentX.push_back(previousX[i]);
        currentY.push_back(previousY[i]);
    }

    if (debug) {
        cout << pos << " fine points reconstructed." << endl;
    }
}

/**
*
*/
void MultiRes1D::reconstCubicOpen(int coarse, int detail, bool partial) {
    // Check to see if the vector has been deconstructed
    if (decompLevel <= 0) {
        return;
    }

    // Copy current vector points to previous vectors
    copyToPrevious();
    currentX.clear();
    currentY.clear();

    // Construct the E vector
    vector<double> eX, eY;
    eX.push_back(0);
    eY.push_back(0);

    eX.push_back(previousX[coarse]);
    eY.push_back(previousY[coarse]);

    eX.push_back((-2033.0/3000)*previousX[coarse] + (-49.0/152)*previousX[coarse+1]);
    eY.push_back((-2033.0/3000)*previousY[coarse] + (-49.0/152)*previousY[coarse+1]);

    eX.push_back((2137.0/12000)*previousX[coarse] + (-289.0/608)*previousX[coarse+1] + (-23.0/208)*previousX[coarse+2]);
    eY.push_back((2137.0/12000)*previousY[coarse] + (-289.0/608)*previousY[coarse+1] + (-23.0/208)*previousY[coarse+2]);

    eX.push_back((139.0/500)*previousX[coarse] + previousX[coarse+1] + (-23.0/52)*previousX[coarse+2]);
    eY.push_back((139.0/500)*previousY[coarse] + previousY[coarse+1] + (-23.0/52)*previousY[coarse+2]);

    eX.push_back((139.0/2000)*previousX[coarse] + (-347.0/912)*previousX[coarse+1] + (-63.0/208)*previousX[coarse+2] + (-23.0/208)*previousX[coarse+3]);
    eY.push_back((139.0/2000)*previousY[coarse] + (-347.0/912)*previousY[coarse+1] + (-63.0/208)*previousY[coarse+2] + (-23.0/208)*previousY[coarse+3]);

    eX.push_back((-115.0/228)*previousX[coarse+1] + previousX[coarse+2] + (-23.0/52)*previousX[coarse+3]);
    eY.push_back((-115.0/228)*previousY[coarse+1] + previousY[coarse+2] + (-23.0/52)*previousY[coarse+3]);

    eX.push_back((-115.0/912)*previousX[coarse+1] + (-63.0/208)*previousX[coarse+2] + (-63.0/208)*previousX[coarse+3] + (-23.0/208)*previousX[coarse+4]);
    eY.push_back((-115.0/912)*previousY[coarse+1] + (-63.0/208)*previousY[coarse+2] + (-63.0/208)*previousY[coarse+3] + (-23.0/208)*previousY[coarse+4]);

    for (int i = 2; i <= detail - 5; i++) {
        eX.push_back((-23.0/52)*previousX[coarse+i] + previousX[coarse+i+1] + (-23.0/52)*previousX[coarse+i+2]);
        eY.push_back((-23.0/52)*previousY[coarse+i] + previousY[coarse+i+1] + (-23.0/52)*previousY[coarse+i+2]);

        eX.push_back((-23.0/208)*previousX[coarse+i] + (-63.0/208)*previousX[coarse+i+1] + (-63.0/208)*previousX[coarse+i+2] + (-23.0/208)*previousX[coarse+i+3]);
        eY.push_back((-23.0/208)*previousY[coarse+i] + (-63.0/208)*previousY[coarse+i+1] + (-63.0/208)*previousY[coarse+i+2] + (-23.0/208)*previousY[coarse+i+3]);
    }

    eX.push_back((-23.0/208)*previousX[coarse + detail - 5] + (-63.0/208)*previousX[coarse + detail - 4] + (-63.0/208)*previousX[coarse + detail - 3] + (-115.0/912)*previousX[coarse + detail - 2]);
    eY.push_back((-23.0/208)*previousY[coarse + detail - 5] + (-63.0/208)*previousY[coarse + detail - 4] + (-63.0/208)*previousY[coarse + detail - 3] + (-115.0/912)*previousY[coarse + detail - 2]);

    eX.push_back((-23.0/52)*previousX[coarse + detail - 4] + previousX[coarse + detail - 3] + (-115.0/228)*previousX[coarse + detail - 2]);
    eY.push_back((-23.0/52)*previousY[coarse + detail - 4] + previousY[coarse + detail - 3] + (-115.0/228)*previousY[coarse + detail - 2]);

    eX.push_back((-23.0/208)*previousX[coarse + detail - 4] + (-63.0/208)*previousX[coarse + detail - 3] + (-347.0/912)*previousX[coarse + detail - 2] + (139.0/2000)*previousX[coarse + detail - 1]);
    eY.push_back((-23.0/208)*previousY[coarse + detail - 4] + (-63.0/208)*previousY[coarse + detail - 3] + (-347.0/912)*previousY[coarse + detail - 2] + (139.0/2000)*previousY[coarse + detail - 1]);

    eX.push_back((-23.0/52)*previousX[coarse + detail - 3] + previousX[coarse + detail - 2] + (139.0/500)*previousX[coarse + detail - 1]);
    eY.push_back((-23.0/52)*previousY[coarse + detail - 3] + previousY[coarse + detail - 2] + (139.0/500)*previousY[coarse + detail - 1]);

    eX.push_back((-23.0/208)*previousX[coarse + detail - 3] + (-289.0/608)*previousX[coarse + detail - 2] + (2137.0/12000)*previousX[coarse + detail - 1]);
    eY.push_back((-23.0/208)*previousY[coarse + detail - 3] + (-289.0/608)*previousY[coarse + detail - 2] + (2137.0/12000)*previousY[coarse + detail - 1]);

    eX.push_back((-49.0/152)*previousX[coarse + detail - 2] + (-2033.0/3000)*previousX[coarse + detail - 1]);
    eY.push_back((-49.0/152)*previousY[coarse + detail - 2] + (-2033.0/3000)*previousY[coarse + detail - 1]);

    eX.push_back(previousX[coarse + detail - 1]);
    eY.push_back(previousY[coarse + detail - 1]);

    eX.push_back(0);
    eY.push_back(0);

    // Reconstruct the fine points
    currentX.push_back(previousX[0] + eX[0]);
    currentY.push_back(previousY[0] + eY[0]);

    currentX.push_back(0.5*previousX[0] + 0.5*previousX[1] + eX[1]);
    currentY.push_back(0.5*previousY[0] + 0.5*previousY[1] + eY[1]);

    currentX.push_back(0.75*previousX[1] + 0.25*previousX[2] + eX[2]);
    currentY.push_back(0.75*previousY[1] + 0.25*previousY[2] + eY[2]);

    currentX.push_back(0.1875*previousX[1] + 0.6875*previousX[2] + 0.125*previousX[3] + eX[3]);
    currentY.push_back(0.1875*previousY[1] + 0.6875*previousY[2] + 0.125*previousY[3] + eY[3]);

    int pos = 4;
    for (int i = 2; i <= coarse - 4; i++) {
        currentX.push_back(0.5*previousX[i] + 0.5*previousX[i+1] +eX[pos]);
        currentY.push_back(0.5*previousY[i] + 0.5*previousY[i+1] +eY[pos]);
        pos++;

        currentX.push_back(0.125*previousX[i] + 0.75*previousX[i+1] + 0.125*previousX[i+2] + eX[pos]);
        currentY.push_back(0.125*previousY[i] + 0.75*previousY[i+1] + 0.125*previousY[i+2] + eY[pos]);
        pos++;
    }

    currentX.push_back(0.125*previousX[coarse-4] + 0.6875*previousX[coarse-3] + 0.1875*previousX[coarse-2] + eX[pos]);
    currentY.push_back(0.125*previousY[coarse-4] + 0.6875*previousY[coarse-3] + 0.1875*previousY[coarse-2] + eY[pos]);
    pos++;

    currentX.push_back(0.25*previousX[coarse-3] + 0.75*previousX[coarse-2] + eX[pos]);
    currentY.push_back(0.25*previousY[coarse-3] + 0.75*previousY[coarse-2] + eY[pos]);
    pos++;

    currentX.push_back(0.5*previousX[coarse-2] + 0.5*previousX[coarse-1] + eX[pos]);
    currentY.push_back(0.5*previousY[coarse-2] + 0.5*previousY[coarse-1] + eY[pos]);
    pos++;

    currentX.push_back(previousX[coarse-1] + eX[pos]);
    currentY.push_back(previousY[coarse-1] + eY[pos]);
    pos++;

    cout << pos << " - " << eX.size() << endl;

    // Copy old detail back into vector
    for (int i = (coarse + detail); i < previousX.size(); i++) {
        currentX.push_back(previousX[i]);
        currentY.push_back(previousY[i]);
    }

    if (debug) {
        cout << pos << " fine points reconstructed." << endl;
    }
}

/**
*
*/
void MultiRes1D::reconstCubicShort(int coarse, int detail, bool partial) {
    // Check to see if the vector has been deconstructed
    if (decompLevel <= 0) {
        return;
    }

    // Copy current vector points to previous vectors
    copyToPrevious();
    currentX.clear();
    currentY.clear();

    // Construct the E vectors
    vector<double> eX, eY;
    eX.push_back(0);
    eY.push_back(0);

    eX.push_back(0);
    eY.push_back(0);

    for (int i = 0; i < detail - 1; i++) {
        eX.push_back(previousX[coarse+i]);
        eY.push_back(previousY[coarse+i]);

        eX.push_back(0.25*previousX[coarse+i] + 0.25*previousX[coarse+i+1]);
        eY.push_back(0.25*previousY[coarse+i] + 0.25*previousY[coarse+i+1]);
    }

    eX.push_back(0);
    eY.push_back(0);

    eX.push_back(0);
    eY.push_back(0);

    // Reconstruct the fine points
    currentX.push_back(previousX[0] + eX[0]);
    currentY.push_back(previousY[0] + eY[0]);

    currentX.push_back(0.5*previousX[0] + 0.5*previousX[1] + eX[1]);
    currentY.push_back(0.5*previousY[0] + 0.5*previousY[1] + eY[1]);

    currentX.push_back(0.75*previousX[1] + 0.25*previousX[2] + eX[2]);
    currentY.push_back(0.75*previousY[1] + 0.25*previousY[2] + eY[2]);

    currentX.push_back((3.0/16)*previousX[1] + (11.0/16)*previousX[2] + (1.0/8)*previousX[3] + eX[3]);
    currentY.push_back((3.0/16)*previousY[1] + (11.0/16)*previousY[2] + (1.0/8)*previousY[3] + eY[3]);

    int pos = 4;
    for (int i = 2; i < coarse - 4; i++) {
        currentX.push_back(0.5*previousX[i] + 0.5*previousX[i+1] + eX[pos]);
        currentY.push_back(0.5*previousY[i] + 0.5*previousY[i+1] + eY[pos]);
        pos++;

        currentX.push_back(0.125*previousX[i] + 0.75*previousX[i+1] + 0.125*previousX[i+2] + eX[pos]);
        currentY.push_back(0.125*previousY[i] + 0.75*previousY[i+1] + 0.125*previousY[i+2] + eY[pos]);
        pos++;
    }

    currentX.push_back(0.125*previousX[coarse-4] + 0.6875*previousX[coarse-3] + 0.1875*previousX[coarse-2] + eX[pos]);
    currentY.push_back(0.125*previousY[coarse-4] + 0.6875*previousY[coarse-3] + 0.1875*previousY[coarse-2] + eY[pos]);
    pos++;

    currentX.push_back(0.25*previousX[coarse-3] + 0.75*previousX[coarse-2] + eX[pos]);
    currentY.push_back(0.25*previousY[coarse-3] + 0.75*previousY[coarse-2] + eY[pos]);
    pos++;

    currentX.push_back(0.5*previousX[coarse-2] + 0.5*previousX[coarse-1] + eX[pos]);
    currentY.push_back(0.5*previousY[coarse-2] + 0.5*previousY[coarse-1] + eY[pos]);
    pos++;

    currentX.push_back(previousX[coarse-1] + eX[pos]);
    currentY.push_back(previousY[coarse-1] + eY[pos]);
    pos++;

    cout << pos << " - " << eX.size() << endl;

    // Copy old detail back into vector
    for (int i = (coarse + detail); i < previousX.size(); i++) {
        currentX.push_back(previousX[i]);
        currentY.push_back(previousY[i]);
    }

    if (debug) {
        cout << pos << " fine points reconstructed." << endl;
    }
}
