#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
    char sentence[] = "Lets have dinner together";

    char *word = strtok(sentence, " ");
    while (NULL != word){
        printf("%s\n", word);
        word = strtok(NULL, " ");
    }

    return 0;
}