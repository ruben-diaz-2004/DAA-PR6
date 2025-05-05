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
#include "include/localsearch.h"
#include "include/element.h"
#include "include/solution.h"
#include "include/utils.h"


std::vector<Element> LocalSearch::runLocalSearch() {
  std::vector<Element> currentSolution = solution_.getSelectedElements();
  double currentDiversity = evaluateDiversity(currentSolution);
  bool improved = true;

  while (improved) {
    improved = false;
    for (size_t i = 0; i < currentSolution.size(); ++i) {
      Element originalElement = currentSolution[i];
      double bestSwapDiversity = currentDiversity;
      Element bestCandidate = originalElement;
      for (const auto& candidate : solution_.getAllElements()) {
        if (std::find(currentSolution.begin(), currentSolution.end(), candidate) == currentSolution.end()) {
          currentSolution[i] = candidate;
          double newDiversity = evaluateDiversity(currentSolution);
          if (newDiversity > bestSwapDiversity) {
            bestSwapDiversity = newDiversity;
            bestCandidate = candidate;
          }
          currentSolution[i] = originalElement;
        }
      }
      if (bestSwapDiversity > currentDiversity) {
        currentSolution[i] = bestCandidate;
        currentDiversity = bestSwapDiversity;
        improved = true;
      }
    }
  }
  solution_.setSelectedElements(currentSolution);
  return currentSolution;
}