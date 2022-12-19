#!/bin/bash
function fail() {
    echo "$1"
    exit 1
}

[ -x /usr/bin/time ] || fail "There is no non-built in time tool (/usr/bin/time)"

NUM=100000000

function parse_out() {
    echo "$1" | awk -v name="$2" 'BEGIN { b=-1; s=-1; t=-1; m=0; t=0; r=0}
    /Building*/ {
        r = $2
    }
    /Time elapsed*/ {
        if (b == -1) {
            b = $3
            next
        }
        if (s == -1) {
            s = $3
            next
        }
        if (t == -1) {
            t = $3
            next
        }
    }
    $1 == "max_rss" {
        m = $2
        t = $5
    }
    END {
        len = length(r); res=""; 
        for (i = 0; i <= len; i++) {
            res = substr(r, len-i+1, 1) res; 
            if (i > 0 && i < len && i % 3 == 0) { res = "," res } 
        }
        printf("%-20s %13s B: %7.3f s, S: %7.3f s, T: %7.3f s, Total: %7.3f s, Mem: %.1f GB (%d kB)\n",
            name, res, b / 1000, s / 1000, t / 1000, t, m / (1024*1024), m)
    }
'
}

TIME_FORMAT="max_rss %M kB, real: %e secs,"

function c() {
    out=$(/usr/bin/time -f "$TIME_FORMAT" ./c/sort $NUM 2>&1)
    if [ $? -ne 0 ]; then echo "$out"; fail "Can't execute test"; fi
    parse_out "$out" "c optimized"
    out=$(/usr/bin/time -f "$TIME_FORMAT" ./c/sort_debug $NUM 2>&1)
    if [ $? -ne 0 ]; then echo "$out"; fail "Can't execute test"; fi
    parse_out "$out" "c debug"
}

function cpp() {
    out=$(/usr/bin/time -f "$TIME_FORMAT" ./cpp/sort $NUM 2>&1)
    if [ $? -ne 0 ]; then echo "$out"; fail "Can't execute test"; fi
    parse_out "$out" "cpp optimized"
    out=$(/usr/bin/time -f "$TIME_FORMAT" ./cpp/sort_debug $NUM 2>&1)
    if [ $? -ne 0 ]; then echo "$out"; fail "Can't execute test"; fi
    parse_out "$out" "cpp debug"
}

function java() {
    out=$(/usr/bin/time -f "$TIME_FORMAT" ./java/run.sh $NUM 2>&1)
    if [ $? -ne 0 ]; then echo "$out"; fail "Can't execute test"; fi
    parse_out "$out" "java"
}

function go() {
    out=$(/usr/bin/time -f "$TIME_FORMAT" ./go/sort $NUM 2>&1)
    if [ $? -ne 0 ]; then echo "$out";  fail "Can't execute test"; fi
    parse_out "$out" "go"
}

function python() {
    NUM_PY=$((NUM/5))
    out=$(/usr/bin/time -f "max_rss %M kB, real: %e secs," python ./python/sort.py $NUM_PY 2>&1)
    if [ $? -ne 0 ]; then echo "$out"; fail "Can't execute test"; fi
    parse_out "$out" "python"
}

echo "Starting tests..."
echo "Language             Records #     Bulding time  Sorting time  Testing time  Total time        RSS memory usage"
for test in cpp c go java python; do
    #echo "--------------------------------------" 
    #echo "Running test program written in $test..."
    $test
done