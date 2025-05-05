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
#ifndef PROBLEM_INSTANCE_H
#define PROBLEM_INSTANCE_H

#include <iostream>
#include <vector>
#include <cmath>
#include "element.h"

class ProblemInstance {
public:
  ProblemInstance(const std::string& filename);
  void printInstance() const;
  const std::vector<Element>& getElements() const { return elements_; }
  double getDistance(int id1, int id2) const;
  int getN() const { return n_; }
  int getK() const { return K_; }
  
private:
  std::vector<Element> elements_;
  int numElements_;
  std::vector<std::vector<double>> distanceMatrix_;
  int n_;
  int K_;
  void calculateDistanceMatrix();
};

#endif // PROBLEM_INSTANCE_H