package main

import (
	"fmt"
	"os"
	"sort"
	"strconv"
	"time"
)

type RndData struct {
	prev uint64
}

const rng_a uint64 = 48271
const rng_c uint64 = 0
const rng_m uint64 = 2147483647

func (this *RndData) gen_num() uint64 {
	this.prev = (this.prev*rng_a + rng_c) % rng_m
	return this.prev
}

type Data struct {
	id    uint64
	value uint64
}

type sortData []Data

func (this sortData) Swap(i, j int) {
	this[i].value, this[j].value = this[j].value, this[i].value
	this[i].id, this[j].id = this[j].id, this[i].id
}

func (this sortData) Less(i, j int) bool {
	return this[i].value < this[j].value
}

func (this sortData) Len() int {
	return len(this)
}

func main() {

	var RecordsNum uint64 = 100000000

	if len(os.Args) > 1 {
		v, err := strconv.ParseUint(os.Args[1], 0, 64)
		if err != nil {
			panic("Can't convert argument")
		}
		RecordsNum = v
	}

	rng_data := RndData{prev: 1}

	fmt.Printf("Building %d records...\n", RecordsNum)
	start := time.Now().UnixNano()

	d := make([]Data, RecordsNum)

	var i uint64
	for i = 0; i < RecordsNum; i++ {
		d[i].value = rng_data.gen_num()
		d[i].id = d[i].value + 10
	}

	var nanoConv int64 = 1000000

	msec := (time.Now().UnixNano() - start) / nanoConv
	fmt.Printf("Time elapsed: %d ms\n", msec)

	fmt.Printf("Sorting %d elements...\n", RecordsNum)
	start = time.Now().UnixNano()
	sort.Sort(sortData(d))
	msec = (time.Now().UnixNano() - start) / nanoConv
	fmt.Printf("Time elapsed: %d ms\n", msec)

	fmt.Printf("Checking whether the collection is sorted\n")
	start = time.Now().UnixNano()
	if !sort.IsSorted(sortData(d)) {
		fmt.Printf("Collection not sorted!\n")
	}
	msec = (time.Now().UnixNano() - start) / nanoConv
	fmt.Printf("Time elapsed: %d ms\n", msec)
}
