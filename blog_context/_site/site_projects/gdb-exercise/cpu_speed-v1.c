#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char filename[] = "/proc/cpuifo";
const char cpu_section[] = "processor\t: %d";
const char speed_tag[] = "cpu MHz\t\t: ";

static int is_cpu_section(const char* section_line, const char* curr_line) {
    do {
        if (*section_line == '\0') {
            return 1;
        }
    } while (curr_line != '\0' && *section_line == *curr_line);
    return 0;
}

static const char* extract_mhz(const char* line)
{
    const char* str = NULL;
    if ((str = strstr(line, speed_tag)) != NULL) {
        str += strlen(speed_tag);
    }
    return str;
} 

static void scan_file(FILE *f, const char* cpu_section_num)
{
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    int section_found = 0;
    const char* mhz = NULL; 

    while ((read = getline(&line, &len, f)) != -1) {
        if (!section_found && !is_cpu_section(cpu_section_num, line)) {
            section_found = 1;
            continue;
        }

        if ((mhz = extract_mhz(line)) != NULL) {
            printf("%s MHz", mhz);
            break;
        }
    }

    if (line) {
        free(line);
    }
}

int main(int argc, char const *argv[])
{
    FILE* f = NULL;
    int core_num;
    char cpu_section_num[255];

    if (argc < 2) {
        fprintf(stderr, "usage: cpu_speed <cpu_num>\n");
        exit(EXIT_FAILURE);
    }

    core_num = atoi(argv[1]);
    sprintf(cpu_section_num, cpu_section, core_num);

    if ((f = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "can't open %s file", filename);
        exit(EXIT_FAILURE);
    }

    scan_file(f, cpu_section_num);

    fclose(f);
    return EXIT_SUCCESS;
}
