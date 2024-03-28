#ifndef FILTERS_H
#define FILTERS_H

#include <vector>

std::vector< std::vector<double> > getAFilter(int decompDegree);
std::vector< std::vector<double> > getBFilter(int decompDegree);
std::vector< std::vector<double> > getPFilter(int decompDegree);
std::vector< std::vector<double> > getQFilter(int decompDegree);
std::vector< std::vector<double> > getReconFilter(int decompDegree);

#endif
