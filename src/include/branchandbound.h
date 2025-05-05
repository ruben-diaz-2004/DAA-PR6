/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Diseño y Análisis de Algoritmos 2024-2025
  *
  * @author Rubén Díaz Marrero 
  * @date 25/03/2025
  * @brief Maximum Diversity Problem
  */
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
    int m_;
    int lrc_;
    int nodesExplored_ = 0;
    double calculateUpperBound(const std::vector<Element>& selected, const std::vector<Element>& candidates, double currentDiversity);
    double calculateDiversityContribution(const Element& element, const std::vector<Element>& selected);
};

#endif // BRANCHANDBOUND_H