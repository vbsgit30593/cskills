#include <stdio.h>
void displayAndUpdatePtr(char** ptr) {
    printf("String received : %s\n", *ptr);
    *ptr = "Updated String";
}

void unrealPointers(char***** ptr) {
    ****ptr = "After final update";
}
int main(void) {
    char* origptr = "Hello! I am real";
    displayAndUpdatePtr(&origptr);
    printf("After update, new string: %s\n", origptr);

    // unusual pointers
    char** str1 = &origptr;
    char*** str2 = &str1;
    char**** str3 = &str2;
    unrealPointers(&str3);
    printf("final string: %s\n", origptr);
 
    return 0;

}