#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>

typedef struct{
	unsigned char jour;
	unsigned char mois;
	unsigned short int annee;
	char jourDeLaSemaine[10];	// le jour en toute lettre
}datePerso;

int main(int argc, char *argv[]) {
    int retourSocket;
    struct sockaddr_in infosServeur;
    struct sockaddr_in infosClient;
    int retourBind;
    int retourRcv;
    int retourSend;
    int tailleClient;
    datePerso date;

    printf("serveur UDP sur port 4444 attend une DATE\n");
    retourSocket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

    /* Infos du serveur */
    infosServeur.sin_family = AF_INET;
    infosServeur.sin_port = htons(4444); //numero de port du serveur 
    infosServeur.sin_addr.s_addr = htonl(INADDR_ANY); // adresse IP du serveur 

    /* Bind */
    retourBind = bind(retourSocket, (struct sockaddr*) &infosServeur, sizeof (infosServeur));

    tailleClient = sizeof (infosClient);

    /* Attente de data client */
    retourRcv = recvfrom(retourSocket, &date, sizeof(date), 0, (struct sockaddr *) &infosClient, &tailleClient);

    /* Affichage data client */
    printf("message client %s : %s %hhu/%hhu/%hu\n", inet_ntoa(infosClient.sin_addr), date.jourDeLaSemaine, date.jour, date.mois, date.annee);

    return EXIT_SUCCESS;
}