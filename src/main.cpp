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
#include <iostream>
#include <string>
#include <cmath>
#include <memory>
#include <chrono>
#include "include/probleminstance.h"
#include "include/solution.h"
#include "include/instanceparcer.h"
#include "include/element.h"
#include "include/parameters.h"
#include "include/algorithm.h"
#include "include/greedy.h"
#include "include/grasp.h"
#include "include/localsearch.h"
#include "include/branchandbound.h"
#include "include/utils.h"

int main(int argc, char* argv[]) {
  // Check if input file and m are provided
  if (argc < 3) {
    std::cerr << "Error: Insufficient arguments." << std::endl;
    std::cerr << "Usage: " << argv[0] << " <input_file> <m> [-greedy | -grasp <n> | -bnb]" << std::endl;
    return 1;
  }
  
  // Parse parameters
  parameters options = parse_args(argc, argv);
  
  // Load problem instance
  ProblemInstance instance(argv[1]);
  std::cout << "Instance loaded successfully.\n";
  int nodesExplored = 0;
  
  // Solution object
  Solution solution(instance.getElements());
  
  // Measure CPU time
  auto start_time = std::chrono::high_resolution_clock::now();

  // Check algorithm type
  switch (options.algorithm) {
    case 1: { // Greedy algorithm
      std::cout << "Using Greedy Algorithm...\n";
      GreedyAlgorithm greedy(instance, options.m);
      solution.setSelectedElements(greedy.solve());
      break;
    }
    case 2: { // GRASP algorithm
      std::cout << "Using GRASP Algorithm...\n";
      GraspAlgorithm grasp(instance, options.m, options.graspN, options.iterations);
      solution.setSelectedElements(grasp.solve());
      break;
    }
    case 3: { // Local Search algorithm
      std::cout << "Using Local Search Algorithm...\n";
      GraspAlgorithm grasp(instance, options.m, options.graspN, options.iterations);
      solution.setSelectedElements(grasp.solve());
      LocalSearch localSearch(solution, options.m);
      localSearch.runLocalSearch();
      break;
    }
    case 4: { // Branch and Bound algorithm
      std::cout << "Using Branch and Bound Algorithm...\n";
      BranchAndBoundAlgorithm bnb(instance, options.m, options.graspN);
      solution.setSelectedElements(bnb.solve());
      nodesExplored = bnb.getNodesExplored();
      break;
    }
    default:
      std::cerr << "Error: No algorithm selected." << std::endl;
      return 1;
  }
  
  // Calculate CPU time
  auto end_time = std::chrono::high_resolution_clock::now();
  double cpu_time = std::chrono::duration<double>(end_time - start_time).count();
  
  // Print results
  std::cout << "\n==== Solution ====\n";
  solution.printSolution();
  std::cout << "\nCPU time: " << cpu_time << " seconds\n";
  
  // Extract filename for reporting
  std::string filename = argv[1];
  size_t last_slash = filename.find_last_of("/\\");
  if (last_slash != std::string::npos) {
    filename = filename.substr(last_slash + 1);
  }
  
  // Print result in unified format for later processing
  std::cout << "RESULTADO," << filename << ", " << instance.getN() << ", " << instance.getK() << ", " << options.m << ", " << evaluateDiversity(solution.getSelectedElements()) << ", " << solution.toString() << ", " << cpu_time << ", " << nodesExplored << std::endl;

  return 0;
}