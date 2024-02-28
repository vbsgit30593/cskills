#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int x;
    int y;
} Point;


int main(int argc, char* argv[]){
    Point p = {1, 2};
    Point p1;
    FILE *fp;
    const char* fmt = "Point : (%d, %d)\n";

    fp = fopen("point.dat", "w+");
    if (fp == NULL){
        printf("Error in writing to file\n");
        return 1;
    }

    int bytes_wrote = fprintf(fp, fmt, p.x, p.y);
    if (bytes_wrote <= 0){
        fclose(fp);
        return 2;
    }

    fseek(fp, 0, SEEK_SET);

    // read the file
    int elems_read = fscanf(fp, fmt, &p1.x, &p1.y);
    if (elems_read < 2){
        printf("Incomplete read: %d elements\n", elems_read);
        fclose(fp);
        return 3;
    }

    printf("Read to point : (%d, %d)\n", p1.x, p1.y);
    fclose(fp);
    return 0;
}