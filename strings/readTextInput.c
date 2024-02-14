#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, char* argv[])
{
    char text1[100], text2[100];
    // printf("Enter input text!\n");
    // scanf("%s", text);
    // printf("Inputed text: %s\n", text);
    // the chunk of code above stop reading input once space is encountered

    printf("Enter input text 1!\n");
    scanf("%[^\n]s", text1);
    printf("Inputed text: %s\n", text1);

    getchar();
    printf("Enter input text 2!\n");
    scanf("%[^\n]s", text2);
    printf("Inputed text: %s\n", text2);

/*
    char text3[100];
    printf("Lets read a paragraph of text\n");
    fgets(text3, 100, stdin);
    text3[strlen(text3) - 1] = '\0';
    printf("Data read: %s\n", text3);
*/
    return 0;
}