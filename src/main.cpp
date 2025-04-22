/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Computabilidad y Algoritmia 2023-2024
  *
  * @author Rubén Díaz Marrero 
  * @date 25/03/2025
  * @brief VRPT-SWTS
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

int main(int argc, char* argv[]) {
  // Check if input file is provided
  // if (argc < 2) {
  //   std::cerr << "Error: No input file provided." << std::endl;
  //   std::cerr << "Usage: " << argv[0] << " <input_file> [-greedy | -grasp <n>]" << std::endl;
  //   return 1;
  // }
  // parameters options = parse_args(argc, argv);
  ProblemInstance instance(argv[1]);
  instance.printInstance();
  // Solution solution = Solution();

  // Para medir el tiempo de CPU
  // auto start_time = std::chrono::high_resolution_clock::now();

  // Calcular tiempo de CPU
  // auto end_time = std::chrono::high_resolution_clock::now();
  // double cpu_time = std::chrono::duration<double>(end_time - start_time).count();
  // Extraer el nombre del archivo de la ruta completa
  // std::string filename = argv[1];
  // size_t last_slash = filename.find_last_of("/\\");
  // if (last_slash != std::string::npos) {
  //   filename = filename.substr(last_slash + 1);
  // }
  // Imprimir resultados en formato uniforme para facilitar el procesamiento posterior
  // std::cout << "RESULTADO," << filename << "," << num_vehicles << "," << total_time << "," << cpu_time << std::endl;

  return 0;
}