#include <search.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

static void *fd_tree_root = NULL;

void log_write_entry(const char *logfile, const char *operation, const char *path) {
    struct timeval now;
    FILE *fh = fopen(logfile, "a");

    gettimeofday(&now, NULL);
    fprintf(fh, "%ld.%06ld %s %s\n", now.tv_sec, now.tv_usec, operation, path);

    fclose(fh);
}

int log_compare(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}

void log_touch(const int fd) {
    int *ptr = (int*) malloc(sizeof(int));
    *ptr = fd;

    tsearch((void*)ptr, &fd_tree_root, log_compare);
}

void log_close(const char *logfile, const int fd, const char *path) {
    int **ptr = (int**) tfind((void*)&fd, &fd_tree_root, log_compare);

    if (ptr != NULL) {
        int *element = *ptr;
        tdelete((void*)&fd, &fd_tree_root, log_compare);
        free(element);

        log_write_entry(logfile, "WR", path);
    }
}
