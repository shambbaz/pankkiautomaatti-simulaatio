#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME 50
#define MAX_PIN 10

// Funktio lukee tilitiedoston ja palauttaa saldon, jos PIN on oikea
int lue_tiedosto(char *tiedostonimi, char *kayttaja_pin, int *saldo) {
    FILE *tiedosto;
    char tiedosto_pin[MAX_PIN];

    tiedosto = fopen(tiedostonimi, "r");
    if (tiedosto == NULL) {
        printf("Tilitiedostoa ei voitu avata. Tarkista tilinumero.\n");
        return 0;
    }

    // Lue PIN ensimmaiselta rivilta
    if (fgets(tiedosto_pin, MAX_PIN, tiedosto) == NULL) {
        printf("Tilitiedostoa ei voitu lukea.\n");
        fclose(tiedosto);
        return 0;
    }

    // Poista mahdollinen rivinvaihto merkkijonosta
    tiedosto_pin[strcspn(tiedosto_pin, "\n")] = 0;

    if (strcmp(tiedosto_pin, kayttaja_pin) != 0) {
        printf("Vaarin syotetty PIN-koodi.\n");
        fclose(tiedosto);
        return 0;
    }

    // Lue saldo toiselta rivilta
    if (fscanf(tiedosto, "%d", saldo) != 1) {
        printf("Saldoa ei voitu lukea tiedostosta.\n");
        fclose(tiedosto);
        return 0;
    }

    fclose(tiedosto);
    return 1;
}

// Funktio tallentaa paivitetyn saldon tiedostoon
int paivita_saldo_tiedostoon(char *tiedostonimi, char *pin, int saldo) {
    FILE *tiedosto;

    tiedosto = fopen(tiedostonimi, "w");
    if (tiedosto == NULL) {
        printf("Tilitiedostoa ei voitu avata kirjoittamista varten.\n");
        return 0;
    }

    // Kirjoita PIN ja uusi saldo tiedostoon
    fprintf(tiedosto, "%s\n%d\n", pin, saldo);
    fclose(tiedosto);
    return 1;
}

void tarkista_saldo(int saldo) {
    printf("Tilisi saldo on: %d euroa\n", saldo);
}

int nosta_rahaa(int saldo) {
    int summa;
    printf("Syota nostettava summa (20-1000 euroa, 10 euron valein): ");
    if (scanf("%d", &summa) != 1 || summa <= 0) {
        printf("Virheellinen syote. Syota positiivinen kokonaisluku.\n");
        while (getchar() != '\n');
        return saldo;
    }

    if (summa % 10 != 0 || summa < 20 || summa > 1000) {
        printf("Virheellinen summa. Voit nostaa vain 20-1000 euroa, 10 euron valein.\n");
        return saldo;
    }

    if (summa > saldo) {
        printf("Tililla ei ole tarpeeksi katetta.\n");
    } else {
        saldo -= summa;
        printf("Nostit %d euroa. Jaljella oleva saldo: %d euroa\n", summa, saldo);
    }

    return saldo;
}

int talleta_rahaa(int saldo) {
    int summa;
    printf("Syota talletettava summa: ");
    if (scanf("%d", &summa) != 1 || summa <= 0) {
        printf("Virheellinen syote. Syota positiivinen kokonaisluku.\n");
        while (getchar() != '\n');
        return saldo;
    }

    saldo += summa;
    printf("Talletit %d euroa. Uusi saldo: %d euroa\n", summa, saldo);

    return saldo;
}

void lopeta() {
    printf("Kiitos, etta kaytit automaattia. Hyvaa paivan jatkoa!\n");
}

int valikko(int saldo) {
    int valinta;

    do {
        printf("\nValitse toiminto:\n");
        printf("1. Tarkista saldo\n");
        printf("2. Nosta rahaa\n");
        printf("3. Talleta rahaa\n");
        printf("4. Lopeta\n");
        printf("Valintasi: ");
        if (scanf("%d", &valinta) != 1) {
            printf("Virheellinen syote. Kayta vain numeroita.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (valinta) {
            case 1:
                tarkista_saldo(saldo);
                break;
            case 2:
                saldo = nosta_rahaa(saldo);
                break;
            case 3:
                saldo = talleta_rahaa(saldo);
                break;
            case 4:
                lopeta();
                break;
            default:
                printf("Virheellinen valinta. Yrita uudelleen.\n");
        }
    } while (valinta != 4);

    return saldo;
}

int main() {
    char tilinumero[MAX_FILENAME];
    char pin[MAX_PIN];
    int saldo;

    printf("Syota tilinumero: ");
    scanf("%s", tilinumero);

    // Lisaa tiedostopaate tilinumeroon
    strcat(tilinumero, ".tili");

    printf("Syota PIN-koodi: ");
    scanf("%s", pin);

    if (!lue_tiedosto(tilinumero, pin, &saldo)) {
        printf("Ohjelma paattyy virheellisen syotteen vuoksi.\n");
        return 1;
    }

    saldo = valikko(saldo);

    if (!paivita_saldo_tiedostoon(tilinumero, pin, saldo)) {
        printf("Saldoa ei voitu paivittaa tiedostoon.\n");
    }

    return 0;
}
