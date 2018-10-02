/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: kleca
 *
 * Created on 21 septembre 2018, 11:38
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

// Fonction du traitement du signal SIGUSR1
void traitement(int sig){
    (void) signal(SIGUSR1, traitement);
    printf("un signal SIGUSR1 ppid: %d\n", getppid());
}

/*
 *
 */

// Programme main
int main(int argc, char** argv) {
    int pid;
    (void) signal(SIGUSR1, traitement);
    
    pid = fork();
    
    if(pid == -1){ // Error fork
        printf("Problème de création fork : %s\n", strerror(errno));
        exit(1);
    }
    
    else{ // Success fork
        if (pid == 0){ // On est dans le processus fils de PP
            printf("fils pid = %d\n", getpid());
            kill(getppid(), SIGUSR1);
            sleep(2); // Tempo pour etre certain que le fils sera
                      // Encore vivant quand le pere lui
                      // Enverra son signal
        }
        else{ // On est dans le processus pere PP
            printf("pere pid = %d\n", getpid());
            kill(pid, SIGUSR1);
            sleep(2); // Tempo pour etre certain que le pere sera 
                      // encore vivant quand le fils lui
                      // Enverra son signal
        }
    }
    return (EXIT_SUCCESS);
}

