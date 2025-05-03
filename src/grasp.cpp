#include "include/grasp.h"
#include "include/localsearch.h"
#include "include/element.h"
#include "include/utils.h"

std::vector<Element> GraspAlgorithm::solve() {
  std::vector<Element> bestSolution;
  double bestDiversity = -1.0;
  Solution solution(instance_.getElements());
  LocalSearch localSearch(solution, m_);
  
  for (int iter = 0; iter < iterations_; ++iter) {
    std::vector<Element> Elem = instance_.getElements(); // All elements
    std::vector<Element> S;  // Current solution set
    S.reserve(m_);
    std::vector<double> sc = calculateCenterOfGravity(Elem);

    while (S.size() < m_) {
      int farthestIdx = findNFarthestElement(Elem, sc, n_);
      if (farthestIdx == -1) break; // No more elements
      S.push_back(Elem[farthestIdx]);
      Elem.erase(Elem.begin() + farthestIdx);
      sc = calculateCenterOfGravity(S);
    }
    solution.setSelectedElements(S);
    S = localSearch.runLocalSearch();
    double currentDiversity = evaluateDiversity(S);
    if (currentDiversity > bestDiversity) {
      bestDiversity = currentDiversity;
      bestSolution = S;
    }
  }
  return bestSolution;
}
