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
    // Pour eviter la possibilite de modifier l'adresse originale
    char adresseCopy[LONGUEUR_MAX]; 
    strcpy(adresseCopy, adresseIP);

    // Separer l'adresse IP et le masque de sous-reseau
    char *adresseIPToken = strtok(adresseCopy, "/");
    char *subnetMaskStr = strtok(NULL, "/");

    // Si le masque de sous-reseau n'est pas present, retournez faux
    if (!adresseIPToken || !subnetMaskStr) {
        return false;
    }

    // Valider le masque de sous-reseau
    int subnetMask = sscanf(subnetMaskStr, "%d", &subnetMask);
    if (subnetMask != 1 || subnetMask < 0 || subnetMask > 32) {
        return false;
    }

    // Valider l'adresse IP
    char *token = strtok(adresseIPToken, ".");
    int segments = 0;
    while (token != NULL) {
        int octet = sscanf(token, "%d", &octet);
        if (octet != 1 || octet < 0 || octet > 255) {
            return false;
        }
        segments++;
        token = strtok(NULL, ".");
    }

    // L'adresse IP doit avoir 4 segments
    if (segments != 4) {
        return false;
    }

    return true;
}

/*
int main(void) {
    char adresseIP[LONGUEUR_MAX];
    printf("Entrez une adresse IP: ");
    scanf("%s", adresseIP);

    if (estAdresseIPValide(adresseIP)) {
        printf("L'adresse IP est valide.\n");
    } else {
        printf("L'adresse IP n'est pas valide.\n");
    }

    return 0;
}
*/