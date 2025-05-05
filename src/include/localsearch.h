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

  std::vector<Element> runLocalSearch();

private:
  Solution& solution_;
  int m_;
};

#endif // LOCALSEARCH_H