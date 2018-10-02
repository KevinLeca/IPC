/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: kleca
 *
 * Created on September 25, 2018, 11:22 AM
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#define BUFSIZE 255

/*
 * 
 */
int main(int argc, char** argv) {
    int pid;
    int tube[2];
    int tube2[2];
    char *chaine = "Bonjour fils !";
    char *chaine2 = "Bonjour pere !";
    char buffer[BUFSIZE];
    

    memset(buffer, '\0', BUFSIZE);

    if (pipe(tube) == 0) {
        if(pipe(tube2) == 0){
            pid = fork();

            if (pid == 0) // On est dans le processus fils
            {
                memset(buffer, 0, BUFSIZE);
                read(tube[0], buffer, BUFSIZE);
                write(tube2[1], chaine2, strlen(chaine2));
                printf("Message lut par le fils : %s\n", buffer);
            } else // On est dans le processus pere
            {
                sleep(2);
                write(tube[1], chaine, strlen(chaine));
                read(tube2[0], buffer, BUFSIZE);
                printf("Message lut par le pere : %s\n", buffer);
            }
        }
    }
    exit(EXIT_SUCCESS);
}

