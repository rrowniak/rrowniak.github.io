#!/bin/bash

VM_OPTS=""
VM_OPTS="${VM_OPTS} -Xmx50g -Xms50g"
VM_OPTS="${VM_OPTS} -XX:+UseConcMarkSweepGC"
#VM_OPTS="${VM_OPTS} -XX:+UseG1GC"
VM_OPTS="${VM_OPTS} -XX:NewSize=5g"
#VM_OPTS="${VM_OPTS} -XX:+PrintGCDetails -XX:+PrintGCTimeStamps"

java ${VM_OPTS} -cp target/classes Main
