#pragma once
#include <algorithm>
#include "_main.hxx"
#include "vertices.hxx"
#include "edges.hxx"
#include "pagerank.hxx"

using std::swap;




float pagerankTeleport(const vector<float>& r, const vector<int>& vfrom, const vector<int>& efrom, const vector<int>& vdata, int N, float p) {
  float a = (1-p)/N;
  for (int u=0; u<N; u++)
    if (vdata[u] == 0) a += p*r[u]/N;
  return a;
}

void pagerankFactor(vector<float>& a, const vector<int>& vfrom, const vector<int>& efrom, const vector<int>& vdata, int N, float p) {
  for (int u=0; u<N; u++) {
    int d = vdata[u];
    a[u] = d>0? p/d : 0;
  }
}

void pagerankCalculate(vector<float>& a, const vector<float>& c, const vector<int>& vfrom, const vector<int>& efrom, const vector<int>& vdata, int N, float c0) {
  for (int v=0; v<N; v++)
    a[v] = c0 + sumAt(c, slice(efrom, vfrom[v], vfrom[v+1]));
}

int pagerankFloatLoop(vector<float>& a, vector<float>& r, const vector<float>& f, vector<float>& c, const vector<int>& vfrom, const vector<int>& efrom, const vector<int>& vdata, int N, float p, float E, int L) {
  int l = 0;
  float e0 = float();
  for (; l<L; l++) {
    float c0 = pagerankTeleport(r, vfrom, efrom, vdata, N, p);
    multiply(c, r, f);
    pagerankCalculate(a, c, vfrom, efrom, vdata, N, c0);
    float e1 = absError(a, r);
    if (e1 < E || e1 == e0) break;
    swap(a, r);
    e0 = e1;
  }
  return l;
}

int pagerankFloatCore(vector<float>& a, vector<float>& r, vector<float>& f, vector<float>& c, const vector<int>& vfrom, const vector<int>& efrom, const vector<int>& vdata, int N, const vector<float> *q, float p, float E, int L) {
  if (q) copy(r, *q);
  else fill(r, float(1)/N);
  pagerankFactor(f, vfrom, efrom, vdata, N, p);
  return pagerankFloatLoop(a, r, f, c, vfrom, efrom, vdata, N, p, E, L);
}


// Find pagerank using a single thread.
// @param xt transpose graph, with vertex-data=out-degree
// @param q initial ranks (optional)
// @param o options {damping=0.85, tolerance=1e-6, maxIterations=500}
// @returns {ranks, iterations, time}
template <class G>
PagerankResult<float> pagerankFloat(const G& xt, const vector<float> *q=nullptr, PagerankOptions<float> o={}) {
  float p = o.damping;
  float E = o.tolerance;
  int   L = o.maxIterations, l;
  auto vfrom = sourceOffsets(xt);
  auto efrom = destinationIndices(xt);
  auto vdata = vertexData(xt);
  int  N     = xt.order();
  vector<float> a(N), r(N), f(N), c(N);
  float t = measureDuration([&]() { l = pagerankFloatCore(a, r, f, c, vfrom, efrom, vdata, N, q, p, E, L); }, o.repeat);
  return {vertexContainer(xt, a), l, t};
}
