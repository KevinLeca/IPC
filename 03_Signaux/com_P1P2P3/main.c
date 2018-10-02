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

static int cpt = 0;

// fonction de traitement du signal SIGUSR1

void traitement(int sig) {
    
    (void) signal(SIGUSR1, traitement); 
    cpt++;
    printf("Signal %d recu par %d\n", cpt, getpid());
    
}

/*
 *
 */

int main(int argc, char** argv) {

    int pid1, pid2, pid3; // pids de P1, P2 et P3
    (void) signal(SIGUSR1, traitement);
    pid1 = getpid(); // Je récupère le pid de P1
    pid2 = fork(); // Je fork pour créer P2
    
    if (pid2 == 0) { // On est dans le processus fils P2 de P1
        pid3 = fork(); // Je fork pour créer P3
        
        if (pid3 == 0) { // On est dans le processus fils P3 de P2
            sleep(2); // Tempo pour attendre l'envoie de P2 à P1 avant d'envoyer
            printf("P3: envoie un signal à %d\n", pid1);
            kill(pid1, SIGUSR1);
            
        } else { // On est dans le processus fils P2 de P1
            
            printf("P2: envoie un signal à %d\n", getppid());
            kill(pid1, SIGUSR1);
            wait(NULL);
        }
        
    } else { // On est dans le processus pere P1
        printf("P1: pid=%d \n\n", pid1);
        pause();
        pause();
        wait(NULL);
    }
    
    return (EXIT_SUCCESS);
}

