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
#include "include/greedy.h"
#include "include/element.h"


std::vector<Element> GreedyAlgorithm::solve() {
  std::vector<Element> Elem = instance_.getElements(); // All elements
  std::vector<Element> S;  // Solution set
  S.reserve(m_);
  std::vector<double> sc = calculateCenterOfGravity(Elem);

  while (S.size() < m_) {
    int farthestIdx = findFarthestElement(Elem, sc);
    if (farthestIdx == -1) break; // No more elements
    S.push_back(Elem[farthestIdx]);
    Elem.erase(Elem.begin() + farthestIdx);
    sc = calculateCenterOfGravity(S);
  }
  
  return S;
}

