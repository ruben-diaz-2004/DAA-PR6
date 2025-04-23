#include "include/localsearch.h"
#include "include/element.h"
#include "include/solution.h"


void LocalSearch::runLocalSearch() {
    std::vector<Element> currentSolution = solution_.getSelectedElements();
    double bestDiversity = solution_.evaluateDiversity(solution_.getSelectedElements());
    bool improved = true;

    while (improved) {
        improved = false;
        // Try to replace each element in the current solution
        for (size_t i = 0; i < currentSolution.size(); ++i) {
            Element originalElement = currentSolution[i];
            // Try to replace with each element not in the current solution
            for (const auto& candidate : solution_.getAllElements()) {
                if (std::find(currentSolution.begin(), currentSolution.end(), candidate) == currentSolution.end()) {
                    // Replace and evaluate
                    currentSolution[i] = candidate;
                    double newDiversity = solution_.evaluateDiversity(currentSolution);

                    // Check if the new solution is better
                    if (newDiversity > bestDiversity) {
                        bestDiversity = newDiversity;
                        improved = true;
                        break; // Exit inner loop if improvement found
                    }
                }
            }

            // Restore original element if no improvement was found
            if (!improved) {
                currentSolution[i] = originalElement;
            }
        }
    }

    // Update the solution with the best found
    solution_.setSelectedElements(currentSolution);
}