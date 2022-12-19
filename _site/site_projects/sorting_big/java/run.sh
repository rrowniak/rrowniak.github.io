#!/bin/bash

VM_OPTS=""
VM_OPTS="${VM_OPTS} -Xmx15g -Xms15g"
VM_OPTS="${VM_OPTS} -XX:+UseConcMarkSweepGC"
#VM_OPTS="${VM_OPTS} -XX:+UseG1GC"
VM_OPTS="${VM_OPTS} -XX:NewSize=5g"
#VM_OPTS="${VM_OPTS} -XX:+PrintGCDetails -XX:+PrintGCTimeStamps"

SCRIPT_DIR="$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"
shift
java ${VM_OPTS} -cp $SCRIPT_DIR/target/classes Main "$@"
