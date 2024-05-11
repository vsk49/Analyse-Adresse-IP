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
*  Nom du fichier :    main.c                                                 *
*                                                                             *
******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./../obj/constantes.h"
#include "./../obj/structs.h"
#include "./../obj/verificationFormat.h"
#include "./../obj/extraireChampsIP.h"
#include "./../obj/afficherChamps.h"

int main(void) {
    char adresseIP[LONGUEUR_MAX];
    printf("Entrez une adresse IP : ");
    scanf("%s", adresseIP);
    if (estAdresseIPValide(adresseIP) == false) {
        printf("L'adresse IP est invalide.\n");
    } else {
        extraireChampsIP(adresseIP);
        afficherChampsIP(adresseIP);
    }
    return 0;
}