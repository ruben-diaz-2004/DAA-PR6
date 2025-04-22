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

private:
  std::vector<Element> elements_;
  std::string filename_;
  void parse();
};

#endif // INSTANCE_PARSER_H