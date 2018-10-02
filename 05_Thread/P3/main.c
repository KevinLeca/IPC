/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: kleca
 *
 * Created on 2 octobre 2018, 09:19
 */

#include "zone.h"

/*
 * 
 */
int main(int argc, char** argv) {

    struct donnees file;
    int fileID, retourRcv;

    /* ------ Definition de la clé de la file ------ */
    key_t key;
    key = ftok("/tmp/mafile", CLE);
    if (key == -1) {
        printf("Problème creation file : %s\n", strerror(errno));
        exit(1);
    }
    /* -------------------------------------------- */

    /* ----- Obtention de la file de messages ----- */
    fileID = msgget(key, 0666 | IPC_CREAT);
    if (fileID == -1) {
        printf("Problème creation file : %s\n", strerror(errno));
        exit(1);
    }
    /* -------------------------------------------- */

    memset(file.texte, '\0', 9); // Reinitialise le message a afficher
    retourRcv = msgrcv(fileID, (void*) &file, 9, 2, IPC_NOWAIT); // Message de type 2 de P1
    if (retourRcv != -1) {
        printf("température : %s\n", file.texte);
    }
    memset(file.texte, '\0', 9); // Reinitialise le message a afficher
    retourRcv = msgrcv(fileID, (void*) &file, 9, 3, IPC_NOWAIT); // Message de type 3 de P2
    if (retourRcv != -1) {
        printf("ordre : %s\n", file.texte);
    }
    memset(file.texte, '\0', 9); // Reinitialise le message a afficher
    retourRcv = msgrcv(fileID, (void*) &file, 9, 4, IPC_NOWAIT); // Message de type 4 de P1
    if (retourRcv != -1) {
        printf("pression : %s\n", file.texte);
    }
    
    msgctl(fileID, IPC_RMID, NULL);
    return (EXIT_SUCCESS);
}

