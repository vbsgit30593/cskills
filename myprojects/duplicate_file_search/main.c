#include <assert.h>
#include <dirent.h>
#include <errno.h>
#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/dirent.h>

#define PATH_SEP "/"
#define PATH_SEP_LEN (sizeof(PATH_SEP) - 1)

char* join_path(const char* basepath, const char* dirname)
{
    /* printf("Basepath: %s, dirname: %s\n", basepath, dirname); */
    size_t length = strlen(basepath) + strlen(dirname);
    char* buf = malloc(length + 1 + PATH_SEP_LEN);
    assert(buf != NULL);
    snprintf(buf, length + 2, "%s%s%s", basepath, PATH_SEP, dirname);
    buf[length+1] = '\0';
    return buf;
}

void explore_dir_recursively(const char* dir)
{
    DIR* dirp = opendir(dir);
    if (dirp == NULL)
    {
        fprintf(stderr,
                "Could not open directory : %s due to error: %s\n",
                dir, strerror(errno));
        exit(1);
    }

    struct dirent *entry = readdir(dirp);
    while (entry != NULL) {
        if (entry->d_name[0] != '.')
        {
            char* newpath = join_path(dir, entry->d_name);
            if (entry->d_type == DT_DIR) {
                /* printf("Found a directory: %s\n", entry->d_name); */
                explore_dir_recursively(newpath);
            }
            else {
                printf("%s\n", newpath);
            }
            free(newpath);
        }
        entry = readdir(dirp);
    }
    closedir(dirp);
}

int main(int argc, char *argv[]) {
    const char *dir = "/Users/vsingh/Desktop";
    explore_dir_recursively(dir);
    return 0;
}
