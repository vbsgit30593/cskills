#include "fileops.h"

#define LOOPS 10
int main(int argc, char *argv[])
{
    size_t size = 0;
    FILE *fps[LOOPS];
    struct aiocb *aiocbs[LOOPS];
    char *bufs[LOOPS];
    const char *filepath = get_file_path(argc, argv);
    struct timeval start, end;

    FILE *fp = fopen(filepath, "r");
    if (fp == NULL)
    {
        perror("Error opening file");
        exit(1);
    }
    size = get_file_size(fp);
    fclose(fp);

    // allocate aiocbs
    for (int i = 0; i < LOOPS; i++) {
        aiocbs[i] = calloc(1, sizeof(struct aiocb));
        bufs[i] = calloc(size + 1, sizeof(char));
        if (!aiocbs[i] || !bufs[i])
        {
            perror("Allocation error");
            exit(1);
        }

        fps[i] = fopen(filepath, "r");
        if (fps[i] == NULL)
        {
            perror("Error opening file");
            exit(1);
        }
    }

    // init aiocbs
    for (int i = 0; i < LOOPS; i++)
    {
        aiocbs[i]->aio_buf = bufs[i];
        aiocbs[i]->aio_fildes = fileno(fps[i]);
        aiocbs[i]->aio_offset = 0;
        aiocbs[i]->aio_nbytes = size;
    }

    gettimeofday(&start, NULL);
    // issue reads
    for (int i = 0; i < LOOPS; i++)
    {
        if(aio_read(aiocbs[i]) != 0)
        {
            perror("aio read request could not be issued");
            goto cleanup;
        }
        printf("Reads issued: %d\n", (i + 1));
    }

    // wait for completions - Note that the slowest read should be
    // the one defining the overall time.
    for (int i = 0; i < LOOPS; i++)
    {
        while(aio_error(aiocbs[i]) == EINPROGRESS);
        int bytes_read = 0;
        if ((bytes_read = aio_return(aiocbs[i])) < 0)
        {
            perror("aio read returned an error");
            goto cleanup;
        }
        else
        {
            printf("File %d bytes read : %d\n", (i + 1), bytes_read);
        }
    }

    gettimeofday(&end, NULL);
    
    printf("Total time for reads: %lf\n",
           (end.tv_sec - start.tv_sec) +
           (end.tv_usec - start.tv_usec) / 1e6);

cleanup:
    // clean up aiocbs, fds, buffers
    for (int i = 0; i < LOOPS; i++)
    {
        free(bufs[i]);
        free(aiocbs[i]);
        if (fps[i] != NULL) fclose(fps[i]);
    }

    return 0;
}
/*
Reads issued: 1
Reads issued: 2
Reads issued: 3
Reads issued: 4
Reads issued: 5
Reads issued: 6
Reads issued: 7
Reads issued: 8
Reads issued: 9
Reads issued: 10
File 1 bytes read : 1073741824
File 2 bytes read : 1073741824
File 3 bytes read : 1073741824
File 4 bytes read : 1073741824
File 5 bytes read : 1073741824
File 6 bytes read : 1073741824
File 7 bytes read : 1073741824
File 8 bytes read : 1073741824
File 9 bytes read : 1073741824
File 10 bytes read : 1073741824
Total time for reads: 0.711428
*/
