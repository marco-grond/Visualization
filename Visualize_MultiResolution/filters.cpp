#include "headers/filters.h"

using namespace std;

/**
* Computes and returns the A-filter of the selected order, which is used to compute the 
* coarse approximation of the data.
*/
vector< vector<double> > getAFilter(int decompDegree) {
    vector<double> filt;
    vector< vector<double> > ret;
    if (decompDegree == 0) {
        filt.push_back(0.5);
        filt.push_back(0.5);
    } else if (decompDegree == 1) {
        filt.push_back(-1.0/6);
        filt.push_back(2.0/6);
        filt.push_back(4.0/6);
        filt.push_back(2.0/6);
        filt.push_back(-1.0/6);
    } else if (decompDegree == 2) {
        filt.push_back(-1.0/4);
        filt.push_back(3.0/4);
        filt.push_back(3.0/4);
        filt.push_back(-1.0/4);
    } else if (decompDegree == 3) {
        filt.push_back(0.125);
        filt.push_back(-0.5);
        filt.push_back(0.375);
        filt.push_back(1);
        filt.push_back(0.375);
        filt.push_back(-0.5);
        filt.push_back(0.125);
    }

    ret.push_back(filt);
    return ret;
}

/**
* Computes and returns the B-filter of the selected order, which is used to compute the 
* details lost when approximating the data
*/
vector< vector<double> > getBFilter(int decompDegree) {
    vector<double> filt;
    vector< vector<double> > ret;
    if (decompDegree == 0) {
        filt.push_back(0.5);
        filt.push_back(-0.5);
    } else if (decompDegree == 1) {
        filt.push_back(-1.0/2);
        filt.push_back(1.0);
        filt.push_back(-1.0/2);
    } else if (decompDegree == 2) {
        filt.push_back(1.0/4);
        filt.push_back(-3.0/4);
        filt.push_back(3.0/4);
        filt.push_back(-1.0/4);
    } else if (decompDegree == 3) {
        filt.push_back(-0.125);
        filt.push_back(0.5);
        filt.push_back(-0.75);
        filt.push_back(0.5);
        filt.push_back(-0.125);
    }

    ret.push_back(filt);
    return ret;
}

/**
* Computes and returns the P-filter of the selected order, which is used to reconstruct
* the fine data from the coarse data
*/
vector< vector<double> > getPFilter(int decompDegree) {
    vector<double> filt;
    vector< vector<double> > ret;
    if (decompDegree == 0) {
        filt.push_back(1.0);
        filt.push_back(1.0);
    } else if (decompDegree == 1) {
        filt.push_back(1.0/2);
        filt.push_back(1.0);
        filt.push_back(1.0/2);
    } else if (decompDegree == 2) {
        filt.push_back(1.0/4);
        filt.push_back(3.0/4);
        filt.push_back(3.0/4);
        filt.push_back(1.0/4);
    } else if (decompDegree == 3) {

    }

    ret.push_back(filt);
    return ret;
}

/**
* Computes and returns the Q-filter of the selected order, which is used to reconstruct
* the fine data from the saved details
*/
vector< vector<double> > getQFilter(int decompDegree) {
    vector<double> filt;
    vector< vector<double> > ret;
    if (decompDegree == 0) {
        filt.push_back(1.0);
        filt.push_back(-1.0);
    } else if (decompDegree == 1) {
        filt.push_back(-1.0/6);
        filt.push_back(-2.0/6);
        filt.push_back(4.0/6);
        filt.push_back(-2.0/6);
        filt.push_back(-1.0/6);
    } else if (decompDegree == 2) {
        filt.push_back(-1.0/4);
        filt.push_back(-3.0/4);
        filt.push_back(3.0/4);
        filt.push_back(1.0/4);
    } else if (decompDegree == 3) {
        
    }

    ret.push_back(filt);
    return ret;
}

/**
* 
*/
vector< vector<double> > getReconFilter(int decompDegree) {
    vector<double> filt1, filt2;
    vector< vector<double> > ret;
    switch(decompDegree) {
        case 0:
                filt1.push_back(1);
                filt1.push_back(1);

                filt2.push_back(1);
                filt2.push_back(-1);
                break;
        case 2:
                filt1.push_back(0.75);
                filt1.push_back(0.25);
                filt1.push_back(0.75);
                filt1.push_back(-0.25);

                filt2.push_back(0.25);
                filt2.push_back(0.75);
                filt2.push_back(0.25);
                filt2.push_back(-0.75);
                break;
        case 3:
                filt1.push_back(0.5);
                filt1.push_back(0.5);
                filt1.push_back(0.5);
                filt1.push_back(-1);
                filt1.push_back(0.5);

                filt2.push_back(0.125);
                filt2.push_back(0.75);
                filt2.push_back(0.125);
                filt2.push_back(0.125);
                filt2.push_back(0.375);
                filt2.push_back(0.375);
                filt2.push_back(0.125);
                break;
    };

    ret.push_back(filt1);
    ret.push_back(filt2);
    return ret;
}
