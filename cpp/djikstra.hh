#ifndef DJIKSTRA_HH_
#define DJIKSTRA_HH_

#include <map>
#include <queue>
#include <set>
#include <vector>

#include "graph.hh"


template <typename Graph>
class Djikstra {
 public:
  using Node = typename Graph::Node;
  using Cost = typename Graph::Cost;

  static std::vector<Cost>
  Solve(const Graph& graph, Node start) {
    std::set<Node> observed;
    std::vector<Cost> costs(
        graph.NodeCount(),
        std::numeric_limits<Cost>::infinity()
    );

    costs[start] = 0;

    using Pair = std::pair<Cost, Node>;
    using PriorityQueue =
        std::priority_queue<Pair, std::vector<Pair>, std::greater<Pair>>;

    PriorityQueue pq;
    pq.push({Cost(0), start});

    while (!pq.empty()) {
      Pair elem = pq.top();
      pq.pop();

      Node node = elem.second;

      if (observed.count(node))
        continue;
      else
        observed.insert(node);

      for (const auto& neigh: graph.Neighbors(node)) {
        Cost old_cost = costs[neigh.node];
        Cost new_cost = costs[node] + neigh.cost;

        if (new_cost < old_cost) {
          costs[neigh.node] = new_cost;
          pq.push({new_cost, neigh.node});
        }
      }
    }

    return costs;
  }
};

#endif // DJIKSTRA_HH_
