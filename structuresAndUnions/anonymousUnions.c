#include <stdio.h>
#include <stdbool.h>

typedef struct {
    union 
    {
       float value;
       double valueExtended;
    };

    bool isExtended;
} CustomFloat;

int main(void){
    CustomFloat cf1, cf2;
    cf1.isExtended = false;
    cf1.value = 12.5f;

    cf2.isExtended = true;
    cf2.valueExtended = 0.25;

    printf("%f %lf %f %lf\n", cf1.value, cf1.valueExtended, cf2.value, cf2.valueExtended);
    return 0;

}