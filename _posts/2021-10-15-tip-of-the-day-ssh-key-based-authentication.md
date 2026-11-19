---
redirect_from: /linux/tip-of-the-day-ssh-key-based-authentication/
id: 845
title: 'Tip of the day: SSH Key-Based Authentication'
date: '2021-10-15T08:32:14+00:00'
author: 'Rafał Równiak'
layout: post
guid: '/?p=845'
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
$ ssh-keygen
```

Then, install a public key on your server:

```
ssh-copy-id username@remote_host
```

If that for some reason does not work, use more manual approach:

```
$ cat ~/.ssh/id_rsa.pub | ssh username@remote_host "mkdir -p ~/.ssh && cat >> ~/.ssh/authorized_keys"
```

You’ll find more details [here](https://www.digitalocean.com/community/tutorials/how-to-configure-ssh-key-based-authentication-on-a-linux-server).
