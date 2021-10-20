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

  // Find pagerank using 32-bit floats.
  auto a1 = pagerankNvgraph(xt, initFloat, {repeat});
  auto e1 = l1Norm(a1.ranks, a1.ranks);
  printf("[%09.3f ms; %03d iters.] [%.4e err.] pagerankNvgraphFloat\n", a1.time, a1.iterations, e1);
  auto a2 = pagerankCuda(xt, initFloat, {repeat});
  auto e2 = l1Norm(a2.ranks, a1.ranks);
  printf("[%09.3f ms; %03d iters.] [%.4e err.] pagerankCudaFloat\n", a2.time, a2.iterations, e2);
  auto a3 = pagerankSeq(xt, initFloat, {repeat});
  auto e3 = l1Norm(a3.ranks, a1.ranks);
  printf("[%09.3f ms; %03d iters.] [%.4e err.] pagerankSeqFloat\n", a3.time, a3.iterations, e3);

  // Find pagerank using 64-bit floats.
  auto a4 = pagerankNvgraph(xt, initDouble, {repeat});
  auto e4 = l1Norm(a4.ranks, a4.ranks);
  printf("[%09.3f ms; %03d iters.] [%.4e err.] pagerankNvgraphDouble\n", a4.time, a4.iterations, e4);
  auto a5 = pagerankCuda(xt, initDouble, {repeat});
  auto e5 = l1Norm(a5.ranks, a4.ranks);
  printf("[%09.3f ms; %03d iters.] [%.4e err.] pagerankCudaDouble\n", a5.time, a5.iterations, e5);
  auto a6 = pagerankSeq(xt, initDouble, {repeat});
  auto e6 = l1Norm(a6.ranks, a4.ranks);
  printf("[%09.3f ms; %03d iters.] [%.4e err.] pagerankSeqDouble\n", a6.time, a6.iterations, e6);
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
