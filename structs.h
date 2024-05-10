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
*  Nom du fichier :    structs.h                                              *
*                                                                             *
******************************************************************************/

#ifndef _STRUCTS

    #define _STRUCTS
    #include "constantes.h"
    typedef struct {
        int masqueSousReseau;
        char adresseClasse;
        char adresseType[LONGUEUR_MAX];
        int adresseReseau[NB_BYTES];
        int adresseMachineHote[NB_BYTES];
    } AdressesAAfficher;

#endif