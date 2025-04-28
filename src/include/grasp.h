#ifndef GRASP_H
#define GRASP_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "probleminstance.h"
#include "solution.h"
#include "element.h"
#include "algorithm.h"

class GraspAlgorithm : public Algorithm {
public:
  GraspAlgorithm(ProblemInstance& instance, int m, int n, int iterations)
    : Algorithm(instance), m_(m), n_(n), iterations_(iterations) {
    selectedElements_.reserve(m_);
  }

  std::vector<Element> solve() override;

private:
  int m_; // Number of elements to select
  int n_; // Number of elements to sample
  int iterations_; // Number of GRASP iterations
  std::vector<Element> selectedElements_;
};

#endif // GRASP_H