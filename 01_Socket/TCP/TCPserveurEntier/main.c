/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: kleca
 *
 * Created on 18 septembre 2018, 08:49
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int retourSocket;
    struct sockaddr_in infosServeur;
    struct sockaddr_in infosClient;
    int entierRecu;
    int tailleClient;
    int retourBind;
    int retourListen;
    int retourAccept;
    int retourRead;
    int retourWrite;


    printf("serveur TCP sur port 5555 attend un ENTIER\n");
    retourSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    /* Infos du serveur */
    infosServeur.sin_family = AF_INET;
    infosServeur.sin_port = htons(5555); //numero de port du serveur 
    infosServeur.sin_addr.s_addr = htonl(INADDR_ANY); // adresse IP du serveur

    /* Infos Client */
    tailleClient = sizeof (infosClient);

    /* Bind */
    retourBind = bind(retourSocket, (struct sockaddr*) &infosServeur, sizeof (infosServeur));

    /* Definition de la taille de la file */
    retourListen = listen(retourSocket, 10);

    while (1) {
        /* Accept de la connexion */
        retourAccept = accept(retourSocket, (struct sockaddr*) &infosClient, &tailleClient);

        /* Attente de data client */
        retourRead = read(retourAccept, &entierRecu, sizeof (entierRecu));

        /* Affichage data client */
        printf("message client %s : %i\n", inet_ntoa(infosClient.sin_addr), entierRecu);

        entierRecu = -entierRecu;
        retourWrite = write(retourAccept, &entierRecu, sizeof (entierRecu));
        close(retourAccept);
    }

    close(retourSocket);

    return EXIT_SUCCESS;
}

