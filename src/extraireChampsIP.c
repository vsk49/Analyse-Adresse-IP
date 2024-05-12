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
    char* slash = strchr(adresseIP, '/');
    if (!slash) {
        return -1;
    }
    int masqueValue;
    if (sscanf(slash + 1, "%d", &masqueValue) != 1) {
        return -1;
    }
    return masqueValue;
}

// Etape 2 : Extraction de la classe de l'adresse IP
char getAdresseClasse(char* adresseIP) {
    char* premierOctetStr = strtok(adresseIP, ".");
    int premierOctet;
    int valeurPremierOctet = sscanf(premierOctetStr, "%d", &premierOctet);
    if (valeurPremierOctet != 1) {
        return 'X';
    } else {
        if (premierOctet >= 0 && premierOctet <= 127) {
            return 'A';
        } else if (premierOctet >= 128 && premierOctet <= 191) {
            return 'B';
        } else if (premierOctet >= 192 && premierOctet <= 223) {
            return 'C';
        } else if (premierOctet >= 224 && premierOctet <= 239) {
            return 'D';
        } else {
            return 'E';
        } 
    }
}

// Etape 3 : Extraction du type d'adresse
char* getAdresseType(char* adresseIP) {
    char adresseCopy[LONGUEUR_MAX]; 
    strcpy(adresseCopy, adresseIP);

    char* premierOctetStr = strtok(adresseCopy, ".");
    int premierOctet;
    sscanf(premierOctetStr, "%d", &premierOctet);

    char* deuxiemeOctetStr = strtok(NULL, ".");
    int deuxiemeOctet = 0;
    if (deuxiemeOctetStr) {
        sscanf(deuxiemeOctetStr, "%d", &deuxiemeOctet);
    }

    char* typeAdresse = malloc(10 * sizeof(char));
    if (premierOctet == 10 || (premierOctet == 172 && (deuxiemeOctet >= 16 && deuxiemeOctet <= 31)) || (premierOctet == 192 && deuxiemeOctet == 168)) {
        strcpy(typeAdresse, "Private");
    } else if (premierOctet == 255) {
        strcpy(typeAdresse, "Broadcast");
    } else if (premierOctet == 0) {
        strcpy(typeAdresse, "Network");
    } else if (premierOctet >= 1 && premierOctet <= 223) {
        strcpy(typeAdresse, "Unicast");
    } else {
        strcpy(typeAdresse, "Public");
    }
    return typeAdresse;
}

// Etape 4 : Extraction de l'adresse de reseau
int* getAdresseReseau(char* adresseIP) {
    char adresseCopy[LONGUEUR_MAX];
    strcpy(adresseCopy, adresseIP);
    char* slashPosition = strchr(adresseCopy, '/');
    if (slashPosition) {
        *slashPosition = '\0';  // Replace the slash with a null character
    }

    int* octetsReseau = malloc(4 * sizeof(int));
    int i = 0;
    char* dotPosition = strchr(adresseCopy, '.');
    while (dotPosition != NULL && i < 4) {
        *dotPosition = '\0';  // Replace the dot with a null character
        int octet;
        sscanf(adresseCopy, "%d", &octet);
        octetsReseau[i] = octet;
        strcpy(adresseCopy, dotPosition + 1);  // Copy the rest of the string
        dotPosition = strchr(adresseCopy, '.');
        i++;
    }
    if (i < 4) {
        int octet;
        sscanf(adresseCopy, "%d", &octet);
        octetsReseau[i] = octet;
        i++;
    }
    // Fill the remaining octets with zeros
    while (i < 4) {
        octetsReseau[i] = 0;
        i++;
    }

    int masque = getMasqueSousReseau(adresseIP);
    if (masque == -1) {
        free(octetsReseau);
        return NULL;
    }

    int masqueOctets[4] = {0, 0, 0, 0};
    for (i = 0; i < masque / 8; i++) {
        masqueOctets[i] = 255;
    }
    if (masque % 8 != 0) {
        masqueOctets[masque / 8] = 255 - ((1 << (8 - masque % 8)) - 1);
    }

    for (i = 0; i < 4; i++) {
        octetsReseau[i] = octetsReseau[i] & masqueOctets[i];
    }

    return octetsReseau;
}

// Etape 5 : Extraction de l'adresse de l'hote
int* getAdresseMachineHote(char* adresseIP) {
    int masque = getMasqueSousReseau(adresseIP);
    int masqueOctets[4] = {0, 0, 0, 0};
    for (int i = 0; i < masque / 8; i++) {
        masqueOctets[i] = 255;
    }
    if (masque % 8 != 0) {
        masqueOctets[masque / 8] = 255 << (8 - masque % 8);
    }

    char adresseCopy[30];
    strcpy(adresseCopy, adresseIP);
    char* slashPosition = strchr(adresseCopy, '/');
    if (slashPosition) {
        *slashPosition = '\0';  // Replace the slash with a null character
    }

    int* octetsHote = malloc(4 * sizeof(int));
    int i = 0;
    char* dotPosition = strchr(adresseCopy, '.');
    while (dotPosition != NULL && i < 4) {
        *dotPosition = '\0';  // Replace the dot with a null character
        int octet;
        sscanf(adresseCopy, "%d", &octet);
        octetsHote[i] = octet;
        strcpy(adresseCopy, dotPosition + 1);  // Copy the rest of the string
        dotPosition = strchr(adresseCopy, '.');
        i++;
    }
    if (i < 4) {
        int octet;
        sscanf(adresseCopy, "%d", &octet);
        octetsHote[i] = octet;
        i++;
    }
    // Fill the remaining octets with zeros
    while (i < 4) {
        octetsHote[i] = 0;
        i++;
    }

    for (i = 0; i < 4; i++) {
        octetsHote[i] = octetsHote[i] & ~masqueOctets[i];
    }

    return octetsHote;
}

AdressesAAfficher extraireChampsIP(char* adresseIP) {
    // Declaration de la structure
    AdressesAAfficher information;

    if (!estAdresseIPValide(adresseIP)) {
        printf("%d", false);
    } else {
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
    }
    return information;
}

int main(void) {
    char adresseIP[LONGUEUR_MAX];
    printf("Entrez une adresse IP : ");
    scanf("%s", adresseIP);
    AdressesAAfficher champs = extraireChampsIP(adresseIP);
    printf("Masque de sous-réseau : %d\n", champs.masqueSousReseau);
    printf("Classe: %c\n", champs.adresseClasse);
    printf("Type: %s\n", champs.adresseType);
    printf("Adresse réseau: %d.%d.%d.%d\n", champs.adresseReseau[0], champs.adresseReseau[1], 
        champs.adresseReseau[2], champs.adresseReseau[3]);
    printf("Adresse machine hôte: %d.%d.%d\n", champs.adresseMachineHote[0], 
        champs.adresseMachineHote[1], champs.adresseMachineHote[2]);
    return 0;
}