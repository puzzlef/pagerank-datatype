Comparison of PageRank using float vs bfloat16 as the storage type (pull, CSR).

This experiment was for comparing the result between:
1. Find pagerank using float as the storage type.
2. Find pagerank using bfloat16 as the storage type.

Both datatypes were attempted on different types of graphs, running each
technique 5 times per graph to get a good time measure. It seems using
**double** datatype increases execution time by a small factor in all cases.
This could be attributed to increased memory bandwidth requirement. However,
since most of the data for a graph (CSR) is stored as 32-bit ints, it possibly
makes up most of the memory bottleneck, and not the rank vector.

See ["pagerank-push-vs-pull"] for a discussion on *push* vs *pull* method, and["pagerank-class-vs-csr"] for a comparisionbetween using a C++ DiGraph class
directly vs using its CSR representation. The input data used for this
experiment is available at ["graphs"] (for small ones), and the
[SuiteSparse Matrix Collection].

```bash
$ g++ -O3 main.cxx
$ ./a.out ~/data/min-1DeadEnd.mtx
$ ./a.out ~/data/min-2SCC.mtx
$ ...

# Loading graph /home/subhajit/data/min-1DeadEnd.mtx ...
# order: 5 size: 6 {}
# order: 5 size: 6 {} (transposeWithDegree)
# [00000.002 ms; 016 iters.] [0.0000e+00 err.] pagerankFloat
# [00000.002 ms; 016 iters.] [8.9407e-08 err.] pagerankDouble
#
# Loading graph /home/subhajit/data/min-2SCC.mtx ...
# order: 8 size: 12 {}
# order: 8 size: 12 {} (transposeWithDegree)
# [00000.005 ms; 039 iters.] [0.0000e+00 err.] pagerankFloat
# [00000.005 ms; 039 iters.] [5.5929e-08 err.] pagerankDouble
#
# Loading graph /home/subhajit/data/min-4SCC.mtx ...
# order: 21 size: 35 {}
# order: 21 size: 35 {} (transposeWithDegree)
# [00000.015 ms; 044 iters.] [0.0000e+00 err.] pagerankFloat
# [00000.014 ms; 044 iters.] [7.4726e-08 err.] pagerankDouble
#
# Loading graph /home/subhajit/data/min-NvgraphEx.mtx ...
# order: 6 size: 10 {}
# order: 6 size: 10 {} (transposeWithDegree)
# [00000.003 ms; 023 iters.] [0.0000e+00 err.] pagerankFloat
# [00000.003 ms; 023 iters.] [5.8122e-08 err.] pagerankDouble
#
# Loading graph /home/subhajit/data/web-Stanford.mtx ...
# order: 281903 size: 2312497 {}
# order: 281903 size: 2312497 {} (transposeWithDegree)
# [00400.480 ms; 062 iters.] [0.0000e+00 err.] pagerankFloat
# [00480.127 ms; 062 iters.] [4.8116e-06 err.] pagerankDouble
#
# Loading graph /home/subhajit/data/web-BerkStan.mtx ...
# order: 685230 size: 7600595 {}
# order: 685230 size: 7600595 {} (transposeWithDegree)
# [00886.251 ms; 063 iters.] [0.0000e+00 err.] pagerankFloat
# [00932.142 ms; 063 iters.] [2.3126e-05 err.] pagerankDouble
#
# Loading graph /home/subhajit/data/web-Google.mtx ...
# order: 916428 size: 5105039 {}
# order: 916428 size: 5105039 {} (transposeWithDegree)
# [01493.679 ms; 060 iters.] [0.0000e+00 err.] pagerankFloat
# [01620.996 ms; 061 iters.] [5.1387e-04 err.] pagerankDouble
#
# Loading graph /home/subhajit/data/web-NotreDame.mtx ...
# order: 325729 size: 1497134 {}
# order: 325729 size: 1497134 {} (transposeWithDegree)
# [00215.677 ms; 057 iters.] [0.0000e+00 err.] pagerankFloat
# [00226.778 ms; 057 iters.] [7.7317e-04 err.] pagerankDouble
#
# Loading graph /home/subhajit/data/soc-Slashdot0811.mtx ...
# order: 77360 size: 905468 {}
# order: 77360 size: 905468 {} (transposeWithDegree)
# [00089.458 ms; 054 iters.] [0.0000e+00 err.] pagerankFloat
# [00091.632 ms; 054 iters.] [1.4557e-07 err.] pagerankDouble
#
# Loading graph /home/subhajit/data/soc-Slashdot0902.mtx ...
# order: 82168 size: 948464 {}
# order: 82168 size: 948464 {} (transposeWithDegree)
# [00098.767 ms; 055 iters.] [0.0000e+00 err.] pagerankFloat
# [00100.595 ms; 055 iters.] [4.5454e-06 err.] pagerankDouble
#
# Loading graph /home/subhajit/data/soc-Epinions1.mtx ...
# order: 75888 size: 508837 {}
# order: 75888 size: 508837 {} (transposeWithDegree)
# [00080.112 ms; 053 iters.] [0.0000e+00 err.] pagerankFloat
# [00078.032 ms; 053 iters.] [2.6043e-05 err.] pagerankDouble
#
# Loading graph /home/subhajit/data/coAuthorsDBLP.mtx ...
# order: 299067 size: 1955352 {}
# order: 299067 size: 1955352 {} (transposeWithDegree)
# [00237.238 ms; 044 iters.] [0.0000e+00 err.] pagerankFloat
# [00250.450 ms; 044 iters.] [8.0891e-08 err.] pagerankDouble
#
# Loading graph /home/subhajit/data/coAuthorsCiteseer.mtx ...
# order: 227320 size: 1628268 {}
# order: 227320 size: 1628268 {} (transposeWithDegree)
# [00189.405 ms; 047 iters.] [0.0000e+00 err.] pagerankFloat
# [00197.162 ms; 047 iters.] [1.5103e-07 err.] pagerankDouble
#
# Loading graph /home/subhajit/data/soc-LiveJournal1.mtx ...
# order: 4847571 size: 68993773 {}
# order: 4847571 size: 68993773 {} (transposeWithDegree)
# [11482.458 ms; 050 iters.] [0.0000e+00 err.] pagerankFloat
# [14564.962 ms; 050 iters.] [2.0510e-03 err.] pagerankDouble
#
# Loading graph /home/subhajit/data/coPapersCiteseer.mtx ...
# order: 434102 size: 32073440 {}
# order: 434102 size: 32073440 {} (transposeWithDegree)
# [02158.691 ms; 050 iters.] [0.0000e+00 err.] pagerankFloat
# [02185.612 ms; 050 iters.] [3.4078e-07 err.] pagerankDouble
#
# Loading graph /home/subhajit/data/coPapersDBLP.mtx ...
# order: 540486 size: 30491458 {}
# order: 540486 size: 30491458 {} (transposeWithDegree)
# [02070.509 ms; 048 iters.] [0.0000e+00 err.] pagerankFloat
# [02119.474 ms; 048 iters.] [2.1566e-07 err.] pagerankDouble
#
# Loading graph /home/subhajit/data/indochina-2004.mtx ...
# order: 7414866 size: 194109311 {}
# order: 7414866 size: 194109311 {} (transposeWithDegree)
# [18790.924 ms; 060 iters.] [0.0000e+00 err.] pagerankFloat
# [19182.994 ms; 059 iters.] [8.0596e-04 err.] pagerankDouble
#
# Loading graph /home/subhajit/data/italy_osm.mtx ...
# order: 6686493 size: 14027956 {}
# order: 6686493 size: 14027956 {} (transposeWithDegree)
# [04076.062 ms; 062 iters.] [0.0000e+00 err.] pagerankFloat
# [04782.375 ms; 061 iters.] [8.5956e-07 err.] pagerankDouble
#
# Loading graph /home/subhajit/data/great-britain_osm.mtx ...
# order: 7733822 size: 16313034 {}
# order: 7733822 size: 16313034 {} (transposeWithDegree)
# [08080.853 ms; 066 iters.] [0.0000e+00 err.] pagerankFloat
# [07263.394 ms; 066 iters.] [1.0659e-07 err.] pagerankDouble
#
# Loading graph /home/subhajit/data/germany_osm.mtx ...
# order: 11548845 size: 24738362 {}
# order: 11548845 size: 24738362 {} (transposeWithDegree)
# [09947.280 ms; 064 iters.] [0.0000e+00 err.] pagerankFloat
# [10904.824 ms; 064 iters.] [9.3623e-08 err.] pagerankDouble
#
# Loading graph /home/subhajit/data/asia_osm.mtx ...
# order: 11950757 size: 25423206 {}
# order: 11950757 size: 25423206 {} (transposeWithDegree)
# [07596.662 ms; 062 iters.] [0.0000e+00 err.] pagerankFloat
# [08693.011 ms; 062 iters.] [9.6745e-08 err.] pagerankDouble
```

<br>
<br>


## References

- [PageRank Algorithm, Mining massive Datasets (CS246), Stanford University](http://snap.stanford.edu/class/cs246-videos-2019/lec9_190205-cs246-720.mp4)
- [SuiteSparse Matrix Collection]

<br>
<br>

[![](https://i.imgur.com/wmbbEzJ.jpg)](https://www.youtube.com/watch?v=rKv_l1RnSqs)

["pagerank-push-vs-pull"]: https://github.com/puzzlef/pagerank-push-vs-pull
["pagerank-class-vs-csr"]: https://github.com/puzzlef/pagerank-class-vs-csr
["graphs"]: https://github.com/puzzlef/graphs
[SuiteSparse Matrix Collection]: https://suitesparse-collection-website.herokuapp.com
