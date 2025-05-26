/*
* Steps involved:
* get file from args and get its file size
* Rather than the fread, issue an aio_read -
*   Note that the completion isn't need here.
*   What's needed is that the request should be issued successfully.
*   To resume work post read completion: some state must be saved
*       this code might not cover that
* Keep polling in an infinitely loop via aio_error
*   Check if its still EINPROGRESS
*   if yes, continue doing some other work
*
* in the end, highlight total bytes read and other work accomplished!!
*/


#include <aio.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/aio.h>
#include <sys/time.h>
#include <stdbool.h>

size_t get_file_size(FILE *fp)
{
    fseek(fp, 0, SEEK_END);
    size_t size = ftell(fp);
    rewind(fp);
    return size;
}


int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        perror("File path missing");
        exit(1);
    }
    char *buf = NULL;
    struct timeval start, end;
    struct aiocb *aio = NULL;

    const char *filepath = argv[1];
    FILE *fp = fopen(filepath, "r");
    if (fp == NULL)
    {
        perror("Could not open file");
        goto cleanup;
    }
    size_t size = get_file_size(fp);

    printf("Expectations: File %s of size %zu bytes\n", filepath, size);

    buf = calloc(size + 1, sizeof(char));

    gettimeofday(&start, NULL);
    // allocate a control block
    aio = calloc(1, sizeof(struct aiocb));
    aio->aio_buf = buf;
    aio->aio_fildes = fileno(fp);
    aio->aio_offset = 0;
    aio->aio_nbytes = size;

    bool flag = true;
    if (aio_read(aio) != 0)
    {
        perror("Async read request could not be issued");
        free(buf);
        goto cleanup;
    }
    uint64_t counter = 0;
    while (aio_error(aio) == EINPROGRESS)
    {
        counter++;
    }
    printf("Counter updated %lld times during async read\n", counter);

    size_t bytes_read = aio_return(aio);
    if (bytes_read == -1)
    {
        perror("Async IO read problems");
        goto cleanup;
    }

    buf[size] = '\0';
    printf("Async IO read %zu bytes\n", bytes_read);
    gettimeofday(&end, NULL);
    printf("Total time spent: %lfs\n",
           end.tv_sec - start.tv_sec +
           (end.tv_usec - start.tv_usec) / 1e6);

cleanup:
    free(aio);
    free(buf);
    fclose(fp);
         
    return 0;
}

