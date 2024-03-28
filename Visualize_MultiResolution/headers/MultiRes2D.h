#ifndef MULTIRES2D_H
#define MULTIRES2D_H

#include <iostream>
#include <vector>
#include <stack>
#include <math.h>

/**
* 
*/
class MultiRes2D {
private:
    // Struct to keep track of the details of different decompositions
    struct decomp {
        bool added;
        bool partial;
        int degree;
        char rowCol;
    };

    // Class variables
    std::vector< std::vector<double> > currentData;
    std::vector< std::vector<double> > previousData;
    std::stack<decomp> decompList;
    bool debug;
    int rowDecomp;
    int colDecomp;

public:
    // Constructors
    MultiRes2D(bool debug=false);
    MultiRes2D(std::vector< std::vector<double> > new_data, bool debug=false);
    MultiRes2D(int width, int height, bool debug=false);

    // Updating class variables (Getters and setters)
    int getWidth();
    int getHeight();
    int getRowDecomp();
    int getColDecomp();
    void setCurrentValue(int col, int row, double val);
    void setPreviousValue(int col, int row, double val);
    void addRow();
    void addColumn();
    void deleteRow();
    void deleteColumn();
    bool noDecomp();
    std::vector< std::vector<double> > getCurrent();
    std::vector< std::vector<double> > getPrevious();

    // Helper functions
    int mod(int value1, int value2);
    bool increaseRows(int numRows);
    bool increaseCols(int numCols);
    void printCurrent();
    void printPrevious();

    // Decomposition functions
    bool decompRowsHaar(bool partial=true);
    bool decompColsHaar(bool partial=true);
    bool decompRowsChaikin(bool partial=true);
    bool decompColsChaikin(bool partial=true);
    bool decompRowsCubic(bool partial=true);
    bool decompColsCubic(bool partial=true);

    // Reconstruction functions
    int reconstruct();
    void reconstRowsHaar(bool partial=true);
    void reconstColsHaar(bool partial=true);
    void reconstRowsChaikin(bool partial=true);
    void reconstColsChaikin(bool partial=true);
    void reconstRowsCubic(bool partial=true);
    void reconstColsCubic(bool partial=true);
};

#endif
