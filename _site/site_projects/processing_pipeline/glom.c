#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define GIG 1073741824l

int main(int argc, char** argv)
{
    char   *a = NULL;
    char    mesg[1024];
    size_t  size = 0;
    size_t  i = 0;

    if (argc != 2) {
        fprintf(stderr, "Usage: glom N\n");
        fprintf(stderr, "    where N = no. of bytes\n");
        exit(1);
    }

    size = atol(argv[1]);

    printf("Trying to allocate %ld chars (%ld GB) ...\n", size, size/GIG);
    fflush(stdout);

    for (i = 0; i < 1024; ++i)
        mesg[i] = '\0';

    a = malloc(size);
    if (a == (char*)NULL) {
        sprintf(mesg, "Cannot allocate %ld chars", size);
        perror(mesg);
    } else {
        printf("Allocated %ld chars for %ld GB\n", size, size/GIG);
    }

    free(a);
    
    return 0;
}