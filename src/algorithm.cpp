#include "include/algorithm.h"
#include "include/element.h"

#include <cmath>
#include <limits>
#include <algorithm>
#include <random>
#include <utility>

std::vector<double> Algorithm::calculateCenterOfGravity(const std::vector<Element>& elements) {
    std::vector<double> center(elements[0].getNodes().size(), 0.0);
    // Sum up the coordinates of all elements
    for (const auto& element : elements) {
        const auto& nodes = element.getNodes();
        for (size_t i = 0; i < nodes.size(); ++i) {
            center[i] += nodes[i];
        }
    }
    // Average the coordinates
    for (auto& coord : center) {
        coord /= elements.size();
    }
    return center;
}

int Algorithm::findFarthestElement(const std::vector<Element>& elements, const std::vector<double>& center) {
    double maxDistance = -1.0;
    int farthestIdx = -1;

    for (size_t i = 0; i < elements.size(); ++i) {
        const auto& nodes = elements[i].getNodes();
        double distance = 0.0;
        for (size_t j = 0; j < nodes.size(); ++j) {
            distance += std::pow(nodes[j] - center[j], 2);
        }
        distance = std::sqrt(distance);

        if (distance > maxDistance) {
            maxDistance = distance;
            farthestIdx = static_cast<int>(i);
        }
    }
    return farthestIdx;
}

int Algorithm::findNFarthestElement(const std::vector<Element>& elements, const std::vector<double>& center, int n) {
  std::vector<std::pair<int, double>> distances;
  distances.reserve(elements.size());

  for (size_t i = 0; i < elements.size(); ++i) {
    const auto& nodes = elements[i].getNodes();
    double distanceSquared = 0.0;
    for (size_t j = 0; j < nodes.size(); ++j) {
        double diff = nodes[j] - center[j];
        distanceSquared += diff * diff;
    }
    distances.emplace_back(static_cast<int>(i), std::sqrt(distanceSquared));
  }
  // Partially sort only the top-n elements
  std::partial_sort(distances.begin(), distances.begin() + n, distances.end(),
    [](const auto& a, const auto& b) {
        return a.second > b.second; // Descending order
    });
  // Use C++11 random engine
  static std::mt19937 rng(std::random_device{}());
  std::uniform_int_distribution<int> dist(0, n - 1);
  int randomIndex = dist(rng);
  return distances[randomIndex].first;
}