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

