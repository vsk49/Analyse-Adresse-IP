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
#include "verificationFormat.h"
#include "./../constantes.h"
#include "./../structs.h"

void extraireChampsIP(char* adresseIP) {
    if (!estAdresseIPValide(adresseIP)) {
        printf("\p", ADRESSE_INVALIDE);
    } else {
        NULL;
    }

}