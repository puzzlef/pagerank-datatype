#include <vector>
#include <string>
#include <cstdio>
#include <iostream>
#include "src/main.hxx"

using namespace std;




template <class G, class H>
void runPagerank(const G& x, const H& xt, int repeat) {
  vector<float>  *initFloat  = nullptr;
  vector<double> *initDouble = nullptr;

  // Find pagerank using nvGraph (double).
  auto a0 = pagerankNvgraph(x, xt, initDouble, {repeat});

  // Find pagerank using 64-bit floats.
  auto a1 = pagerankMonolithicCuda(x, xt, initDouble, {repeat});
  auto e1 = l1Norm(a1.ranks, a0.ranks);
  printf("[%09.3f ms; %03d iters.] [%.4e err.] pagerankDouble\n", a1.time, a1.iterations, e1);

  // Find pagerank using 32-bit floats.
  auto a2 = pagerankMonolithicCuda(x, xt, initFloat, {repeat});
  auto e2 = l1Norm(a2.ranks, a0.ranks);
  printf("[%09.3f ms; %03d iters.] [%.4e err.] pagerankFloat\n", a2.time, a2.iterations, e2);
}


int main(int argc, char **argv) {
  char *file = argv[1];
  int repeat = argc>2? stoi(argv[2]) : 5;
  printf("Loading graph %s ...\n", file);
  auto x  = readMtx(file); println(x);
  auto xt = transposeWithDegree(x); print(xt); printf(" (transposeWithDegree)\n");
  runPagerank(x, xt, repeat);
  printf("\n");
  return 0;
}
