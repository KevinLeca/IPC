/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: kleca
 * Questions 3 et 4 du TD01 Threads
 * Created on 28 septembre 2018, 09:06
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/syscall.h>

typedef struct {
    int v1;
    int v2;
    int v3;
} laStruct;

laStruct global; // Ma variable globale

/* ----- Création du mutex et initialisation ----- */
pthread_mutex_t flag = PTHREAD_MUTEX_INITIALIZER; 

void *tache1(void *p_data) {

    laStruct val = *((laStruct *) p_data);
    int tid;

    sleep(3); //Tempo
    
    pthread_mutex_lock(&flag); // On verrouille le mutex 
    
    /* ------ On effectue la tâche ----- */
    global.v1 = val.v1;
    global.v2 = val.v2;
    global.v3 = val.v3;
    /* --------------------------------- */
    
    pthread_mutex_unlock(&flag); // On déverrouille le mutex 

    tid = syscall(SYS_gettid);
    printf("T1: TID = %d v1 = %d,\n", tid, global.v1);
    printf("T1: argument = %d\n", val.v1);
    sleep(3);

    pthread_exit((void *) "tâche terminée \n");
}

void *tache2(void *p_data) {


    laStruct val = *((laStruct *) p_data);
    int tid;

    sleep(3);//Tempo

    pthread_mutex_lock(&flag); // On verrouille le mutex 
    
    /* ------ On effectue la tâche ----- */
    global.v1 = val.v1;
    global.v2 = val.v2;
    global.v3 = val.v3;
    /* --------------------------------- */
    
    pthread_mutex_unlock(&flag); // On déverrouille le mutex 

    tid = syscall(SYS_gettid);

    printf("T2: TID = %d v2 = %d,\n", tid, global.v2);
    printf("T2: argument = %d\n", val.v2);
    sleep(1);
    pthread_exit((void *) "tâche terminée \n");
}

void *tache3(void *p_data) {


    laStruct val = *((laStruct *) p_data);
    int tid;
    
    sleep(3);//Tempo

    pthread_mutex_lock(&flag); // On verrouille le mutex 
    
    /* ------ On effectue la tâche ----- */
    global.v1 = val.v1;
    global.v2 = val.v2;
    global.v3 = val.v3;
    /* --------------------------------- */
    
    pthread_mutex_unlock(&flag); //  On déverrouille le mutex 

    tid = syscall(SYS_gettid);
    printf("T3: TID = %d v3 = %d,\n", tid, global.v3);
    printf("T3: l'argument = %d\n", val.v3);
    sleep(2);

    pthread_exit((void *) "tâche terminée \n");
}

int main() {
    int i, res;
    int tmp = 0; // Pour un affichage propre
    pthread_t T[3];

    void *thread_result;

    laStruct a, b, c;
    a.v1 = 11; a.v2 = 12; a.v3 = 13;
    b.v1 = 21; b.v2 = 22; b.v3 = 23;
    c.v1 = 31; c.v2 = 32; c.v3 = 33;

    /* ----- Création des trois threads  ----- */
    res = pthread_create(&T[0], NULL, tache1, (void *) &a);
    if (res != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }

    res = pthread_create(&T[1], NULL, tache2, (void *) &b);
    if (res != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }

    res = pthread_create(&T[2], NULL, tache3, (void *) &c);
    if (res != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
    
    /* ----- attente de la fin des trois threads ----- */

    for (i = 0; i < 3; i++) {
        res = pthread_join(T[i], &thread_result);
        if (res != 0) {
            perror("Thread join a échoué");
            exit(EXIT_FAILURE);
        }
        if(tmp == 0){
            printf("\n");
            tmp++;
        }
        printf("T%i: %s", i+1, (char *) thread_result);
    }

    /* ----- affichage de la variable globale ----- */

    printf("\nV1 = %d\nV2 = %d\nV3 = %d\n", global.v1, global.v2, global.v3);

    pthread_mutex_destroy(&flag);

    exit(EXIT_SUCCESS);
}

