#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* typedef struct TEST */
/* { */
/*     char *sentence; */
/*     int va; */
/* } TEST; */
/**/

void dtor(char **p)
{
    printf("freeing up :%p\n", *p);
    free(*p);
}

int main(void)
{
    char *name __attribute__((cleanup(dtor))) = malloc(51);
    for (int i = 0; i < 50; i++)
    {
        name[i] = (char)(i + 65); 
    }
    printf("name: %p, %s\n", name, name);

    /* free(name); */
    return 0;
}

