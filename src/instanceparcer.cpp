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
#include "include/instanceparcer.h"
#include "include/element.h"
#include <algorithm>

InstanceParser::InstanceParser(const std::string& filename) : filename_(filename) { 
  parse();
}

void InstanceParser::parse() {
  std::ifstream file(filename_);
  if (!file.is_open()) {
    std::cerr << "Error opening file: " << filename_ << std::endl;
    return;
  }
  std::string line;
  int id = 0;
  // First line is the number of elements
  std::getline(file, line);
  int numElements = std::stoi(line);
  n_ = numElements;
  elements_.reserve(numElements);
  // Second line is the dimension (K)
  std::getline(file, line);
  int dimension = std::stoi(line);
  K_ = dimension;
  // Next lines are the elements
  while (std::getline(file, line)) {
    std::vector<double> nodes;
    std::istringstream iss(line);
    std::string coordinate;
    // Process each coordinate (separated by tabs)
    while (std::getline(iss, coordinate, '\t')) {
      std::replace(coordinate.begin(), coordinate.end(), ',', '.');
      if (coordinate.empty()) continue; // ← evita errores con coordenadas vacías
      try {
        double value = std::stod(coordinate);
        nodes.push_back(value);
      } catch (const std::invalid_argument& e) {
        std::cerr << "Error: coordenada inválida '" << coordinate << "' en línea: " << line << std::endl;
        throw;
      }
    }    
    elements_.emplace_back(id++, nodes);
  }
  file.close();
  std::cout << "Parsed " << elements_.size() << " elements from " << filename_ << std::endl;
}
