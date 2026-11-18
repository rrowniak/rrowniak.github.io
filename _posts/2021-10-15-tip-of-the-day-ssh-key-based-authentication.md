---
id: 845
title: 'Tip of the day: SSH Key-Based Authentication'
date: '2021-10-15T08:32:14+00:00'
author: 'Rafał Równiak'
layout: post
guid: 'http://rrowniak.com/?p=845'
permalink: /linux/tip-of-the-day-ssh-key-based-authentication/
categories:
    - Linux
tags:
    - 'key-based authentication'
    - Linux
    - ssh
---

This type of authentication is considered to be among the most secured ones. You can setup this config in two steps.

First, you need to generate a public/private key pair. Use default location. Be careful to not override existing keys.

```
<pre class="wp-block-code">```
$ ssh-keygen
```
```

Then, install a public key on your server:

```
<pre class="wp-block-code">```
ssh-copy-id username@remote_host
```
```

If that for some reason does not work, use more manual approach:

```
<pre class="wp-block-code">```
$ cat ~/.ssh/id_rsa.pub | ssh username@remote_host "mkdir -p ~/.ssh && cat >> ~/.ssh/authorized_keys"
```
```

You’ll find more details [here](https://www.digitalocean.com/community/tutorials/how-to-configure-ssh-key-based-authentication-on-a-linux-server).