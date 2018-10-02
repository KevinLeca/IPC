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

/*
 *
 */

int main(int argc, char *argv[]) {
    int socketServeur;
    struct sockaddr_in infosServeur;
    struct sockaddr_in infosClient;
    int tailleClient;
    int retourBind;
    int retourListen;
    int socketClient;
    int retourRead;
    int retourWrite;
    char codeHTML[1024] = "HTTP/1.1 200 OK\nContent-Lenght: 122\nContent-Type: text/html;\n\n<html></head><body><center><h1>C'est mon serveur http</h1></center></body></html>";

    socketServeur = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(socketServeur == -1){
        printf("Error creating socket server \n");
    }

    /* Infos du serveur */
    infosServeur.sin_family = AF_INET;
    infosServeur.sin_port = htons(8888); //numero de port du serveur 
    infosServeur.sin_addr.s_addr = htonl(INADDR_ANY); // adresse IP des clients

    /* Infos Client */
    tailleClient = sizeof (infosClient);

    /* Bind */
    retourBind = bind(socketServeur, (struct sockaddr*) &infosServeur, sizeof (infosServeur));
    if(retourBind == -1){
        printf("Error Binding server \n");
    }

    /* Definition de la taille de la file */
    retourListen = listen(socketServeur, 10);
    if(retourListen == -1){
        printf("Error Listening server \n");
    }

    while (1) {
        /* Accept de la connexion */
        socketClient = accept(socketServeur, (struct sockaddr*) &infosClient, &tailleClient);
        if (socketClient == -1) {
            printf("Error Accepting connexion server \n");
        }
        
        /* Envoie de data */
        printf("%s", codeHTML);
        retourWrite = write(socketClient, &codeHTML, strlen(codeHTML));
        if(retourWrite == -1){
            printf("Error wrinting file");
        }
        close(socketClient);
    }
    
    close(socketServeur);

    return EXIT_SUCCESS;
}

