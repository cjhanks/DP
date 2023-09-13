#ifndef GRAPH_HH_
#define GRAPH_HH_

#include <map>
#include <set>
#include <vector>

template <typename Node_, typename Cost_>
class Graph {
 public:
  using Node = Node_;
  using Cost = Cost_;

  struct Edge {
    Node node;
    Cost cost;
  };

  using EdgeList = std::vector<Edge>;

  Graph(bool directed=false)
   : directed(directed)
  {}

  void
  AddEdge(Node node_fr, Node node_to, Cost cost) {
    nodes.insert(node_fr);
    nodes.insert(node_to);

    auto& edge1 = edges[node_fr];
    edge1.push_back({node_to, cost});

    if (!directed) {
      auto& edge2 = edges[node_to];
      edge2.push_back({node_fr, cost});
    }
  }

  std::size_t
  NodeCount() const {
    return nodes.size();
  }

  const std::set<Node>&
  Nodes() const {
   return nodes;
  }

  const EdgeList&
  Neighbors(Node node) const {
    return edges.at(node);
  }

 private:
  bool directed;
  std::set<Node>           nodes;
  std::map<Node, EdgeList> edges;
};

#endif // GRAPH_HH_
