#include "kernel/types.h"
#include "user/user.h"

void func(int *input, int num){
    if(num == 1){
        printf("prime %d\n", *input);
        return;
    }
    int p[2];
    int prime = *input;
    printf("prime %d\n", prime);
    pipe(p);
    if(fork() == 0){
        close(p[0]);
        for(int i = 0; i < num; ++i){
            int temp = *(input + i);
            write(p[1], (char *)(&temp), 4);
        }
        close(p[1]);
        exit(0);
    }
    if(fork() == 0){
        close(p[1]);
        int count = 0;
        char buffer[4];
        while(read(p[0], buffer, 4) != 0){
            int temp = *((int *)buffer);
            if(temp % prime != 0){
                *input = temp;
                input += 1;
                count++;
            }    
        }
        func(input - count, count);
        close(p[0]);
        exit(0);
    }
    wait(0);
    wait(0);
}

int main(){
    int input[34];
    for(int i = 0; i < 34; ++i){
        input[i] = i + 2;
    }
    func(input, 34);
    exit(0);
}