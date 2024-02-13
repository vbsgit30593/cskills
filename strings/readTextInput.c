#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void betterRead() {
    // Use fgets
    char text[100];
    printf("Lets read a paragraph of text\n");
    fgets(text, 100, stdin);

    printf("Data read: %s \n", text);
    
}
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

    return 0;
}