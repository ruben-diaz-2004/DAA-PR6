#include "include/grasp.h"
#include "include/element.h"
#include "include/utils.h"

std::vector<Element> GraspAlgorithm::solve() {
  std::vector<Element> bestSolution;
  double bestDiversity = -1.0;

  for (int iter = 0; iter < iterations_; ++iter) {
    // Initialize
    std::vector<Element> Elem = instance_.getElements(); // All elements
    std::vector<Element> S;  // Current solution set
    S.reserve(m_);

    // Calculate center of gravity of all elements
    std::vector<double> sc = calculateCenterOfGravity(Elem);

    // Build a solution
    while (S.size() < m_) {
      int farthestIdx = findNFarthestElement(Elem, sc, n_);
      if (farthestIdx == -1) break; // No more elements
      
      S.push_back(Elem[farthestIdx]);
      Elem.erase(Elem.begin() + farthestIdx);
      
      // Recalculate center of gravity of S
      sc = calculateCenterOfGravity(S);
    }

    // Evaluate diversity of current solution
    double currentDiversity = evaluateDiversity(S);
    
    // Update best solution if necessary
    if (currentDiversity > bestDiversity) {
      bestDiversity = currentDiversity;
      bestSolution = S;
    }
  }

  return bestSolution;
}
