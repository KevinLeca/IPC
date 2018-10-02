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

/*
 * 
 */
int main(int argc, char** argv) {

    int pid1, pid2;;
    char buffer[255];
    
    pid1 = fork();
    if(pid1 == 0){ // Enfant de PP nomé P1
        sprintf(buffer, "mon pid est %i, le pid de mon pere est %i", getpid(), getppid());
        boite("boite1", buffer);
        pid2 = fork();
        if(pid2 == 0){ // Enfant de P1 nomé P2
            sprintf(buffer, "mon pid est %i, le pid de mon pere est %i", getpid(), getppid());
            boite("boite2", buffer);
        }
        else{ // On est toujours dans P1
            sprintf(buffer, "mon pid est %i, le pid de mon pere est %i", getpid(), getppid());
            boite("boite3", buffer);
        }
    }
    else{ // On est toujours dans PP
        sprintf(buffer, "mon pid est %i, le pid de mon pere est %i", getpid(), getppid());
        boite("boite4", buffer);
    }
    return (EXIT_SUCCESS);
}

