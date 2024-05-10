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
*  Nom du fichier :    extraireChampsIP.c                                     *
*                                                                             *
******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./../verificationFormat/verificationFormat.h"
#include "./../constantes.h"
#include "./../structs.h"

AdressesAAfficher extraireChampsIP(char* adresseIP) {
    if (!estAdresseIPValide(adresseIP)) {
        printf(false);
    } else {
        // Declaration de la structure
        AdressesAAfficher information;

        // Etape 1 : Extraction de la masque de l'adresse IP
        char* adresse = strtok(adresseIP, "/");
        char* masque = strtok(NULL, "/");
        information.masqueSousReseau = sscanf(masque, "%d", &information.masqueSousReseau);

        // Etape 2 : Extraction de la classe de l'adresse IP
        int premierOctet = strtok(adresse, ".");
        int valeurPremierOctet = sscanf(premierOctet, "%d", &premierOctet);
        if (valeurPremierOctet != 1) {
            printf(false);
        } else {
            if (premierOctet >= 0 && premierOctet <= 127) {
                information.adresseClasse = 'A';
            } else if (premierOctet >= 128 && premierOctet <= 191) {
                information.adresseClasse = 'B';
            } else if (premierOctet >= 192 && premierOctet <= 223) {
                information.adresseClasse = 'C';
            } else if (premierOctet >= 224 && premierOctet <= 239) {
                information.adresseClasse = 'D';
            } else if (premierOctet >= 240 && premierOctet <= 255) {
                information.adresseClasse = 'E';
            } 
        }

        // Etape 3 : Extraction de l'adresse de reseau
        char* adresseReseau = strtok(adresse, ".");
        int i = 0;
        while (adresseReseau != NULL && i < information.masqueSousReseau / 4) {
            int octet = sscanf(adresseReseau, "%d", &octet);
            information.adresseReseau[i] = octet;
            adresseReseau = strtok(NULL, ".");
            i++;
        }
        // Remplir les octets restants avec des zeros
        while (i < 4) {
            information.adresseReseau[i] = 0;
            i++;
        }

        // Etape 4 : Extraction de l'adresse de l'hote
        char* adresseHote = strtok(adresse, ".");
        int i = 0;
        int j = 0;
        while (adresseHote != NULL) {
            int octet;
            sscanf(adresseHote, "%d", &octet);
            // Si l'octet est superieur ou egal au nombre d'octets necessaires 
            // pour l'adresse de reseau
            if (i >= information.masqueSousReseau / 4) {
                information.adresseMachineHote[j] = octet;
                j++;
            }
            adresseHote = strtok(NULL, ".");
            i++;
        }

        // Remplir les octets restants avec des zeros
        while (j < 4) {
            information.adresseMachineHote[j] = 0;
            j++;
        }

        // Etape 5 : Extraction du type d'adresse
        char* premierOctet = strtok(adresse, ".");
        int octet = sscanf(premierOctet, "%d", &octet);
        if (octet == 10 || (octet == 172 && (octet >= 16 && octet <= 31)) || (octet == 192 && octet == 168)) {
            strcpy(information.adresseType, "Private");
        } else if (octet == 255) {
            strcpy(information.adresseType, "Broadcast");
        } else if (octet == 0) {
            strcpy(information.adresseType, "Network");
        } else if (octet >= 1 && octet <= 223) {
            strcpy(information.adresseType, "Unicast");
        } else {
            strcpy(information.adresseType, "Public");
        }
    
        return information;
    }

}