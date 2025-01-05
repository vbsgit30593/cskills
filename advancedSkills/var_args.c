#include <stdio.h>
#include <stdarg.h>

typedef enum types {
    INT,
    FLOAT,
    STRING,
} TYPES;

double sum(int count, ...)
{
    va_list ap;
    va_start(ap, count);
    double sum = 0.0;
    int i = 0;
    while (i < count)
    {
        TYPES type = va_arg(ap, int);
        i++;
        switch(type) {
            case INT:
                sum +=  va_arg(ap, int);
                break;
            case FLOAT:
                sum += va_arg(ap, double);
                break;
            case STRING:
                printf("String found: %s\n", va_arg(ap, char *));
                break;
            
            default:
                printf("Invalid\n");
        }
        i++;
    }
    va_end(ap);
    return sum;
}
int main(void)
{
    TYPES type;
    printf("Sum: %f\n", sum(6, INT, 10, FLOAT, 20.11, INT, 30));
    printf("Sum: %f\n", sum(8, INT, 10, INT, 20, INT, 30, STRING, "hello"));

    return 0;
}