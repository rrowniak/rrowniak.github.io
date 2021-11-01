#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

struct  RndData {
    uint64_t prev;
};

const uint64_t rng_a = 48271;
const uint64_t rng_c = 0;
const uint64_t rng_m = 2147483647;

uint64_t gen_num(struct RndData* state) {
    state->prev = (state->prev * rng_a + rng_c) % rng_m;
    return state->prev;
}

struct Data {
    uint64_t id;
    uint64_t value;
};

int cmp(const void* d1, const void*d2) {
    uint64_t v1 = ((struct Data*)d1)->value;
    uint64_t v2 = ((struct Data*)d2)->value;

    if (v1 < v2) {
        return -1;
    } else if (v1 == v2) {
        return 0;
    }
    
    return 1;
}

size_t RecordsNum = 100000000;

int main(int argc, char** argv)
{
    if (argc > 1) {
        RecordsNum = atol(argv[1]);
    }

    struct RndData rng_data = {
        .prev = 1
    };

    printf("Building %ld records...\n", RecordsNum);
    clock_t start = clock();

    struct Data* d = (struct Data*)malloc(sizeof(struct Data) * RecordsNum);

    for (size_t i = 0; i < RecordsNum; ++i) {
        d[i].value = gen_num(&rng_data);
        d[i].id = d[i].value + 10;
    }

    const clock_t clk_per_msec = CLOCKS_PER_SEC / 1000;
    int msec = (clock() - start) / clk_per_msec;
    printf("Time elapsed: %d ms\n", msec);

    printf("Sorting %ld elements...\n", RecordsNum);
    start = clock();
    qsort(d, RecordsNum, sizeof(struct Data), cmp);
    msec = (clock() - start) / clk_per_msec;
    printf("Time elapsed: %d ms\n", msec);

    printf("Checking whether the collection is sorted\n");
    start = clock();
    for (size_t i = 0; i < RecordsNum - 1; ++i) {
        if (d[i].value > d[i+1].value) {
            printf("Collection not sorted!\n");
            break;
        }
    }
    msec = (clock() - start) / clk_per_msec;
    printf("Time elapsed: %d ms\n", msec);

    free(d);
    return 0;
}
