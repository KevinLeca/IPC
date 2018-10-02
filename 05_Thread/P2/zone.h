/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   zone.h
 * Author: kleca
 *
 * Created on 2 octobre 2018, 09:10
 */

#ifndef ZONE_H
#define ZONE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>
#include <sys/ipc.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/msg.h>
    
#define CLE 5678
    
    struct donnees {
        long type;
        char texte[9];
    };


#ifdef __cplusplus
}
#endif

#endif /* ZONE_H */

