---
id: 818
title: 'Learning awk by examples'
date: '2021-10-14T07:18:01+00:00'
author: 'Rafał Równiak'
layout: post
guid: 'http://rrowniak.com/?p=818'
permalink: /linux/learning-awk-by-examples/
categories:
    - Linux
tags:
    - awk
    - Linux
---

*awk* is a powerful Linux/Unix tool that simplifies your life when it comes to parsing text files/outputs, doing various text manipulation, or, what’s surprising to the newbies, doing certain calculations without using Excel. Let’s get started!

##  

## Example 1 – Change output on the fly

Suppose that you want to get 4 biggest files in */etc/init.d* and display their names together with associated sizes. Let’s start from something like that:

```
<pre class="wp-block-code">```bash
$ ls -l /etc/init.d/ | sort -nrk 5 | head -n4
```
```

The above combination might give you the following output:

```
<pre class="wp-block-code">```bash
$ ls -l /etc/init.d/ | sort -nrk 5 | head -n4
-rwxr-xr-x 1 root root 9138 gru  3  2018 openvpn
-rwxr-xr-x 1 root root 6872 paź 11  2019 udev
-rwxr-xr-x 1 root root 6032 wrz  7  2020 virtualbox
-rwxr-xr-x 1 root root 5574 lis  5  2019 alsa-utils
```
```

Well, we’re not quite there, too many columns. Here comes *awk*:

```
<pre class="wp-block-code">```bash
awk '{ print $5, "bytes:", $9 }'
```
```

Which simply prints column number 5, short text and finally column number 9:

```
<pre class="wp-block-code">```bash
$ ls -l /etc/init.d/ | sort -nrk 5 | head -n4 | awk '{ print $5, "bytes:", $9 }'
9138 bytes: openvpn
6872 bytes: udev
5658 bytes: nfs-common
5574 bytes: alsa-utils
```
```

## Example 2 – parse /proc/cpuinfo and calculate total amount of CPUs and cores

*/proc/cpuinfo* contains a lot of useful information about CPU(s) that are visible by the kernel. This file may be long, a few first lines are shown below:

```
<pre class="wp-block-code">```bash
processor       : 0
vendor_id       : GenuineIntel
cpu family      : 15
model           : 6
model name      : Intel(R) Xeon(R) CPU E5-2650 v4 @ 2.20GHz
stepping        : 1
microcode       : 0x1
cpu MHz         : 2199.996
cache size      : 16384 KB
physical id     : 0
siblings        : 1
core id         : 0
cpu cores       : 1
apicid          : 0
initial apicid  : 0
```
```

But we’re interested only in a short summary – CPUs and cores amount. Simple and a bit hacky awk script that does the job:

```
<pre class="wp-block-code">```bash
awk '
{
    # regex matching, we could alternatively
    # write $1 == "processor"
    if ($1 ~/processor/) {
        stats["processors"]++;
    }

    # tricky part: "cpu cores" is actually interpreted as
    # two columns!
    if ($1 == "cpu" && $2 == "cores") {
        stats["cores"] += $4;
    }
}
END {
    # iterate over associative array and print
    # key-value pairs
    for (s in stats) {
        print s , ":", stats[s];
    }
}
' /proc/cpuinfo
```
```

The output:

```
<pre class="wp-block-code">```bash
processors : 24
cores : 24
```
```

## Example 3: pretty formatting

Sometimes we want a better tool than `print "str1", $1, ...` . Here comes a built-in C-like function `printf`:

```
<pre class="wp-block-code">```bash
awk 'BEGIN {
    PI=3.14159
    printf("%s: int(%.2f) = %d\n", "Int function", PI, int(PI));
}'
```
```

Output:

```
<pre class="wp-block-code">```bash
Int function: int(3.14) = 3
```
```

This example isn’t very practical in this shape but I’m pretty sure that you know what’s going on and how to use that example in real world scenarios.

