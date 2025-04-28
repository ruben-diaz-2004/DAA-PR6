#ifndef UTILS_H
#define UTILS_H


  // Calculate Euclidean distance between two points
inline double calculateDistance(const std::vector<double>& p1, const std::vector<double>& p2) {
  double sum = 0.0;
  for (size_t i = 0; i < p1.size(); ++i) {
    sum += std::pow(p1[i] - p2[i], 2);
  }
  return std::sqrt(sum);
}

// Evaluates the diversity of the solution (sum of pairwise distances)
inline double evaluateDiversity(const std::vector<Element>& selectedElements) {
  double diversity = 0.0;
  
  for (size_t i = 0; i < selectedElements.size(); ++i) {
    for (size_t j = i + 1; j < selectedElements.size(); ++j) {
      diversity += calculateDistance(selectedElements[i].getNodes(), selectedElements[j].getNodes());
    }
  }
  
  return diversity;
}

#endif // UTILS_H