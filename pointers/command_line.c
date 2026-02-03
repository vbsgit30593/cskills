#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* We will be provided a file of commands and each command starts with a keyword
* in the first index.
* cut 5 7
* copy 3
* paste 8
* find abcd 3 6
* search abcd 3 8
* We expect the output to be such that we can dump the read command along with
* the passed args
*/


/*
 * Ugly copy-paste approach.
 * 1. read the file line by line
 * 2. call the functions in a switch case based on the matched strings
 * */

void cut(const char *args)
{
    printf("Cut called with args: %s\n", args);
}

void copy(const char *args)
{
    printf("Copy called with args: %s\n", args);
}

void paste(const char *args)
{
    printf("Paste called with args: %s\n", args);
}

void find(const char *args)
{ 
    printf("Find called with args: %s\n", args);
}

void search(const char *args)
{   
    printf("Search called with args: %s\n", args);
}


typedef void (*handler_t)(const char *);

typedef struct {
    handler_t handle;
    const char *cmd;
} command_map;

command_map map[] = {
    {.handle=cut, .cmd="cut"},
    {.handle=copy, .cmd="copy"},
    {.handle=paste, .cmd="paste"},
    {.handle=find, .cmd="find"},
    {.handle=search, .cmd="search"},
};

handler_t get_handler(const char *cmd)
{
    size_t size = sizeof(map) / sizeof(map[0]);
    for (int i = 0; i < size; i++)
    {
        if (strcmp(map[i].cmd, cmd) == 0)
        {
            return map[i].handle;
        }
    }
    return NULL;
}

int main(void) {
    // continuously reading commands from a file until we encounter `end`
    FILE *file = fopen("commands.txt", "r");
    if (file == NULL) {
        perror("Could not open commands.txt");
        return 1;
    }
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char command[50];
        char args[200];
        if (sscanf(line, "%s %[^\n]", command, args) < 1) {
            continue; // skip empty lines
        }

        if (strcmp(command, "end") == 0) break;

        // get a function handler
        handler_t hdl = get_handler(command);
        if (!hdl)
        {
            printf("Invalid command : %s\n", command);
            continue;
        }
        hdl(args);
    }

    fclose(file);

    return 0;
}
