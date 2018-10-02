/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: kleca
 *
 * Created on September 25, 2018, 8:21 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

/*
 * 
 */

// fonction de traitement du signal SIGUSR1

void traitement(int sig) {

    (void) signal(SIGUSR1, traitement);
    printf("Signal recu par %d\n", getpid());

}

/*
 *
 */

int main(int argc, char** argv) {

    int pid1, pid2, pid3; // pids de P1, P2 et P3
    int tube[2];
    int msg;
    (void) signal(SIGUSR1, traitement);
    pid1 = getpid(); // Je récupère le pid de P1

    if (pipe(tube) == 0) {
        pid2 = fork(); // Je fork pour créer P2
        if (pid2 == 0) { // On est dans le processus fils P2 
            pid3 = fork(); // Je fork pour créer P3

            if (pid3 == 0) { // On est dans le processus fils P3 
                printf("P3: pid = %d\n", getpid());
                int pidP3 = getpid();
                write(tube[1], &pidP3, sizeof(pidP3));
                pause();

            } else { // On est dans le processus fils P2 de P1
                printf("P2: pid = %d\n", getpid());
                pause();
            }

        } else { // On est dans le processus pere P1
            printf("P1: pid = %d\n", getpid());
            kill(pid2, SIGUSR1);
            read(tube[0], &msg, sizeof(msg));
            kill(msg, SIGUSR1);
            printf("message de p3 : %i\n", msg);
        }
    }
    return (EXIT_SUCCESS);
}

