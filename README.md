Comparison of *PageRank algorithm* using various **datatypes**.

<br>


### Comparing Float vs Double Rank vector

This experiment ([rank-float-vs-double]) was for comparing the performance
between finding pagerank using *32-bit floats* (**float**), and finding pagerank
using *64-bit floats* (**double**). Both datatypes were attempted on different
types of graphs, running each technique 5 times per graph to get a good time
measure.

It seems using **double** datatype **increases execution time by 0-33%**, when
compared to *float*. With respect to **GM-RATIO**, using *64-bit floating point*
*rank vector* is **12% slower** **(0.89x)** than using 32-bit floating point rank
vector. With respect to **AM-RATIO**, using *64-bit floating point rank vector*
is **17% slower (0.85x)**. This could be attributed to increased memory
bandwidth requirement. However, this overhead is somewhat large, despite the
fact that most of the data for a graph is actually associated with the CSR
representation, and not the rank vector. As the rank vector is accessed
randomly, a high cache miss ratio might be the *culprit* here. Note that neither
approach makes use of *SIMD instructions* which are available on all modern
hardware.

[rank-float-vs-double]: https://github.com/puzzlef/pagerank-datatype/tree/rank-float-vs-double

<br>


### Comparing Float vs BFloat16 Rank vector

This experiment ([rank-float-vs-bfloat16]) was for comparing the result between
finding pagerank using [float] as the storage type, and finding pagerank using
[bfloat16] as the storage type. Both datatypes were attempted on different
types of graphs, running each technique 5 times per graph to get a good time
measure.

Unfortunately it seems **bfloat16** cannot be used for PageRank as its
**too inaccurate** (atleast when simply replacing *float* vectors with *bfloat16*
vectors). Using [fp16] might work, but likely give negligible performance
improvement over float. Note that neither approach makes use of *SIMD
instructions* which are available on all modern hardware.

[rank-float-vs-bfloat16]: https://github.com/puzzlef/pagerank-datatype/tree/rank-float-vs-bfloat16
[float]: https://en.wikipedia.org/wiki/Single-precision_floating-point_format
[bfloat16]: https://en.wikipedia.org/wiki/Bfloat16_floating-point_format
[fp16]: https://en.wikipedia.org/wiki/Half-precision_floating-point_format

<br>


### Comparing Float vs Double Rank vector with CUDA

This experiment ([cuda-rank-float-vs-double]) was for comparing the performance
between finding pagerank using *32-bit floats* (**float**), and finding pagerank
using *64-bit floats* (**double**). Both datatypes were attempted on different
types of graphs, running each technique 5 times per graph to get a good time
measure.

It seems using **double** datatype **increases execution time by 1-60%**, when
compared to *float*. With respect to **GM-RATIO**, using *64-bit floating point*
*rank vector* is **24% slower** **(0.81x)** than using 32-bit floating point rank
vector. With respect to **AM-RATIO**, using *64-bit floating point rank vector*
is **34% slower (0.75x)**. This could be attributed to increased memory
bandwidth requirement. However, this overhead is somewhat large, despite the
fact that most of the data for a graph is actually associated with the CSR
representation, and not the rank vector. As the rank vector is accessed
randomly, low memory coalescing might be the *culprit* here.

[cuda-rank-float-vs-double]: https://github.com/puzzlef/pagerank-datatype/tree/cuda-rank-float-vs-double

<br>


### Comparing Float vs Double Rank vector with nvGraph

This experiment ([nvgraph-rank-float-vs-double]) was for comparing the
performance between finding pagerank using *32-bit floats* (**float**), and
finding pagerank using *64-bit floats* (**double**). Both datatypes were
attempted on different types of graphs, running each technique 5 times per graph
to get a good time measure.

It seems using **double** datatype **increases execution time by 17-103%**, when
compared to *float*. With respect to **GM-RATIO**, using *64-bit floating point*
*rank vector* is **52% slower** **(0.66x)** than using 32-bit floating point rank
vector. With respect to **AM-RATIO**, using *64-bit floating point rank vector*
is **67% slower (0.60x)**. This could be attributed to increased memory
bandwidth requirement. However, this overhead is significant, despite the fact
that most of the data for a graph is actually associated with the CSR
representation, and not the rank vector. As the rank vector is quite likely
accessed randomly, low memory coalescing might be the *culprit* here.

[nvgraph-rank-float-vs-double]: https://github.com/puzzlef/pagerank-datatype/tree/nvgraph-rank-float-vs-double

<br>


### Comparing Int32 vs Int64 CSR

This experiment ([csr-int32-vs-int64]) was for comparing the performance between
finding pagerank using *32-bit ints* (**int32**), and finding pagerank using
*64-bit ints* (**int64**). Both datatypes were attempted on different types of
graphs, running each technique 5 times per graph to get a good time measure.

It seems using **int64** datatype **increases execution time by 1-16%**, when
compared to *int32*. With respect to **GM-RATIO** as well as **AM-RATIO**, using
*64-bit integer CSR* *representation* is **9% slower** **(0.92x)** than using
32-bit integer CSR representation. This could be attributed to increased memory
bandwidth requirement. However, this overhead is quite small, despite the fact
that most of the data for a graph is actually associated with the CSR
representation. As the CSR representation is accessed linearly, improved cache
usage might be the *saviour* here. Note that neither approach makes use of *SIMD
instructions* which are available on all modern hardware.

[csr-int32-vs-int64]: https://github.com/puzzlef/pagerank-datatype/tree/csr-int32-vs-int64

<br>


### Comparing Int32 vs Int64 CSR with CUDA

This experiment ([cuda-csr-int32-vs-int64]) was for comparing the performance
between find pagerank using *32-bit ints* (**int32**), and finding pagerank
using *64-bit ints* (**int64**). Both datatypes were attempted on different
types of graphs, running each technique 5 times per graph to get a good time
measure.

It seems using **int64** datatype **increases execution time by 6-35%**, when
compared to *int32*. With respect to **GM-RATIO**, using *64-bit integer CSR*
*representation* is **17% slower** **(0.85x)** than using 32-bit integer CSR
representation. With respect to **AM-RATIO**, using *64-bit integer CSR*
*representation* is **24% slower (0.81x)**. This could be attributed to increased
memory bandwidth requirement. However, this overhead is somewhat small, despite
the fact that most of the data for a graph is actually associated with the CSR
representation. As the CSR representation is accessed linearly, improved memory
coalescing might be the *saviour* here.

[cuda-csr-int32-vs-int64]: https://github.com/puzzlef/pagerank-datatype/tree/cuda-csr-int32-vs-int64

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
[![DOI](https://zenodo.org/badge/366614563.svg)](https://zenodo.org/badge/latestdoi/366614563)
![](https://ga-beacon.deno.dev/G-KD28SG54JQ:hbAybl6nQFOtmVxW4if3xw/github.com/puzzlef/pagerank-datatype)

[Prof. Dip Sankar Banerjee]: https://sites.google.com/site/dipsankarban/
[Prof. Kishore Kothapalli]: https://www.iiit.ac.in/people/faculty/kkishore/
[SuiteSparse Matrix Collection]: https://sparse.tamu.edu
