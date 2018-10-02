#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    int retourSocket;
    struct sockaddr_in infosServeur;
    struct sockaddr_in infosClient;
    int retourBind;
    int retourRcv;
    int retourSend;
    int tailleClient;
    int entierRecu;

    printf("serveur UDP sur port 2222 attend un ENTIER\n");
    retourSocket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

    /* Infos du serveur */
    infosServeur.sin_family = AF_INET;
    infosServeur.sin_port = htons(2222); //numero de port du serveur 
    infosServeur.sin_addr.s_addr = htonl(INADDR_ANY); // adresse IP du serveur 

    /* Bind */
    retourBind = bind(retourSocket, (struct sockaddr*) &infosServeur, sizeof (infosServeur));

    tailleClient = sizeof (infosClient);

    /* Attente de data client */
    retourRcv = recvfrom(retourSocket, &entierRecu, sizeof (entierRecu), 0, (struct sockaddr *) &infosClient, &tailleClient);

    /* Affichage data client */
    printf("message client %s : %i\n", inet_ntoa(infosClient.sin_addr), entierRecu);

    entierRecu = -entierRecu;
    retourSend = sendto(retourSocket, &entierRecu, sizeof (entierRecu), 0, (struct sockaddr *) &infosClient, sizeof (infosClient));

    return EXIT_SUCCESS;
}