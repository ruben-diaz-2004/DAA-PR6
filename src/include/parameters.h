/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Computabilidad y Algoritmia 2023-2024
  *
  * @author Rubén Díaz Marrero 
  * @date 25/03/2025
  * @brief 
  */
 
  #ifndef PARAMETERS_H
  #define PARAMETERS_H 
  #include <iostream>
  #include <vector>
  #include <string>
  #include <fstream>
  
  
  struct parameters {
    int algorithm = 1;     // 0: no algorithm selected, 1: greedy, 2: grasp, 3: local search, 4: branch and bound
    int graspN = 2;        // Default value for graspN (candidatos)
    int m = 2;  // Default number of elements to select
    int iterations = 10;   // Default number of GRASP iterations
  };
  
  parameters parse_args(int argc, char* argv[]) {
    std::vector<std::string> args(argv + 1, argv + argc);
    parameters options;
    
    // Skip the first argument (input file)
    for (auto it = args.begin() + 1, end = args.end(); it != end; ++it) {
      if (*it == "-greedy") {
        options.algorithm = 1;
      } else if (*it == "-grasp") {
        options.algorithm = 2;
        if (it + 1 != end) {
          options.graspN = std::stoi(*++it);
        }
      } else if (*it == "-ls") {
        options.algorithm = 3;
      } else if (*it == "-bnb") {
        options.algorithm = 4;
      } else if (*it == "-m") {
        if (it + 1 != end) {
          options.m = std::stoi(*++it);
        }
      } else if (*it == "-it") {
        if (it + 1 != end) {
          options.iterations = std::stoi(*++it);
        }
      } else if (*it == "-help") {
        std::cout << "Usage: " << argv[0] << " <input_file> <m> [-greedy | -grasp <n> | -ls | -bnb] [-it <n>]" << std::endl;
        std::cout << "Options:" << std::endl;
        std::cout << "  -greedy: Use greedy algorithm" << std::endl;
        std::cout << "  -grasp <n>: Use GRASP algorithm with n candidates" << std::endl;
        std::cout << "  -ls: Use Local Search algorithm (applies after GRASP)" << std::endl;
        std::cout << "  -bnb: Use Branch and Bound algorithm" << std::endl;
        std::cout << "  -it <n>: Number of iterations for GRASP (default: 10)" << std::endl;
        std::cout << "  -m <m>: Number of elements to select (default: 2)" << std::endl;
        exit(0);
      } else {
        std::cerr << "Error: invalid argument " << *it << std::endl;
        std::cerr << "Usage: " << argv[0] << " <input_file> <m> [-greedy | -grasp <n> | -ls | -bnb]" << std::endl;
      }
    }
    
    return options;
  }
  
    
  #endif // PARAMETERS_H