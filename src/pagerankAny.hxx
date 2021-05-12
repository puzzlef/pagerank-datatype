#pragma once
#include <algorithm>
#include "_main.hxx"
#include "vertices.hxx"
#include "edges.hxx"
#include "pagerank.hxx"

using std::swap;




template <class T>
float pagerankTeleport(const vector<T>& r, const vector<int>& vfrom, const vector<int>& efrom, const vector<int>& vdata, int N, float p) {
  float a = (1-p)/N;
  for (int u=0; u<N; u++)
    if (vdata[u] == 0) a += p*r[u]/N;
  return a;
}

template <class T>
void pagerankFactor(vector<T>& a, const vector<int>& vfrom, const vector<int>& efrom, const vector<int>& vdata, int N, float p) {
  for (int u=0; u<N; u++) {
    int d = vdata[u];
    a[u] = d>0? p/d : 0.0f;
  }
}

template <class T>
void pagerankCalculate(vector<T>& a, const vector<T>& c, const vector<int>& vfrom, const vector<int>& efrom, const vector<int>& vdata, int N, float c0) {
  for (int v=0; v<N; v++)
    a[v] = c0 + sumAt(c, slice(efrom, vfrom[v], vfrom[v+1]), 0.0f);
}

template <class T>
int pagerankAnyLoop(vector<T>& a, vector<T>& r, const vector<T>& f, vector<T>& c, const vector<int>& vfrom, const vector<int>& efrom, const vector<int>& vdata, int N, float p, float E, int L) {
  int l = 0;
  float e0 = 0.0f;
  for (; l<L; l++) {
    float c0 = pagerankTeleport(r, vfrom, efrom, vdata, N, p);
    multiply(c, r, f);
    pagerankCalculate(a, c, vfrom, efrom, vdata, N, c0);
    float e1 = absError(a, r, 0.0f);
    if (e1 < E || e1 == e0) break;
    swap(a, r);
    e0 = e1;
  }
  return l;
}

template <class T>
int pagerankAnyCore(vector<T>& a, vector<T>& r, vector<T>& f, vector<T>& c, const vector<int>& vfrom, const vector<int>& efrom, const vector<int>& vdata, int N, const vector<T> *q, float p, float E, int L) {
  if (q) copy(r, *q);
  else fill(r, T(1.0f/N));
  pagerankFactor(f, vfrom, efrom, vdata, N, p);
  return pagerankAnyLoop(a, r, f, c, vfrom, efrom, vdata, N, p, E, L);
}


// Find pagerank using float or bfloat16 as the storage type.
// @param xt transpose graph, with vertex-data=out-degree
// @param q initial ranks (optional)
// @param o options {damping=0.85, tolerance=1e-6, maxIterations=500}
// @returns {ranks, iterations, time}
template <class G, class T=float>
PagerankResult<T> pagerankAny(const G& xt, const vector<T> *q=nullptr, PagerankOptions<float> o={}) {
  float p = o.damping;
  float E = o.tolerance;
  int   L = o.maxIterations, l;
  auto vfrom = sourceOffsets(xt);
  auto efrom = destinationIndices(xt);
  auto vdata = vertexData(xt);
  int  N     = xt.order();
  vector<T> a(N), r(N), f(N), c(N);
  float t = measureDuration([&]() { l = pagerankAnyCore(a, r, f, c, vfrom, efrom, vdata, N, q, p, E, L); }, o.repeat);
  return {vertexContainer(xt, a), l, t};
}
