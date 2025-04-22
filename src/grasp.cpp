#include "include/grasp.h"
#include "include/element.h"

std::vector<Element> GraspAlgorithm::solve() {
  // Initialize
  std::vector<Element> Elem = instance_.getElements(); // All elements
  std::vector<Element> S;  // Solution set
  S.reserve(m_);
  
  // Calculate center of gravity of all elements
  std::vector<double> sc = calculateCenterOfGravity(Elem);
  
  // Main loop
  while (S.size() < m_) {
    // Find element farthest from center of gravity
    int farthestIdx = findNFarthestElement(Elem, sc, n_);
    if (farthestIdx == -1) break; // No more elements
    
    // Add to solution and remove from available elements
    S.push_back(Elem[farthestIdx]);
    Elem.erase(Elem.begin() + farthestIdx);
    
    // Recalculate center of gravity of S
    sc = calculateCenterOfGravity(S);
  }
  
  return S;
}