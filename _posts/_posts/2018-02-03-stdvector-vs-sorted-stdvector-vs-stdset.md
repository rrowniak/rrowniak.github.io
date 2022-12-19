---
id: 11
title: 'std::vector vs sorted std::vector vs std::set'
date: '2018-02-03T12:57:39+00:00'
author: 'Rafał Równiak'
layout: post
guid: 'http://rrowniak.com/?p=11'
permalink: /programming/stdvector-vs-sorted-stdvector-vs-stdset/
categories:
    - English
    - Performance
    - Programming
tags:
    - C
    - comparison
    - Performance
    - sort
    - sorting
---

In this short article I’m going to make a comparison between std::vector, sorted std::vector and std::set. However, I’m going to focus only on one aspect – which collection is faster during lookup.

Looks like the answer is rather trivial – std::map and sorted std::vector offer access to any element in O(log n) time while unsorted std::vector offers linear finding. To be precise – std::vector + std::find as std::vector doesn’t have built-in find function. Indeed, sorted collections are winners… Or maybe the answer is not so trivial?

## Disclaimer

First of all, this is not a definitive answer which collection is faster in that particular case. The test results strongly depends on underlying hardware, especially CPU model and memory. In my case it is Intel’s i7. So if you would like to know how it behaves on your hardware, you need to make such tests on your own. Fortunately, the source code is available [here](https://github.com/rrowniak/blog/tree/master/vect_vs_set) so there is no need to write them once again.

## Test procedure

The test procedure is rather simple. Fill out given collection with random data and then ask for some randomly generated items. The latter operations will be checked against execution time.

Please note that the results should not be interpreted as absolute values, rather they should be compared to each other.

## 1 element

| **Action** | **Time for unoptimized** | **Time for O2** | **Time for O3** |
|---|---|---|---|
| Unsorted std::vector lookup | 170 ms | 8 ms | 9 ms |
| Sorted std::vector lookup | 169 ms | 4 ms | 4 ms |
| std::set lookup | 174 ms | 4 ms | 5 ms |

## 10 elements

| **Action** | **Time for unoptimized** | **Time for O2** | **Time for O3** |
|---|---|---|---|
| Unsorted std::vector lookup | 207 ms | 7 ms | 7 ms |
| Sorted std::vector lookup | 240 ms | 12 ms | 10 ms |
| std::set lookup | 259 ms | 7 ms | 7 ms |

## 100 elements

| **Action** | **Time for unoptimized** | **Time for O2** | **Time for O3** |
|---|---|---|---|
| Unsorted std::vector lookup | 1 115 ms | 56 ms | 56 ms |
| Sorted std::vector lookup | 384 ms | 16 ms | 17 ms |
| std::set lookup | 449 ms | 12 ms | 11 ms |

## 1k elements

| **Action** | **Time for unoptimized** | **Time for O2** | **Time for O3** |
|---|---|---|---|
| Unsorted std::vector lookup | 9 964 ms | 408 ms | 408 ms |
| Sorted std::vector lookup | 546 ms | 59 ms | 59 ms |
| std::set lookup | 589 ms | 60 ms | 61 ms |

## 10k elements

| **Action** | **Time for unoptimized** | **Time for O2** | **Time for O3** |
|---|---|---|---|
| Unsorted std::vector lookup | 99 537 ms | 4 269 ms | 4 473 ms |
| Sorted std::vector lookup | 708 ms | 86 ms | 96 ms |
| std::set lookup | 742 ms | 120 ms | 121 ms |

## 100k elements

| **Action** | **Time for unoptimized** | **Time for O2** | **Time for O3** |
|---|---|---|---|
| Unsorted std::vector lookup | – | – | – |
| Sorted std::vector lookup | 864 ms | 138 ms | 136 ms |
| std::set lookup | 959 ms | 207 ms | 213 ms |

## 1 000k elements

| **Action** | **Time for unoptimized** | **Time for O2** | **Time for O3** |
|---|---|---|---|
| Unsorted std::vector lookup | – | – | – |
| Sorted std::vector lookup | 1 073 ms | 191 ms | 195 ms |
| std::set lookup | 1 725 ms | 702 ms | 706 ms |

## Conclusions

The unoptimized build offers significantly worse performance. There is no difference between O2 and O3 in this particular case.

Sorted std::vector is faster than std::set when the collection size is large, &gt; 1k. The bigger collection, the more significant difference.

When a collection size is small, no more than 20 items, one can notice some anomalies. For example, linear searching unsorted collection may be faster than binary search. However, it may strongly depend on underlying hardware.