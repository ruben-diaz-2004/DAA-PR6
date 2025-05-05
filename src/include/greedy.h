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
  int m_;
  std::vector<Element> selectedElements_;
};

#endif // GREEDY_H