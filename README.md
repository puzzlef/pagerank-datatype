Performance of CUDA-based PageRank using **32-bit floats** vs **64-bit floats** ([pull], [CSR]).

`TODO!`

This experiment was for comparing the performance between:
1. Find pagerank using *32-bit floats* (**float**).
2. Find pagerank using *64-bit floats* (**double**).

Both datatypes were attempted on different types of graphs, running each
technique 5 times per graph to get a good time measure. It seems using
**double** datatype **increases execution time by a small factor** in all cases.
This could be attributed to increased memory bandwidth requirement. However,
since most of the data for a graph (CSR) is stored as 32-bit ints, it possibly
makes up most of the memory bottleneck, and not the rank vector. Note that
neither approach makes use of *SIMD instructions* which are available on all
modern hardware.

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
# [00400.480 ms; 062 iters.] [0.0000e+00 err.] pagerankFloat
# [00480.127 ms; 062 iters.] [4.8116e-06 err.] pagerankDouble
#
# ...
#
# Loading graph /home/subhajit/data/soc-LiveJournal1.mtx ...
# order: 4847571 size: 68993773 {}
# order: 4847571 size: 68993773 {} (transposeWithDegree)
# [11482.458 ms; 050 iters.] [0.0000e+00 err.] pagerankFloat
# [14564.962 ms; 050 iters.] [2.0510e-03 err.] pagerankDouble
#
# ...
```

[![](https://i.imgur.com/BlQlw5h.png)][sheets]
[![](https://i.imgur.com/Qiwx1Wa.png)][sheets]

<br>
<br>


## References

- [PageRank Algorithm, Mining massive Datasets (CS246), Stanford University](https://www.youtube.com/watch?v=ke9g8hB0MEo)
- [SuiteSparse Matrix Collection]

<br>
<br>

[![](https://i.imgur.com/wmbbEzJ.jpg)](https://www.youtube.com/watch?v=rKv_l1RnSqs)

[Prof. Dip Sankar Banerjee]: https://sites.google.com/site/dipsankarban/
[Prof. Kishore Kothapalli]: https://cstar.iiit.ac.in/~kkishore/
[SuiteSparse Matrix Collection]: https://suitesparse-collection-website.herokuapp.com
["graphs"]: https://github.com/puzzlef/graphs
[pull]: https://github.com/puzzlef/pagerank-push-vs-pull
[CSR]: https://github.com/puzzlef/pagerank-class-vs-csr
[charts]: https://photos.app.goo.gl/tPd6r5AqbrDbAKscA
[sheets]: https://docs.google.com/spreadsheets/d/11HIFInVml1sxBE86kQadxnVU7rlGBDjrxeFzJSMFmIM/edit?usp=sharing
