---
id: 7
title: 'Ethereal stuff &#8211; volatile'
date: '2018-02-03T11:27:25+00:00'
author: 'Rafał Równiak'
layout: post
guid: 'http://rrowniak.com/?p=7'
permalink: /programming/ethereal-stuff-volatile/
categories:
    - C
    - C++
    - English
    - Java
    - Performance
    - Programming
tags:
    - C
    - Java
    - Performance
    - Python
---

In this article I’m going to share some details about the `volatile` keyword available in a number of programming languages like C++, C, Java. During my professional career, I have found out that the `volatile` type qualifier is frequently misunderstood and, what is even worse, incorrectly used (leading to nasty bugs).

I’ll show the differences between C/C++ and Java languages and present some examples. However, this is not a definitive guide. The main purpose of this article is to give some overview and highlight potential problems.

The `volatile` keyword differs from language to language, thus we can’t just write one definition for all. Fortunately, the `volatile` type identifier serves the same purpose in C and C++ (albeit C++ slightly extends the definition).

## C++ and C

#### A bit of theory

A common answer to a question „what’s volatile” is „well, it prevents a compiler from aggressive optimizations…”. But what are these optimizations? Is there anything else we should know about? Can we leverage these properties in multi-threaded code?

According to [cppreference.com](http://en.cppreference.com/w/cpp/language/cv): *Every access (read or write operation, member function call, etc.) on the volatile object is treated as a visible side-effect for the purposes of optimization (that is, within a single thread of execution, volatile accesses cannot be optimized out or reordered with another visible side effect that is sequenced-before or sequenced-after the volatile access. This makes volatile objects suitable for communication with a signal handler, but not with another thread of execution, see std::memory\_order).*

In order to understand the above definition we need to know what happens when we’re reading or writing an object. Unfortunately, it may be quite complex depending on underlying hardware, but the idea simply boils down to one rule – a processor (or micro-controller) doesn’t operate directly on variables located in RAM. It works on registers instead. So every operation on a given variable requires „transfer” corresponding value from RAM to a certain register (load) and then, after the operation completion, update that variable, that is, „transfer” in reverse direction (store). However, accessing RAM memory could be very expensive, sometimes far more than 100 cycles.

To overcome that problem, engineers and architects have invented a lot of optimizations and tricks like memory multi-level caching (L1, L2, L3), caching values in registers, reordering computations. Also other optimizations can be applied like eliminating useless and redundant computations and many more.

Sometimes we don’t want compilers to optimize access to a given variable. For example, the following code snippet:

```
<pre class="brush: cpp; title: ; notranslate" title="">
i = 0;
i = 1;
i = 2;
```

could be optimized by C/C++ compiler in a way that it would be equivalent to:

```
<pre class="brush: cpp; title: ; notranslate" title="">
i = 2;
```

which is quite reasonable because previous assignments have no effects. But not always. For example, variable `i` could be a hardware register and the underlying hardware expects a certain sequence of changes. After optimizations, we won’t be even informed that our sequence of value changes doesn’t exist at all.

Let’s see practical implications.

#### Example – 8 bit micro-controller

The following code for an embedded device written in C was compiled by avr-gcc.

The program is simple (and pretty useless, but it was created for the purpose of this article) – changes `PORTA` output when a hardware interrupt happens (caused by an external event).

```
<pre class="brush: cpp; highlight: [1,4]; title: ; notranslate" title="">
unsigned char int_flag = 0;
ISR(INT0_vect) // interrupt handler
{
int_flag = 1;
}

int main(void)
{
unsigned char led_status = 0;
configure();

while (1) {
if (int_flag) {
led_status = !led_status;
PORTA = led_status;
int_flag = 0;
}
}
}
```

And it works as expected until we set the optimization level to C3…

Raising optimization level brings some problems – interrupts don’t make any changes to `PORTA` as if the while loop was not evaluated at all. We need to go deeper to find out what’s going on. Here is generated assembly of the main part:

```
<pre class="brush: plain; highlight: [5]; title: ; notranslate" title="">
LDS R24,0x0060 ; Load int_flag to R24
TST R24        ; Test for Zero or Minus
BREQ PC+0x05   ; Branch if equal
LDI R24,0x01   ; Load immediate
OUT 0x1B,R24   ; Out to I/O location (PORTA = 1)
STS 0x0060,R1  ; Store direct to data space
RJMP PC-0x0000 ; Relative jump
CLI            ; Global Interrupt Disable
RJMP PC-0x0000 ;Relative jump
```

And indeed, it looks like there is no while loop! That’s because the compiler deduced that `int_flag` variable is modified only once inside the while loop and, after that modification, the if statement will always be evaluated to false. So the while loop is not necessary here.

Most of the code was optimized out, the compiler decided that the equivalent implementation would be:

```
<pre class="brush: cpp; title: ; notranslate" title="">
if (int_flag) {
PORTA = 1;
int_flag = 0;
} 
```

Definitely the result is not what we have expected. Why that optimization has been applied here? Are data loading operations (`LDS`, `STS`) so expensive? No, they are not very expensive (at least in this particular case – takes two cycles). But remember that this code can be deployed on very small micro-controllers (e.g. ATtiny2313) having 128 bytes RAM (or even less) and 2kB flash thus aggressive optimizations against program space and used resources are highly desired here. In this particular case the compiler removed unnecessary instructions.

Let’s fix it by adding the `volatile` identifier to `int_flag` variable:

```
<pre class="brush: cpp; title: ; notranslate" title=""> volatile unsigned char int_flag = 0; 
```

Here is generated assembly:

```
<pre class="brush: plain; highlight: [3,8]; title: ; notranslate" title="">
LDI R25,0x00     ; Load immediate
LDI R18,0x01     ; Load immediate
LDS R24,0x0060   ; Load int_flag to R24
TST R24          ; Test for Zero or Minus
BREQ PC-0x03     ; Branch if equal
EOR R25,R18      ; Exclusive OR
OUT 0x1B,R25     ; Out to I/O location
STS 0x0060,R1    ; Store R1 to int_flag
RJMP PC-0x0008   ; Relative jump
CLI              ; Global Interrupt Disable
RJMP PC-0x0000   ; Relative jump
```

Everything looks fine and works as expected. Now the compiler assumes that `int_flag` might be modified out of the compiler’s knowledge at any time, so **every access to that volatile variable have to be expressed in generated code**.  
Using volatiles in embedded programming is a common practice because there are plenty of memory mapped registers and dealing with interrupts is normal.

#### volatile and multi-threading

Can we take advantage of `volatile` in multi-threading programming? No. It wasn’t designed for it. At first glance it seems like a good choice because every time a variable is accessed the read/write actually happen. But that’s not enough, not all guarantees are preserved: lack of atomicity and reordering.

Lack of atomicity. There is no guarantee that write or read operations will be atomic. The consequences can be deplorable; you may get weird values – consider a situation where not all bytes have been written yet to a variable (write is not a single instruction) and simultaneously a read operation gets started…

Reordering. The only guarantee is that only `volatile` reads/writes won’t be reordered by compilers. However, an underlying hardware (where weak memory consistency model is implemented) may still reorder these instructions. See [Dekker’s algorithm](https://en.wikipedia.org/?title=Dekker%27s_algorithm) and related [troubles](http://jakob.engbloms.se/archives/65) on multi-core machines. Moreover, access to `volatile`s and non-`volatile`s can be reordered by compilers and/or hardware as well. In order to prevent from reordering memory barriers needs to be used. This is a hardware instruction, but compilers are also aware of that as they are also supposed to stop reordering.

The above explanation about reordering might sound odd, but it could be seen in the following example:

```
<pre class="brush: cpp; title: ; notranslate" title="">
volatile bool ready = false;
int message;

void foo(int i)
{
message = 53 * i;
ready = true;
} 
```

The code is quite easy: write a message and then let another thread get that message. However, there is no guarantee that the `ready` flag will be updated after the `message` is set which is quite important. We don’t want the message being read while the update is in progress.  
I’ve compiled this code by gcc 5.4.1 with `-O2` and here is the result:

```
<pre class="brush: plain; title: ; notranslate" title="">
_Z3fooi:
imull $53, %edi, %edi
movb $1, ready(%rip)
movl %edi, message(%rip)
ret
```

`ready` flag is set to `true` *before* `message` is modified. A reordering happens. But when optimizations are turned off we don’t experience the reordering. That can be very deceptive because the code would work as expected until we decide to turn some optimizations on, usually when we’re trying to solve performance problems reported by a client…

Note that some compilers (e.g. Visual C++) may provide reordering guarantees for volatiles anyway but if you want to write portable code you should not rely on that.

What about very popular „pattern”:

```
<pre class="brush: cpp; highlight: [1]; title: ; notranslate" title="">
volatile bool running = true;

void stop() {
// called from main thread
running = false;
}

void worker() {
// called from another thread
while (running) {
// do something
}
}
```

That code would work in most of the cases and many developers use this technique with success. But there are some subtleties.

First of all, there are better suited tools like atomic types which should be leveraged here.

A second problem is that the above example may suggest that changing `bool` to `int` and adding some innocently looking operations like incrementing (`running++`) is still thread safe. It is not.

Another problem is that this code may not work as expected, at least in theory. Imagine a multi-core processor where the main and worker threads are being executed on separate physical cores. Each core might have its own cache. Writing and reading a volatile object doesn’t imply memory barrier, that is, caches may not be synchronized so each core may have a different view of the same variable. Therefore, our worker might not be stopped for some time. In practice, it is highly unlikely that a memory barrier won’t be executed for a long time.

In case of multi-threading programming, we have alternatives which should be used instead of `volatile`s. In C++ use aforementioned atomic types defined in atomic header e.g:

```
<pre class="brush: cpp; title: ; notranslate" title="">
#include &amp;lt;atomic&amp;gt;
// ...
std::atomic_bool running{true};
```

C (in this particular case C11) also comes with similar types:

```
<pre class="brush: cpp; title: ; notranslate" title="">
#include &amp;lt;atomic.h&amp;gt;
// ...
atomic_bool running = ATOMIC_VAR_INIT(1);
```

#### Conclusion

Very popular (and really needed) in embedded programming (interrupt/signal handling, dealing with memory mapped IO registers).

Using volatiles turns off some optimizations – code can be significantly slower.

Not relevant in multi-threading programming (makes an illusion of thread safe code but potentially hazardous).

## Java

The situation in Java (&gt;=5) is a bit simpler. `volatile` has got a different definition which is easier to understand and narrows the possibility of making errors.

In contrast to C and C++, Java’s `volatile` type identifier is intended to be used in multi-threading programming. However, there are still some limitations.

Atomic writes to volatile variables are guaranteed. Also memory barriers are applied. But these features may not be strong enough to make `volatile` a replacement for `synchronized` section, e.g. incrementing a volatile integer is not thread safe. Incrementing looks like a simple instruction, but in fact, this is a sequence of read-modify-write operations which are not guaranteed to be performed as a transaction. So simultaneous attempts to increment the variable from different threads may interfere yielding unpredictable results. A full synchronization is needed here.

Some call the `volatile` a weak form of synchronization. Although `volatile` in Java is not widely recommended, it is often used when dealing with interruptions, or used as status flags.

One of the common usage is as follows:

```
<pre class="brush: java; title: ; notranslate" title="">
volatile boolean running = true;

public void stop() { running = false; }
public void doWork() {
while (running) {
// do some stuff
}
}
```

## Summary

Although `volatile` in C and C++ is not the same as `volatile` in Java there is one common advice – use volatile if you fully understand how it works. If you are not certain about the details and consequences consider using stronger tools like `synchronized` sections in Java.

I hope that this article gives you some overview and warns about potential problems. However, this is not a definitive guide, some aspects were simplified. If you want to get „expert level” you need to go deeper and find more accurate documentation.