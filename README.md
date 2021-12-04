Performance of PageRank using **32-bit ints** vs **64-bit ints** for the
CSR representation ([pull], [CSR]).

This experiment was for comparing the performance between:
1. Find pagerank using *32-bit ints* (**int32**).
2. Find pagerank using *64-bit ints* (**int64**).

Both datatypes were attempted on different types of graphs, running each
technique 5 times per graph to get a good time measure. It seems using **int64**
datatype **increases execution time by 1-16%**, when compared to *int32*. With
respect to **GM-RATIO** as well as **AM-RATIO**, using *64-bit integer CSR*
*representation* is **9% slower** **(0.92x)** than using 32-bit integer CSR
representation. This could be attributed to increased memory bandwidth
requirement. However, this overhead is quite small, despite the fact that most
of the data for a graph is actually associated with the CSR representation. As
the CSR representation is accessed linearly, improved cache usage might be the
*saviour* here. Note that neither approach makes use of *SIMD instructions*
which are available on all modern hardware.

All outputs are saved in [out](out/) and a small part of the output is listed
here. Some [charts] are also included below, generated from [sheets]. The input
data used for this experiment is available at ["graphs"] (for small ones), and
the [SuiteSparse Matrix Collection]. This experiment was done with guidance
from [Prof. Dip Sankar Banerjee] and [Prof. Kishore Kothapalli].

<br>

```bash
$ g++ -std=c++17 -O3 main.cxx
$ ./a.out ~/data/min-1DeadEnd.mtx
$ ./a.out ~/data/min-2SCC.mtx
$ ...

# ...
#
# Loading graph /home/subhajit/data/web-Stanford.mtx ...
# order: 281903 size: 2312497 {}
# order: 281903 size: 2312497 {} (transposeWithDegree)
# [00414.212 ms; 063 iters.] [0.0000e+00 err.] pagerankInt32
# [00468.302 ms; 063 iters.] [0.0000e+00 err.] pagerankInt64
#
# ...
#
# Loading graph /home/subhajit/data/soc-LiveJournal1.mtx ...
# order: 4847571 size: 68993773 {}
# order: 4847571 size: 68993773 {} (transposeWithDegree)
# [12163.961 ms; 051 iters.] [0.0000e+00 err.] pagerankInt32
# [13902.273 ms; 051 iters.] [0.0000e+00 err.] pagerankInt64
#
# ...
```

[![](https://i.imgur.com/hVnPp0I.png)][sheetp]
[![](https://i.imgur.com/PNGt374.png)][sheetp]

<br>
<br>


## References

- [Adjusting PageRank parameters and Comparing results](https://arxiv.org/abs/2108.02997)
- [PageRank Algorithm, Mining massive Datasets (CS246), Stanford University](https://www.youtube.com/watch?v=ke9g8hB0MEo)
- [SuiteSparse Matrix Collection]

<br>
<br>

[![](https://i.imgur.com/UN5uFOX.png)](https://www.youtube.com/watch?v=rKv_l1RnSqs)

[Prof. Dip Sankar Banerjee]: https://sites.google.com/site/dipsankarban/
[Prof. Kishore Kothapalli]: https://www.iiit.ac.in/people/faculty/kkishore/
[SuiteSparse Matrix Collection]: https://sparse.tamu.edu
["graphs"]: https://github.com/puzzlef/graphs
[pull]: https://github.com/puzzlef/pagerank-push-vs-pull
[CSR]: https://github.com/puzzlef/pagerank-class-vs-csr
[charts]: https://photos.app.goo.gl/S9mGYDgE2PXUbjVr8
[sheets]: https://docs.google.com/spreadsheets/d/1u9Hn4tA682wYj00hcvWZSrz94nhhvwRxqEjhDjbZWKo/edit?usp=sharing
[sheetp]: https://docs.google.com/spreadsheets/d/e/2PACX-1vQG_Xiqo2aM1BSRlRQ0Hmhu_fqXjffAAQb0R82YhXmydan-uRo54gllhTpBIwVkJgHg1KKRpGpwaU1_/pubhtml
