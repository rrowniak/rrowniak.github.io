---
id: 9
title: 'New word order &#8211; sorting'
date: '2018-02-03T11:28:33+00:00'
author: 'Rafał Równiak'
layout: post
guid: 'http://rrowniak.com/?p=9'
permalink: /programming/new-word-order-sorting/
categories:
    - English
    - IT
    - Performance
    - Programming
    - Python
tags:
    - C
    - comparison
    - Java
    - Performance
    - Python
    - sort
---

Almost every modern language comes with sorting procedures. Is there any reason to dive into?

Very often it doesn’t matter which sorting procedure we select. Especially when we’re sorting a relatively small set of data, say, less than 1000 records, and the performance is not critical. Moreover, some languages give no options but one sorting procedure (taking into consideration only basic language facilities).

But what if we have gigabytes to be sorted? Let’s check out that case.

## Disclaimer

Before we go further, I’d like to clarify some things.

In this test I use only basic facilities of a given language so specialized libraries are not present here. Moreover, in real life you should consider using appropriate tools when dealing with gigabytes of data. Good examples are specialized libraries like [Numpy](http://www.numpy.org/) or [Panda](http://pandas.pydata.org/), memory cached systems ([Memcached](https://memcached.org/), [Redis](https://redis.io/)), NoSQL databases, embedded databases ([Berkeley DB](http://www.oracle.com/technetwork/database/database-technologies/berkeleydb/downloads/index.html), [LevelDB](leveldb.org/)), big data processing tools like [Apache Spark](http://spark.apache.org/), [Hadoop framework](https://hadoop.apache.org/) to name a few.

This is neither a scientific experiment nor a proof of superiority one language over the others. This is only a brief description and short test of built-in sorting procedures.

The tests were executed on a laptop with i7 processor and 64 GB RAM. The source code is available [here](https://github.com/rrowniak/blog/tree/master/sorting_big).

## Data (generator)

In order to generate a representative set of data I prepared a special procedure. I could have used randomly generated data but I wanted to have the same data across all tests.

The procedure is just a simple linear congruential generator.

```
<pre class="brush: plain; title: ; notranslate" title="">
x_1 = seed
x_n+1 = (a x_n + c) mod m
```

with the following factors:

```
<pre class="brush: plain; title: ; notranslate" title="">
a = 48271
c = 0
m = 2147483647
seed = 1
```

Using this procedure I’ll generate 1 000 000 000 records (or less if that number cannot be handled).

Each record is a structure containing two 64-bit unsigned integers. The first field acts as a simple identifier, the second field is a value to be sorted. In C and C++ the record looks as follows:

```
<pre class="brush: cpp; title: ; notranslate" title="">
struct {
uint64_t id;
uint64_t value;
};
```

Although this is only an example, you can imagine the structure as being a simple index record, pointing to some real data. However, in real life you’d rather use a specialized tool or library instead of reinventing the wheel.

## C++

C++ comes with two sorting procedures; the first one called `std::sort` is guaranteed to have *O(N log(N))* complexity. This constraint is valid since C++11 (before C++11, it was *O(N log(N))* on average). Engineers who implement the Standard Library are free to take any sorting algorithm provided it conforms the requirements. In case of libstdc++ (used by e.g. gcc) it is the [introsort](https://en.wikipedia.org/wiki/Introsort), that is, kind of quick-sort with limited branching (by switching to the heap sort) to avoid the worst case scenario which is *O(N²)*.

The second sorting procedure is `std::stable_sort`. As the name suggests, sorting is stable, that is, equal elements preserve its relative order. The complexity is *O(N log²(N))* but it can be reduced to *O(N log(N))* if additional memory is available.

So the title of this paragraph might be misleading as we are going to test sorting procedures implemented in libstdc++ and compiled by gcc v5.4.1, in this particular case.

Let’s check the results of sorting 1 000 000 000 (one billion) records.

| **Sorting procedure** | **Memory** | **Creation** | **Sorting** | **Checking result** | **Remarks** |
|---|---|---|---|---|---|
| std::sort | 15 GB | 5 seconds | 112 seconds | 1 second | -O2/-O3 |
| std::sort | 15 GB | 21 seconds | 614 seconds | 13 second | optimizations turned off |
| std::stable\_sort | 22 GB | 5 seconds | 140 seconds | 1 second | -O2/-O3 |
| std::stable\_sort | 22 GB | 21 seconds | 689 seconds | 12 second | optimizations turned off |

Also, I checked which comparator is faster, lambda or struct based – there is no difference. Similar story with optimization level O2 vs O3 – no difference.

## C

The standard C library offers the `qsort` procedure. The implementation is not defined (like in C++). Moreover, there are no complexity requirements and `qsort` doesn’t have to be stable. Theoretically, it could be even the bubble sort (*O(n²)*) but fortunately this is very unlikely.

The implementation can be tricky, for example, there might be leveraged more than one algorithm depending on collection size and whether „additional” memory is available.

In this particular execution (linux, glibc, gcc v5.4.1), the merge sort variant was chosen by the runtime taking additional memory (about +7GB). If that additional memory was not available, quick-sort would be selected.

Sorting 1 000 000 000 records…

| **Sorting procedure** | **Memory** | **Creation** | **Sorting** | **Checking result** | **Remarks** |
|---|---|---|---|---|---|
| qsort | 22 GB | 4 seconds | 277 seconds | &lt; 1 second | -O2/-O3 |
| qsort | 22 GB | 12 seconds | 355 seconds | 2 seconds | optimizations turned off |

Like in C++, optimization levels O2 and O3 don’t differ too much.

C++ seems to be a bit faster, probably due to the fact, that the comparison function was inlined, and possibly, different algorithms and implementations also matters.

## Python

As Python is not intended to be a high-performance language, I had to limit data set to 100 000 000 (a tenth of the initial number).

Python’s built-in sort is implemented in C and the algorithm is called [timsort](https://en.wikipedia.org/wiki/Timsort). This is a kind of the merge sort supported by the insertion sort. Requires additional memory; *O(n)* in the worst case. The complexity is *O(n log(n))* – the worst case and average case as well.

| **Sorting procedure** | **Memory** | **Creation** | **Sorting** | **Checking result** | **Remarks** |
|---|---|---|---|---|---|
| sort | 43 GB | 129 seconds | 340 seconds | 50 seconds |  |

Pretty good numbers as for a scripting language. Python allows playing with reasonable big data sets.

## Java

Java (&gt;=7) also uses the timsort algorithm, at least for sorting objects. For sorting primitives, heuristics are leveraged to select right algorithm.

The distinction in sorting between objects and primitive types has been introduced to take advantage of some properties allowing further optimizations. One property is that for primitive types, the sorting algorithm doesn’t have to be stable. Another observation is that in order to compare objects, the function `Object.compare()` is called. It doesn’t have to be expensive, but there is a certain cost related anyway. Primitive types can be compared using faster and inline code.

Let’s sort 1 000 000 000 records…

| **Sorting procedure** | **Memory** | **Creation** | **Sorting** | **Checking result** | **Remarks** |
|---|---|---|---|---|---|
| sort | 41 GB | 60 seconds | 788 seconds | 22 seconds | \* |

The test can’t be completed if one uses only default VM parameters. The first thing is to set Xms and Xmx parameters to large enough values. In my test I used the concurrent collector as it gives relatively good results in this case.

\*) -Xmx50g -Xms50g -XX:+UseConcMarkSweepGC -XX:NewSize=5g

## Conclusions

Be aware that some sorting algorithms might take additional memory (e.g. the merge sort and its derivatives).

Some sorting procedures take advantage of more than one sorting algorithm. They may select the best algorithm depending on the input (size, if almost sorted, if array of built-in types, etc).

C and C++. Always take into consideration compiler’s optimization options as it gives a significant speed boost. Not only when dealing with sorting procedures.

Java. Be aware the default VM settings won’t always be a good choice.

The more dynamic language, the bigger memory consumption. Usually.

When dealing with huge data sets, consider using specialized tools.

Regarding the performance – always measure, don’t make blind assumptions.