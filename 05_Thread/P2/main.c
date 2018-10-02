/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: kleca
 *
 * Created on 2 octobre 2018, 09:09
 */

#include "zone.h"

/*
 * 
 */
int main(int argc, char** argv) {
    struct donnees maFile;
    int fileID;
    char ordre = 'O';

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

    /* ---------------- Traitement ---------------- */

    /* ----- Envoie du message de type 4 ----- */
    maFile.texte[0] = ordre;
    maFile.type = 3;
    msgsnd(fileID, (void*) &maFile, sizeof (char), IPC_NOWAIT);
    sleep(10);
    /* --------------------------------------- */

    /* -------------------------------------------- */

    return (EXIT_SUCCESS);
}

