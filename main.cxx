#include <vector>
#include <string>
#include <cstdio>
#include <iostream>
#include "src/main.hxx"

using namespace std;




template <class G, class H>
void runPagerank(const G& x, const H& xt, int repeat) {
  vector<float>    *initFloat    = nullptr;
  vector<Bfloat16> *initBfloat16 = nullptr;

  // Find pagerank using float as the storage type.
  auto a1 = pagerankAny(xt, initFloat, {repeat});
  auto e1 = absError(a1.ranks, a1.ranks);
  printf("[%09.3f ms; %03d iters.] [%.4e err.] pagerankFloat\n", a1.time, a1.iterations, e1);

  // Find pagerank using bfloat16 as the storage type.
  auto a2 = pagerankAny(xt, initBfloat16, {repeat});
  auto e2 = absError(a2.ranks, a1.ranks, 0.0f);
  printf("[%09.3f ms; %03d iters.] [%.4e err.] pagerankBfloat16\n", a2.time, a2.iterations, e2);
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
