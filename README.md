Performance of CUDA-based PageRank using **32-bit ints** vs **64-bit ints**
for the CSR representation ([pull], [CSR]).

This experiment was for comparing the performance between:
1. Find pagerank using *32-bit ints* (**int32**).
2. Find pagerank using *64-bit ints* (**int64**).

Both datatypes were attempted on different types of graphs, running each
technique 5 times per graph to get a good time measure. It seems using **int64**
datatype **increases execution time by 6-35%**, when compared to *int32*. With
respect to **GM-RATIO**, using *64-bit integer CSR representation* is **17%
slower** **(0.85x)** than using 32-bit integer CSR representation. With respect
to **AM-RATIO**, using *64-bit integer CSR representation* is **24% slower
(0.81x)**. This could be attributed to increased memory bandwidth requirement.
However, this overhead is somewhat small, despite the fact that most of the data
for a graph is actually associated with the CSR representation. As the CSR
representation is accessed linearly, improved memory coalescing might be the
*saviour* here.

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
# [00011.290 ms; 063 iters.] [7.0093e-07 err.] pagerankInt32
# [00012.017 ms; 063 iters.] [7.0093e-07 err.] pagerankInt64
#
# ...
#
# Loading graph /home/subhajit/data/soc-LiveJournal1.mtx ...
# order: 4847571 size: 68993773 {}
# order: 4847571 size: 68993773 {} (transposeWithDegree)
# [00157.232 ms; 051 iters.] [3.1616e-06 err.] pagerankInt32
# [00205.449 ms; 051 iters.] [3.1616e-06 err.] pagerankInt64
#
# ...
```

[![](https://i.imgur.com/YF3yxlJ.png)][sheetp]
[![](https://i.imgur.com/wpbOzEz.png)][sheetp]

<br>
<br>


## References

- [CUDA by Example :: Jason Sanders, Edward Kandrot](https://gist.github.com/wolfram77/72c51e494eaaea1c21a9c4021ad0f320)
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
[charts]: https://photos.app.goo.gl/Z3bJ8MTR8LrT3NHg9
[sheets]: https://docs.google.com/spreadsheets/d/1d1YsfEv5967W4cZTJicZ0IQk23IXDIP97-WoVUozpCg/edit?usp=sharing
[sheetp]: https://docs.google.com/spreadsheets/d/e/2PACX-1vQeG20hGWF2s5Li0h9zTdKxlRxM792216klp_s4X-eGQCXg-0_ri4qkE_qALZDl28bXUFy4bR16FNXA/pubhtml
