#ifndef ELEMENT_H
#define ELEMENT_H

#include <vector>

class Element {
public:
  Element(int id, const std::vector<double>& nodes)
      : id_(id), nodes_(nodes) {}

  int getId() const { return id_; }
  const std::vector<double>& getNodes() const { return nodes_; }
  std::string Nodes() const {
    std::string result;
    for (const auto& node : nodes_) {
      result += std::to_string(node) + " ";
    }
    return result;
  }
  
  bool operator==(const Element& other) const {
    return id_ == other.id_;
  }

private:
  int id_;
  std::vector<double> nodes_;
};

#endif // ELEMENT_H