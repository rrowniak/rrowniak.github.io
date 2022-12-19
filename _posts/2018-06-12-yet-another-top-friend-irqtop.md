---
id: 280
title: 'Yet another top-friend: irqtop'
date: '2018-06-12T06:07:45+00:00'
author: 'Rafał Równiak'
layout: post
guid: 'http://rrowniak.com/?p=280'
permalink: /performance/yet-another-top-friend-irqtop/
image: /wp-content/uploads/2018/05/metal-eye.jpg
categories:
    - English
    - Linux
    - Performance
tags:
    - Python
---

Some time ago I wrote an article about [top-tools](http://rrowniak.com/en/linux-en/linux-top-tools-performance-measurements/). Today I’d like to add another one to the list, that is, *irqtop* which is very useful for performance measurements and investigations. I may be biased a little bit because I have contributed to that project but the tool has given me help in many cases so I have no doubt about its value. Let me show you what’s that.

### Description

*irqtop* is a simple tool; presents statistics in realtime about interrupts which are processed by your Linux. You can download *irqtop* from [my github](https://github.com/rrowniak/IrqTop.git) repository. Let’s see *irqtop* in action:

`$ ./irqtop.py`

[![](https://i0.wp.com/rrowniak.com/wp-content/uploads/2018/05/irqtop1.jpg?resize=696%2C427)](https://i0.wp.com/rrowniak.com/wp-content/uploads/2018/05/irqtop1.jpg)

It’s simple, first column shows interrupt numbers, then we can see irqs/s per CPU core, then summary and last column contains device names. Self explanatory.

### Non interactive mode

Except standard mode (realtime) which is common for every top-like tool, there is a possibility to run this tool in non-interactive mode. This is a very useful option as it allows to combine *irqtop* together with some automation like bash scripting or any other monitoring tool. For example, you may be interested in one particular period happening randomly and you don’t want to spend a few days staring at the screen. The easiest way is to leverage *-b* and *-n* options:

`$ ./irqtop.py -b -n 1`

*irqtop* will wait one second to gather all data and print them to the standard output, *-n 1* means do it only once. Simple as that. It’s up to you how those data will be processed. You can use grep-like tools to select data of interest or, for example, you may want to log it to a disk file:

`$ while true; do date >> log1.log; ./irqtop.py -b -n 1 >> irq_out.log;test $? -gt 0 && break; done`

…and easily Ctrl-C when necessary. That’s it:)