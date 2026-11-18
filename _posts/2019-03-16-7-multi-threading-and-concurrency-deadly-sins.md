---
id: 15
title: '7 multi-threading and concurrency deadly sins'
date: '2019-03-16T19:29:49+00:00'
author: 'Rafał Równiak'
layout: post
guid: 'http://rrowniak.com/?p=15'
permalink: /it-pl/7-multi-threading-and-concurrency-deadly-sins/
image: /wp-content/uploads/2018/07/close-up-colors-design-small.jpg
categories:
    - 'Architektura oprogramowania'
    - 'Dobre praktyki'
    - IT
    - Performance
tags:
    - 'best practices'
    - multithreading
    - programming
---

Let’s see what kind of pitfalls are common in multi-threading &amp; concurrency world. This kind of code is simply hard to write and even harder to maintain. I’m going to share what can go wrong and how to avoid many traps.

## \# 7 Home cooking lock-free and wait-free data structures

Do not develop your own [lock-free](https://en.wikipedia.org/wiki/Non-blocking_algorithm) or wait-free data structures intended to be used on production unless you are expert in this field. There are several reasons behind that advice. First of all, it’s really hard to develop lock-free/wait-free data structures that are **error-free**. Even harder if those are supposed to be cross-platform. If you have a good reason to use such structures take a look at e.g. [Boost.Lockfree](http://www.boost.org/doc/libs/1_63_0/doc/html/lockfree.html).

Another problem with those structures is a common belief that they will always be faster by an order of magnitude than corresponding „classic” structures. That does not have to be the truth, moreover, in some extreme cases it could be quite the opposite.

## \# 6 Calling unknown code

Do not call unknown code from [a critical section](https://en.wikipedia.org/wiki/Critical_section). Doing so is a simple recipe to [deadlocks](https://en.wikipedia.org/wiki/Deadlock) and [race conditions](https://en.wikipedia.org/wiki/Race_condition). Unknown code may call back your code, may use the same synchronization primitives, may share data with another threads. And who knows what else.

If you really have to do so, make unknown code a known code. However, later on I’ll provide some rationale on why this idea (calling any code inside a critical section) is still totally wrong.

## \# 5 Copy&amp;paste methodology

Do not blindly copy-paste code snippets found in [the Internet](https://stackoverflow.com/). This advice applies not only to multi-threading though it is especially important here.

Code snippets found elsewhere may be correct and well prepared but this is not a guarantee for the success in your code. You need to be aware of the runtime context, the underlying hardware and specific assumptions. This is especially true if the finding is a heavily optimized piece of code, sometimes with assembly. It is almost always platform specific solution which may not work for you.

What’s the advice here? It’s as simple as that – first understand the code then apply it.

## \# 4 Golden hammer for performance

Concurrent code not always means „faster”. But it’s always more complex and error prone. Also a linear scalability is usually not the case.

If you decide to go into mutli-threading <del>heaven</del>hell you’d better have a good reason to do so. This is a complex piece of engineering with many obstacles, traps and hidden difficulties which might yield with the performance below the expectations. I’ll list a few of them to give you some idea what I’m talking about: [context switching](https://en.wikipedia.org/wiki/Context_switch), [false sharing](https://en.wikipedia.org/wiki/False_sharing), [memory synchronization](https://en.wikipedia.org/wiki/Consistency_model), [system calls](https://en.wikipedia.org/wiki/System_call), [live locks](https://en.wikipedia.org/wiki/Deadlock#Livelock), [starvation](https://en.wikipedia.org/wiki/Starvation_(computer_science)), [priority inversion](https://en.wikipedia.org/wiki/Priority_inversion), [CPU contention](https://en.wikipedia.org/wiki/Resource_contention), [CPU stalling](https://en.wikipedia.org/wiki/Pipeline_stall). Do you know all of them? This is only a top of the iceberg. Nothing but deep understanding of the matter is your friend. You should know how the things work under the hood and what are the consequences of using particular tools. *Naive* thinking simple does not work here. For example, have a look at my [article](http://rrowniak.com/en/programming/ethereal-stuff-volatile/) about *volatiles* – it seems to be a simple and well suited tool for multi-threading but it’s not.

## \# 3 Concurrency poker

Do not play with the probability, if something is unlikely but possible – it’ll happen, usually at least expected moment. If you are mathematician (hopefully not) like me you already know that – [Borel–Cantelli lemma](https://en.wikipedia.org/wiki/Borel%E2%80%93Cantelli_lemma). If your concurrency code has at least one possibility to go wrong, even very unlikely, you will be notified by a client/support guy that your system has suddenly broken down or even crashed randomly. We call such situation *race condition*. A race condition doesn’t have to be harmful but in many cases it is.

If you are aware of introducing a race condition – simply do not do that. And this advice is like any other of this kind – trivial to state, difficult to apply. People very often don’t realize that they’re introducing a race condition. What I’d advice here? There is no a single trick which makes you immortal. But you can follow a few rules like:

- Make any synchronization explicit and readable
- Avoid any „*clever*” tricks (people think they’re more clever than they really are)
- Use immutable and const data as much as possible (no modifications no problems)
- Minimize a scope of any critical section and hold locks as little time as necessary
- Avoid any micro-optimizations
- All the others described in this article

## \# 2 Using global synchronization primitives

Using a global lock (e.g. mutex) is almost always asking for troubles. Sometimes that design comes from the situation where the code not designed to be multi-thread safe is being quickly transformed to concurrency word. By quickly I mean „as fast as possible, no time to think”. The consequences are usually catastrophic. Maintenance becomes a nightmare, deadlocks are on daily basis, random failures don’t surprise, refactoring is almost impossible. Sometimes people responsible for the design can’t forecast the consequence of this pattern.

Advice? Change the code or job.

## \# 1 Protecting code

Is that really a sin? Protecting code against multi-threaded access is a good idea, isn’t it? No, it’s a sin, deadly sin, deadliest one!

**Always protect data instead of code**. Without exceptions. Ever. What does it mean? When you’re writing code and are about to acquire a mutex, ask yourself what data or resource are you going to protect. Dispose of your natural temptation that *some piece of code* needs to be protected. Protecting code makes no sense as the problem is always with accessing data which can be modified at the same time. If any code is not touching your data, it should be moved off the critical section.

This advice seems to be obvious but it’s a bit tricky. It must be tricky because I have seen a massive amount of violations of this law. Interestingly, most of these cases were made by senior engineers! Why is that? I don’t know but I’ve heart quite interesting yet controversial theory explaining that. The theory is saying that some people were born having potential for understanding multi-threading, the others were born with no such potential.

You may assert this advice saying that sometimes there is a need to use certain *not-thread-safe-API* from different threads. Then you have to synchronize a piece of code instead of data. Well, in fact the API is nothing less and nothing more but resource which needs to be protected.

Another *odd* case seems to be when one routine is waiting for some other tasks to be completed. That scenario can be realized using specialized tool called *condition variables*. You may ask what kind of resources we shall protect here? Well, this is a different problem but it’s still not about protecting code. It’s about synchronization (e.g. [happened-before](https://en.wikipedia.org/wiki/Happened-before) relationship) and that’s something different. So multi-threading is not only about protecting resources but also about synchronization.

Despite everything, what if you’d follow [Ovid’s](https://en.wikipedia.org/wiki/Ovid) advice: *I see better things, and approve, but I follow worse*? Let’s see what Ovid kept in silence about protecting the code:

- Larger critical sections
- Hard to reason what is really protected
- Easier to make a mistake (e.g. race condition or deadlock)
- Maintenance nightmare
- Temptation to follow the broken window theory ([my article on that PL](http://rrowniak.com/it-pl/syndrom-wybitej-szyby/), [wiki](https://en.wikipedia.org/wiki/Broken_windows_theory))