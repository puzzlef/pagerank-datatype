#pragma once
#include <utility>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include "_main.hxx"
#include "vertices.hxx"
#include "components.hxx"

using std::vector;
using std::unordered_set;
using std::max;
using std::make_pair;




// ADJUST-RANKS
// ------------
// For calculating inital ranks for incremental/dynamic pagerank.

template <class T, class J>
void adjustRanks(vector<T>& a, const vector<T>& r, const J& ks0, const J& ks1, T radd, T rmul, T rset) {
  unordered_set<int> kt0(ks0.begin(), ks0.end());
  unordered_set<int> kt1(ks1.begin(), ks1.end());
  for (int k : ks0)
    if (kt1.count(k)>0)  a[k] = (r[k]+radd)*rmul;  // if vertex not removed
  for (int k : ks1)
    if (kt0.count(k)==0) a[k] = rset;              // if vertex added
}

template <class T, class J>
auto adjustRanks(int N, const vector<T>& r, const J& ks0, const J& ks1, T radd, T rmul, T rset) {
  vector<T> a(N); adjustRanks(a, r, ks0, ks1, radd, rmul, rset);
  return a;
}




// CHANGED-VERTICES
// ----------------
// Find vertices with edges added/removed.

template <class G, class F>
void changedVerticesForEach(const G& x, const G& y, F fn) {
  for (int u : y.vertices())
    if (!x.hasVertex(u) || !verticesEqual(x, u, y, u)) fn(u);
}

template <class G, class H, class F>
void changedVerticesForEach(const G& x, const H& xt, const G& y, const H& yt, F fn) {
  for (int u : y.vertices())
    if (!x.hasVertex(u) || !verticesEqual(x, xt, u, y, yt, u)) fn(u);  // both ways
}

template <class G>
auto changedVertices(const G& x, const G& y) {
  vector<int> a; changedVerticesForEach(x, y, [&](int u) { a.push_back(u); });
  return a;
}

template <class G, class H>
auto changedVertices(const G& x, const H& xt, const G& y, const H& yt) {
  vector<int> a; changedVerticesForEach(x, xt, y, yt, [&](int u) { a.push_back(u); });
  return a;
}




// AFFECTED-VERTICES
// -----------------
// Find vertices reachable from changed vertices.

template <class G, class F>
void affectedVerticesForEach(const G& x, const G& y, F fn) {
  auto visx = createContainer(x, bool());
  auto visy = createContainer(y, bool());
  auto fny  = [&](int u) { if (u>=visx.size() || !visx[u]) fn(u); };  // check bounds!
  changedVerticesForEach(x, y, [&](int u) { if (x.hasVertex(u)) dfsDoLoop(visx, x, u, fn); });
  changedVerticesForEach(x, y, [&](int u) { dfsDoLoop(visy, y, u, fny); });
}

template <class G, class H, class F>
void affectedVerticesForEach(const G& x, const H& xt, const G& y, const H& yt, F fn) {
  auto vis = createContainer(y, bool());
  changedVerticesForEach(x, xt, y, yt, [&](int u) { dfsDoLoop(vis, y, u, fn); });
}

template <class G>
auto affectedVertices(const G& x, const G& y) {
  vector<int> a; affectedVerticesForEach(x, y, [&](int u) { a.push_back(u); });
  return a;
}

template <class G, class H>
auto affectedVertices(const G& x, const H& xt, const G& y, const H& yt) {
  vector<int> a; affectedVerticesForEach(x, xt, y, yt, [&](int u) { a.push_back(u); });
  return a;
}




// DYNAMIC-VERTICES
// ----------------
// Find affected, unaffected vertices (vertices, no. affected).

template <class G, class FA>
auto dynamicVerticesBy(const G& y, FA fa) {
  vector<int> a; unordered_set<int> aff;
  fa([&](int u) { a.push_back(u); aff.insert(u); });
  for (int u : y.vertices())
    if (aff.count(u)==0) a.push_back(u);
  return make_pair(a, aff.size());
}

