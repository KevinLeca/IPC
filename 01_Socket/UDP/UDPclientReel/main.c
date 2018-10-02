/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: kleca
 *
 * Created on 12 septembre 2018, 08:34
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>

/*
 * 
 */
typedef struct {
    unsigned char jour;
    unsigned char mois;
    unsigned short int annee;
    char jourDeLaSemaine[10]; // le jour en toute lettre
} datePerso;

int main(int argc, char** argv) {

    int socketClient;
    struct sockaddr_in infosServeur;
    float reelAEnvoyer = 33;
    float reelRecu;
    int retourRecv;
    int retourSend;

    /* Création de la socket client */
    socketClient = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (socketClient == -1) {
        printf("Problème création socket client : %s \n", strerror(errno));
    }

    /* Init des infos serveur */
    infosServeur.sin_addr.s_addr = inet_addr("172.18.58.81");
    infosServeur.sin_family = AF_INET;
    infosServeur.sin_port = htons(3333);

    int tailleSend = sizeof (infosServeur);

    /* Envoyer l'entier au serveur */
    retourSend = sendto(socketClient, &reelAEnvoyer, sizeof (reelAEnvoyer), 0, (struct sockaddr *) &infosServeur, tailleSend);

    /*Recevoir l'entier du serveur */
    retourRecv = recvfrom(socketClient, &reelRecu, sizeof (reelRecu), 0, (struct sockaddr *) &infosServeur, &tailleSend);

    /* Afficher du reel du serveur */
    printf("Reel recu : %.2f", reelRecu);

    return (EXIT_SUCCESS);
}

