#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <aio.h>
#include <sys/time.h>
#include <unistd.h>

static inline size_t get_file_size(FILE *fp)
{
    fseek(fp, 0, SEEK_END);
    size_t size = ftell(fp);
    rewind(fp);
    return size;
}

static inline const char* get_file_path(int argc, char *argv[])
{
    if(argc < 2)
    {
        perror("Please provide file path");
        exit(1);
    }

    return argv[1];
}

static inline int sync_file_read(FILE *fp, char *buf, int size)
{
    size_t bytes_read = fread(buf, 1, size, fp);
    if (bytes_read < size)
    {
        return -1;
    }
    buf[size] = 0;
    printf("Bytes read: %zu\n", bytes_read);
    return size;
}

