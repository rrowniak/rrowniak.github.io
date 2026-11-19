---
layout: page
title: About
permalink: /about/
description: >-
  Rafał Równiak — software architect, security engineer and founder of Underground
  Engineering. More than 20 years of experience across fintech, cybersecurity and
  distributed systems.
---
{%- include rel.html -%}
<link rel="alternate" hreflang="pl" href="{{ '/o-mnie/' | absolute_url }}">
<link rel="alternate" hreflang="en" href="{{ '/about/' | absolute_url }}">

<script type="application/ld+json">
{
  "@context": "https://schema.org",
  "@type": "Person",
  "name": "Rafał Równiak",
  "url": "{{ '/about/' | absolute_url }}",
  "jobTitle": "Software architect and security engineer",
  "worksFor": {
    "@type": "Organization",
    "name": "Underground Engineering",
    "url": "{{ site.url }}/"
  },
  "alumniOf": "AGH University of Krakow, Faculty of Applied Mathematics",
  "knowsAbout": ["Enterprise AI", "Cybersecurity", "Distributed systems", "C++", "Python", "Go"],
  "sameAs": [
    "https://www.linkedin.com/in/{{ site.linkedin_username }}",
    "https://github.com/{{ site.github_username }}"
  ]
}
</script>

I am Rafał Równiak, a software engineer and architect with more than twenty
years in the industry. I studied applied mathematics at AGH University in
Kraków and have since worked as a programmer, team leader, software architect,
project and development manager and freelancer — on start-up projects and on
large enterprise systems alike. Today I work as a Principal Software Engineer
and run [Underground Engineering]({{ rel }}), where I consult and
train on enterprise AI adoption, AI-driven cybersecurity and distributed
architectures.

My primary language is C++, but I work daily with C, Python and Go, and I care
more about the engineering process than about any single language.

## About this site

This site is two things in one place: the home of Underground Engineering and my
engineering blog. On the blog I share knowledge, measurements and the results of
experiments — not only in software engineering but in adjacent technical fields
too. You will find posts about C++, C, Python and Java, as well as electronics,
embedded systems and mechanics. Some posts are in English, some in Polish; if
you would like a particular one translated, just ask.

My projects are on [GitHub](https://github.com/{{ site.github_username }}).

## Other interests

Outside of work I am into electronics — especially measurement equipment and
automotive control systems — and, more recently, into building and riding
electric vehicles. Two of those projects, [Perun]({{ rel }}e-bike-perun/) and
[Aitwar]({{ rel }}e-bike-aitwar/), are documented on this site.

<p class="mt-4"><a href="{{ rel }}o-mnie/" hreflang="pl" lang="pl">Wersja polska</a></p>
