Performance of PageRank using **32-bit floats** vs **64-bit floats** for the
rank vector ([pull], [CSR]).

`TODO!`

This experiment was for comparing the performance between:
1. Find pagerank using *32-bit floats* (**float**).
2. Find pagerank using *64-bit floats* (**double**).

Both datatypes were attempted on different types of graphs, running each
technique 5 times per graph to get a good time measure. It seems using
**double** datatype **increases execution time by a small factor** in all cases.
With respect to **GM-RATIO**, using *64-bit floating point rank vector* is **12%
slower** **(1.12x)** than using 32-bit floating point rank vector. With respect
to **AM-RATIO**, using *64-bit floating point rank vector* is **17% slower
(1.17x)**. This could be attributed to increased memory bandwidth requirement.
However, since most of the data for a graph (CSR) is stored as 32-bit ints, it
possibly makes up most of the memory bottleneck, and not the rank vector. Note
that neither approach makes use of *SIMD instructions* which are available on
all modern hardware.

All outputs are saved in [out](out/) and a small part of the output is listed
here. Some [charts] are also included below, generated from [sheets]. The input
data used for this experiment is available at ["graphs"] (for small ones), and
the [SuiteSparse Matrix Collection]. This experiment was done with guidance
from [Prof. Dip Sankar Banerjee] and [Prof. Kishore Kothapalli].

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
# [00501.080 ms; 063 iters.] [0.0000e+00 err.] pagerankDouble
# [00408.583 ms; 063 iters.] [4.8093e-06 err.] pagerankFloat
#
# ...
#
# Loading graph /home/subhajit/data/soc-LiveJournal1.mtx ...
# order: 4847571 size: 68993773 {}
# order: 4847571 size: 68993773 {} (transposeWithDegree)
# [16090.539 ms; 051 iters.] [0.0000e+00 err.] pagerankDouble
# [12090.672 ms; 051 iters.] [2.0580e-03 err.] pagerankFloat
#
# ...
```

[![](https://i.imgur.com/DLrzXMA.png)][sheetp]
[![](https://i.imgur.com/zMVDfv5.png)][sheetp]

<br>
<br>


## References

- [Adjusting PageRank parameters and Comparing results](https://arxiv.org/abs/2108.02997)
- [PageRank Algorithm, Mining massive Datasets (CS246), Stanford University](https://www.youtube.com/watch?v=ke9g8hB0MEo)
- [SuiteSparse Matrix Collection]

<br>
<br>

[![](https://i.imgur.com/wmbbEzJ.jpg)](https://www.youtube.com/watch?v=rKv_l1RnSqs)

[Prof. Dip Sankar Banerjee]: https://sites.google.com/site/dipsankarban/
[Prof. Kishore Kothapalli]: https://www.iiit.ac.in/people/faculty/kkishore/
[SuiteSparse Matrix Collection]: https://sparse.tamu.edu
["graphs"]: https://github.com/puzzlef/graphs
[pull]: https://github.com/puzzlef/pagerank-push-vs-pull
[CSR]: https://github.com/puzzlef/pagerank-class-vs-csr
[charts]: https://photos.app.goo.gl/tPd6r5AqbrDbAKscA
[sheets]: https://docs.google.com/spreadsheets/d/11HIFInVml1sxBE86kQadxnVU7rlGBDjrxeFzJSMFmIM/edit?usp=sharing
[sheetp]: https://docs.google.com/spreadsheets/d/e/2PACX-1vQ-MHyi0AIIXVex8NUAJDfwChpxAa0khRF5Z_PDBGoVx8Kv_vt6kYwEc7iGaHRlyBF1dPOlqZMhOvBQ/pubhtml
