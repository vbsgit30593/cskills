#include <stdio.h>
#include <stdlib.h>

void func(void *anon)
{

}
int main(void) {
    func(
    &(
        struct {
            int a;
            int b;
        }
    )
    );
    return 0;
}
