/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: kleca
 *
 * Created on 21 septembre 2018, 10:46
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
 * 
 */
int main(int argc, char** argv) {

    int pid1, pid2;
    pid1 = fork();
    if(pid1 == 0){ // Enfant de PP nommé P1
        printf("P1: pid=%d ppid=%d\n", getpid(), getppid());
    }
    else{ // On est toujours dans PP
        pid2 = fork();
        if(pid2 == 0){ // Enfant de PP nommé P2
            printf("P2: pid=%d ppid=%d\n", getpid(), getppid());
        }
        else{ // On est toujours dans PP
            wait(NULL);
            wait(NULL);
            printf("PP: pid=%d ppid=%d\n", getpid(), getppid());
        }
    }
    return (EXIT_SUCCESS);
}

