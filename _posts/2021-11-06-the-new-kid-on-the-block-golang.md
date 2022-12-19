---
id: 853
title: 'The new kid on the block &#8211; golang'
date: '2021-11-06T16:31:48+00:00'
author: 'Rafał Równiak'
layout: post
guid: 'http://rrowniak.com/?p=853'
permalink: /performance/the-new-kid-on-the-block-golang/
categories:
    - Performance
tags:
    - C
    - c++
    - go
    - Golang
    - Java
    - Performance
    - Python
    - sorting
---

Do you remember my [article](http://rrowniak.com/performance/new-word-order-sorting/) about the speed of sorting large data chunk in different languages? Of course you don’t. So, I advice you to go through that article as there is a description of the test procedure. However, today I’m going to extend this benchmark by testing *go* language. The results will be surprising…

Let’s re-execute the test. This time I’ll be using a dedicated script `run_experiment.sh` which does all what’s needed and prints results in a friendly way:

<div class="wp-block-syntaxhighlighter-code ">```
<pre class="brush: plain; title: ; notranslate" title="">
$ ./run_experiment.sh 
Starting tests...
Language             Records #     Bulding time  Sorting time  Testing time  Total time        RSS memory usage
cpp optimized          100,000,000 B:   1.027 s, S:  10.312 s, T:   0.011 s, Total:  11.500 s, Mem: 1.5 GB (1565736 kB)
cpp debug              100,000,000 B:   2.496 s, S:  54.936 s, T:   0.059 s, Total:  58.890 s, Mem: 1.5 GB (1565672 kB)
c optimized            100,000,000 B:   0.899 s, S:  31.997 s, T:   0.033 s, Total:  33.060 s, Mem: 3.0 GB (3126412 kB)
c debug                100,000,000 B:   1.707 s, S:  39.647 s, T:   0.042 s, Total:  41.660 s, Mem: 3.0 GB (3126492 kB)
go                     100,000,000 B:   0.686 s, S:  29.685 s, T:   0.031 s, Total:  30.750 s, Mem: 1.5 GB (1614968 kB)
java                   100,000,000 B:   1.793 s, S:  71.187 s, T:   0.078 s, Total:  78.480 s, Mem: 3.9 GB (4062140 kB)
python                  20,000,000 B:  25.476 s, S:  50.473 s, T:   0.148 s, Total: 147.800 s, Mem: 9.0 GB (9466744 kB)
```

</div>Here is the visualization.

<figure class="wp-block-image size-large">[![](https://i2.wp.com/rrowniak.com/wp-content/uploads/2021/11/Results.png?resize=696%2C348)](https://i2.wp.com/rrowniak.com/wp-content/uploads/2021/11/Results.png)</figure>All sources including supporting scripts and gnuplot script are available on my [github](https://github.com/rrowniak/blog/tree/master/sorting_big).

Ok, tests have passed, so now it’s time to review the results and draw the conclusions.

- C++ optimized test program is the fastest one. No surprise here.
- C++ with debug symbols enabled – isn’t performing well. **If you’re looking for speed, debug symbols need to be switch off.**
- C program. Not a big difference between optimized and debug version. Relatively slow in comparison to C++. That might be due to a different sorting algorithm used and inability to inline the comparison function. Another unpleasant surprise **is memory consumption which is double in comparison to** C++. The algorithm that is used when calling qsort (merge sort?) has apparently O(n) memory complexity.
- Go. Very good results! Memory consumption like C++ version and **faster than C optimized program!** Of course, it doesn’t mean that Go is faster than C in general, just for this task it performs better (better sorting algo).
- Java. I’d expect that Java will produce the results similar to Go’s and vice versa.
- Python. Very high memory consumption and pretty slow execution time. It requires 9GB of memory while theoretical minimum is 1,5 GB (C++ and Go). For doing such tasks, specialized libraries will be needed (e.g. scipy).