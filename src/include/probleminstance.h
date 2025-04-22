#ifndef PROBLEM_INSTANCE_H
#define PROBLEM_INSTANCE_H

#include <iostream>
#include "element.h"


class ProblemInstance {
public:
  ProblemInstance(const std::string& filename);
  void printInstance() const;
  const std::vector<Element>& getElements() const { return elements_; }

private:
  std::vector<Element> elements_;
  int numElements_;
  std::vector<std::vector<double>> distanceMatrix_;
  void calculateDistanceMatrix();
};

#endif // PROBLEM_INSTANCE_H