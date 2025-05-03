#ifndef BNBNODE_H
#define BNBNODE_H

// Node structure for the branch and bound tree
struct BnBNode {
  std::vector<Element> selected;     // Elements currently selected in this node
  std::vector<Element> candidates;   // Remaining candidate elements
  double currentDiversity;          // Current diversity value
  double upperBound;                // Upper bound for this node
  int level;                        // Current level in the search tree

  BnBNode(const std::vector<Element>& sel, const std::vector<Element>& cand, double diversity, double ub, int lev) 
      : selected(sel), candidates(cand), currentDiversity(diversity), upperBound(ub), level(lev) {}
};

// Custom comparator for priority queue (max-heap based on upper bound)
struct BnBNodeComparator {
  bool operator()(const std::shared_ptr<BnBNode>& a, const std::shared_ptr<BnBNode>& b) const {
      return a->upperBound < b->upperBound;  // Smaller upper bound = lower priority
  }
};

#endif // BNBNODE_H