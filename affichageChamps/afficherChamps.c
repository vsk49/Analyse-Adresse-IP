#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./../constantes.h"
#include "./../structs.h"
#include "./../verificationFormat/verificationFormat.h"
#include "./../extractionChamps/extraireChampsIP.h"

void afficherChampsIP(char* adresseIP) {
    if (estAdresseIPValide(adresseIP) == false) {
        printf("L'adresse IP est invalide.\n");
    } else {
        AdressesAAfficher champs = extraireChampsIP(adresseIP);
        printf("Adresse IP : %s\n", adresseIP);
        printf("Masque de sous-réseau : %d\n", champs.masqueSousReseau);
        printf("Classe: %s\n", champs.adresseClasse);
        printf("Type: %s\n", champs.adresseType);
        printf("Adresse réseau: %d.%d.%d.%d\n", champs.adresseReseau[0], champs.adresseReseau[1], 
            champs.adresseReseau[2], champs.adresseReseau[3]);
        printf("Adresse machine hôte: %d.%d\n", champs.adresseMachineHote[0], 
            champs.adresseMachineHote[1]);
    }
}