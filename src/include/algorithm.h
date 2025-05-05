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
#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <iostream>
#include <vector>
#include "probleminstance.h"

class Algorithm {
public:
  Algorithm(ProblemInstance& instance) : instance_(instance) {}

  virtual std::vector<Element> solve() = 0;
protected:
  ProblemInstance& instance_;
  std::vector<double> calculateCenterOfGravity(const std::vector<Element>& elements);
  int findFarthestElement(const std::vector<Element>& elements, const std::vector<double>& center);
  int findNFarthestElement(const std::vector<Element>& elements, const std::vector<double>& center, int n);
};

#endif // ALGORITHM_H