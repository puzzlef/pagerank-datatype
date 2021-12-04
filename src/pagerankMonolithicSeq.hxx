#pragma once
#include <vector>
#include <algorithm>
#include "_main.hxx"
#include "transpose.hxx"
#include "dynamic.hxx"
#include "pagerank.hxx"
#include "pagerankSeq.hxx"

using std::vector;
using std::swap;




// PAGERANK-LOOP
// -------------

template <class T, class K=int>
int pagerankMonolithicSeqLoop(vector<T>& a, vector<T>& r, vector<T>& c, const vector<T>& f, const vector<K>& vfrom, const vector<K>& efrom, const vector<int>& vdata, int i, int n, int N, T p, T E, int L, int EF) {
  int l = 0;
  while (l<L) {
    T c0 = pagerankTeleport(r, vdata, N, p);
    pagerankCalculate(a, c, vfrom, efrom, i, n, c0);  // assume contribtions (c) is precalculated
    T el = pagerankError(a, r, i, n, EF); ++l;        // one iteration complete
    if (el<E || l>=L) break;                          // check tolerance, iteration limit
    multiply(c, a, f, i, n);                          // update partial contributions (c)
    swap(a, r);                                       // final ranks always in (a)
  }
  return l;
}




// PAGERANK (STATIC / INCREMENTAL)
// -------------------------------

// Find pagerank using a single thread (pull, CSR).
// @param x  original graph
// @param xt transpose graph (with vertex-data=out-degree)
// @param q  initial ranks (optional)
// @param o  options {damping=0.85, tolerance=1e-6, maxIterations=500}
// @returns {ranks, iterations, time}
template <class G, class H, class T, class K=int>
PagerankResult<T> pagerankMonolithicSeq(const G& x, const H& xt, const vector<T> *q, PagerankOptions<T> o, K _) {
  int  N  = xt.order();    if (N==0) return PagerankResult<T>::initial(xt, q);
  auto ks = vertices(xt);
  return pagerankSeq(xt, ks, 0, N, pagerankMonolithicSeqLoop<T, K>, q, o, K());
}

template <class G, class T, class K=int>
PagerankResult<T> pagerankMonolithicSeq(const G& x, const vector<T> *q, PagerankOptions<T> o, K _) {
  auto xt = transposeWithDegree(x);
  return pagerankMonolithicSeq(x, xt, q, o, K());
}




// PAGERANK (DYNAMIC)
// ------------------

template <class G, class H, class T, class K=int>
PagerankResult<T> pagerankMonolithicSeqDynamic(const G& x, const H& xt, const G& y, const H& yt, const vector<T> *q, PagerankOptions<T> o, K _) {
  int  N = yt.order();                           if (N==0) return PagerankResult<T>::initial(yt, q);
  auto [ks, n] = dynamicVertices(x, xt, y, yt);  if (n==0) return PagerankResult<T>::initial(yt, q);
  return pagerankSeq(yt, ks, 0, n, pagerankMonolithicSeqLoop<T, K>, q, o, K());
}

template <class G, class T, class K=int>
PagerankResult<T> pagerankMonolithicSeqDynamic(const G& x, const G& y, const vector<T> *q, PagerankOptions<T> o, K _) {
  auto xt = transposeWithDegree(x);
  auto yt = transposeWithDegree(y);
  return pagerankMonolithicSeqDynamic(x, xt, y, yt, q, o, K());
}
