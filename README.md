Comparison of PageRank using [float] vs [bfloat16] as the **storage type**
([pull], [CSR]).

This experiment was for comparing the result between:
1. Find pagerank using **float** as the storage type.
2. Find pagerank using **bfloat16** as the storage type.

Both datatypes were attempted on different types of graphs, running each
technique 5 times per graph to get a good time measure. Unfortunately it seems
**bfloat16** cannot be used for PageRank as its **too inaccurate** (atleast
when simply replacing *float* vectors with *bfloat16* vectors). Using [fp16]
might work, but likely give negligible performance improvement over float.
Note that neither approach makes use of *SIMD instructions* which are
available on all modern hardware.

All outputs are saved in [out](out/) and a small part of the output is listed
here. The input data used for this experiment is available at ["graphs"] (for
small ones), and the [SuiteSparse Matrix Collection]. This experiment was done
with guidance from [Prof. Dip Sankar Banerjee] and [Prof. Kishore Kothapalli].

<br>

```bash
$ g++ -O3 main.cxx
$ ./a.out ~/data/min-1DeadEnd.mtx
$ ./a.out ~/data/min-2SCC.mtx
$ ...

# ...
#
# Loading graph /home/subhajit/data/web-Stanford.mtx ...
# order: 281903 size: 2312497 {}
# order: 281903 size: 2312497 {} (transposeWithDegree)
# [00375.217 ms; 062 iters.] [0.0000e+00 err.] pagerankFloat
# [00298.391 ms; 047 iters.] [4.1805e-02 err.] pagerankBfloat16
#
# ...
#
# Loading graph /home/subhajit/data/soc-LiveJournal1.mtx ...
# order: 4847571 size: 68993773 {}
# order: 4847571 size: 68993773 {} (transposeWithDegree)
# [11260.648 ms; 050 iters.] [0.0000e+00 err.] pagerankFloat
# [13895.689 ms; 068 iters.] [4.3118e-02 err.] pagerankBfloat16
#
# ...
```

<br>
<br>


## References

- [PageRank Algorithm, Mining massive Datasets (CS246), Stanford University](https://www.youtube.com/watch?v=ke9g8hB0MEo)
- [Convert FP32 to Bfloat16 in C++](https://stackoverflow.com/a/64493446/1413259)
- [Why is there no 2-byte float and does an implementation already exist?](https://stackoverflow.com/a/56017304/1413259)
- [Is it safe to reinterpret_cast an integer to float?](https://stackoverflow.com/a/13982359/1413259)
- [SuiteSparse Matrix Collection]

<br>
<br>

[![](https://i.imgur.com/CwLkGUW.jpg)](https://www.youtube.com/watch?v=ikAmrXP8p64)

[Prof. Dip Sankar Banerjee]: https://sites.google.com/site/dipsankarban/
[Prof. Kishore Kothapalli]: https://cstar.iiit.ac.in/~kkishore/
[SuiteSparse Matrix Collection]: https://suitesparse-collection-website.herokuapp.com
["graphs"]: https://github.com/puzzlef/graphs
[float]: https://en.wikipedia.org/wiki/Single-precision_floating-point_format
[bfloat16]: https://en.wikipedia.org/wiki/Bfloat16_floating-point_format
[fp16]: https://en.wikipedia.org/wiki/Half-precision_floating-point_format
[pull]: https://github.com/puzzlef/pagerank-push-vs-pull
[CSR]: https://github.com/puzzlef/pagerank-class-vs-csr
