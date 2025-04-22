#include "include/instanceparcer.h"
#include "include/element.h"
#include "include/solution.h"
#include "include/probleminstance.h"


ProblemInstance::ProblemInstance(const std::string& filename) {
    InstanceParser parser(filename);
    elements_ = parser.getElements();
    numElements_ = elements_.size();
    calculateDistanceMatrix();
}

void ProblemInstance::printInstance() const {
  std::cout << "Number of elements: " << numElements_ << "\n";
  for (const auto& element : elements_) {
    std::cout << "Element ID: " << element.getId() << "\n";
    const auto& nodes = element.getNodes();
    std::cout << "Nodes: ";
    for (const auto& node : nodes) {
      std::cout << node << " ";
    }
    std::cout << "\n";
  }
}

void ProblemInstance::calculateDistanceMatrix() {
  distanceMatrix_.resize(numElements_, std::vector<double>(numElements_, 0.0));
  for (size_t i = 0; i < numElements_; ++i) {
    for (size_t j = 0; j < numElements_; ++j) {
      if (i != j) {
        const auto& nodes1 = elements_[i].getNodes();
        const auto& nodes2 = elements_[j].getNodes();
        double distance = 0.0;
        for (size_t k = 0; k < nodes1.size(); ++k) {
          distance += std::pow(nodes1[k] - nodes2[k], 2);
        }
        distanceMatrix_[i][j] = std::sqrt(distance);
      }
    }
  }
}

double ProblemInstance::getDistance(int id1, int id2) const {
    if (id1 < 0 || id1 >= numElements_ || id2 < 0 || id2 >= numElements_) {
        std::cerr << "Error: Invalid element IDs." << std::endl;
        return -1.0;
    }
    return distanceMatrix_[id1][id2];
}