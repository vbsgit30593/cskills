#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int x;
    int y;
} Point;

int main(int argc, char* argv[]){
    Point p1 = {
        .x = 13,
        .y = -5
    };

    Point p2;

    FILE *fp1, *fp2;
    fp1 = fopen("point.bin", "wb");
    if (fp1 == NULL ){
        return 1;
    }

    size_t elems_written = fwrite(&p1, sizeof(Point), 1, fp1);
    if (elems_written == 0){
        return 2;
    }

    fclose(fp1);
    printf("Binary file written!\n");

    // Read from binary file
    fp2 = fopen("point.bin", "rb");
    if (fp2 == NULL){
        return 3;
    }

    size_t elems_read = fread(&p2, sizeof(Point), 1, fp2);
    if (elems_read == 0){
        printf("Unsuccessful fread\n");
        return 3;
    }
    fclose(fp2);

    printf("Read struct: (%d, %d)\n", p2.x, p2.y);
    return 0;
}