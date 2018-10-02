/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: kleca
 * Questions 1 et 2 du TD01 Threads
 * Created on 28 septembre 2018, 08:04
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/syscall.h>

/* ----- Ma structure ----- */
typedef struct {
    int v1;
    int v2;
    int v3;
} maStruct;
/* ----------------------- */

maStruct global; // Definition d'une variable global de type struct

void *tache1(void *p_data) {
    int val = *((int *) p_data);
    int tid;

    global.v1 = val;
    tid = syscall(SYS_gettid);
    printf("T1: TID = %d v1 = %d,\n", tid, global.v1);
    printf("T1: argument = %d\n", val);
    sleep(3);

    pthread_exit((void *) "T1 tâche terminée \n");
}

void *tache2(void *p_data) {

    int val = *((int *) p_data);
    int tid;

    global.v2 = val;
    tid = syscall(SYS_gettid);
    printf("T2: TID = %d v2 = %d,\n", tid, global.v2);
    printf("T2: argument = %d\n", val);
    sleep(3);
    pthread_exit((void *) "T2 tâche terminée \n");
}

void *tache3(void *p_data) {

    int val = *((int *) p_data);
    int tid;


    global.v3 = val;
    tid = syscall(SYS_gettid);
    printf("T3: TID = %d v3 = %d,\n", tid, global.v3);
    printf("T3: argument = %d\n", val);
    sleep(2);

    pthread_exit((void *) "T3 tâche terminée \n");
}

int main() {
    int i, res;
    int tmp = 0; // Pour un affichage plus propre
    pthread_t T[3];
    void *thread_result;

    int a = 10;
    int b = 20;
    int c = 30;



    /* ----- Création des threads ----- */

    // Thread T1
    res = pthread_create(&T[0], NULL, tache1, (void *) &a);
    if (res != 0) {
        perror("Error creation Thread");
        exit(EXIT_FAILURE);
    }

    // Thread T2
    res = pthread_create(&T[1], NULL, tache2, (void *) &b);
    if (res != 0) {
        perror("Error creation Thread");
        exit(EXIT_FAILURE);
    }

    // Thread T3
    res = pthread_create(&T[2], NULL, tache3, (void *) &c);
    if (res != 0) {
        perror("Error creation Thread");
        exit(EXIT_FAILURE);
    }

    /* ----- attente de la fin des trois threads ----- */

    for (i = 0; i < 3; i++) {
        res = pthread_join(T[i], &thread_result); // T[i] pour attendre tout mes thread 
        // Soit T[0], T[1], T[2] pour T1, T2 et T3
        if (res != 0) {
            perror(" Error Thread join");
            exit(EXIT_FAILURE);
        }
        if (tmp == 0) {
            printf("\n");
            tmp++;
        }
        printf("OK : %s", (char *) thread_result);
    }

    printf("\nV1 = %d\nV2 = %d\nV3 = %d\n", global.v1, global.v2, global.v3);

    exit(EXIT_SUCCESS);
}