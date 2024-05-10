#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "constantes.h"
#include "structs.h"
#include "verificationFormat/verificationFormat.h"
#include "extractionChamps/extraireChampsIP.h"
#include "affichageChamps/afficherChamps.h"

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