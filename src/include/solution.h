#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>
#include <iostream>
#include <string>
#include "element.h"

class Solution {
public:
  Solution(const std::vector<Element>& elements)
    :elements_(elements) {
      solution_.resize(elements.size(), false);
    }

  const std::vector<Element>& getElements() const { return elements_; }

  void printSolution() const {
    for (const auto& element : elements_) {
      std::cout << "Element ID: " << element.getId() << "\n";
    }
  }

private:
  std::vector<Element> elements_;
  std::vector<bool> solution_;
};

#endif // SOLUTION_H