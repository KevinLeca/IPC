/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: kleca
 *
 * Created on September 25, 2018, 11:04 AM
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */
int main(int argc, char** argv) {
    FILE *flux;
    char buffer[1024];
    int retour;
    
    flux= popen("halt -p", "r"); // Ouverture
    retour = fread(buffer, sizeof(buffer), 1, flux);
    printf("%s", buffer);
    pclose(flux); // Fermeture
    
    return (EXIT_SUCCESS);
}