## Example 4: get rid of Excel! Playing with CSV.

Consider the following CSV file:

```
<pre class="wp-block-code">```bash
"Sell","List","Living","Rooms","Beds","Baths","Age","Acres","Taxes"
142,160,28,10,5,3,60,0.28,3167
175,180,18,8,4,1,12,0.43,4033
129,132,13,6,3,1,41,0.33,1471
138,140,17,7,3,1,22,0.46,3204
232,240,25,8,4,3,5,2.05,3613
135,140,18,7,4,3,9,0.57,3028
150,160,20,8,4,3,18,4.00,3131
```
```

Our task is to calculate the average age (column 7). With *awk* this is easy:

```
<pre class="wp-block-code">```bash
awk 'BEGIN {
    count = 0;
    sum = 0;
    # define custom field separator
    FS=","
}
{
    # skip first line
    if (NR == 1) {
        next;
    }

    # skip empty or invalid lines
    if (NF < 7) {
        next;
    }

    count++;
    sum += $7
}
END {
    printf("Average age: %.1f years\n", sum / count)
}
' example.csv
```
```

Output:

```
<pre class="wp-block-code">```bash
Average age: 23.9 years
```
```

## Example 5: Treat units and prefixes

Let’s try to display all directories and files in the home directory which take &gt;= 1GB of disk space and sum them up. Good starting point would be:

```
<pre class="wp-block-code">```bash
$ du -hd1 ~ | head -n -1
12G     /home/rr/Music
1,5G    /home/rr/.config
46M     /home/rr/Pictures
4,0K    /home/rr/Public
752M    /home/rr/Documents
4,0K    /home/rr/.ssh
793M    /home/rr/STM32Cube
5,2G    /home/rr/.cache
...
```
```

Now we have to pick up those with size &gt;= 1G. Let *awk* do the job:

```
<pre class="wp-block-code">```bash
du -hd1 ~ | head -n -1 | awk '$1 ~ /[0-9]*G/ {
    # get rid of following "G"
    val = substr($1, 0, length($1) - 1)
    
    # replace , with .
    # numbers with . decimal sep will be handled correctly
    # (sub available in gawk and nawk)
    sub(/,/, ".", val)
    
    sum += val
    
    print $1, "\t", $2
}
END {
    out = sum "G"
    sub(/\./, ",", out)
    print "total:", out
}'
```
```

Have you noticed a new syntax: `<strong>$1 ~ /[0-9]*G/</strong> {...}` ? This says „execute code in the brackets only when condition `$1 ~ /[0-9]*G/` is fulfilled. In our case – select a line where first column ends with G.

Results:

```
<pre class="wp-block-code">```bash
12G      /home/rr/Music
1,6G     /home/rr/.config
5,2G     /home/rr/.cache
51G      /home/rr/VirtualBoxVMs
6,8G     /home/rr/Downloads
12G      /home/rr/dev
7,6G     /home/rr/apps
total: 96,2G
```
```

## Built in variables

We’ve been using some of them. More built-in variables below:

`FS `– The Input Field Separator Variable (defaulted to ” „)

`OFS `– The Output Field Separator Variable

`NF `– The Number of Fields Variable

`NR `– The Number of Records Variable (lines)

`RS `– The Record Separator Variable (defaulted to „\\n”)

`ORS `– The Output Record Separator Variable

`FILENAME `– The Current Filename Variable

## Conclusions

This article shows only a few problems that can be solved using *awk*. However, I strongly recommend you to get familiar with this tool by reading a good article that gives you solid understanding. For example, you can have a look at[ this excellent intro](https://www.grymoire.com/Unix/Awk.html) to awk by Bruce Barnett.

I was using standard commands to produce example data. It’s likely that you could figure out how to avoid using awk in these examples! But that’s not the point – the intention is to show awk potential. In real word you will be dealing with various kind of data – then awk should be your primary tool in your toolbox.