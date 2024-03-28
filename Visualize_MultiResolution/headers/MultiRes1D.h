#ifndef MULTIRES1D_H
#define MULTIRES1D_H

#include <iostream>
#include <vector>
#include <stack>
#include <math.h>

class MultiRes1D {
private:
    // Struct to keep track of the details of different decompositions
    struct decomp {
        bool added;
        bool partial;
        int degree;
    };

    struct decompOpen {
        bool partial;
        bool added;
        int degree;
        int coarse;
        int detail;
    };

    // Class variables
    std::vector<double> currentX;
    std::vector<double> currentY;
    std::vector<double> previousX;
    std::vector<double> previousY;
    std::stack<decomp> decompList;
    std::stack<decompOpen> decompListOpen;
    bool debug;
    int decompLevel;

public:
    // Constructors
    MultiRes1D(bool debug=false);
    MultiRes1D(std::vector<double> xData, std::vector<double> yData, bool debug=false);
    MultiRes1D(int size, bool debug=false);

    // Updating class variables (Getters and setters)
    void addPoint(double x, double y);
    void deletePoint(double x, double y);
    void deletePoint(int index);
    void movePoint(double initialX, double initialY, double newX, double newY);
    void movePoint(double x, double y, int index);
    int getPointIndex(double x, double y, double distance);
    std::vector<double> getCoarseX();
    std::vector<double> getCoarseY();
    std::vector<double> getDetailX();
    std::vector<double> getDetailY();

    // Helper functions
    int mod(int value1, int value2);
    bool increasePoints(int numPoints);
    void printX();
    void printY();
    void printPoints();
    void copyToPrevious();

    // Closed decomposition functions
    void decompHaarClosed(bool partial=true);
    void decompChaikinClosed(bool partial=true);
    void decompCubicClosed(bool partial=true);

    // Closed reconstruction functions
    int reconstructClosed();
    void reconstHaarClosed(bool partial=true);
    void reconstChaikinClosed(bool partial=true);
    void reconstCubicClosed(bool partial=true);

    // Open decomposition functions
    void decompHaarOpen(bool partial=true);
    void decompChaikinOpen(bool partial=true);
    void decompCubicOpen(bool partial=true);
    void decompCubicShort(bool partial=true);

    // Open reconstruction functions
    int reconstructOpen();
    void reconstHaarOpen(int coarse, int detail, bool partial=true);
    void reconstChaikinOpen(int coarse, int detail, bool partial=true);
    void reconstCubicOpen(int coarse, int detail, bool partial=true);
    void reconstCubicShort(int coarse, int detail, bool partial=true);
};

#endif
