#pragma once
#include <vector>
#include <algorithm>
#include "_main.hxx"

using std::vector;
using std::transform;




// SOURCE-OFFSETS
// --------------

template <class G, class J, class K=int>
auto sourceOffsets(const G& x, const J& ks, K _) {
  K i = 0;
  vector<K> a;
  a.reserve(x.order()+1);
  for (auto u : ks) {
    a.push_back(i);
    i += x.degree(u);
  }
  a.push_back(i);
  return a;
}

template <class G, class K=int>
auto sourceOffsets(const G& x, K _) {
  return sourceOffsets(x, x.vertices(), K());
}




// DESTINATION-INDICES
// -------------------

template <class G, class J, class F, class K=int>
auto destinationIndices(const G& x, const J& ks, F fp, K _) {
  vector<K> a;
  auto ids = indices(ks);
  for (int u : ks) {
    append(a, x.edges(u));
    auto ie = a.end(), ib = ie-x.degree(u);
    fp(ib, ie); transform(ib, ie, ib, [&](auto v) { return ids[v]; });
  }
  return a;
}

template <class G, class J, class K=int>
auto destinationIndices(const G& x, const J& ks, K _) {
  return destinationIndices(x, ks, [](auto ib, auto ie) {}, K());
}

template <class G, class K=int>
auto destinationIndices(const G& x, K _) {
  return destinationIndices(x, x.vertices(), K());
}
