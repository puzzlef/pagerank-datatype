#include <vector>
#include <string>
#include <cstdio>
#include <iostream>
#include "src/main.hxx"

using namespace std;




template <class G, class H>
void runPagerank(const G& x, const H& xt, int repeat) {
  vector<float> *init = nullptr;

  // Find pagerank using nvGraph (int32).
  auto a0 = pagerankNvgraph(x, xt, init, {repeat});

  // Find pagerank using 32-bit ints.
  auto a1 = pagerankMonolithicCuda(x, xt, init, {repeat}, int32_t());
  auto e1 = l1Norm(a1.ranks, a0.ranks);
  printf("[%09.3f ms; %03d iters.] [%.4e err.] pagerankInt32\n", a1.time, a1.iterations, e1);

  // Find pagerank using 64-bit ints.
  auto a2 = pagerankMonolithicCuda(x, xt, init, {repeat}, int64_t());
  auto e2 = l1Norm(a2.ranks, a0.ranks);
  printf("[%09.3f ms; %03d iters.] [%.4e err.] pagerankInt64\n", a2.time, a2.iterations, e2);
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
