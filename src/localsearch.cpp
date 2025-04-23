#include "include/localsearch.h"
#include "include/element.h"
#include "include/solution.h"


void LocalSearch::runLocalSearch() {
  std::vector<Element> currentSolution = solution_.getSelectedElements();
  double currentDiversity = solution_.evaluateDiversity(currentSolution);
  bool improved = true;

  while (improved) {
      improved = false;
      
      for (size_t i = 0; i < currentSolution.size(); ++i) {
          Element originalElement = currentSolution[i];
          double bestSwapDiversity = currentDiversity;
          Element bestCandidate = originalElement;
          
          // Try all possible candidates for this position
          for (const auto& candidate : solution_.getAllElements()) {
              if (std::find(currentSolution.begin(), currentSolution.end(), candidate) == currentSolution.end()) {
                  // Try the swap
                  currentSolution[i] = candidate;
                  double newDiversity = solution_.evaluateDiversity(currentSolution);
                  
                  // Keep track of the best candidate
                  if (newDiversity > bestSwapDiversity) {
                      bestSwapDiversity = newDiversity;
                      bestCandidate = candidate;
                  }
                  
                  // Restore for next evaluation
                  currentSolution[i] = originalElement;
              }
          }
          
          // Apply the best swap if an improvement was found
          if (bestSwapDiversity > currentDiversity) {
              currentSolution[i] = bestCandidate;
              currentDiversity = bestSwapDiversity;
              improved = true;
          }
      }
  }
  
  // Update the solution with the best found
  solution_.setSelectedElements(currentSolution);
}