#include "fileops.h"
#include <sys/time.h>

const int LOOPS = 10;
int main(int argc, char *argv[])
{
    size_t size = 0;
    FILE *fps[LOOPS];
    char *bufs[LOOPS];
    struct timeval start, end;

    const char *filepath = get_file_path(argc, argv);
    FILE *fp = fopen(filepath, "r");
    if (fp == NULL)
    {
        perror("Could not open file");
        goto cleanup;
    }
    size = get_file_size(fp);
    fclose(fp);

    // allocate bufs and open files
    for (int i = 0; i < LOOPS; i++)
    {
        bufs[i] = calloc(size + 1, sizeof(char));
        if (bufs[i] == NULL)
        {
            perror("Allocation error");
            goto cleanup;
        }

        fps[i] = fopen(filepath, "r");
        if (fps[i] == NULL)
        {
            perror("Error opening file");
            goto cleanup;
        }
    }

    gettimeofday(&start, NULL);
    for (int i = 0; i < LOOPS; i++)
    {
        printf("Reading file %d\n", (i + 1));
        int bytes_read = sync_file_read(fps[i], bufs[i], size);
        if (bytes_read == -1)
        {
            perror("Could not read file");
            goto cleanup;
        }
    }
    gettimeofday(&end, NULL);
    printf("Time spent on %d file reads: %lf\n", LOOPS,
           (end.tv_sec - start.tv_sec) + 
           (end.tv_usec - start.tv_usec)/1e6);

cleanup:
    // clean up aiocbs, fds, buffers
    for (int i = 0; i < LOOPS; i++)
    {
        free(bufs[i]);
        if (fps[i] != NULL) fclose(fps[i]);
    }

    return 0;
}

/*
Reading file 1
Bytes read: 1073741824
Reading file 2
Bytes read: 1073741824
Reading file 3
Bytes read: 1073741824
Reading file 4
Bytes read: 1073741824
Reading file 5
Bytes read: 1073741824
Reading file 6
Bytes read: 1073741824
Reading file 7
Bytes read: 1073741824
Reading file 8
Bytes read: 1073741824
Reading file 9
Bytes read: 1073741824
Reading file 10
Bytes read: 1073741824
Time spent on 10 file reads: 1.537130
*/
