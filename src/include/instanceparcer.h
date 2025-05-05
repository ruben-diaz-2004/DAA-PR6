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
#ifndef INSTANCE_PARSER_H
#define INSTANCE_PARSER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "element.h"
#include "solution.h"

class InstanceParser {
public:
  InstanceParser(const std::string& filename);
  const std::vector<Element>& getElements() const { return elements_; }
  int getN() const { return n_; }
  int getK() const { return K_; }

private:
  std::vector<Element> elements_;
  std::string filename_;
  void parse();
  int n_;
  int K_;
};

#endif // INSTANCE_PARSER_H