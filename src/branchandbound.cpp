#include "include/branchandbound.h"
#include "include/grasp.h"
#include "include/bnbnode.h"
#include "include/element.h"
#include "include/utils.h"
#include <queue>
#include <memory>
#include <algorithm>
#include <limits>
#include <set>

std::vector<Element> BranchAndBoundAlgorithm::solve() {
  std::vector<Element> bestSolution;
  double bestDiversity = 0.0;
  std::vector<Element> allElements = instance_.getElements();
  GraspAlgorithm grasp(instance_, m_, lrc_, 10);
  std::vector<Element> greedySolution = grasp.solve();
  bestDiversity = evaluateDiversity(greedySolution);
  bestSolution = greedySolution;
  std::cout << "Initial lower bound (grasp solution): " << bestDiversity << std::endl;
  if (m_ >= allElements.size()) {
    return allElements;
  }
  // Priority queue to manage nodes - uses a max heap based on upper bounds
  std::priority_queue<std::shared_ptr<BnBNode>, std::vector<std::shared_ptr<BnBNode>>, BnBNodeComparator> queue;
  std::vector<Element> empty;
  double rootUpperBound = calculateUpperBound(empty, allElements, 0.0);
  auto rootNode = std::make_shared<BnBNode>(empty, allElements, 0.0, rootUpperBound, 0);
  queue.push(rootNode);
  while (!queue.empty()) {
    auto currentNode = queue.top();
    queue.pop();
    nodesExplored_++;
    if (currentNode->upperBound <= bestDiversity) { // If this node's upper bound is not better than our current best solution, prune it
      continue;
    }
    if (currentNode->selected.size() == m_) {     // If we've selected m elements, check if it's a better solution
      if (currentNode->currentDiversity > bestDiversity) {
        bestDiversity = currentNode->currentDiversity;
        bestSolution = currentNode->selected;
      }
      continue;
    }
    // Try to expand this node
    for (size_t i = 0; i < currentNode->candidates.size(); i++) {
      const Element& candidate = currentNode->candidates[i];
      // Create a new selection by adding this candidate
      std::vector<Element> newSelected = currentNode->selected;
      newSelected.push_back(candidate);
      // Create a new candidate list excluding the selected element
      std::vector<Element> newCandidates;
      for (size_t j = 0; j < currentNode->candidates.size(); j++) {
        if (j != i) {
          newCandidates.push_back(currentNode->candidates[j]);
        }
      }
      // Calculate diversity contribution of adding this element
      double diversityContribution = calculateDiversityContribution(candidate, currentNode->selected);
      double newDiversity = currentNode->currentDiversity + diversityContribution;
      double upperBound = calculateUpperBound(newSelected, newCandidates, newDiversity);
      // If upper bound is better than current best solution, add to queue
      if (upperBound > bestDiversity) {
        auto newNode = std::make_shared<BnBNode>(newSelected, newCandidates, newDiversity, upperBound, currentNode->level + 1);
        queue.push(newNode);
      }
    }
  }
  std::cout << "Branch and Bound explored " << nodesExplored_ << " nodes" << std::endl;
  return bestSolution;
}

/**
 * @brief Calculate the contribution of an element to the diversity of the selected set.
 * @param element The element to evaluate.
 * @param selected The currently selected elements.
 * @return The contribution of the element to the diversity.
 */
double BranchAndBoundAlgorithm::calculateDiversityContribution(const Element& element, const std::vector<Element>& selected) {
  double contribution = 0.0;
  for (const auto& existingElement : selected) {
    contribution += calculateDistance(element.getNodes(), existingElement.getNodes());
  }
  return contribution;
}

/**
 * @brief Calculate the upper bound for the diversity of a node in the branch and bound tree.
 * @param selected The currently selected elements.
 * @param candidates The remaining candidate elements.
 * @param currentDiversity The current diversity of the selected set.
 * @return The upper bound for the diversity.
 */
double BranchAndBoundAlgorithm::calculateUpperBound(const std::vector<Element>& selected, const std::vector<Element>& candidates, double currentDiversity) {
  if (selected.size() >= m_ || candidates.empty()) {
    return currentDiversity;
  }
  int remainingToSelect = m_ - selected.size();
  // Paso 1: Agregar diversidad actual
  double upperBound = currentDiversity;
  // Paso 2: Calcular contribuciones individuales de cada candidato al conjunto actual
  std::vector<double> contributionsToSelected;
  for (const auto& candidate : candidates) {
    double contribution = 0.0;
    for (const auto& sel : selected) {
      contribution += calculateDistance(candidate.getNodes(), sel.getNodes());
    }
    contributionsToSelected.push_back(contribution);
  }
  // Ordenar y sumar las k mayores contribuciones
  std::sort(contributionsToSelected.begin(), contributionsToSelected.end(), std::greater<double>());
  for (int i = 0; i < std::min(remainingToSelect, (int)contributionsToSelected.size()); ++i) {
    upperBound += contributionsToSelected[i];
  }
  // Paso 3: Estimar la mejor diversidad posible entre los nuevos seleccionados (las distancias entre pares de los candidatos)
  std::vector<std::pair<int, int>> selectedIndices;
  int n = candidates.size();
  // Calcular y guardar todas las distancias entre pares de candidatos
  std::vector<double> pairwiseDistances;
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      double dist = calculateDistance(candidates[i].getNodes(), candidates[j].getNodes());
      pairwiseDistances.push_back(dist);
    }
  }
  // Ordenar de mayor a menor
  std::sort(pairwiseDistances.begin(), pairwiseDistances.end(), std::greater<double>());
  // Calcular cuántos pares únicos puede haber entre los nuevos elementos
  int maxPairs = (remainingToSelect * (remainingToSelect - 1)) / 2;
  // Sumar las distancias más grandes posibles entre los nuevos seleccionados
  for (int i = 0; i < std::min(maxPairs, (int)pairwiseDistances.size()); ++i) {
    upperBound += pairwiseDistances[i];
  }

  return upperBound;
}