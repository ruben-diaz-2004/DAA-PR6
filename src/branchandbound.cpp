#include "include/branchandbound.h"
#include "include/element.h"
#include "include/utils.h"
#include <queue>
#include <memory>
#include <algorithm>
#include <limits>
#include <set>

std::vector<Element> BranchAndBoundAlgorithm::solve() {
    // Initialize best solution and best diversity
    std::vector<Element> bestSolution;
    double bestDiversity = 0.0;

    // Get all elements
    std::vector<Element> allElements = instance_.getElements();
    
    // Get an initial lower bound using greedy algorithm
    bestDiversity = getLowerBound(allElements, m_);
    
    std::cout << "Initial lower bound (greedy solution): " << bestDiversity << std::endl;
    
    // If m_ is equal to the total number of elements, return all elements
    if (m_ >= allElements.size()) {
        return allElements;
    }
    
    // Priority queue to manage nodes - uses a max heap based on upper bounds
    std::priority_queue<std::shared_ptr<BnBNode>, 
                        std::vector<std::shared_ptr<BnBNode>>, 
                        BnBNodeComparator> queue;
    
    // Create and add root node
    std::vector<Element> empty;
    double rootUpperBound = calculateUpperBound(empty, allElements, 0.0);
    auto rootNode = std::make_shared<BnBNode>(empty, allElements, 0.0, rootUpperBound, 0);
    queue.push(rootNode);
    
    // Start branch and bound
    int nodesExplored = 0;
    while (!queue.empty()) {
        // Get the node with the highest upper bound
        auto currentNode = queue.top();
        queue.pop();
        nodesExplored++;
        
        // If this node's upper bound is not better than our current best solution, prune it
        if (currentNode->upperBound <= bestDiversity) {
            continue;
        }
        
        // If we've selected m elements, check if it's a better solution
        if (currentNode->selected.size() == m_) {
            if (currentNode->currentDiversity > bestDiversity) {
                bestDiversity = currentNode->currentDiversity;
                bestSolution = currentNode->selected;
            }
            continue;
        }
        
        // Try to expand this node
        for (size_t i = 0; i < currentNode->candidates.size(); i++) {
            const Element& candidate = currentNode->candidates[i];
            
            // Create a new selection by adding this candidate
            std::vector<Element> newSelected = currentNode->selected;
            newSelected.push_back(candidate);
            
            // Create a new candidate list excluding the selected element
            std::vector<Element> newCandidates;
            for (size_t j = 0; j < currentNode->candidates.size(); j++) {
                if (j != i) {
                    newCandidates.push_back(currentNode->candidates[j]);
                }
            }
            
            // Calculate diversity contribution of adding this element
            double diversityContribution = calculateDiversityContribution(candidate, currentNode->selected);
            double newDiversity = currentNode->currentDiversity + diversityContribution;
            
            // Calculate upper bound for this new node
            double upperBound = calculateUpperBound(newSelected, newCandidates, newDiversity);
            
            // If upper bound is better than current best solution, add to queue
            if (upperBound > bestDiversity) {
                auto newNode = std::make_shared<BnBNode>(
                    newSelected, newCandidates, newDiversity, upperBound, currentNode->level + 1
                );
                queue.push(newNode);
            }
        }
    }
    
    std::cout << "Branch and Bound explored " << nodesExplored << " nodes" << std::endl;
    
    return bestSolution;
}

double BranchAndBoundAlgorithm::calculateDiversityContribution(
    const Element& element, const std::vector<Element>& selected) {
    
    double contribution = 0.0;
    for (const auto& existingElement : selected) {
        contribution += calculateDistance(element.getNodes(), existingElement.getNodes());
    }
    return contribution;
}

double BranchAndBoundAlgorithm::calculateUpperBound(
    const std::vector<Element>& selected, const std::vector<Element>& candidates, double currentDiversity) {
    
    if (candidates.empty() || selected.size() >= m_) {
        return currentDiversity;
    }
    
    // Calculate maximum potential contribution from remaining elements
    // We need to select (m_ - selected.size()) more elements from candidates
    int remainingToSelect = m_ - selected.size();
    
    if (remainingToSelect >= candidates.size()) {
        // If we need to select all remaining candidates, calculate exact diversity
        std::vector<Element> completeSet = selected;
        completeSet.insert(completeSet.end(), candidates.begin(), candidates.end());
        return evaluateDiversity(completeSet);
    }
    
    // Calculate all pairwise distances between candidates
    std::vector<std::pair<std::pair<int, int>, double>> candidateDistances;
    for (size_t i = 0; i < candidates.size(); i++) {
        for (size_t j = i + 1; j < candidates.size(); j++) {
            double dist = calculateDistance(candidates[i].getNodes(), candidates[j].getNodes());
            candidateDistances.push_back(std::make_pair(std::make_pair(i, j), dist));
        }
    }
    
    // Sort distances in descending order
    std::sort(candidateDistances.begin(), candidateDistances.end(), 
              [](const auto& a, const auto& b) { return a.second > b.second; });
    
    // Calculate distances from each candidate to already selected elements
    std::vector<double> candidateContributions;
    for (const auto& candidate : candidates) {
        double contribution = 0.0;
        for (const auto& selectedElement : selected) {
            contribution += calculateDistance(candidate.getNodes(), selectedElement.getNodes());
        }
        candidateContributions.push_back(contribution);
    }
    
    // Sort contributions in descending order
    std::sort(candidateContributions.begin(), candidateContributions.end(), std::greater<double>());
    
    // Calculate an upper bound
    double upperBound = currentDiversity;
    
    // Add top k contributions from candidates to selected elements
    for (int i = 0; i < remainingToSelect && i < static_cast<int>(candidateContributions.size()); i++) {
        upperBound += candidateContributions[i];
    }
    
    // Add top possible pairwise distances between newly selected elements
    // We need to be careful not to double-count elements here
    // This is a greedy approximation of the maximum value we could get
    
    // Create a set to keep track of which candidate indices have been used
    std::set<int> usedIndices;
    int pairsAdded = 0;
    int maxPairsToAdd = (remainingToSelect * (remainingToSelect - 1)) / 2;
    
    for (const auto& distPair : candidateDistances) {
        int idx1 = distPair.first.first;
        int idx2 = distPair.first.second;
        
        if (usedIndices.size() < remainingToSelect || 
            (usedIndices.find(idx1) != usedIndices.end() && usedIndices.find(idx2) != usedIndices.end())) {
            
            if (usedIndices.find(idx1) == usedIndices.end() && usedIndices.size() < remainingToSelect) {
                usedIndices.insert(idx1);
            }
            
            if (usedIndices.find(idx2) == usedIndices.end() && usedIndices.size() < remainingToSelect) {
                usedIndices.insert(idx2);
            }
            
            if (usedIndices.find(idx1) != usedIndices.end() && usedIndices.find(idx2) != usedIndices.end()) {
                upperBound += distPair.second;
                pairsAdded++;
                
                if (pairsAdded >= maxPairsToAdd) {
                    break;
                }
            }
        }
    }
    
    return upperBound;
}

double BranchAndBoundAlgorithm::getLowerBound(const std::vector<Element>& initialElements, int numToSelect) {
    // Create a temporary instance with the initial elements
    ProblemInstance tempInstance = instance_;
    
    // Create and run a greedy algorithm
    GreedyAlgorithm greedy(tempInstance, numToSelect);
    std::vector<Element> greedySolution = greedy.solve();
    
    // Return the diversity of the greedy solution
    return evaluateDiversity(greedySolution);
}