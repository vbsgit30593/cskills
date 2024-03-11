#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
/*
exec family
-----------
execl
execv
execlp
execvp
execlpe
execvpe

Note that on triggering exec, current process is replaced by the new program
So, the rest of the code does not get executed.
*/

int main(void) {
    /* EXECL */
    // execl(
    //     "/sbin/ping",
    //     "/sbin/ping",
    //     "-c",
    //     "2",
    //     "google.com",
    //     NULL
    // );

    /* EXECLP */
    // execlp(
    //     "ping",
    //     "ping",
    //     "-c",
    //     "2",
    //     "google.com"
    //     NULL
    // );

    /* EXECVP */
    // char* cmd[] = {
    //     "ping",
    //     "-c",
    //     "2",
    //     "google.com",
    //     NULL
    // };

    // execvp(
    //     "ping", 
    //     cmd
    // );

    /* EXECLE */
    char* env[] = {
        "ENV=TRUE",
        NULL
    };

    execle(
        "/sbin/ping",
        "/sbin/ping",
        "-c",
        "2",
        "google.com",
        NULL,
        env
    );

    printf("## After the exec call ##\n");
    printf("Exec error: %s\n", strerror(errno));
    return 0;
}