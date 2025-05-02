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

// Node structure for the branch and bound tree
struct BnBNode {
    std::vector<Element> selected;     // Elements currently selected in this node
    std::vector<Element> candidates;   // Remaining candidate elements
    double currentDiversity;          // Current diversity value
    double upperBound;                // Upper bound for this node
    int level;                        // Current level in the search tree

    // Constructor
    BnBNode(const std::vector<Element>& sel, const std::vector<Element>& cand, 
            double diversity, double ub, int lev) 
        : selected(sel), candidates(cand), currentDiversity(diversity), 
          upperBound(ub), level(lev) {}

    // Comparison operator for priority queue (min-heap based on upper bound)
    bool operator<(const BnBNode& other) const {
        return upperBound < other.upperBound;  // Smaller upper bound = higher priority
    }
};

// Custom comparator for priority queue (max-heap based on upper bound)
struct BnBNodeComparator {
    bool operator()(const std::shared_ptr<BnBNode>& a, const std::shared_ptr<BnBNode>& b) const {
        return a->upperBound < b->upperBound;  // Smaller upper bound = lower priority
    }
};

class BranchAndBoundAlgorithm : public Algorithm {
public:
    BranchAndBoundAlgorithm(ProblemInstance& instance, int m)
        : Algorithm(instance), m_(m) {}

    std::vector<Element> solve() override;

private:
    int m_;  // Number of elements to select
    
    // Calculate upper bound for a node
    double calculateUpperBound(const std::vector<Element>& selected, 
                              const std::vector<Element>& candidates,
                              double currentDiversity);
    
    // Get lower bound using greedy algorithm
    double getLowerBound(const std::vector<Element>& initialElements, int numToSelect);
    
    // Calculate diversity contribution of a new element
    double calculateDiversityContribution(const Element& element, 
                                         const std::vector<Element>& selected);
};

#endif // BRANCHANDBOUND_H