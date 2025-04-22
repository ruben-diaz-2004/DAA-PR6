#ifndef GREEDY_H
#define GREEDY_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "probleminstance.h"
#include "solution.h"
#include "element.h"
#include "algorithm.h"

class GreedyAlgorithm : public Algorithm {
public:
  GreedyAlgorithm(ProblemInstance& instance, int m): Algorithm(instance), m_(m) {
    selectedElements_.reserve(m_);
  }

  std::vector<Element> solve() override;

private:
  int m_; // Number of elements to select
  std::vector<Element> selectedElements_;
};

#endif // GREEDY_H