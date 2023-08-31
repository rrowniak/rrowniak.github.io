---
id: 805
title: 'Tip of the day: gcc address sanitizer'
date: '2021-02-03T08:05:24+00:00'
author: 'Rafał Równiak'
layout: post
guid: 'http://rrowniak.com/?p=805'
permalink: /linux/tip-of-the-day-gcc-memory-sanitizer/
categories:
    - C
    - C++
    - English
    - Linux
---

Today I’m going to show you how effectively solve painful issues related to memory corruption occurrences.

Let’s start from the example. Consider the following code:

```
<pre class="wp-block-code">```cpp
#include <iostream>

int array[2];
int table[2];

int main(int argc, char** argv)
{   
    array[2] = 11;

    if (table[0] == 0) {
        std::cout << "Obvious!" << std::endl;
    } else {
        std::cout << "Not really... Something is wrong" << std::endl;
        std::cout << table[0] << " vs " << array[2] << std::endl;
    }

    return array[0];
}
```
```

And corresponding makefile:

```
<pre class="wp-block-code">```bash
CPPFLAGS = -g -Wall
LDFLAGS = -g
LDLIBS = -lm -ldl

test: test.o
    g++ $(LDFLAGS) -o test test.o $(LDLIBS)

test.o: test.cpp
    g++ $(CPPFLAGS) -c test.cpp

clean:
    @rm test test.o
```
```

Let’s build &amp; execute the program:

```
<pre class="wp-block-code">```bash
$ make
 g++ -g -Wall -c test.cpp
 g++ -g -o test test.o -lm -ldl
$ ./test 
 Not really… Something is wrong
 11 vs 11
```
```

The issue is visible in the source without using any fancy tool. But if you have hundreds of thousands of lines of code, the problem isn’t such trivial. Moreover, it may not manifest all the time but just from time to time and it doesn’t have to be a crash – sometimes it’s just a weird program behavior like the above example.

Can we do anything around that? Yes – gcc built-in address sanitizer. That feature adds additional instrumentation to our code and will perform monitoring in the runtime like checking whether our code access only allocated memory, stack overflows, and many more.

In order to enable the address sanitizer let’s modify slightly our makefile:

```
<pre class="wp-block-code">```bash
CPPFLAGS = -g -Wall
LDFLAGS = -g
LDLIBS = -lm -ldl

test: test.o
    g++ $(LDFLAGS) -o test test.o $(LDLIBS)

test.o: test.cpp
    g++ $(CPPFLAGS) -c test.cpp

asan: CPPFLAGS += -fsanitize=address
asan: LDLIBS += -lasan
asan: test

clean:
    @rm test test.o
```
```

And build – this time using non-default target:

```
<pre class="wp-block-code">```bash
$ make clean
$ make asan
 g++ -g -Wall -fsanitize=address -c test.cpp
 g++ -g -o test test.o -lm -ldl -lasan
```
```

Now the most interesting part – let’s execute our program:

```
<pre class="wp-block-code">```bash
$ ./test 
 ==26315==ERROR: AddressSanitizer: global-buffer-overflow on address 0x55b90bac2388 at pc 0x55b90b8c0ffb bp 0x7ffe6500cb20 sp 0x7ffe6500cb10
 WRITE of size 4 at 0x55b90bac2388 thread T0
     #0 0x55b90b8c0ffa in main /home/local/CORVIL/rrowniak/tmp/sanitizer/test.cpp:8
     #1 0x7f088b811bf6 in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x21bf6)
     #2 0x55b90b8c0ed9 in _start (/home/local/CORVIL/rrowniak/tmp/sanitizer/test+0xed9)
 0x55b90bac2388 is located 0 bytes to the right of global variable 'array' defined in 'test.cpp:3:5' (0x55b90bac2380) of size 8
 0x55b90bac2388 is located 56 bytes to the left of global variable 'table' defined in 'test.cpp:4:5' (0x55b90bac23c0) of size 8
 SUMMARY: AddressSanitizer: global-buffer-overflow /home/local/CORVIL/rrowniak/tmp/sanitizer/test.cpp:8 in main
 Shadow bytes around the buggy address:
   0x0ab7a1750420: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
   0x0ab7a1750430: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
   0x0ab7a1750440: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
   0x0ab7a1750450: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
   0x0ab7a1750460: 00 00 00 00 00 00 00 00 01 f9 f9 f9 f9 f9 f9 f9
 =>0x0ab7a1750470: 00[f9]f9 f9 f9 f9 f9 f9 00 f9 f9 f9 f9 f9 f9 f9
   0x0ab7a1750480: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
   0x0ab7a1750490: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
   0x0ab7a17504a0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
   0x0ab7a17504b0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
   0x0ab7a17504c0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
 Shadow byte legend (one shadow byte represents 8 application bytes):
   Addressable:           00
   Partially addressable: 01 02 03 04 05 06 07 
   Heap left redzone:       fa
   Freed heap region:       fd
   Stack left redzone:      f1
   Stack mid redzone:       f2
   Stack right redzone:     f3
   Stack after return:      f5
   Stack use after scope:   f8
   Global redzone:          f9
   Global init order:       f6
   Poisoned by user:        f7
   Container overflow:      fc
   Array cookie:            ac
   Intra object redzone:    bb
   ASan internal:           fe
   Left alloca redzone:     ca
   Right alloca redzone:    cb
 ==26315==ABORTING
```
```

At first glance the output looks a bit scary. But there is everything that you need to solve the puzzle. Especially that comment: „*AddressSanitizer: **global-buffer-overflow on address** (…) **WRITE of size 4** in main /home/**test.cpp:8** (…)*” – that’s all what you really need.

That’s it, see you next time 🙂