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
    FILE *fp_out, *fp_in;
    char outp_buf[256];
    char inp_buf[256];
    const char* fmt = "Point : (%d, %d)\n";

    fp_out = fopen("point.dat", "w");
    if (fp_out == NULL){
        printf("Error in writing to file\n");
        return 1;
    }

    snprintf(outp_buf, 256, fmt, p.x, p.y);
    size_t bytes_written = fwrite(outp_buf, sizeof(char), strlen(outp_buf), fp_out);
    fclose(fp_out);

    if (bytes_written != strlen(outp_buf)){
        printf("Error in write operation!\n");
        return 2;
    }

    // read the file
    fp_in = fopen("point.dat", "r");
    if (fp_in == NULL){
        return 1;
    }

    // read to  buffer
    if (fgets(inp_buf, 256, fp_in) == NULL){
        fclose(fp_in);
        return 3;
    }
    fclose(fp_in);

    printf("Read text: %s", inp_buf);

    // read from buffer to struct
    sscanf(inp_buf, fmt, &p1.x, &p1.y);
    printf("Read to point : (%d, %d)\n", p1.x, p1.y);

    return 0;
}