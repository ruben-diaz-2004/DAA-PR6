/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Diseño y Análisis de Algoritmos 2024-2025
  *
  * @author Rubén Díaz Marrero 
  * @date 25/03/2025
  * @brief Maximum Diversity Problem
  */
#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>
#include <iostream>
#include <string>
#include <numeric>
#include <cmath>
#include "element.h"
#include "utils.h" 

class Solution {
public:
  Solution(const std::vector<Element>& elements)
      : allElements_(elements), selectedElements_() {}
  
  Solution(const std::vector<Element>& allElements, const std::vector<Element>& selectedElements)
      : allElements_(allElements), selectedElements_(selectedElements) {}
  
  void setSelectedElements(const std::vector<Element>& selectedElements) {
      selectedElements_ = selectedElements;
  }
  
  const std::vector<Element>& getAllElements() const { return allElements_; }
  const std::vector<Element>& getSelectedElements() const { return selectedElements_; }
  
  void printSolution() const {
    std::cout << "Selected " << selectedElements_.size() << " elements:\n";
    for (const auto& element : selectedElements_) {
      std::cout << "Element ID: " << element.getId() << " - Coordinates: ";
      const auto& nodes = element.getNodes();
      for (const auto& node : nodes) {
        std::cout << node << " ";
      }
      std::cout << "\n";
    }
    std::cout << "Total diversity: " << evaluateDiversity(selectedElements_) << std::endl;
  }

  std::string toString() const {
    std::string result = "";
    for (const auto& element : selectedElements_) {
      // result += element.Nodes() + " ";
      result += std::to_string(element.getId()) + " ";
    }
    return result;
  }
private:
  std::vector<Element> allElements_;
  std::vector<Element> selectedElements_;
};

#endif // SOLUTION_H