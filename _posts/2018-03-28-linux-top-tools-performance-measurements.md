---
redirect_from: /performance/linux-top-tools-performance-measurements/
id: 231
title: 'Linux top-tools: performance measurements'
date: '2018-03-28T16:51:52+00:00'
author: 'Rafał Równiak'
layout: post
guid: '/?p=231'
categories:
    - English
    - Linux
    - Performance
tags:
    - atop
    - devops
    - htop
    - iftop
    - iotop
    - Linux
    - 'perf top'
    - Performance
    - powertop
    - top
---
This article presents a short list of very useful tools which are used for getting some information about what’s going on in our Linux system. These tools show some of the system’s resources utilization and saturation. Top-tools share one common property, that is, give a snapshot of certain properties in real time. Also they work in command line mode so there is no need to have a graphics user interface, perfect for servers. Let’s see what we can get and measure.

## top

This is the most popular tool and probably it has come with your favorite Linux distribution. It gives some information about running processes like CPU saturation, memory consumption and bunch of other useful statistics. Type *top* and enter:

`$ top`

The result should be similar to the following print screen:

Some tips and tricks:

- press **c** to display command line
- press **V** to show relations between running processes
- press **H** to show all threads (only tasks are displayed by default)

Read the manual for more tricks.

## htop

*htop* is a kind of alternative to *top*. It gives you similar information about running processes but in a less spartan way. It’s also a bit more extensive and gives more options. You may need to install that tool. On Ubuntu it’s pretty straightforward:

`$ sudo apt install htop`

And type:

`$ sudo htop`

Notice *sudo* – it might be needed for getting some additional information from the kernel.

You should see something like that:

There are a few interesting features:

- select a process of interest and press **s** – you will see a list of system calls made by the process
- select a process of interest and press **l** – you will see a list of files opened by the process (equivalent to lsof command)
- **M** – sort by memory usage
- **P** – sort by CPU usage
- **p** – show/hide command line
- **F5** – tree view (relations between processes)
- **F2** – setup, a lot of useful options. I’d really recommend going there as this is really a user friendly list of beneficial features

## atop

Yet another tool for monitoring Linux system and corresponding processes. It gives a little bit more information if we compare it to *top*. For example, in addition to CPU and memory consumption we can monitor network traffic, io usage and many other things which are important from a performance point of view. You may need to install it, on Ubuntu it’s a piece of cake:

`$ sudo apt install atop`

And run it (notice *sudo* – it might be needed for getting some additional information from the kernel):

`$ sudo atop`

The output:

Things to remember:

- press **g** to switch to generic view
- press **m** to see detailed statistics related to memory
- press **d** to see disk-related output
- press **n** to get some network related statistics (however, you may need to apply some patches to the kernel)
- press **s** to see a lot of statistics related to process scheduling, may be important when you’re dealing with heavy loaded multi-threading application

*atop* has another useful feature, it can store all statistics in a compressed binary files allowing long-run analysis.

## iotop

A tool for monitoring I/O operations like disk read/write. It might not be installed by default. On Ubuntu just type:

`$ sudo apt install iotop`

And run it (notice *sudo* – it might be needed for getting some additional information from the kernel):

`$ sudo iotop`

The output:

This is quite simple tool so there is no many useful shortcuts.

## powertop

This is a power management diagnosis tool. It gives a lot of information about power consumption and allows some experiments with various power management settings. It may not be installed, on Ubuntu:

`$ sudo apt install powertop`

And run it (notice *sudo* – it might be needed for getting some additional information from the kernel):

`$ sudo powertop`

The output:  
The tool is fully interactive so you have to use menu. There are also some command line options to perform auto-tuning of your current power-related settings. But it hangs my computer so I have nothing interesting to say about that. Nevertheless, you can find many useful statistics like CPU [C-states](http://www.hardwaresecrets.com/everything-you-need-to-know-about-the-cpu-c-states-power-saving-modes/) (Idle stats), current CPU frequencies per core, power consumption by each device.

## iftop

This tool is used for getting networking stats and it’s focused on network traffic analysis and corresponding flow. It may not be installed, on Ubuntu:

`$ sudo apt install iftop`

And run it (notice *sudo* – it might be needed for getting some additional information from the kernel):

`$ sudo iftop`

The output:

Useful options:

- when running *iftop* you need to specify an interface you’d like to monitor e.g. *sudo iftop -i wlp3s0*
- press **n** to turn on/off DNS resolutions
- press **S** to show source ports
- press **D** to show destination ports
- press **f** to specify filter, some examples: `port https and not host golem.canonical.com `, `not port domain`

## perf top

This is a really powerful and complex tool. It’s impossible to cover even basic functionalities and provide some guidance in that short post. I’ll just give a high level overview and brief description.

*perf top* is an advanced performance profiling tool which gives the output in realtime. It a member of a family *perf* tools. By default *perf top* shows the functions where most of the time is spend on. It monitors the usage on user level and kernel level as well.

Installing perf top on Ubuntu can be a little bit tricky:

`sudo apt install linux-tools-common linux-tools-generic linux-tools-`uname -r``

Let’s see how it looks:

This is a good candidate for series of posts so I won’t go further here.

Do you know other top-like tools worth describing? Let us know 🙂
