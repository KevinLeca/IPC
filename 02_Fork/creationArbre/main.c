/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: kleca
 *
 * Created on 21 septembre 2018, 08:08
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
 * 
 */
int main(int argc, char *argv[]) {
    int pid1, pid2, pid3, pid4, pid5, pid6, pid7;
    int status;
    
    pid1 = getpid();
    pid3 = fork();
    if (pid3 == 0) { // Enfant de P1 nommé P3
        printf("P3: pid=%d ppid=%d \n", getpid(), getppid());
        pid2 = fork();
        if (pid2 == 0) { // Enfant de P3 nommé P2
            printf("P2: pid=%d ppid=%d \n", getpid(), getppid());
        } else { // On est toujours dans P3
            pid4 = fork();
            if (pid4 == 0) { // Enfant de P3 nommé P4
                printf("P4: pid=%d ppid=%d \n", getpid(), getppid());
            } else { // On est toujours dans P3
                pid5 = fork();
                if (pid5 == 0) { // Enfant de P3 nommé P5
                    printf("P5: pid=%d ppid=%d \n", getpid(), getppid());
                    pid6 = fork();
                    if(pid6 == 0){ // Enfant de P5 nommé P6
                        printf("P6: pid=%d ppid=%d \n", getpid(), getppid());
                    }
                    else{ // On est toujours dans P5
                        pid7 = fork();
                        if(pid7 == 0){ // Enfant de P5 nommé P7
                            printf("P7: pid=%d ppid=%d \n", getpid(), getppid());
                        }
                        else{
                            wait(NULL);
                            wait(NULL);
                        }
                    }
                }
            }
            wait(NULL);
            wait(NULL);
            wait(NULL);
        }
    } else { // On est toujours dans P1
        printf("P1: pid=%d ppid=%d \n", getpid(), getppid());
        wait(NULL);
    }
    return EXIT_SUCCESS;
}