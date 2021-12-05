Performance of [nvGraph] PageRank using **32-bit floats** vs **64-bit floats**
for the rank vector.

This experiment was for comparing the performance between:
1. Find pagerank using *32-bit floats* (**float**).
2. Find pagerank using *64-bit floats* (**double**).

Both datatypes were attempted on different types of graphs, running each
technique 5 times per graph to get a good time measure. It seems using
**double** datatype **increases execution time by 17-103%**, when compared to
*float*. With respect to **GM-RATIO**, using *64-bit floating point rank vector*
is **52% slower** **(0.66x)** than using 32-bit floating point rank vector. With
respect to **AM-RATIO**, using *64-bit floating point rank vector* is **67%
slower (0.60x)**. This could be attributed to increased memory bandwidth
requirement. However, this overhead is significant, despite the fact that most
of the data for a graph is actually associated with the CSR representation, and
not the rank vector. As the rank vector is quite likely accessed randomly, low
memory coalescing might be the *culprit* here.

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
# [00014.689 ms; 000 iters.] [0.0000e+00 err.] pagerankDouble
# [00011.340 ms; 000 iters.] [1.1893e-07 err.] pagerankFloat
#
# ...
#
# Loading graph /home/subhajit/data/soc-LiveJournal1.mtx ...
# order: 4847571 size: 68993773 {}
# order: 4847571 size: 68993773 {} (transposeWithDegree)
# [00293.897 ms; 000 iters.] [0.0000e+00 err.] pagerankDouble
# [00168.549 ms; 000 iters.] [6.9520e-08 err.] pagerankFloat
#
# ...
```

[![](https://i.imgur.com/rYpzAlM.png)][sheetp]
[![](https://i.imgur.com/q9kgf0Z.png)][sheetp]

<br>
<br>


## References

- [nvGraph pagerank example, EN605.617, JHU-EP-Intro2GPU](https://github.com/JHU-EP-Intro2GPU/EN605.617/blob/master/module9/nvgraph_examples/nvgraph_Pagerank.cpp)
- [nvGraph pagerank example, CUDA Toolkit Documentation](https://docs.nvidia.com/cuda/archive/10.0/nvgraph/index.html#nvgraph-pagerank-example)
- [nvGraph Library User's Guide](https://docs.nvidia.com/cuda/archive/10.1/pdf/nvGRAPH_Library.pdf)
- [RAPIDS nvGraph NVIDIA graph library][nvGraph]
- [Adjusting PageRank parameters and Comparing results](https://arxiv.org/abs/2108.02997)
- [PageRank Algorithm, Mining massive Datasets (CS246), Stanford University](https://www.youtube.com/watch?v=ke9g8hB0MEo)
- [SuiteSparse Matrix Collection]

<br>
<br>

[![](https://i.imgur.com/wmbbEzJ.jpg)](https://www.youtube.com/watch?v=rKv_l1RnSqs)
[![DOI](https://zenodo.org/badge/433848242.svg)](https://zenodo.org/badge/latestdoi/433848242)

[Prof. Dip Sankar Banerjee]: https://sites.google.com/site/dipsankarban/
[Prof. Kishore Kothapalli]: https://www.iiit.ac.in/people/faculty/kkishore/
[SuiteSparse Matrix Collection]: https://sparse.tamu.edu
[nvGraph]: https://github.com/rapidsai/nvgraph
["graphs"]: https://github.com/puzzlef/graphs
[charts]: https://photos.app.goo.gl/eA471JBX91eGxvuy7
[sheets]: https://docs.google.com/spreadsheets/d/1GKfPQQzqbchRDfxa_6Ajqskgz_JmjOUnYTpf9AJP6bg/edit?usp=sharing
[sheetp]: https://docs.google.com/spreadsheets/d/e/2PACX-1vQykW749moJ_5S-6Sb_Us7uxuMVfQDD8KfQR8F4j0OOoA073f9tH4bd4rrWKcUnsg_UxCrblwlIM_d2/pubhtml
