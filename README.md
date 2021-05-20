Comparison of PageRank using [float] vs [bfloat16] as the storage type ([pull], [CSR]).

This experiment was for comparing the result between:
1. Find pagerank using **float** as the storage type.
2. Find pagerank using **bfloat16** as the storage type.

Both datatypes were attempted on different types of graphs, running each
technique 5 times per graph to get a good time measure. Unfortunately it seems
**bfloat16** cannot be used for PageRank as its too inaccurate (atleast when
simply replacing **float** vectors with **bfloat16** vectors). Using [fp16]
might work, but likely give negligible performance improvement over float.

The input data used for this experiment is available at ["graphs"] (for small
ones), and the [SuiteSparse Matrix Collection].

<br>

```bash
$ g++ -O3 main.cxx
$ ./a.out ~/data/min-1DeadEnd.mtx
$ ./a.out ~/data/min-2SCC.mtx
$ ...

# Loading graph /home/subhajit/data/min-1DeadEnd.mtx ...
# order: 5 size: 6 {}
# order: 5 size: 6 {} (transposeWithDegree)
# [00000.002 ms; 016 iters.] [0.0000e+00 err.] pagerankFloat
# [00000.002 ms; 008 iters.] [2.3437e-02 err.] pagerankBfloat16
#
# Loading graph /home/subhajit/data/min-2SCC.mtx ...
# order: 8 size: 12 {}
# order: 8 size: 12 {} (transposeWithDegree)
# [00000.008 ms; 039 iters.] [0.0000e+00 err.] pagerankFloat
# [00000.002 ms; 016 iters.] [3.9551e-02 err.] pagerankBfloat16
#
# Loading graph /home/subhajit/data/min-4SCC.mtx ...
# order: 21 size: 35 {}
# order: 21 size: 35 {} (transposeWithDegree)
# [00000.015 ms; 044 iters.] [0.0000e+00 err.] pagerankFloat
# [00000.009 ms; 019 iters.] [4.6814e-02 err.] pagerankBfloat16
#
# Loading graph /home/subhajit/data/min-NvgraphEx.mtx ...
# order: 6 size: 10 {}
# order: 6 size: 10 {} (transposeWithDegree)
# [00000.007 ms; 023 iters.] [0.0000e+00 err.] pagerankFloat
# [00000.002 ms; 011 iters.] [3.9795e-02 err.] pagerankBfloat16
#
# Loading graph /home/subhajit/data/web-Stanford.mtx ...
# order: 281903 size: 2312497 {}
# order: 281903 size: 2312497 {} (transposeWithDegree)
# [00375.217 ms; 062 iters.] [0.0000e+00 err.] pagerankFloat
# [00298.391 ms; 047 iters.] [4.1805e-02 err.] pagerankBfloat16
#
# Loading graph /home/subhajit/data/web-BerkStan.mtx ...
# order: 685230 size: 7600595 {}
# order: 685230 size: 7600595 {} (transposeWithDegree)
# [00873.394 ms; 063 iters.] [0.0000e+00 err.] pagerankFloat
# [00858.717 ms; 057 iters.] [4.3443e-02 err.] pagerankBfloat16
#
# Loading graph /home/subhajit/data/web-Google.mtx ...
# order: 916428 size: 5105039 {}
# order: 916428 size: 5105039 {} (transposeWithDegree)
# [01421.171 ms; 060 iters.] [0.0000e+00 err.] pagerankFloat
# [11504.431 ms; 500 iters.] [4.1604e-02 err.] pagerankBfloat16
#
# Loading graph /home/subhajit/data/web-NotreDame.mtx ...
# order: 325729 size: 1497134 {}
# order: 325729 size: 1497134 {} (transposeWithDegree)
# [00214.057 ms; 057 iters.] [0.0000e+00 err.] pagerankFloat
# [00190.326 ms; 045 iters.] [3.4149e-02 err.] pagerankBfloat16
#
# Loading graph /home/subhajit/data/soc-Slashdot0811.mtx ...
# order: 77360 size: 905468 {}
# order: 77360 size: 905468 {} (transposeWithDegree)
# [00086.386 ms; 054 iters.] [0.0000e+00 err.] pagerankFloat
# [00078.190 ms; 042 iters.] [4.4025e-02 err.] pagerankBfloat16
#
# Loading graph /home/subhajit/data/soc-Slashdot0902.mtx ...
# order: 82168 size: 948464 {}
# order: 82168 size: 948464 {} (transposeWithDegree)
# [00096.832 ms; 055 iters.] [0.0000e+00 err.] pagerankFloat
# [00075.025 ms; 037 iters.] [4.3648e-02 err.] pagerankBfloat16
#
# Loading graph /home/subhajit/data/soc-Epinions1.mtx ...
# order: 75888 size: 508837 {}
# order: 75888 size: 508837 {} (transposeWithDegree)
# [00075.764 ms; 053 iters.] [0.0000e+00 err.] pagerankFloat
# [00067.337 ms; 042 iters.] [4.3389e-02 err.] pagerankBfloat16
#
# Loading graph /home/subhajit/data/coAuthorsDBLP.mtx ...
# order: 299067 size: 1955352 {}
# order: 299067 size: 1955352 {} (transposeWithDegree)
# [00228.499 ms; 044 iters.] [0.0000e+00 err.] pagerankFloat
# [00254.093 ms; 044 iters.] [4.0308e-02 err.] pagerankBfloat16
#
# Loading graph /home/subhajit/data/coAuthorsCiteseer.mtx ...
# order: 227320 size: 1628268 {}
# order: 227320 size: 1628268 {} (transposeWithDegree)
# [00184.534 ms; 047 iters.] [0.0000e+00 err.] pagerankFloat
# [00165.354 ms; 037 iters.] [3.9538e-02 err.] pagerankBfloat16
#
# Loading graph /home/subhajit/data/soc-LiveJournal1.mtx ...
# order: 4847571 size: 68993773 {}
# order: 4847571 size: 68993773 {} (transposeWithDegree)
# [11260.648 ms; 050 iters.] [0.0000e+00 err.] pagerankFloat
# [13895.689 ms; 068 iters.] [4.3118e-02 err.] pagerankBfloat16
#
# Loading graph /home/subhajit/data/coPapersCiteseer.mtx ...
# order: 434102 size: 32073440 {}
# order: 434102 size: 32073440 {} (transposeWithDegree)
# [02153.722 ms; 050 iters.] [0.0000e+00 err.] pagerankFloat
# [01466.724 ms; 031 iters.] [4.2958e-02 err.] pagerankBfloat16
#
# Loading graph /home/subhajit/data/coPapersDBLP.mtx ...
# order: 540486 size: 30491458 {}
# order: 540486 size: 30491458 {} (transposeWithDegree)
# [02052.050 ms; 048 iters.] [0.0000e+00 err.] pagerankFloat
# [01564.964 ms; 033 iters.] [4.3985e-02 err.] pagerankBfloat16
#
# Loading graph /home/subhajit/data/indochina-2004.mtx ...
# order: 7414866 size: 194109311 {}
# order: 7414866 size: 194109311 {} (transposeWithDegree)
# [18735.855 ms; 060 iters.] [0.0000e+00 err.] pagerankFloat
# [160078.828 ms; 500 iters.] [4.0621e-02 err.] pagerankBfloat16
#
# Loading graph /home/subhajit/data/italy_osm.mtx ...
# order: 6686493 size: 14027956 {}
# order: 6686493 size: 14027956 {} (transposeWithDegree)
# [03938.734 ms; 062 iters.] [0.0000e+00 err.] pagerankFloat
# [30156.482 ms; 500 iters.] [4.8967e-02 err.] pagerankBfloat16
#
# Loading graph /home/subhajit/data/great-britain_osm.mtx ...
# order: 7733822 size: 16313034 {}
# order: 7733822 size: 16313034 {} (transposeWithDegree)
# [06110.001 ms; 066 iters.] [0.0000e+00 err.] pagerankFloat
# [20856.783 ms; 235 iters.] [4.0153e-02 err.] pagerankBfloat16
#
# Loading graph /home/subhajit/data/germany_osm.mtx ...
# order: 11548845 size: 24738362 {}
# order: 11548845 size: 24738362 {} (transposeWithDegree)
# [09588.165 ms; 064 iters.] [0.0000e+00 err.] pagerankFloat
# [06618.520 ms; 042 iters.] [4.6186e-02 err.] pagerankBfloat16
#
# Loading graph /home/subhajit/data/asia_osm.mtx ...
# order: 11950757 size: 25423206 {}
# order: 11950757 size: 25423206 {} (transposeWithDegree)
# [07311.353 ms; 062 iters.] [0.0000e+00 err.] pagerankFloat
# [04768.323 ms; 039 iters.] [4.8319e-02 err.] pagerankBfloat16
```

