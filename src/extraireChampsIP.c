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
#include "./../obj/verificationFormat.h"
#include "./../obj/constantes.h"
#include "./../obj/structs.h"

// Etape 1 : Extraction de la masque de l'adresse IP
int getMasqueSousReseau(char* adresseIP) {
    char* adresse = strtok(adresseIP, "/");
    char* masque = strtok(NULL, "/");
    return sscanf(masque, "%d", &masque);
}

// Etape 2 : Extraction de la classe de l'adresse IP
char getAdresseClasse(char* adresseIP) {
    char* premierOctetStr = strtok(adresseIP, ".");
    int premierOctet;
    int valeurPremierOctet = sscanf(premierOctetStr, "%d", &premierOctet);
    if (valeurPremierOctet != 1) {
        printf("%d", false);
    } else {
        if (premierOctet >= 0 && premierOctet <= 127) {
            return 'A';
        } else if (premierOctet >= 128 && premierOctet <= 191) {
            return 'B';
        } else if (premierOctet >= 192 && premierOctet <= 223) {
            return 'C';
        } else if (premierOctet >= 224 && premierOctet <= 239) {
            return 'D';
        } else if (premierOctet >= 240 && premierOctet <= 255) {
            return 'E';
        } 
    }
}

// Etape 3 : Extraction du type d'adresse
char* getAdresseType(char* adresseIP) {
    char* premierOctet = strtok(adresseIP, ".");
    int octet = sscanf(premierOctet, "%d", &octet);
    char* typeAdresse = malloc(10 * sizeof(char));
    if (octet == 10 || (octet == 172 && (octet >= 16 && octet <= 31)) || (octet == 192 && octet == 168)) {
        strcpy(typeAdresse, "Private");
    } else if (octet == 255) {
        strcpy(typeAdresse, "Broadcast");
    } else if (octet == 0) {
        strcpy(typeAdresse, "Network");
    } else if (octet >= 1 && octet <= 223) {
        strcpy(typeAdresse, "Unicast");
    } else {
        strcpy(typeAdresse, "Public");
    }
    return typeAdresse;
}

// Etape 4 : Extraction de l'adresse de reseau
int* getAdresseReseau(char* adresseIP) {
    char* adresseReseau = strtok(adresseIP, ".");
    int* octetsReseau = malloc(4 * sizeof(int));
    int i = 0;
    while (adresseReseau != NULL && i < getMasqueSousReseau(adresseIP) / 4) {
        int octet = sscanf(adresseReseau, "%d", &octet);
        octetsReseau[i] = octet;
        adresseReseau = strtok(NULL, ".");
        i++;
    }
    // Remplir les octets restants avec des zeros
    while (i < 4) {
        octetsReseau[i] = 0;
        i++;
    }
    return octetsReseau;
}

int* getAdresseMachineHote(char* adresseIP) {
    // Etape 5 : Extraction de l'adresse de l'hote
        char* premierOctetStr = strtok(adresseIP, ".");
        int* octetsMachineHote = malloc(4 * sizeof(int));
        int i = 0;
        int j = 0;
        while (premierOctetStr != NULL) {
            int octet;
            sscanf(premierOctetStr, "%d", &octet);
            // Si l'octet est superieur ou egal au nombre d'octets necessaires 
            // pour l'adresse de reseau
            if (i >= getMasqueSousReseau(adresseIP) / 4) {
                octetsMachineHote[j] = octet;
                j++;
            }
            premierOctetStr = strtok(NULL, ".");
            i++;
        }
        // Remplir les octets restants avec des zeros
        while (j < 4) {
            octetsMachineHote[j] = 0;
            j++;
        }
        return octetsMachineHote;
}

AdressesAAfficher extraireChampsIP(char* adresseIP) {
    if (!estAdresseIPValide(adresseIP)) {
        printf("%d", false);
    } else {
        // Declaration de la structure
        AdressesAAfficher information;
        // Extraction des champs
        information.masqueSousReseau = getMasqueSousReseau(adresseIP);
        information.adresseClasse = getAdresseClasse(adresseIP);
        // Allocation de memoire pour le type d'adresse
        strcpy(information.adresseType, getAdresseType(adresseIP));  

        int* tempReseau = getAdresseReseau(adresseIP);
        // Copie des valeurs de l'adresse de reseau
        memcpy(information.adresseReseau, tempReseau, NB_BYTES * sizeof(int)); 

        int* tempHote = getAdresseMachineHote(adresseIP);
        // Copie des valeurs de l'adresse de l'hote
        memcpy(information.adresseMachineHote, tempHote, NB_BYTES * sizeof(int));

        return information;
    }
}