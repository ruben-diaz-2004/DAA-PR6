#ifndef LOCALSEARCH_H
#define LOCALSEARCH_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include "probleminstance.h"
#include "solution.h"


class LocalSearch {
public:
  LocalSearch(Solution& solution, int m)
      : solution_(solution), m_(m) {}

  // Perform local search to improve the solution
  void runLocalSearch();

private:
  Solution& solution_;
  int m_;
};

#endif // LOCALSEARCH_H