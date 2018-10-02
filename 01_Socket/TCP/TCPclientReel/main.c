/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: kleca
 *
 * Created on 18 septembre 2018, 08:08
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

/*
 *
 */

int main(int argc, char** argv) {

    int socketClient;
    struct sockaddr_in infosServeur;
    float reelAEnvoyer = 33;
    float reelRecu;
    int retourConnect;
    int retourWrite;
    int retourRead;

    /* Création de la socket client */
    socketClient = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socketClient == -1) {
        printf("Problème création socket client : %s \n", strerror(errno));
    }

    /* Init des infos serveur */
    infosServeur.sin_addr.s_addr = inet_addr("172.18.58.74");
    infosServeur.sin_family = AF_INET;
    infosServeur.sin_port = htons(6666);
    int addrlen = sizeof (infosServeur);

    /* Connect */
    retourConnect = connect(socketClient, (struct sockaddr *) &infosServeur, addrlen);

    /* Envoie de l'entier */
    retourWrite = write(socketClient, &reelAEnvoyer, sizeof (reelAEnvoyer));

    /* Reception de l'entier */
    retourRead = read(socketClient, &reelRecu, sizeof (reelRecu));

    /* Fin de connection par close*/
    int close(int socketClient);

    /* Afficher du reel du serveur */
    printf("Entier recu : %.f", reelRecu);

    return (EXIT_SUCCESS);
}

