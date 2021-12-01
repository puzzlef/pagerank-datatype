#pragma once
#include <vector>
#include <algorithm>
#include "vertices.hxx"
#include "dfs.hxx"

using std::vector;
using std::reverse;




template <class G>
auto topologicalSort(const G& x) {
  vector<int> a;
  auto vis = createContainer(x, bool());
  for (int u : x.vertices())
    if (!vis[u]) dfsEndLoop(a, vis, x, u);
  reverse(a.begin(), a.end());
  return a;
}
