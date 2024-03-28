#include <vector>

#include "headers/MultiRes2D.h"
#include "headers/MultiRes1D.h"

using namespace std;

// Main function for testing purposes
int main() {
    MultiRes1D obj1(10, true);
    obj1.printX();
    obj1.printY();
    obj1.addPoint(5, 5);
    obj1.addPoint(5, 6);
    obj1.addPoint(6, 5);
    obj1.deletePoint(5, 6);
    obj1.deletePoint(5, 6);
    obj1.movePoint(6, 5, 3.91, 4.2);
    obj1.movePoint(3.91, 4.19, 1, 1);
    obj1.movePoint(3.9, 4.2, 2, 2);
    obj1.movePoint(3.91, 4.2, 9, 9);
    int index = obj1.getPointIndex(8.95, 8.95, 0.1);
    int index2 = obj1.getPointIndex(8.95, 8.95, 0.01);
    obj1.movePoint(3.5, 4.5, index);
    obj1.movePoint(2, 4, 0);
    obj1.movePoint(1, 3, -1);
    obj1.printX();
    obj1.printY();
    cout << "********************************************************" << endl << endl;

    vector<double> testX;
    vector<double> testY;
    for (int i = 0; i < 16; i++) {
        testX.push_back((i*i)%59);
        testY.push_back((i*i+i)%37);
    }
    MultiRes1D obj2(testX, testY, true);
    obj2.printX();
    obj2.printY();
    
    /*obj2.decompHaarClosed();
    obj2.decompHaarClosed(false);
    obj2.decompHaarClosed();
    obj2.reconstructClosed();
    obj2.reconstructClosed();
    obj2.reconstructClosed();*/

    /*obj2.decompChaikinClosed();
    obj2.decompChaikinClosed(false);
    obj2.decompChaikinClosed();
    obj2.reconstructClosed();
    obj2.reconstructClosed();
    obj2.reconstructClosed();*/

    /*obj2.decompCubicClosed();
    obj2.decompCubicClosed();
    obj2.reconstructClosed();
    obj2.reconstructClosed();*/

    obj2.decompChaikinOpen();
    obj2.decompChaikinOpen(false);
    obj2.reconstructOpen();
    obj2.reconstructOpen();

    /*MultiRes2D obj(5, 8, true);
    obj.printCurrent();
    obj.setValue(0, 0, 5.6);
    obj.setValue(4, 7, 2.1);
    obj.setValue(5, 8, 3);
    obj.printCurrent();

    vector< vector<double>  > test;
    int j = 0;
    for (int i = 0; i < 14; i++) {
        vector<double> vec;
        for (int k = 0; k < 14; k++) {
            vec.push_back(j);
            j+=1;
        }
        test.push_back(vec);
    }
    MultiRes2D obj2(test, true);
    obj2.printCurrent();

    obj2.decompColsHaar();
    obj2.decompColsHaar();
    obj2.decompColsHaar();
    obj2.decompRowsHaar();
    obj2.decompColsHaar();
    obj2.decompRowsHaar();
    obj2.reconstruct();
    obj2.reconstruct();
    obj2.reconstruct();
    obj2.reconstruct();
    obj2.reconstruct();
    obj2.reconstruct();
    obj2.reconstruct();
    obj2.reconstruct();
    

    obj2.decompColsChaikin();
    obj2.decompColsChaikin();
    obj2.decompColsChaikin();
    obj2.decompRowsChaikin();
    obj2.decompColsChaikin();
    obj2.reconstruct();
    obj2.reconstruct();
    obj2.reconstruct();
    obj2.reconstruct();
    obj2.reconstruct();

    cout << endl;
    cout << "0 - " << obj2.mod(0, 10) << endl;
    cout << "0 - " <<  obj2.mod(10, 10) << endl;
    cout << "1 - " <<  obj2.mod(11, 10) << endl;
    cout << "8 - " <<  obj2.mod(18, 10) << endl;
    cout << "8 - " <<  obj2.mod(8, 10) << endl;
    cout << "9 - " <<  obj2.mod(-1, 10) << endl;
    cout << "0 - " <<  obj2.mod(-10, 10) << endl;
    cout << "5 - " <<  obj2.mod(-5, 10) << endl;
    cout << "7 - " <<  obj2.mod(-23, 10) << endl;

    obj2.decompRowsCubic();
    obj2.decompColsCubic();
    obj2.decompColsChaikin();
    obj2.decompColsChaikin();
    obj2.decompRowsChaikin();
    obj2.decompRowsHaar();
    obj2.decompColsHaar();
    obj2.decompRowsHaar();
    obj2.reconstruct();
    obj2.reconstruct();
    obj2.reconstruct();
    obj2.reconstruct();
    obj2.reconstruct();
    obj2.reconstruct();
    obj2.reconstruct();
    obj2.reconstruct();
    obj2.reconstruct();
    obj2.decompRowsCubic();
    obj2.decompRowsCubic();
    obj2.decompColsCubic();
    obj2.decompColsHaar();
    obj2.decompRowsHaar();*/

    
    return 0;
}
