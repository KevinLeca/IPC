/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: kleca
 *
 * Created on 2 octobre 2018, 08:25
 */

#include "zone.h" // Contient la structure pour les données à envoyer

/*
 * 
 */
int main(int argc, char** argv) {

    struct donnees message; // Le message structuré
    int fileID; // L'ID de la file de messages
    float temperature = 9.8; // Valeur à écrire dans la file (type 2)
    int pression = 5; // Valeur a ecriure dans la file (type 4)

    /* ------ Definition de la clé de la file ------ */
    key_t key;
    key = ftok("/tmp/mafile", CLE);
    if (key == -1) {
        printf("Problème attribution clé : %s\n", strerror(errno));
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


    /* ----- Envoie du message de type 2 ----- */
    sprintf(message.texte, "%f", temperature); // Conversion en chaine de caractères 
    message.type = 2;
    msgsnd(fileID, (void*) &message, sizeof (message.texte), IPC_NOWAIT);
    /* --------------------------------------- */

    /* ----- Envoie du message de type 4 ----- */
    sprintf(message.texte, "%d", pression); // Conversion en chaine de caractères 
    message.type = 4;
    msgsnd(fileID, (void*) &message, sizeof (message.texte), IPC_NOWAIT);
    sleep(10);
    /* --------------------------------------- */

    /* -------------------------------------------- */

    return (EXIT_SUCCESS);
}

