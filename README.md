Performance of CUDA-based PageRank using **32-bit floats** vs **64-bit floats**
for the rank vector ([pull], [CSR]).

This experiment was for comparing the performance between:
1. Find pagerank using *32-bit floats* (**float**).
2. Find pagerank using *64-bit floats* (**double**).

Both datatypes were attempted on different types of graphs, running each
technique 5 times per graph to get a good time measure. It seems using
**double** datatype **increases execution time by 1-60%**, when compared to
*float*. With respect to **GM-RATIO**, using *64-bit floating point rank vector*
is **24% slower** **(0.81x)** than using 32-bit floating point rank vector. With
respect to **AM-RATIO**, using *64-bit floating point rank vector* is **34%
slower (0.75x)**. This could be attributed to increased memory bandwidth
requirement. However, this overhead is somewhat large, despite the fact that
most of the data for a graph is actually associated with the CSR representation,
and not the rank vector. As the rank vector is accessed randomly, low memory
coalescing might be the *culprit* here.

All outputs are saved in [out](out/) and a small part of the output is listed
here. Some [charts] are also included below, generated from [sheets]. The input
data used for this experiment is available at ["graphs"] (for small ones), and
the [SuiteSparse Matrix Collection]. This experiment was done with guidance
from [Prof. Dip Sankar Banerjee] and [Prof. Kishore Kothapalli].

<br>

```bash
$ nvcc -std=c++17 -Xcompiler -lnvgraph -O3 main.cu
$ ./a.out ~/data/min-1DeadEnd.mtx
$ ./a.out ~/data/min-2SCC.mtx
$ ...

# ...
#
# Loading graph /home/subhajit/data/web-Stanford.mtx ...
# order: 281903 size: 2312497 {}
# order: 281903 size: 2312497 {} (transposeWithDegree)
# [00011.816 ms; 063 iters.] [6.5175e-07 err.] pagerankDouble
# [00011.265 ms; 063 iters.] [7.1775e-07 err.] pagerankFloat
#
# ...
#
# Loading graph /home/subhajit/data/soc-LiveJournal1.mtx ...
# order: 4847571 size: 68993773 {}
# order: 4847571 size: 68993773 {} (transposeWithDegree)
# [00234.717 ms; 051 iters.] [3.2842e-06 err.] pagerankDouble
# [00158.415 ms; 051 iters.] [3.1327e-06 err.] pagerankFloat
#
# ...
```

[![](https://i.imgur.com/fA2z7sV.png)][sheetp]
[![](https://i.imgur.com/fAvfjWI.png)][sheetp]

<br>
<br>


## References

- [CUDA by Example :: Jason Sanders, Edward Kandrot](https://gist.github.com/wolfram77/72c51e494eaaea1c21a9c4021ad0f320)
- [Adjusting PageRank parameters and Comparing results](https://arxiv.org/abs/2108.02997)
- [PageRank Algorithm, Mining massive Datasets (CS246), Stanford University](https://www.youtube.com/watch?v=ke9g8hB0MEo)
- [SuiteSparse Matrix Collection]

<br>
<br>

[![](https://i.imgur.com/wmbbEzJ.jpg)](https://www.youtube.com/watch?v=rKv_l1RnSqs)
[![ORG](https://img.shields.io/badge/org-puzzlef-green?logo=Org)](https://puzzlef.github.io)
[![DOI](https://zenodo.org/badge/419420012.svg)](https://zenodo.org/badge/latestdoi/419420012)

[Prof. Dip Sankar Banerjee]: https://sites.google.com/site/dipsankarban/
[Prof. Kishore Kothapalli]: https://www.iiit.ac.in/people/faculty/kkishore/
[SuiteSparse Matrix Collection]: https://sparse.tamu.edu
["graphs"]: https://github.com/puzzlef/graphs
[pull]: https://github.com/puzzlef/pagerank-push-vs-pull
[CSR]: https://github.com/puzzlef/pagerank-class-vs-csr
[charts]: https://photos.app.goo.gl/WYDPyR6BaspyYByH8
[sheets]: https://docs.google.com/spreadsheets/d/1gKWLl5fjutalsFTbYObPjmBrWTmZiTYgCgH_7s8UxtE/edit?usp=sharing
[sheetp]: https://docs.google.com/spreadsheets/d/e/2PACX-1vSrHd3r7CW_4DJMuoqzvvCdWri5ZanzWG1d6wk-tEJEe-ek-toEDtx_enhvXpBxuZXbvRY4cuwk4-Lq/pubhtml
