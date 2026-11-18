---
id: 865
title: 'Bash cheat-sheet'
date: '2022-01-06T11:13:41+00:00'
author: 'Rafał Równiak'
layout: post
guid: '/?p=865'
permalink: /dobre-praktyki/bash-cheat-sheet/
categories:
    - 'Dobre praktyki'
    - Linux
tags:
    - Bash
    - Linux
---
If you are not a daily bash scripter, you may forget how to do certain operations. This cheat-sheet contains the most common tasks that you may want to do.

### Check if given commands exists

```
$ command -v curl > /dev/null || echo "Curl not installed"
```
### Common string tests

```
# empty string?
[[ -z STRING ]]

# non empty string?
[[ -n STRING ]]

# strings are equal?
[[ STRING == STRING ]]

# strings aren't equal?
[[ STRING != STRING ]]
```
### Common file tests

```
# exists?
[[ -e FILE ]]

# directory?
[[ -d FILE ]]

# file?
[[ -f FILE ]]

# executable?
[[ -x FILE ]]
```
### Test if environment variable is set

```
[[ -z "${DEPLOY_ENV}" ]]

# example
[ -z "${HOST}" ] && HOST=localhost
```
### Range loops

```
# C-like (undefined in sh)
for ((i = 0 ; i < 100 ; i++)); do
  echo $i
done

# standard
for i in $(seq 1 100); do
    echo "Welcome $i"
done
```
### Conditional execution

```
$ git commit && git push
$ git commit || echo "Commit failed"
```
### Test if command succeeded/failed

```
if some_command; then
    echo command returned true
else
    echo command returned some error
fi

if ! some_command; then
    echo command returned some error
else
    echo command returned true
fi
```
### Directory of the script

```
SCRIPT_DIR=$(dirname "$0")
```
## Resources

- https://devhints.io/bash
