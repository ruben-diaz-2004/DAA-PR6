#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>
#include <iostream>
#include <string>
#include <numeric>
#include <cmath>
#include "element.h"

class Solution {
public:
    Solution(const std::vector<Element>& elements)
        : allElements_(elements), selectedElements_() {}
    
    Solution(const std::vector<Element>& allElements, const std::vector<Element>& selectedElements)
        : allElements_(allElements), selectedElements_(selectedElements) {}
    
    void setSelectedElements(const std::vector<Element>& selectedElements) {
        selectedElements_ = selectedElements;
    }
    
    const std::vector<Element>& getAllElements() const { return allElements_; }
    const std::vector<Element>& getSelectedElements() const { return selectedElements_; }
    
    // Evaluates the diversity of the solution (sum of pairwise distances)
    double evaluateDiversity(const std::vector<Element>& selectedElements) const {
        double diversity = 0.0;
        
        for (size_t i = 0; i < selectedElements.size(); ++i) {
            for (size_t j = i + 1; j < selectedElements.size(); ++j) {
                diversity += calculateDistance(selectedElements[i].getNodes(), selectedElements_[j].getNodes());
            }
        }
        
        return diversity;
    }
    
    void printSolution() const {
        std::cout << "Selected " << selectedElements_.size() << " elements:\n";
        for (const auto& element : selectedElements_) {
            std::cout << "Element ID: " << element.getId() << " - Coordinates: ";
            const auto& nodes = element.getNodes();
            for (const auto& node : nodes) {
                std::cout << node << " ";
            }
            std::cout << "\n";
        }
        std::cout << "Total diversity: " << evaluateDiversity(selectedElements_) << std::endl;
    }

private:
    std::vector<Element> allElements_;
    std::vector<Element> selectedElements_;
    
    // Calculate Euclidean distance between two points
    double calculateDistance(const std::vector<double>& p1, const std::vector<double>& p2) const {
        double sum = 0.0;
        for (size_t i = 0; i < p1.size(); ++i) {
            sum += std::pow(p1[i] - p2[i], 2);
        }
        return std::sqrt(sum);
    }
};

#endif // SOLUTION_H