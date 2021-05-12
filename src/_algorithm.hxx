#pragma once
#include <cmath>
#include <vector>
#include <algorithm>

using std::vector;
using std::find;
using std::count;
using std::count_if;
using std::copy;
using std::abs;




// FIND
// ----

template <class J, class T>
auto find(const J& x, const T& v) {
  return find(x.begin(), x.end(), v);
}

template <class J, class T>
int findIndex(const J& x, const T& v) {
  auto i = find(x.begin(), x.end(), v);
  return i==x.end()? -1 : i-x.begin();
}




// COUNT-*
// -------

template <class J, class T>
int count(const J& x, const T& v) {
  return count(x.begin(), x.end(), v);
}


template <class I, class F>
int countIf(I ib, I ie, F fn) {
  return count_if(ib, ie, fn);
}

template <class J, class F>
int countIf(const J& x, F fn) {
  return count_if(x.begin(), x.end(), fn);
}




// ERASE
// -----

template <class T>
void eraseIndex(vector<T>& x, int i) {
  x.erase(x.begin()+i);
}

template <class T>
void eraseIndex(vector<T>& x, int i, int I) {
  x.erase(x.begin()+i, x.begin()+I);
}




// COPY
// ----

template <class T, class U>
void copy(T *a, U *x, int N) {
  for (int i=0; i<N; i++)
    a[i] = x[i];
}

template <class T, class U>
void copy(vector<T>& a, const vector<U>& x) {
  copy(a.data(), x.data(), int(x.size()));
}


template <class T, class U>
void copyOmp(T *a, U *x, int N) {
  #pragma omp parallel for schedule(static,4096)
  for (int i=0; i<N; i++)
    a[i] = x[i];
}

template <class T, class U>
void copyOmp(vector<T>& a, const vector<T>& x) {
  copyOmp(a.data(), x.data(), int(x.size()));
}




// FILL
// ----

template <class T, class U>
void fill(T *a, int N, const U& v) {
  for (int i=0; i<N; i++)
    a[i] = v;
}

template <class T, class U>
void fill(vector<T>& a, const U& v) {
  fill(a.data(), int(a.size()), v);
}


template <class T, class U>
void fillOmp(T *a, int N, const U& v) {
  #pragma omp parallel for schedule(static,4096)
  for (int i=0; i<N; i++)
    a[i] = v;
}

template <class T, class U>
void fillOmp(vector<T>& a, const U& v) {
  fillOmp(a.data(), int(a.size()), v);
}




// FILL-AT
// -------

template <class T, class U, class I>
void fillAt(T *a, const U& v, I&& is) {
  for (int i : is)
    a[i] = v;
}

template <class T, class U, class I>
void fillAt(vector<T>& a, const U& v, I&& is) {
  fillAt(a.data(), v, is);
}




// SUM
// ---

template <class T, class U=T>
U sum(const T *x, int N, U a=U()) {
  for (int i=0; i<N; i++)
    a += x[i];
  return a;
}

template <class T, class U=T>
U sum(const vector<T>& x, U a=U()) {
  return sum(x.data(), int(x.size()), a);
}


template <class T, class U=T>
U sumOmp(const T *x, int N, U a=U()) {
  #pragma omp parallel for schedule(static,4096) reduction(+:a)
  for (int i=0; i<N; i++)
    a += x[i];
  return a;
}

template <class T, class U=T>
U sumOmp(const vector<T>& x, U a=U()) {
  return sumOmp(x.data(), int(x.size()), a);
}




// SUM-AT
// ------

template <class T, class I, class U=T>
U sumAt(const T *x, I&& is, U a=U()) {
  for (int i : is)
    a += x[i];
  return a;
}

template <class T, class I, class U=T>
U sumAt(const vector<T>& x, I&& is, U a=U()) {
  return sumAt(x.data(), is, a);
}




// ADD-VALUE
// ---------

template <class T, class U>
void addValue(T *a, int N, const U& v) {
  for (int i=0; i<N; i++)
    a[i] += v;
}

template <class T, class U>
void addValue(vector<T>& a, const U& v) {
  addValue(a.data(), int(a.size()), v);
}


template <class T, class U>
void addValueOmp(T *a, int N, const U& v) {
  #pragma omp parallel for schedule(static,4096)
  for (int i=0; i<N; i++)
    a[i] += v;
}

template <class T, class U>
void addValueOmp(vector<T>& a, const U& v) {
  addValueOmp(a.data(), int(a.size()), v);
}




// ADD-VALUE-AT
// ------------

template <class T, class U, class I>
void addValueAt(T *a, const U& v, I&& is) {
  for (int i : is)
    a[i] += v;
}

template <class T, class U, class I>
void addValueAt(vector<T>& a, const U& v, I&& is) {
  addValueAt(a.data(), v, is);
}




// ABS-ERROR
// ---------

template <class T, class U, class V=T>
V absError(const T *x, const U *y, int N, V a=V()) {
  for (int i=0; i<N; i++)
    a += abs(x[i] - y[i]);
  return a;
}

template <class T, class U, class V=T>
V absError(const vector<T>& x, const vector<U>& y, V a=V()) {
  return absError(x.data(), y.data(), int(x.size()), a);
}


template <class T, class U, class V=T>
V absErrorOmp(const T *x, const U *y, int N, V a=V()) {
  #pragma omp parallel for schedule(static,4096) reduction(+:a)
  for (int i=0; i<N; i++)
    a += abs(x[i] - y[i]);
  return a;
}

template <class T, class U, class V=T>
V absErrorOmp(const vector<T>& x, const vector<U>& y, V a=V()) {
  return absErrorOmp(x.data(), y.data(), int(x.size()), a);
}




// MULTIPLY
// --------

template <class T, class U, class V>
void multiply(T *a, const U *x, const V *y, int N) {
  for (int i=0; i<N; i++)
    a[i] = x[i] * y[i];
}

template <class T, class U, class V>
void multiply(vector<T>& a, const vector<U>& x, const vector<V>& y) {
  multiply(a.data(), x.data(), y.data(), int(x.size()));
}


template <class T, class U, class V>
void multiplyOmp(T *a, const U *x, const V *y, int N) {
  #pragma omp parallel for schedule(static,4096)
  for (int i=0; i<N; i++)
    a[i] = x[i] * y[i];
}

template <class T, class U, class V>
void multiplyOmp(vector<T>& a, const vector<U>& x, const vector<V>& y) {
  multiplyOmp(a.data(), x.data(), y.data(), int(x.size()));
}
