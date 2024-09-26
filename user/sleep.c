#include "kernel/types.h"
#include "user/user.h"

int main(int argn, char *argv[]){
    if(argn != 2){
        fprintf(2, "must one argument for sleep\n");
        exit(1);
    }
    int sleepTime = atoi(argv[1]);
    printf("(nothing happens for a little while)\n");
	sleep(sleepTime);
	exit(0);
}