#ifndef BRANCHANDBOUND_H
#define BRANCHANDBOUND_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <memory>
#include "probleminstance.h"
#include "solution.h"
#include "element.h"
#include "greedy.h"
#include "algorithm.h"


class BranchAndBoundAlgorithm : public Algorithm {
public:
    BranchAndBoundAlgorithm(ProblemInstance& instance, int m, int lrc): Algorithm(instance), m_(m), lrc_(lrc) {}
    std::vector<Element> solve() override;
    // Get the number of nodes explored
    int getNodesExplored() const { return nodesExplored_; }
private:
    int m_;  // Number of elements to select
    int lrc_; // Local search radius for GRASP
    int nodesExplored_ = 0; // Number of nodes explored in the search tree
    // Get greedy solution for initial lower bound
    std::vector<Element> getGraspSolution(const std::vector<Element>& elements, int numToSelect, int lrc);
    // Calculate upper bound for a node
    double calculateUpperBound(const std::vector<Element>& selected, const std::vector<Element>& candidates, double currentDiversity);
    // Get lower bound using greedy algorithm
    double getLowerBound(const std::vector<Element>& initialElements, int numToSelect);
    // Calculate diversity contribution of a new element
    double calculateDiversityContribution(const Element& element, const std::vector<Element>& selected);
};

#endif // BRANCHANDBOUND_H