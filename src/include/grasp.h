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