#!/bin/bash

PROCESS_NAME=firefox
SAMPLE_INTERVAL=1

VOL_CTX_SW=0
NON_VOL_CTX_SW=0
print_preemtions() {
    local v=$(cat /proc/${1}/status | grep "^voluntary_ctxt_switches" | awk '{print $2}')
    local cnt=$(expr $v - $VOL_CTX_SW)
    VOL_CTX_SW=$v
    echo "voluntary_ctxt_switches ${cnt}"

    local v=$(cat /proc/${1}/status | grep "^nonvoluntary_ctxt_switches" | awk '{print $2}')
    local cnt=$(expr $v - $NON_VOL_CTX_SW)
    NON_VOL_CTX_SW=$v
    echo "nonvoluntary_ctxt_switches ${cnt}"
}

while true;
do
    PROCESS_ID=$(ps -e -T | grep ${PROCESS_NAME} | awk '{print $1}')
    PROCESS_ID=(${PROCESS_ID})
    PROCESS_ID=${PROCESS_ID[1]}
    re='^[0-9]+$'
    if ! [[ ${PROCESS_ID} =~ ${re} ]]; then
        echo "Process not found... going sleep for 2 seconds" >&2;
        sleep 2
        continue
    fi

    echo "Found process ${PROCESS_NAME}:${PROCESS_ID}. Gathering statistics..."
    while true;
    do
        echo "$(date) Statistics dump from the following second"
        PSTAT="sched:*"
        PSTAT="${PSTAT},cache-references,cache-misses"
        PSTAT="${PSTAT},cycles,instructions,branches,faults,page-faults,cpu-migrations"
        PSTAT="${PSTAT},context-switches"
        PSTAT="${PSTAT},irq:*:k,irq:*:u"
        PSTAT="${PSTAT},raw_syscalls:sys_enter"
        PSTAT="${PSTAT},net:net_dev_xmit"
        sudo perf stat -e "${PSTAT}" -p ${PROCESS_ID} sleep 1
        #sudo perf record -e "${PSTAT}" -p ${PROCESS_ID} sleep 1

        print_preemtions ${PROCESS_ID}

        #exit 0
        if [[ $? -ne 0 ]]; then
            break
        fi
    done
done
