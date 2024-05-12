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
*  Nom du fichier :    extraireChampsIP.h                                     *
*                                                                             *
******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "verificationFormat.h"
#include "constantes.h"
#include "structs.h"

int getMasqueSousReseau(char* adresseIP);
char getAdresseClasse(char* adresseIP);
char* getAdresseType(char* adresseIP);
int* getAdresseReseau(char* adresseIP);
int* getAdresseMachineHote(char* adresseIP);
AdressesAAfficher extraireChampsIP(char* adresseIP);