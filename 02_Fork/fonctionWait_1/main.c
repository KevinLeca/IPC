/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: kleca
 *
 * Created on 21 septembre 2018, 10:31
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
 * 
 */
int main(int argc, char** argv) {
    
    int pid1, pid2;
    int cpt = 0;
    
    pid1 = fork();
    if(pid1 == 0){ // Enfant du PP nommé P1
        cpt++;
        printf("Dans le petit fils cpt=%d à l'adresse %4X\n", cpt, &cpt);
    }
    else{ // On est toujours dans PP
        cpt++;
        printf("Dans le père cpt=%d à l'adresse %4X\n", cpt, &cpt);
    }
    return (EXIT_SUCCESS);
}

