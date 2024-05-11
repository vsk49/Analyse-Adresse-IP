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
*  Nom du fichier :    afficherChamps.c                                       *
*                                                                             *
******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./../obj/constantes.h"
#include "./../obj/structs.h"
#include "./../obj/verificationFormat.h"
#include "./../obj/extraireChampsIP.h"

void afficherChampsIP(char* adresseIP) {
    if (estAdresseIPValide(adresseIP) == false) {
        printf("L'adresse IP est invalide.\n");
    } else {
        AdressesAAfficher champs = extraireChampsIP(adresseIP);
        printf("Adresse IP : %s\n", adresseIP);
        printf("Masque de sous-réseau : %d\n", champs.masqueSousReseau);
        printf("Classe: %d\n", champs.adresseClasse);
        printf("Type: %s\n", champs.adresseType);
        printf("Adresse réseau: %d.%d.%d.%d\n", champs.adresseReseau[0], champs.adresseReseau[1], 
            champs.adresseReseau[2], champs.adresseReseau[3]);
        printf("Adresse machine hôte: %d.%d\n", champs.adresseMachineHote[0], 
            champs.adresseMachineHote[1]);
    }
}