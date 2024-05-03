/******************************************************************************
*  ASR => 4R2.04                                                              *
*******************************************************************************
*                                                                             *
*  N° de Sujet :  2                                                           *
*                                                                             *
*******************************************************************************
*                                                                             *
*  Intitulé :    Analyse Adresse IP                                           *
*                                                                             *
*******************************************************************************
*                                                                             *
*  Nom-prénom1 :     Koh-Virgil Shaun                                         *
*                                                                             *
*  Nom-prénom2 :     Lfarh-Mouataz                                            *
*                                                                             *
*******************************************************************************
*                                                                             *
*  Nom du fichier :    verificationFormat.c                                   *
*                                                                             *
******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "verificationFormat.h"
#include "./../constantes.h"
#include "./../structs.h"

boolean estAdresseIPValide(char* adresseIP) {
    char adresseCopy[LONGUEUR_MAX]; // Buffer to store a copy of the input address
    strcpy(adresseCopy, adresseIP); // Copy the input to a local buffer

    // Split the IP address and subnet mask
    char *adresseIP = strtok(adresseCopy, "/");
    char *subnetMaskStr = strtok(NULL, "/");

    // Check if either is NULL which means invalid format
    if (!adresseIP || !subnetMaskStr) {
        return false;
    }

    // Validate subnet mask
    int subnetMask = atoi(subnetMaskStr);
    if (subnetMask < 0 || subnetMask > 32) {
        return false;
    }

    // Validate IP address
    char *token = strtok(adresseIP, ".");
    int segments = 0;
    while (token != NULL) {
        int num = atoi(token);
        if (num < 0 || num > 255) {
            return 0;
        }
        segments++;
        token = strtok(NULL, ".");
    }

    // There must be exactly 4 segments in a valid IP address
    if (segments != 4) {
        return false;
    }

    return true;
}