<br>
<br>


## References

- [PageRank Algorithm, Mining massive Datasets (CS246), Stanford University](http://snap.stanford.edu/class/cs246-videos-2019/lec9_190205-cs246-720.mp4)
- [Convert FP32 to Bfloat16 in C++](https://stackoverflow.com/a/64493446/1413259)
- [Why is there no 2-byte float and does an implementation already exist?](https://stackoverflow.com/a/56017304/1413259)
- [Is it safe to reinterpret_cast an integer to float?](https://stackoverflow.com/a/13982359/1413259)
- [SuiteSparse Matrix Collection]

<br>
<br>

[![](https://i.imgur.com/CwLkGUW.jpg)](https://www.youtube.com/watch?v=ikAmrXP8p64)

[float]: https://en.wikipedia.org/wiki/Single-precision_floating-point_format
[bfloat16]: https://en.wikipedia.org/wiki/Bfloat16_floating-point_format
[fp16]: https://en.wikipedia.org/wiki/Half-precision_floating-point_format
[pull]: https://github.com/puzzlef/pagerank-push-vs-pull
[CSR]: https://github.com/puzzlef/pagerank-class-vs-csr
["graphs"]: https://github.com/puzzlef/graphs
[SuiteSparse Matrix Collection]: https://suitesparse-collection-website.herokuapp.com
