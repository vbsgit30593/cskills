#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

size_t get_file_size(FILE *fp)
{
    fseek(fp, 0, SEEK_END);
    size_t size = ftell(fp);
    rewind(fp);
    return size;
}

int main(int argc, char *argv[])
{
    // get the path of file to read
    if (argc < 2)
    {
        printf("Please provide file to read!\n");
        exit(0);
    }
    
    const char *filepath = argv[1];
    printf("File to read: %s\n", filepath);
    // print size of file
    
    FILE *fp = fopen(filepath, "r");
    if (!fp)
    {
        perror("Invalid file path");
        exit(1);
    }

    size_t filesize = get_file_size(fp);

    printf("Size of file to read: %zu bytes\n", filesize);

    // read file data and capture time elapsed
    char *buf = calloc(filesize + 1, sizeof(char));
    if (!buf)
    {
        perror("Failed allocation");
        exit(1);
    }

    struct timeval start, end;
    gettimeofday(&start, NULL);
    size_t bytes_read = fread(buf, 1, filesize, fp);
    buf[filesize] = '\0';
    if (bytes_read < filesize)
    {
        perror("incomplete amount of bytes read");
        exit(1);
    }
    gettimeofday(&end, NULL);
    // print bytes read
    printf("Time to read %zu bytes: %lfs\n", bytes_read,
           (end.tv_sec - start.tv_sec) +
           (end.tv_usec - start.tv_usec) / 1e6);
    free(buf);
    fclose(fp);

    return 0;
}