template <class G>
auto dynamicVertices(const G& x, const G& y) {
  return dynamicVerticesBy(y, [&](auto fn) {
    affectedVerticesForEach(x, y, fn);
  });
}

template <class G, class H>
auto dynamicVertices(const G& x, const H& xt, const G& y, const H& yt) {
  return dynamicVerticesBy(y, [&](auto fn) {
    affectedVerticesForEach(x, xt, y, yt, fn);
  });
}




// CHANGED-COMPONENTS
// ------------------
// Find components with edges added/removed.

template <class G, class F>
void changedComponentIndicesForEach(const G& x, const G& y, const vector2d<int>& cs, F fn) {
  for (int i=0, I=cs.size(); i<I; ++i)
    if (!componentsEqual(x, cs[i], y, cs[i])) fn(i);
}

template <class G, class H, class F>
void changedComponentIndicesForEach(const G& x, const H& xt, const G& y, const H& yt, const vector2d<int>& cs, F fn) {
  for (int i=0, I=cs.size(); i<I; ++i)
    if (!componentsEqual(x, xt, cs[i], y, yt, cs[i])) fn(i);  // both ways
}

template <class G>
auto changedComponentIndices(const G& x, const G& y, const vector2d<int>& cs) {
  vector<int> a; changedComponentIndicesForEach(x, y, cs, [&](int u) { a.push_back(u); });
  return a;
}

template <class G, class H>
auto changedComponentIndices(const G& x, const H& xt, const G& y, const H& yt, const vector2d<int>& cs) {
  vector<int> a; changedVerticesForEach(x, xt, y, yt, cs, [&](int u) { a.push_back(u); });
  return a;
}




// AFFECTED-COMPONENTS
// -------------------
// Find components reachable from changed components.

template <class G, class B, class F>
void affectedComponentIndicesForEach(const G& x, const G& y, const vector2d<int>& cs, const B& b, F fn) {
  vector<bool> vis(cs.size());
  changedComponentIndicesForEach(x, y, cs, [&](int u) { dfsDoLoop(vis, b, u, fn); });
}

template <class G, class H, class B, class F>
void affectedComponentIndicesForEach(const G& x, const H& xt, const G& y, const H& yt, const vector2d<int>& cs, const B& b, F fn) {
  vector<bool> vis(cs.size());
  changedComponentIndicesForEach(x, xt, y, yt, cs, [&](int u) { dfsDoLoop(vis, y, u, fn); });
}

template <class G, class B>
auto affectedComponentIndices(const G& x, const G& y, const vector2d<int>& cs, const B& b) {
  vector<int> a; affectedComponentIndicesForEach(x, y, cs, b, [&](int u) { a.push_back(u); });
  return a;
}

template <class G, class H, class B>
auto affectedComponentIndices(const G& x, const H& xt, const G& y, const H& yt, const vector2d<int>& cs, const B& b) {
  vector<int> a; affectedComponentIndicesForEach(x, xt, y, yt, cs, b, [&](int u) { a.push_back(u); });
  return a;
}




// DYNAMIC-COMPONENTS
// ------------------
// Find affected, unaffected components (components, no. affected).

template <class G, class FA>
auto dynamicComponentIndicesBy(const G& y, const vector2d<int>& cs, FA fa) {
  vector<int> a; unordered_set<int> aff;
  fa([&](int i) { a.push_back(i); aff.insert(i); });
  for (int i=0, I=cs.size(); i<I; ++i)
    if (aff.count(i)==0) a.push_back(i);
  return make_pair(a, aff.size());
}

template <class G, class B>
auto dynamicComponentIndices(const G& x, const G& y, const vector2d<int>& cs, const B& b) {
  return dynamicComponentIndicesBy(y, cs, [&](auto fn) {
    affectedComponentIndicesForEach(x, y, cs, b, fn);
  });
}

template <class G, class H, class B>
auto dynamicComponentIndices(const G& x, const H& xt, const G& y, const H& yt, const vector2d<int>& cs, const B& b) {
  return dynamicComponentIndicesBy(y, cs, [&](auto fn) {
    affectedComponentIndicesForEach(x, xt, y, yt, cs, b, fn);
  });
}
