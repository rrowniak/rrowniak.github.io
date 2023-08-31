---
id: 13
title: 'Behind the scenes: Bitcoin'
date: '2018-02-09T17:55:59+00:00'
author: 'Rafał Równiak'
layout: post
guid: 'http://rrowniak.com/?p=13'
permalink: /bitcoin/investigating-cryptocurrences/
image: /wp-content/uploads/2018/02/chad-kirchoff-small-unsplash.jpg
categories:
    - 'Architektura oprogramowania'
    - Bitcoin
    - English
tags:
    - Bitcoin
    - blockchain
    - 'bloom filter'
    - 'byzantine generals'
    - Cryptocurrency
    - Cryptography
    - 'digital signature'
    - 'distributed system'
    - 'double spending'
    - IT
    - 'merkle tree'
    - peer-to-peer
    - security
    - sha256
---

Cryptocurrencies are really hot and attract attention of the broader public. But a few of us really know what sits behind the curtain. Today I’m going to give you a short overview of the technological side of Bitcoin. However, I’m not going to focus on economics or social impact of cryptocurrencies.

The whole concept is build on the top of several interesting technologies, some of them are innovative, some of them are well know for decades. This article contains a list of some technologies which are leveraged in the majority of current cryptocurrencies. However, this is not a deep study and you won’t find here much details, only a sort of guidance and reference to corresponding documentation.

Although the future cryptocurrencies in a shape as we can see today might not be so bright, I’m pretty sure that used technologies will be more and more important in the future. Especially blockchain is something you should be familiar with.

Let’s start talking about Bitcoin technologies.

### Cryptography

There is no surprise that the cryptography plays a major role in cryptocurrency technology. Let’s see what we may come across.

#### Hashing functions

Hashing functions are the foundation of cryptocurrencies, especially [SHA-256](http://en.wikipedia.org/wiki/SHA-2), double-SHA256, [RIPEMD-160](http://en.wikipedia.org/wiki/RIPEMD). It’s really interesting how many use cases are covered by these innocently looking functions.

#### Public-key cryptography

Ironically, you won’t find many cases of public-key encryption in cryptocurrencies. However, Bitcoin takes advantage of many concepts taken from [asymmetrical cryptography](https://en.wikipedia.org/wiki/Public-key_cryptography) like public and private key pairs, digital signatures.

#### Signatures

One of the most fundamental ideas standing behind the cryptocurrencies. Every transaction request is [signed](https://en.wikipedia.org/wiki/Digital_signature), your wallet is a kind of priv/pub keys holder, even your unique address derives from your public key (to be precise – this is a series of hashes taken from a public key).

### Security

[Security](http://bitcoinsecurity101.com/getting-started/) is the biggest challenge in the word of cryptocurrencies. Bitcoin as a first cryptocurrency project came out with a design which we could label as a distributed digital secure currency. The interesting thing is how to build a secure and trustworthy system on the top of network consisting of untrusted parts.

### Distributed systems

Whole concept is decentralized and distributed by definition. There is no single point of trust, no single point of failure, no „master” node. It’s a [Peer-to-Peer](https://en.wikipedia.org/wiki/Peer-to-peer) network, almost each machine can be full featured part of the network (though for some activities like mining you need a really powerful machine, or farm of machines). That freedom raises many problems as everyone can be part of the network, the software does not have to be the canonical one as long as it talks the same language (underlying protocol). For example, there may be a dishonest node which tries to deceive the rest. In other words, trust no one…

#### <span class="st">Byzantine Generals Problem</span>

[The problem](https://en.wikipedia.org/wiki/Byzantine_fault_tolerance) is defined as follows: you are on war and have N generals who can contact each other through messengers. You know that some of the generals may be traitors (but no more than N / 2) and the messengers are unreliable (may be killed or just abandon the war field). The goal is to agree on the war strategy. To make things worse, the traitors will try to sabotage the agreement. How to reach a consensus about the strategy in a such unreliable environment?

#### Double spending problem

It’s simple – [using the same money twice](https://en.wikipedia.org/wiki/Double-spending) should be forbidden. Otherwise the system does not make any sense. There is no compromise here, even if there is so little possibility for double spending money – that’s a show stopper.

### P2P networks

The [P2P](https://en.wikipedia.org/wiki/Peer-to-peer) network topology is nothing new, just recall Napster or Bittorrent to name a few. Surprisingly, P2P associated with piracy and other bad stuff can be a foundation for something considered secure and reliable.

### Others

#### Reverse Polish notation

There is a transaction scripting language which gives some level of flexibility, that is, you can create many kind of transactions involving more than two actors or adding some time constraints. The language stack is based on [reverse Polish notation](https://en.wikipedia.org/wiki/Reverse_Polish_notation), pretty rare choice nowadays.

#### Bloom filter

How to ask another peer in the network for information without revealing which data are you interested in? If that sounds impossible you should have a look at [bloom filter](https://en.wikipedia.org/wiki/Bloom_filter) algorithm, it’s leveraged in Bitcoin to increase privacy.

### Blockchain

[Blockchain](https://en.wikipedia.org/wiki/Blockchain) is the essence of the cryptocurrency technology. It gained huge attention and many engineers are currently thinking on how to leverage that idea out of the cryptocurrency world. There are some important candidates like decentralized DNS, prove of existence services, digital art registry, decentralized lotteries having no company behind, digital IDs, and many more. You may argue whether these projects have the future but one thing seems to be inevitable – the blockchain technology (or its derivatives, or the pure idea) will be important in the future. So that is a *must have* in your toolbox.

#### <span class="mw-headline" id="Merkle_Trees">Merkle Trees</span>

Suppose you have a thousands transactions in a block. How to check in a fast way whether a given transaction is signed? [Merkle trees](https://en.wikipedia.org/wiki/Merkle_tree) come with help.

## Conclusions

Cryptocurrency technology is a good piece of IT engineering, something you should be at least familiar with. I just provided some hints about technologies and basic sources of more detailed information. If you want to dive into the cryptocurrency world I’d recommend you to get familiar with the following documents:

- [Bitcoin: A Peer-to-Peer Electronic Cash System](https://bitcoin.org/bitcoin.pdf): original paper by Bitcoin’s creator Satoshi Nakamoto
- [Developer documentation](https://bitcoin.org/en/developer-documentation): a lot of useful information about the details
- [Mastering Bitcoin by Andreas M. Antonopoulos](https://bitcoinbook.info/), one of the best book about technical side of Bitcoin! You can review the book for free [here](https://github.com/bitcoinbook/bitcoinbook).